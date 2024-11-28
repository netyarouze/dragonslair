/*

Adapted from Vince Diesi's source code found at "SAMPLE\SCEE\CD\MOVIE2" inside the developer's CD.

Several changes have been made for Dragon's Lair.

*/

/************************************************************
 *                                                          *
 *                        main.c                            *
 *                                                          *
 *                                                          *
 *               Vince Diesi     13/02/97                   *
 *                                                          *
 *   Copyright (C) 1997 Sony Computer Entertainment Inc.    *
 *                  All Rights Reserved                     *
 *                                                          *
 ***********************************************************/
/* --------------------------------------------------------------------------
 * - Description:
 * - ------------
 * - General purpose movie player.
 * -
 * - Refer to ReadMe.txt for more info.
 * ---------------------------------------------------------------------------
 */ 

#include <sys/types.h>
#include <libsn.h>
#include <r3000.h>
#include <asm.h>
#include <kernel.h>
#include <libetc.h>
#include <libgte.h>
#include <libgpu.h>
#include <libcd.h>
#include <libspu.h>
#include <libpress.h>
#include <libsnd.h>

// Headers required for Dragon's Lair.

#define MOVIE_C
#include "files.h"
#include "movie.h"
#include "main.h"
#include "movies.h"
#include "game.h"
#include "assets.h"

/* ---------------------------------------------------------------------------
 * - CONSTANTS
 * ---------------------------------------------------------------------------
 */

// Define for timing and testing functions.
//#define TESTING

// Define for extra debug info.
//#define DEBUG


// Maximum number of retries.
#define MAX_RETRY				5

// Form1 sector size in bytes.
#define FORM1_SIZE				2048 

// Ring buffer size in sectors.
#define RING_SIZE				64

// Maximum possible VLC buffer size (bytes) = 128K + (Header) = 129K.
#define MAX_VLCBUF_SIZE			132096

// Slice width in pixels.
#define SLICE_WIDTH				16

// Words/Pixel for 24-bit and 16-bit modes.
#define PPW24					3 / 2
#define PPW16					1    

// DCT modes for 24-bit and 16-bit (STP = 1) streaming.
#define DCT_MODE24				3
#define DCT_MODE16				2

#define bound(val, n)			((((val) - 1) / (n) + 1) * (n))
#define bound16PPW(val, ppw)	(bound((val), 16 * ppw))
#define bound16(val)			(bound((val), 16))

// Speed of volume fade.
#define FADE_VOL_SPD			8

// RunLevel header size in bytes.
#define RL_HEADER_SIZE			1024

/* ---------------------------------------------------------------------------
 * - DATA TYPE AND STRUCTURE DECLARATIONS
 * ---------------------------------------------------------------------------
 */

// Moved to MOVIE.H

/* ---------------------------------------------------------------------------
 * - GLOBAL DEFINITIONS 
 * ---------------------------------------------------------------------------
 */

#ifdef TESTING
static int		t1, t2;							// Timers.

static DRAWENV	draw[2];						// DrawEnvs for FntPrint.
#endif

// Needed for printing text over movies.
#ifndef TESTING
static DRAWENV	draw[2];						// DrawEnvs for FntPrint.
#endif

#if defined(TESTING)||defined(FIND_VLCBUF)
static short	firstFrame = 1,					// Frame skipping check.
				numSkipped = 0,
				prevFrameNum = 0;			
#endif


#ifdef FIND_VLCBUF
static u_short	maxRunLevel = 0;
#endif

u_long myheapbase = (u_long)REUSABLE_ADDRESS;
// Default heapbase address overwrites our assets.
//extern u_long	__heapbase;						// LibSN memory vars.
extern u_long	__heapsize;
extern u_long	_ramsize;
extern u_long	_stacksize;

DecEnv	dec;							// Streaming Env.

static u_long	oldHeapbase;  					// Heapbase before PlayStream.

static SndVolume oldVolume;						// Old ADPCM volume.

// This keeps track of last double buffer index used by movie player to avoid blank frames when switching movies.
short LastDB = 0;


/* ---------------------------------------------------------------------------
 * - PRIVATE FUNCTION PROTOTYPES
 * ---------------------------------------------------------------------------
 */

