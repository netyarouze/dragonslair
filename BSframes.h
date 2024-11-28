/*

These are the bitstream backgrounds and animations previously loaded from CD.

*/

/* $PSLibId: Run-time Library Release 4.3$ */
#include <sys/types.h>

#define BSLOOP 1
#define BSNOLOOP 0

#define TOTAL_BS_MOVIES 4

#ifdef BSPLAY_C


u_long	*BSBackground[] = {
(u_long *)BG_BS, 0,
};

u_long	*BSEnding[] = {
(u_long *)ENDING_BS, 0,
};

u_long	*BSTitle[] = {
(u_long *)TITLE00_BS, (u_long *)TITLE01_BS, (u_long *)TITLE02_BS, (u_long *)TITLE03_BS, (u_long *)TITLE04_BS, (u_long *)TITLE05_BS, (u_long *)TITLE06_BS, (u_long *)TITLE07_BS, (u_long *)TITLE08_BS, (u_long *)TITLE09_BS, (u_long *)TITLE10_BS, (u_long *)TITLE11_BS, (u_long *)TITLE12_BS, (u_long *)TITLE13_BS, (u_long *)TITLE14_BS, (u_long *)TITLE15_BS, (u_long *)TITLE16_BS, 0,
};

u_long	*BSGameOver[] = {
(u_long *)RESU00_BS, (u_long *)RESU01_BS, (u_long *)RESU02_BS, (u_long *)RESU03_BS, (u_long *)RESU04_BS, (u_long *)RESU05_BS, (u_long *)RESU06_BS, (u_long *)RESU07_BS, (u_long *)RESU08_BS, (u_long *)RESU09_BS, 0,
};

#else

extern u_long	*BSBackground[];
extern u_long	*BSEnding[];
extern u_long	*BSGameOver[];
extern u_long	*BSTitle[];

#endif
