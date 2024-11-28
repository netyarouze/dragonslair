/************************************************************
 *                                                          *
 *                       control.h                          *
 *                                                          *
 *                                                          *
 *                Vince Diesi     13/02/97                  *
 *                                                          *
 *   Copyright (C) 1997 Sony Computer Entertainment Inc.    *
 *                  All Rights Reserved                     *
 *                                                          *
 ***********************************************************/

#ifndef __CONTROL_H
#define __CONTROL_H

#include "ctrller.h"
#include "main.h"

/* ---------------------------------------------------------------------------
 * - MACRO DEFINITIONS
 * ---------------------------------------------------------------------------
 */

// Check controllers every second.
#ifdef NTSC
#define CHECK_CONTROLLERS		60
#else
#define CHECK_CONTROLLERS		50
#endif



// New (more meaningful) controller button names.
#define R2_KEY			PAD_FRB
#define L2_KEY			PAD_FLB
#define R1_KEY			PAD_FRT
#define L1_KEY			PAD_FLT
#define TRIANGLE_KEY	PAD_RU
#define X_KEY			PAD_RD
#define SQUARE_KEY		PAD_RL
#define CIRCLE_KEY		PAD_RR
#define UP_KEY			PAD_LU
#define DOWN_KEY		PAD_LD
#define LEFT_KEY		PAD_LL
#define RIGHT_KEY		PAD_LR
#define SELECT_KEY		PAD_SEL
#define START_KEY		PAD_START

/* ---------------------------------------------------------------------------
 * - PUBLIC FUNCTION PROTOTYPES
 * ---------------------------------------------------------------------------
 */

void InitControllers(void);

/* ------------------------------------------------------------------------ */

void StopControllers(void);

/* ------------------------------------------------------------------------ */

void CheckControllers(void);

/* ------------------------------------------------------------------------ */

short Pressed(short button);

/* ------------------------------------------------------------------------ */

// Additional stuff for Dragon's Lair.

#define TAP_BUTTON 1
#define HOLD_BUTTON 2
#define IDLE_BUTTON 0

typedef struct{
short Up;
short Down;
short Left;
short Right;
short Triangle;
short Cross;
short Square;
short Circle;
short Select;
short Start;
short L_1;
short L_2;
short R_1;
short R_2;
short L_3;
short R_3;
short Sword;
}PAD_BUTTONS;

// Dual shock vibration.
typedef struct{
u_char Strength;
short Duration;
}DS_MOTOR;

#define SMALL_RUMBLE 1
#define BIG_RUMBLE 2
#define BOTH_RUMBLE 3
#define MEDIUM_RUMBLE 4
#define LOW_RUMBLE 5

typedef struct
{
	void (*motor)(void);
}RUMBLE_FUNCTION;


#define STICK_THRESHOLD 80

extern short Left_Stick_X, Right_Stick_X, Left_Stick_Y, Right_Stick_Y;

#endif // __CONTROL_H 

#ifdef CONTROL_C

extern short Game_Status;
extern short Prev_Game_Status;
extern PLAYER Player1;
short Left_Stick_X, Right_Stick_X, Left_Stick_Y, Right_Stick_Y;
PAD_BUTTONS Pad1;

extern GAME_OPTIONS Game_Config;

// Dual Shock stuff.
short DSBufferLength = 2;
unsigned char MotorStatus[2];
u_char DS_Align[6] = {0,1,0xFF,0xFF,0xFF,0xFF};


DS_MOTOR Big_Motor;
DS_MOTOR Small_Motor;

short DualShock_Ready = 0;
u_char Last_Pad_ID;

void DS_Small_Rumble(void);
void DS_Big_Rumble(void);
void DS_Both_Rumble(void);
void DS_Medium_Rumble(void);
void DS_Low_Rumble(void);

RUMBLE_FUNCTION Rumble_Motor[] = {
{(void *)DS_Small_Rumble},
{(void *)DS_Big_Rumble},
{(void *)DS_Both_Rumble},
{(void *)DS_Medium_Rumble},
{(void *)DS_Low_Rumble},
};


#endif