static void StrDecDCToutCB(void);
static void StrInit(StrInfo *str, MOVIE_FILE *StrFile);
static void StrEnd(void);
//static void StrClearVRAM(void);
void StrClearVRAM(void);
static short StrKickCD(CdlLOC *loc);
static u_long *StrGetNextFrame(void);
static void StrVLCFrame(u_long *frame);
static void	StrDrawDecodeSync(void);
//static short StrFadeOutVol(short *fadeVol);
static long GetDCToutSize(void);
static u_short ScalePPW(u_short n);
static u_short GetDCT_MODE(void);

#ifdef FIND_VLCBUF
static void PrintVLCBufSize(void); 
#endif

static u_long AllocMem(u_long size);


/* ---------------------------------------------------------------------------
 * - FUNCTION DEFINITIONS
 * ---------------------------------------------------------------------------
 */

// Force pause. On real hardware one retry is not enough.
int PauseCD(void)
{
short PauseRetry = 0;
CdSync(0, NULL);
while ( !CdControlB(CdlPause, 0, 0) )
	{
	CdSync(0, NULL);
	PauseRetry++;
	if (PauseRetry > MAX_RETRY)
		{
		return 0; // Error trying to pause.
		}
	}

return 1; // Pause succesful.
}

// Callback function for StSetStream. Used as a workaround for playing until the very last frame.

void CheckLastFrame()
{
if ( ( STRCurrentFrame >= dec.endFrame-2 ) || ( STRPreviousFrame > STRCurrentFrame ) )
//if ( ( STRCurrentFrame >= dec.endFrame) || ( STRPreviousFrame > STRCurrentFrame ) )
	{
//	printf ("\nLast frame.");
//	CdControlB(CdlPause, 0, 0);
	if ( !PauseCD() )
		{
		Prev_Game_Status = Game_Status;
		Game_Status = STATUS_ERRORSCREEN;
		SaveError(PLAY_ERROR, __FILE__, __FUNCTION__, __LINE__);
		}
	StopPlayingMovie = 1;
	}
}


