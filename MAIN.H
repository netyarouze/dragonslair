/************************************************************
 *                                                          *
 *                        main.h                            *
 *                                                          *
 *                                                          *
 *                Vince Diesi     13/02/97                  *
 *                                                          *
 *   Copyright (C) 1997 Sony Computer Entertainment Inc.    *
 *                  All Rights Reserved                     *
 *                                                          *
 ***********************************************************/

#ifndef __MAIN_H
#define __MAIN_H

/* ---------------------------------------------------------------------------
 * - CONSTANTS
 * ---------------------------------------------------------------------------
 */

#define NTSC

// Screen position and dimensions. 
#define	FRAME_X			320

#ifdef NTSC

#define	FRAME_Y			240
#define SCREEN_X		0
#define SCREEN_Y		0	
#define FRAMES_PER_SECOND 60

#else

#define	FRAME_Y			256
#define SCREEN_X		0
#define SCREEN_Y		18	
#define FRAMES_PER_SECOND 50

#endif // NTSC

// Maximum Volume.
#define MAX_VOL				127

/* ---------------------------------------------------------------------------
 * - DATA TYPE AND STRUCTURE DECLARATIONS
 * ---------------------------------------------------------------------------
 */
 
typedef struct {
	DRAWENV		draw;
	DISPENV		disp;
} DB;

/* ---------------------------------------------------------------------------
 * - GLOBAL DECLARATIONS
 * ---------------------------------------------------------------------------
 */
 
extern DB		db[2];		
extern short	cdb;
extern long		fIdA;				// Aplic font id.

/* ---------------------------------------------------------------------------
 * - LIBSN.LIB GLOBAL DECLARATIONS
 * ---------------------------------------------------------------------------
 */

extern unsigned long __heapbase;
extern unsigned long __heapsize;
extern unsigned long __bss;
extern unsigned long __bsslen;
extern unsigned long __data;
extern unsigned long __datalen;
extern unsigned long __text;
extern unsigned long __textlen;
extern unsigned long _ramsize;
extern unsigned long _stacksize;

/* ------------------------------------------------------------------------ */

/* Dragon's Lair Stuff */

// Error messages.

#define NO_ERROR 0
#define READ_ERROR 1
#define PLAY_ERROR 2
#define DECODE_ERROR 3

typedef struct{
short ErrorID;
char File[12];
char Function[30];
int Line;
}ERROR_REPORT;

#ifdef MAIN_C


char ErrorType[4][20] = {
"Unexpected error",
"CD read error",
"Error playing movie",
"Error decoding movie",
};

ERROR_REPORT Error_Report;

short Game_Status = 0; // For running required function in main loop.

u_short LoopCount; // Used for timing and blinking text.


#else


extern char ErrorType[4][20];

extern ERROR_REPORT Error_Report;


#endif


#endif // __MAIN_H 
