/*

System setup functions from Vince Diesi's source code located in the path "SAMPLE\SCEE\CD\MOVIE2" inside the developer's CD.

Minimal changes have been made for Dragon's Lair.

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

#include <sys/types.h>
//#include <kernel.h>
//#include <libsn.h>
#include <libgte.h>
#include <libgpu.h>
#include <libetc.h>
#include <libcd.h>
#include <libspu.h>
#include <libsnd.h>

#include "main.h"
#include "control.h"

long fIdA;	// Applic font id.

short Width, Height; // Screen resolution.

static volatile long frameNo = 0;			// Current frame No.


/* ---------------------------------------------------------------------------
 * - PRIVATE FUNCTION PROTOTYPES
 * ---------------------------------------------------------------------------
 */

void InitSys(void); 
void InitEnvs(DB *db);
void SndInit(void);
void SndShutDown(void);
void CloseSys(void);

void VSyncCB(void);	

/* ---------------------------------------------------------------------------
 * - FUNCTION DEFINITIONS
 * ---------------------------------------------------------------------------
 */

void InitSys(void) {


/* - Type:	PRIVATE
 * -
 * - Usage: Init system. 
 */
RECT MyRect;

	ResetCallback();
	ResetGraph(0);
// Clear remaining graphics in vram from the boot sequence.
	setRECT(&MyRect, 0, 0, 640, 512);
	ClearImage(&MyRect, 0x00, 0x00, 0x00);
	DecDCTReset(0);		/* initialize Decompressor	*/
	SetGraphDebug(0);
	CdInit();
	InitGeom();
	InitControllers();

	// Video Mode.
#ifdef NTSC
	SetVideoMode(MODE_NTSC);
#else
	SetVideoMode(MODE_PAL);
#endif

	SndInit();
	VSyncCallback((void (*)()) VSyncCB);
}

/* ------------------------------------------------------------------------ */

extern unsigned char debug_font[];

void InitEnvs(DB *db) {


/* - Type:	PRIVATE
 * -
 * - Usage: Init the drawing and display environments. Also init
 * -		the application and profiler FntPrint streams. 
 */


	// Init the display and drawing environments.
	SetDefDrawEnv(&db[0].draw, 0,   0,       FRAME_X, FRAME_Y);
	SetDefDispEnv(&db[0].disp, 0,   FRAME_Y, FRAME_X, FRAME_Y);
	SetDefDrawEnv(&db[1].draw, 0,   FRAME_Y, FRAME_X, FRAME_Y);
	SetDefDispEnv(&db[1].disp, 0,   0,       FRAME_X, FRAME_Y);
	
	setRECT(&db[0].disp.screen, SCREEN_X, SCREEN_Y, 0, FRAME_Y);	
	setRECT(&db[1].disp.screen, SCREEN_X, SCREEN_Y, 0, FRAME_Y);	
	setRGB0(&db[0].draw, 0, 0, 0);
	setRGB0(&db[1].draw, 0, 0, 0);
	db[1].draw.isbg = db[0].draw.isbg = 1;

//Remove dithering. Redundant?
	db[1].draw.dtd = db[0].draw.dtd = 0;


	// Init font environment.
	FntLoad(960, 0);	
	ReadMyTIM((u_long *)debug_font); // Use custom font instead of the system one.
	fIdA = FntOpen(18, 16, 310, 200, 0, 512);			// Applic stream.
//	fIdA = FntOpen(18, 16, 310, 200, 0, 1024);			// Applic stream.
	SetDumpFnt(fIdA);	

	Width = FRAME_X;
	Height = FRAME_Y;
}

/* ------------------------------------------------------------------------ */

void SndInit(void) {


/* - Type:	PRIVATE
 * -
 * - Usage: Init sound system and volumes.
 */


	CdlATV	aud;
	char	result[8];


	aud.val0 = 127;
	aud.val1 = 127;
	aud.val2 = 127;
	aud.val3 = 127;



	CdControl(CdlDemute, NULL, result);
	CdControlB(CdlSetfilter, NULL, result);
	CdMix(&aud);


	// Clear last 100K of SPU RAM (i.e. maximum reverb workarea). 
	SpuInit();
	SpuSetTransStartAddr(421887);
	SpuWrite0(1024 * 100);


	SsInit();


	SsUtReverbOff();
	SsUtSetReverbType(0);
	SsUtSetReverbDepth(0, 0);

	SsSetTickMode(SS_TICKVSYNC);
	SsStart();
	SsSetMVol(127, 127);

	SsSetSerialAttr(SS_SERIAL_A, SS_MIX, SS_SON);
	SsSetSerialVol(SS_SERIAL_A, 127, 127);

//	SsUtSetReverbType(SS_REV_TYPE_STUDIO_B);
//	SsUtReverbOn();
//	VSync(FRAMES_PER_SECOND);
//	SsUtSetReverbDepth(40, 40);
}

/* ------------------------------------------------------------------------ */

void SndShutDown(void) {


/* - Type:	PRIVATE
 * -
 * - Usage: Shut down the sound system, clear reverb buffer etc. 
 */


    SsUtReverbOff();
    SsUtSetReverbType(0);
    SsUtSetReverbDepth(0,0);


    // Clear last 100K of SPU RAM (i.e. maximum reverb workarea). 
    SpuSetTransStartAddr(421887);
    SpuWrite0(1024 * 100);


	// Wait until SPU RAM cleared.
	VSync(100);


    SsEnd();            
} 	

/* ------------------------------------------------------------------------ */

void CloseSys(void) {


/* - Type:	PRIVATE
 * -
 * - Usage: Clean up / shut down system.	
 */


	VSyncCallback(NULL);
	SndShutDown();
	StopCallback();
	StopControllers();
	ResetGraph(3);
}

/* ------------------------------------------------------------------------ */

void VSyncCB(void) {


/* - Type:	CALLBACK	
 * -
 * - Usage:	VSyncCallback. Check status of controllers every second. 
 */

	
	frameNo++;

	
	if (!(frameNo % CHECK_CONTROLLERS))
		CheckControllers();
}

/* ------------------------------------------------------------------------ */