short PlayStream(MOVIE_FILE *str, int StartingFrame) {


/* - Type:	PUBLIC
 * -
 * - Param:	str = (In) Stream info.
 * -		keyHandler = (In) Read controller function (Returns non-zero if exit).
 * -
 * - Ret:	PLAYSTR_ERROR = Error.
 * -		PLAYSTR_END = End of stream exit.
 * -		PLAYSTR_USER = User exit.
 * -
 * - Usage:	Play a stream.
 */


	CdlFILE		fp;

	u_long		*frame;

	short		frameRetry = 0;
	short		strQuit = 0;
//	short		fadeVol = 0;
//	short TotalFrames = ( str->Frames+1 - StartingFrame ) + 1;


	StopPlayingMovie = 0;
	STRCurrentFrame = 0;
	STRPreviousFrame = 0;

	StrInit(&StrInfoBase, str);

// Skip to desired frame when a checkpoint has been reached. Play from first frame when StartingFrame = 0.

	if ( !CdControl(CdlSetloc, (u_char *)( CdIntToPos(str->Position + ( StartingFrame * SECTORS_PER_FRAME ), &fp.pos) ), 0) )
		{
		StrEnd();
		Prev_Game_Status = Game_Status;
		Game_Status = STATUS_ERRORSCREEN;
		SaveError(PLAY_ERROR, __FILE__, __FUNCTION__, __LINE__);

		return PLAYSTR_ERROR;
		}
//------------


	if (!StrKickCD(&fp.pos)) {;
#ifdef DEBUG
		printf("ERROR: MOVIE -- Couldn't start the CD!!\n");
#endif
		StrEnd();
		Prev_Game_Status = Game_Status;
		Game_Status = STATUS_ERRORSCREEN;
		SaveError(PLAY_ERROR, __FILE__, __FUNCTION__, __LINE__);

		return PLAYSTR_ERROR;
	}


	while (!(frame = StrGetNextFrame())) {		// If we can't get frame exit!
		if (++frameRetry == MAX_RETRY) {
#ifdef DEBUG
			printf("ERROR: MOVIE -- Couldn't get first frame!!\n");
#endif
			StrEnd();
			Prev_Game_Status = Game_Status;
			Game_Status = STATUS_ERRORSCREEN;
			SaveError(PLAY_ERROR, __FILE__, __FUNCTION__, __LINE__);

			return PLAYSTR_ERROR;
		}
	}
	

	frameRetry = 0;
	StrVLCFrame(frame);


	while (!StopPlayingMovie) {

// Play next frame if not in pause mode.

	if ( !(Player1.Pause) )
		{
		DecDCTin(dec.vlcBuffer[dec.vlcId], GetDCT_MODE());
		DecDCTout(dec.imageBuffer[dec.imageId], GetDCToutSize());

		if (!(frame = StrGetNextFrame())) {

			if (++frameRetry == MAX_RETRY)
				{
				strQuit = PLAYSTR_ERROR;
				Prev_Game_Status = Game_Status;
				Game_Status = STATUS_ERRORSCREEN;
				SaveError(PLAY_ERROR, __FILE__, __FUNCTION__, __LINE__);

				StopPlayingMovie = 1;
				}
			
		} else {
			frameRetry = 0;
			}

		} // End if Player1.Pause


#ifdef TESTING
		t2 = VSync(1);					// Time VLC.
		StrVLCFrame(frame);
		t2 = VSync(1) - t2;
#else 
		if ( !(Player1.Pause) )
			{
			StrVLCFrame(frame);
			}
#endif



// Dragon's Lair interactions during movie playback.
		
		if ( Game_Status == STATUS_DEBUGMENU ) // For testing movies.
			{
			Interactions_DebugMenu();
			}
		else if ( Game_Status == STATUS_WATCHMOVIES ) // Hidden option for watching movies.
			{
			Interactions_WatchMovies();
			}
		else // Actual gameplay.
			{
			switch(str->Type)
				{
				case MOVIE_INTRO:
					Interactions_Intro();
				break;

				case MOVIE_STAGE:
					Interactions_Gameplay();
				break;

				case MOVIE_DEATH:
				case MOVIE_DIRK:
				case MOVIE_ALT_EXIT:
					Interactions_Additional_Movie();
				break;

				default: // Error.
				printf("\nError in %s, %s, %d", __FILE__, __FUNCTION__ , __LINE__);
				PauseCD();
				StopPlayingMovie = YES;
				Prev_Game_Status = Game_Status;
				Game_Status = STATUS_ERRORSCREEN;
				SaveError(PLAY_ERROR, __FILE__, __FUNCTION__, __LINE__);

				}
			}

if ( !(Player1.Pause) )
	{
	StrDrawDecodeSync();
	}

else if (!StopPlayingMovie)
	{
	dec.rectId ^= 1;
	}

#ifdef TESTING
		DrawSync(0);
		FntPrint("\nVLC Time = %d\n", t2);
		FntPrint("Total Time = %d\n", VSync(1) - t1);	// Timing.
		FntFlush(-1);
#endif

		DrawSync(0);
		VSync(0);


#ifdef TESTING
		t1 = VSync(1);									// Start timer.
#endif


		PutDispEnv(&dec.disp[dec.rectId]);


		PutDrawEnv(&draw[dec.rectId]);					// Put DrawEnv for FntPrint.

// Pad input control for Dragon's Lair.

		CheckButtons();

	}

// Clear vram in 24bit mode.
if ( dec.is24Bit && ( str->Type == MOVIE_DEATH && Player1.Lives == 1 ) )
	{
	StrClearVRAM();
	}

	StrEnd();


	if (dec.rewindSwitch)								// Check for end of stream exit.
		strQuit =  PLAYSTR_END;


#ifdef DEBUG	
	if (strQuit == PLAYSTR_ERROR) 
		printf("ERROR: MOVIE -- Couldn't get frame from ring buffer!!\n");
#endif


#ifdef FIND_VLCBUF
	// If stream played completely print the maximum VLC buffer size.
	if (strQuit == PLAYSTR_END)
		PrintVLCBufSize(); 
#endif

// Save last double buffer index for next movie.
LastDB = dec.rectId;

	return strQuit;
}

/* ------------------------------------------------------------------------ */

static void StrDecDCToutCB(void) {


/* - Type:	CALLBACK
 * -
 * - Usage:	Receives decoded image data from the MDEC and loads it to VRAM.
 */


	// In 24bit mode call StCdInterrupt() manually.
	if (dec.is24Bit) {

		extern StCdIntrFlag;

		if(StCdIntrFlag) {
			StCdInterrupt();
			StCdIntrFlag = 0;
		}
	}

	LoadImage(&dec.slice, dec.imageBuffer[dec.imageId]);
	dec.imageId ^= 1;
	dec.slice.x += dec.slice.w;

	if (dec.slice.x < (dec.rect[dec.rectId].x + dec.rect[dec.rectId].w)) {

		DecDCTout(dec.imageBuffer[dec.imageId], GetDCToutSize());

	} else {

		dec.frameDone = 1;
	}
}

