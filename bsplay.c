/*

Adapted from the source code found at SAMPLE\PRESS\TUTO inside the developer's CD.

Some changes have been applied for Dragon's Lair.

*/

/* $PSLibId: Run-time Library Release 4.3$ */
/*			tuto3: simplest sample
 */
/*		simple on-memory movie operation (with	frame
 *		double-buffering)  */	
/*		Copyright (C) 1993 by Sony Corporation
 *			All rights Reserved
 */

#include <sys/types.h>
//#include <libetc.h>
#include <libgte.h>
#include <libgpu.h>
#include <libpress.h>
//#include <libsnd.h>

#include "assets.h"
#include "game.h"
#include "main.h"

#define BSPLAY_C
#include "bsframes.h"

static int disp_mdec(u_long *mdec_bs, DECDCTTAB table);


static RECT	SliceRect;			/* slice rectangle */
static int	SliceSize;			/* 1 slice data size */

extern short cdb;
extern short Width, Height;


DECDCTTAB	table;

short BSCurrentFrame = 0;

#define BS_DELAY 2

short Delay = 0;

extern short Game_Status;

// *******************************************************************************************


void InitBSMovie(void)
{

DecDCTvlcBuild(table);

Delay = 0;

}


// *******************************************************************************************


void InitBSFrameSize(void)
{

//SliceSize   = 16*Height/2;	/* set slice image size (word) */
//SliceRect.w = 16;		/* set slice area width and height */
//SliceRect.h = Height;

//Fix height to 240. Resolution of our movies is 320x240. No PAL optimization here.
SliceSize   = 16*240/2;		/* set slice image size (word) */
SliceRect.w = 16;		/* set slice area width and height */
SliceRect.h = 240;


}


// *******************************************************************************************


void PlayBSFrame(u_long *mdec_frame[], short Loop){

disp_mdec(mdec_frame[BSCurrentFrame], table);

//printf("\nShowing frame No: %d", BSCurrentFrame);

// Since our movies run at 12fps, a delay is required to slow things down.

if (Delay < BS_DELAY)
	{
	Delay++;
	if (Delay == BS_DELAY)
		{
		BSCurrentFrame++;
		if (mdec_frame[BSCurrentFrame] == 0)
			{
//Last frame reached. Restart or stop animation.
			if (Loop == BSLOOP)
				BSCurrentFrame = 0; // Restart
			else
				BSCurrentFrame--; // Stop
			}
		Delay = 0;
		}
	}


}


// *******************************************************************************************


static int disp_mdec(u_long *mdec_bs, DECDCTTAB table)
{
/* test buffer */
u_long mdec_image[256*256];
u_long mdec_rl[256*256];

	if ( DecDCTvlc2(mdec_bs, mdec_rl, table) == -1 )	/* decode VLC */
		{
		Game_Status = STATUS_ERRORSCREEN;
		SaveError(DECODE_ERROR, __FILE__, __FUNCTION__, __LINE__);
		return;
		}

// Below '0' means 16bit. Additional code is required for handling 24bit pictures.
	DecDCTin(mdec_rl, 0);			/* send run-level */

	SliceRect.x = 0;

//PAL video mode.
if (Height == 256)
	{
	SliceRect.y = (cdb==0)? 256+((256-Height)+18)/2: ((256-Height)+18)/2;
	}
// NTSC video mode.
else
	{
	SliceRect.y = (cdb==0)? 240+(240-Height)/2: (240-Height)/2;
	}

	
	for (SliceRect.x = 0; SliceRect.x < Width; SliceRect.x += 16) {
		DecDCTout(mdec_image, SliceSize);		/* recieve */
		DecDCToutSync(0);				/* wait */
		LoadImage(&SliceRect, mdec_image);		/* load */
	}

}