/* ------------------------------------------------------------------------ */

//static void StrInit(StrInfo *str, MOVIE_FILE *StrFile, int StartingFrame) {
static void StrInit(StrInfo *str, MOVIE_FILE *StrFile) {


/* - Type:	PRIVATE
 * -
 * - Param:	str = (In) = Stream Info.
 * -
 * - Usage: Init internal vars, the MDEC and allocate the buffers.
 */


	short	x, y, w, h;
	short	scrWidth;
	u_long	*ringBuf;
	u_long	vlcBufSize,
			imageBufSize;	


	oldHeapbase = myheapbase;


	x = str->x;
#ifdef NTSC
	y = str->y;
#else
	y = 8;
#endif
	w = str->width;
	h = str->height;
	scrWidth = str->scrWidth;


#ifdef TESTING
	// Init frame skipping checks.
	firstFrame = 1;
	numSkipped = 0;
	prevFrameNum = 0;			

	// Init DrawEnvs for FntPrint.
	SetDefDrawEnv(&draw[0], 0,   0,       scrWidth, FRAME_Y);
	SetDefDrawEnv(&draw[1], 0,   FRAME_Y, scrWidth, FRAME_Y);
	setRGB0(&draw[0], 0, 0, 0);
	setRGB0(&draw[1], 0, 0, 0);
	draw[0].isbg = draw[1].isbg = 1;
#endif

// Needed for printing text over movies.
#ifndef TESTING
	// Init DrawEnvs for FntPrint.
	SetDefDrawEnv(&draw[0], 0,   0,       scrWidth, FRAME_Y);
	SetDefDrawEnv(&draw[1], 0,   FRAME_Y, scrWidth, FRAME_Y);
	setRGB0(&draw[0], 0, 0, 0);
	setRGB0(&draw[1], 0, 0, 0);
	draw[0].isbg = draw[1].isbg = 1;
#endif


#ifdef FIND_VLCBUF
	maxRunLevel = 0;
#endif

	dec.is24Bit = str->mode; 
	dec.scrWidth = scrWidth;
	dec.x = x;
	dec.y = y;
	dec.width = w;
	dec.height = h;
//	dec.endFrame = StrFile->Frames;
	dec.endFrame = StrFile->Frames+1; // Workaround for displaying the last frame.
	dec.volume = str->volume;
	dec.frameCount = 0;
	dec.rewindSwitch = 0;
	dec.frameDone = 0;
//	dec.rectId = 0;
//	dec.vlcId = 0;
//	dec.imageId = 0;

// Restore last double buffer used by previous movie.
	dec.rectId = dec.vlcId = dec.imageId = LastDB;

	

	// Init the display environments.
	SetDefDispEnv(&dec.disp[0], 0,   FRAME_Y, scrWidth, FRAME_Y);
	SetDefDispEnv(&dec.disp[1], 0,   0,       scrWidth, FRAME_Y);
//	setRECT(&dec.disp[0].screen, SCREEN_X, SCREEN_Y, 0, FRAME_Y);	
//	setRECT(&dec.disp[1].screen, SCREEN_X, SCREEN_Y, 0, FRAME_Y);	
// Use same values as in main double buffer.
	setRECT(&dec.disp[0].screen, db[0].disp.screen.x, db[0].disp.screen.y, db[0].disp.screen.w, db[0].disp.screen.h);
	setRECT(&dec.disp[1].screen, db[1].disp.screen.x, db[1].disp.screen.y, db[1].disp.screen.w, db[1].disp.screen.h);

	dec.disp[0].isrgb24 = dec.disp[1].isrgb24 = (str->mode == STR_MODE24);


//	if (str->drawBorders || dec.is24Bit)			// Clear VRAM.
//		StrClearVRAM();

// Clear vram in 24bit mode.
	if ( dec.is24Bit && Game_Status == STATUS_DEBUGMENU )
		{
		StrClearVRAM();
		Prev_Game_Status = Game_Status;
		}



	// Set correct display mode before we begin drawing.
	VSync(0);
	PutDispEnv(&dec.disp[dec.rectId]);


	setRECT(&dec.rect[0], ScalePPW(x), y, ScalePPW(w), h);  
	setRECT(&dec.rect[1], ScalePPW(x), y + FRAME_Y, ScalePPW(w), h);
	dec.slice = dec.rect[dec.rectId];
	dec.slice.w = ScalePPW(SLICE_WIDTH);

	
	// Alloc VLC and image buffers (amount allocated depends on frame size,
	// streaming mode and maximum runlevel size).
#ifdef FIND_VLCBUF
	vlcBufSize = MAX_VLCBUF_SIZE;
#else
	if (str->vlcBufSize)
		vlcBufSize = str->vlcBufSize;
	else
		vlcBufSize = MAX_VLCBUF_SIZE;
#endif // FIND_VLCBUF


	dec.vlcBuffer[0] = (u_long *) AllocMem(vlcBufSize);
	dec.vlcBuffer[1] = (u_long *) AllocMem(vlcBufSize);


	if (dec.is24Bit)
		imageBufSize = SLICE_WIDTH * 3 * h;
	else
		imageBufSize = SLICE_WIDTH * 2 * h;

	dec.imageBuffer[0] = (u_long *) AllocMem(imageBufSize);
	dec.imageBuffer[1] = (u_long *) AllocMem(imageBufSize); 


	// Init the MDEC.
	DecDCTReset(0);
	DecDCTvlcSize(0);
	DecDCToutCallback((void (*)()) StrDecDCToutCB);
	ringBuf = (u_long *) AllocMem(RING_SIZE * FORM1_SIZE);
	StSetRing(ringBuf, RING_SIZE);

// No, if StartingFrame > 0 screen stays blank while the sound plays until desired frame is reached. StSetMask does the same.
//	StSetStream(dec.is24Bit, StartingFrame, StrFile->Frames+1, 0, 0);

	StSetStream(dec.is24Bit, 0, dec.endFrame, CheckLastFrame, 0);

	// Store old ADPCM volume and set new volume.
	SsGetSerialVol(SS_SERIAL_A, &oldVolume);
	SsSetSerialVol(SS_SERIAL_A, dec.volume, dec.volume);
}

/* ------------------------------------------------------------------------ */

static void StrEnd(void) {


/* - Type:	PRIVATE
 * -
 * - Usage: Clean up.
 */

	
	StUnSetRing();
//	CdControlB(CdlPause, 0, 0);
	if ( !PauseCD() )
		{
		Prev_Game_Status = Game_Status;
		Game_Status = STATUS_ERRORSCREEN;
		SaveError(PLAY_ERROR, __FILE__, __FUNCTION__, __LINE__);
		}

	DecDCToutCallback(0);            

	myheapbase = oldHeapbase;

//	if (dec.is24Bit)			// Clear VRAM to remove any 24bit graphics.
//		StrClearVRAM();
// Don't clear vram in 24bit mode between movies.

	if ( dec.is24Bit && ( Game_Status != STATUS_GAMEPLAY && Game_Status != STATUS_DEATH && Game_Status != STATUS_DIRK ) )
		StrClearVRAM();


	// Restore previous ADPCM volume. 
	SsSetSerialVol(SS_SERIAL_A, oldVolume.left, oldVolume.right);


#ifdef DEBUG
	printf("FrameCount %d\n", dec.frameCount);
#endif
}

/* ------------------------------------------------------------------------ */

//static void StrClearVRAM(void) {
void StrClearVRAM(void) {


/* - Type:	PRIVATE
 * -
 * - Usage: Useful before and after streaming in 24bit mode	to ensure
 * - 		24bit data is not displayed in 16bit mode (and vice versa). 
 */


	RECT	clrRect;


	setRECT(&clrRect, 0, 0, ScalePPW(dec.scrWidth), FRAME_Y);
	ClearImage(&clrRect, 0, 0, 0);
	clrRect.y = FRAME_Y;
	ClearImage(&clrRect, 0, 0, 0);
}

/* ------------------------------------------------------------------------ */

static short StrKickCD(CdlLOC *loc) {


/* - Type:	PRIVATE
 * -
 * - Param:	loc = (In) location. 
 * -
 * - Ret:	0 on error, 1 otherwise.	
 * -
 * - Usage: Start the CD. 
 */

	
	short	seekRetry = 0,
			readRetry = 0;	


	do {

		while (!CdControl(CdlSeekL, (u_char *)loc, 0)) {
			
			if (++seekRetry == MAX_RETRY)
				return 0;
		}


		seekRetry = 0;

		if (readRetry++ == MAX_RETRY)
			return 0;
				

	} while (!CdRead2(CdlModeStream|CdlModeSpeed|CdlModeRT));


	return 1;
}

/* ------------------------------------------------------------------------ */

static u_long *StrGetNextFrame(void) {


/* - Type:	PRIVATE
 * -
 * - Ret:	Address of next frame or NULL on error.
 * -
 * - Usage:	Gets next frame from the ring buffer. Also checks for the
 * -		end of the stream. If the end has been reached rewindSwitch
 * -		is set. If frame is not obtained from the ring timeout and
 * -		return NULL.
 */


	long		timer = WAIT_TIME;
	u_long		*addr;                      
	StHEADER	*sector;                         

    
    // Get the next frame from the ring buffer.
	while (StGetNext(&addr, (u_long**) &sector)) {

// Last frame gets stuck here.
			if (--timer == 0)
				return NULL;
	}



	dec.frameCount++;				// Update internal frame count.


#if defined(TESTING)||defined(FIND_VLCBUF)

	// Check for frame skipping.
	if (firstFrame) {
		prevFrameNum = sector->frameCount;
		firstFrame = 0;

	} else if ((sector->frameCount - prevFrameNum) != 1) {
		numSkipped++;	
	}
		
	prevFrameNum = sector->frameCount;
	FntPrint("Skipped =  %d\n", numSkipped);
#endif


#ifdef DEBUG
	if (dec.frameCount == 1)
		printf("MOVIE: w = %d, h = %d, sectors = %d\n", 
				sector->width, sector->height, sector->nSectors);

	FntPrint("Frame No. = %d\n", dec.frameCount);
#endif


// Keep track of actual frame number.
STRPreviousFrame = STRCurrentFrame;
STRCurrentFrame = sector->frameCount;



//printf("\nsector->frameCount: %d. dec.frameCount: %d", sector->frameCount, dec.frameCount);

			
	// End of stream checks.
	if (sector->frameCount > dec.endFrame) {
	
#ifdef DEBUG	
		printf("ERROR: MOVIE -- Found sector frame count over > end frame (%d > %d)\n",
				sector->frameCount, dec.endFrame);
#endif
		dec.rewindSwitch = 1;
		StopPlayingMovie = 1;
		return addr;
	}
	

	if (sector->frameCount < dec.frameCount) {
	
#ifdef DEBUG	
		printf("ERROR: MOVIE -- Found sector frame count < internal frame count. (%d < %d)\n",
			 sector->frameCount, dec.endFrame);
#endif
		dec.rewindSwitch = 1;
		StopPlayingMovie = 1;
		return addr;
	}


	if (sector->width != dec.width || sector->height != dec.height) {
	
#ifdef DEBUG	
		printf("ERROR: MOVIE -- Found bad sized frame (%d x %d) is not (%d x %d).\n",
				sector->width, sector->height, dec.width, dec.height);
#endif
		dec.rewindSwitch = 1;
		StopPlayingMovie = 1;
		Prev_Game_Status = Game_Status;
		Game_Status = STATUS_ERRORSCREEN;
		SaveError(DECODE_ERROR, __FILE__, __FUNCTION__, __LINE__);

		return addr;
	}

	
    return addr;                          
}

/* ------------------------------------------------------------------------ */

static void StrVLCFrame(u_long *frame) {


/* - Type:	PRIVATE
 * -
 * - Param:	frame = (In) Address of frame BS.
 * -
 * - Usage:	VLC decodes the frame's BS. Unlock frame from the ring buffer
 * -		once decoded.
 */


	// If no frame to decode return.
	if (frame == NULL) {
#ifdef DEBUG
		printf("ERROR: MOVIE -- No frame to VLC decode!!\n");
#endif
		return;
	}


#ifdef TESTING
		// Print BS Encoded Format (i.e. Version 2 or 3). 
		FntPrint("BS Ver = %d\n", *((u_short *) frame + 3) );
#endif


#ifdef FIND_VLCBUF
	if (DecDCTBufSize(frame) > maxRunLevel)
		maxRunLevel = DecDCTBufSize(frame);
#endif


	dec.vlcId ^= 1;
	DecDCTvlc(frame, dec.vlcBuffer[dec.vlcId]);
	StFreeRing(frame);
}

/* ------------------------------------------------------------------------ */

static void	StrDrawDecodeSync(void) {


/* - Type:	PRIVATE
 * -
 * - Usage:	Wait for current frame's decoding and drawing to be finished.
 */


	long	timer = WAIT_TIME;


	while (!dec.frameDone) {

		if (--timer == 0) {
#ifdef DEBUG
			printf("ERROR: MOVIE -- MDEC decode timeout!!\n");
#endif
			break;
		}
	}

	
	dec.frameDone = 0;

	dec.rectId ^= 1;
	dec.slice.x = dec.rect[dec.rectId].x;
	dec.slice.y = dec.rect[dec.rectId].y;
}

/* ------------------------------------------------------------------------ */

//static short StrFadeOutVol(short *fadeVol) {


/* - Type:	PRIVATE
 * -
 * - Param:	fadeVol = (In/Out) Current volume.
 * -
 * - Ret:	1 = Volume completely faded (therefore finish playing the stream).
 * - 		0 = Otherwise.
 * -		
 * -
 * - Usage: Fade out the volume.
 */

/*
	if ((*fadeVol -= FADE_VOL_SPD) < 0)
		*fadeVol = 0;


	SsSetSerialVol(SS_SERIAL_A, *fadeVol, *fadeVol);


	if (!*fadeVol)
		return PLAYSTR_USER;			// Flag user exit.
	else
		return 0;
}
*/
/* ------------------------------------------------------------------------ */

static long GetDCToutSize(void) {


/* - Type:	PRIVATE
 * -
 * - Ret:	DecDCTout size in longs for current playback mode.
 */


	u_short	h = dec.height;

	
	if (dec.is24Bit)
		return (((SLICE_WIDTH * PPW24) * bound16(h)) >> 1);
	else
		return (((SLICE_WIDTH * PPW16) * bound16(h)) >> 1);
}

/* ------------------------------------------------------------------------ */

static u_short ScalePPW(u_short n) {


/* - Type:	PRIVATE
 * -
 * - Param:	n = (In) A number.
 * -
 * - Ret:	n scaled by the correct PPW (words/pixel). This depends
 * -		on the current playback mode.
 */


	if (dec.is24Bit)
		return (n * PPW24);
	else
		return (n * PPW16);
}

/* ------------------------------------------------------------------------ */

static u_short GetDCT_MODE(void) {


/* - Type:	PRIVATE
 * -
 * - Ret:	The current DCT mode.	
 */


	return ((dec.is24Bit) ? DCT_MODE24 : DCT_MODE16);
}

/* ------------------------------------------------------------------------ */

#ifdef FIND_VLCBUF

static void PrintVLCBufSize(void) {


/* - Type:	PRIVATE
 * -
 * - Usage: Prints the maximum VLC buffer size to play a stream.	
 */


	printf("\nMaximum VLC Buffer (RunLevel) Size\n");
	printf("----------------------------------\n");
	printf("Max RunLevel size = %d bytes.\n", maxRunLevel << 2);
	printf("Max size of each VLC buffer = %d bytes.\n\n", (maxRunLevel << 2) + RL_HEADER_SIZE);

	// If frames were skipped warn of possible incorrect result! 
	if (numSkipped) {
		printf("Warning:\n");
		printf("\tSkipped %d frames during playback!\n", numSkipped);
		printf("\tTherefore the maximum VLC buffer size may be incorrect!\n\n"); 
	}
}

#endif // FIND_VLCBUF

/* ------------------------------------------------------------------------ */

static u_long AllocMem(u_long size) {


/* - Type:	PRIVATE
 * -
 * - Param:	size = (In) No. of bytes to allocate.
 * -
 * - Ret:	Base of allocated mem.
 * -
 * - Usage:	Allocate "size" bytes from the heap.
 */

 
	u_long mem = myheapbase;

	
	if ((size & 3) != 0)
		size = (size + 4) & 0xfffffffc;


#ifdef DEBUG
//	if ((__heapbase + size) >= (0x80000000 + _ramsize - _stacksize))
	if ((myheapbase + size) >= (0x80000000 + _ramsize - _stacksize))
		printf("ERROR: MOVIE -- Not enough memory, can't allocate %d bytes!\n", size);
	else
		printf("Allocated %d bytes. Free memory = %d bytes.\n",
				size,
//				(0x80000000 + _ramsize - _stacksize) - (__heapbase + size)
				(0x80000000 + _ramsize - _stacksize) - (myheapbase + size)
				);
#endif			


	myheapbase += size;


	return mem; 
}

/* ------------------------------------------------------------------------ */
