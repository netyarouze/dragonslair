#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include <libcd.h>
#include "kernel.h"
#include <libsnd.h>

#define OPTIONS_C

#include "control.h"
#include "sound.h"
#include "language.h"
#include "font.h"
#include "bsframes.h"
#include "game.h"
#include "options.h"
#include "assets.h"
#include "files.h"
#include "movie.h"
#include "debug.h"

// ******************************************************************************************


// Just a sizeable window for the options screens.

void DrawWindow(short x, short y, short w, short h)
{
POLY_F4 MenuWindow;
LINE_G2 WindowFrame;

// Window background
setPolyF4(&MenuWindow);
setRGB0(&MenuWindow, 0, 0, 0);
setSemiTrans(&MenuWindow, 1);
setXYWH(&MenuWindow, x, y, w, h );
DrawPrim(&MenuWindow);

// Frame
// Top line
SetLineG2(&WindowFrame);
setRGB0(&WindowFrame, 255, 255, 0);
setRGB1(&WindowFrame, 100, 100, 0);
setXY2(&WindowFrame, MenuWindow.x0-1, MenuWindow.y0-1, MenuWindow.x1, MenuWindow.y0-1);
DrawPrim(&WindowFrame);

// Left line
SetLineG2(&WindowFrame);
setRGB0(&WindowFrame, 255, 255, 0);
setRGB1(&WindowFrame, 100, 100, 0);
//setXY2(&WindowFrame, MenuWindow.x0-1, MenuWindow.y0-1, MenuWindow.x2-1, MenuWindow.y2+1);// no$psx
setXY2(&WindowFrame, MenuWindow.x0-1, MenuWindow.y0-1, MenuWindow.x2-1, MenuWindow.y2);
DrawPrim(&WindowFrame);

// Bottom line
SetLineG2(&WindowFrame);
setRGB0(&WindowFrame, 255, 0, 0);
setRGB1(&WindowFrame, 100, 0, 0);
setXY2(&WindowFrame, MenuWindow.x2, MenuWindow.y2, MenuWindow.x3, MenuWindow.y3);
DrawPrim(&WindowFrame);

// Right line
SetLineG2(&WindowFrame);
setRGB0(&WindowFrame, 255, 0, 0);
setRGB1(&WindowFrame, 100, 0, 0);
//setXY2(&WindowFrame, MenuWindow.x1, MenuWindow.y1-1, MenuWindow.x3, MenuWindow.y3+1);// no$psx
setXY2(&WindowFrame, MenuWindow.x1, MenuWindow.y1-1, MenuWindow.x3, MenuWindow.y3);
DrawPrim(&WindowFrame);

}


// ******************************************************************************************

// Feed custom language strings for the options menu.

void Init_Menu_Entries(void)
{

// Main menu.
strcpy ( Main_Menu_Entries[0], TXT_NewGame[SelectedLanguage] );
strcpy ( Main_Menu_Entries[1], TXT_Options[SelectedLanguage] );

// Options menu.
strcpy ( Options_Menu_Entries[0], TXT_Difficulty[SelectedLanguage] );
strcpy ( Options_Menu_Entries[1], TXT_Vibration[SelectedLanguage] );
strcpy ( Options_Menu_Entries[2], TXT_ScreenAdjust[SelectedLanguage] );

// Difficulty level.
strcpy ( Difficulty_Entries[0], TXT_Easy[SelectedLanguage] );
strcpy ( Difficulty_Entries[1], TXT_Normal[SelectedLanguage] );
strcpy ( Difficulty_Entries[2], TXT_Hard[SelectedLanguage] );

// On / Off
strcpy ( OnOff_Entries[0], TXT_Off[SelectedLanguage] );
strcpy ( OnOff_Entries[1], TXT_On[SelectedLanguage] );

// Moves
strcpy ( Move_Entries[1], TXT_Up[SelectedLanguage] );
strcpy ( Move_Entries[2], TXT_Down[SelectedLanguage] );
strcpy ( Move_Entries[3], TXT_Left[SelectedLanguage] );
strcpy ( Move_Entries[4], TXT_Right[SelectedLanguage] );
strcpy ( Move_Entries[5], TXT_Sword[SelectedLanguage] );

// Init default settings.
//Game_Config.Difficulty = 1; // Normal difficulty.
//Game_Config.Vibration = 0; // Disable vibration.
}

// ******************************************************************************************

// Highlight text in options menu.

RGBColor DecideColor(short i, short Condition)
{

	if (i == Condition)
		{
		return ColorFlash;
		}
	else
		{
		return ColorWhite;
		}

}

// ******************************************************************************************


// Language selection screen shown after loading assets.

void Language_Selection(void)
{
short i;
char MyText[19];

// Draw Background.
PlayBSFrame(BSBackground, BSNOLOOP);


// Print options.
DrawWindow(80, 35, 160, 178);

CenterText(16,16, "Language Selection:", ColorWhite);

for (i=0; i<8; i++)
	{
	CenterText(38+(i*22), 16, Language[i], DecideColor(i, Selected_Option) );
	}

HighlightOption();

// Shortcut to disc validation screen.
if ( Pressed(UP_KEY) && Pressed(RIGHT_KEY) && Pressed(SELECT_KEY) )
	{
	Prev_Game_Status = Game_Status;
	Game_Status = STATUS_VERIFY;
	return;
	}

if ( Pad1.Down == TAP_BUTTON )
	{
	PlaySound(SFXCorrect);
	Selected_Option++;
	if (Selected_Option > 7)
		{
		Selected_Option = 0;
		}
	}

if ( Pad1.Up == TAP_BUTTON )
	{
	PlaySound(SFXCorrect);
	Selected_Option--;
	if (Selected_Option < 0)
		{
		Selected_Option = 7;
		}
	}

// Print countdown.

	if ( ( LoopCount % (FRAMES_PER_SECOND/2) ) == 0)
		{
		AutoStart--;
		}

sprintf(MyText, "Auto-Start in %02d", AutoStart);
CenterText(218, 8, MyText, ColorWhite);

// Leave language selection screen.
if (AutoStart == 0 || Pad1.Start == TAP_BUTTON || Pad1.Sword == TAP_BUTTON )
	{
	PlaySound(SFXConfirm);
	SelectedLanguage = Selected_Option;
	Selected_Option = 0;
	Init_Menu_Entries();
	Init_Status(STATUS_INTRO_MOVIE);

// Update font set if chosen language is Japanese.
	if (SelectedLanguage == 1) // Japanese.
		{
		ReadMyTIM((u_long *)FONT16J_TIM);
		InitFont16p(640, 0, 640, 256);

		ReadMyTIM((u_long *)FONT8J_TIM);
		InitFont8p(704, 0, 704, 256);
		}

// Free space no longer needed. NO, it's very slow.
//	bzero((u_long *)SFX_VB, (u_long)( END_OF_DATA - SFX_VB ) );
	}

}

// ******************************************************************************************


// Main menu screen.

void Main_Menu (void)
{
short i;

DrawWindow(40, 100, 240, 60);

for (i=0; i<2; i++)
	{
	CenterText( 110+(i*22), 16, Main_Menu_Entries[i], DecideColor(i, Selected_Option) );
	}

HighlightOption();


if (Pad1.Down == TAP_BUTTON)
	{
	Countdown_To_Intro = TITLE_IDLE_TIME;
	PlaySound(SFXCorrect);
	Selected_Option++;
	if (Selected_Option > 1)
		{
		Selected_Option = 0;
		}
	}

if (Pad1.Up == TAP_BUTTON)
	{
	Countdown_To_Intro = TITLE_IDLE_TIME;
	PlaySound(SFXCorrect);
	Selected_Option--;
	if (Selected_Option < 0)
		{
		Selected_Option = 1;
		}
	}

if (Pad1.Circle == TAP_BUTTON || Pad1.Cross == TAP_BUTTON || Pad1.Start == TAP_BUTTON)
	{
	Countdown_To_Intro = TITLE_IDLE_TIME;

	if (Selected_Option == 1) // Options highlighted.
		{
		PlaySound(SFXConfirm);
		Options_Menu = 2;
		Selected_Option = 0;
		Debug_Config.Debug_Trigger = 0;
		}
	else // New game highlighted.
		{
		SsUtAllKeyOff(0);
		PlaySound(SFXConfirm);
		Init_Status(STATUS_GAMEPLAY);
		}
	}

}


// ******************************************************************************************

// Options menu screen.

void Options_Screen (void)
{
short i;
char MyText[30];

DrawWindow(40, 100, 240, 80);

for (i=0; i<3; i++)
	{
	if (i == 0) // Difficulty.
		{
		sprintf( MyText, "%s: %s", Options_Menu_Entries[i], Difficulty_Entries[Game_Config.Difficulty]);
		CenterText( 114+(i*22), 8, MyText, DecideColor(i, Selected_Option) );
		}
	else if (i == 1) // Vibration.
		{
		sprintf( MyText, "%s: %s", Options_Menu_Entries[i], OnOff_Entries[Game_Config.Vibration]);
		CenterText( 114+(i*22), 8, MyText, DecideColor(i, Selected_Option) );
		}
	else // Adjust screen.
		{
		CenterText( 114+(i*22), 8, Options_Menu_Entries[2], DecideColor(i, Selected_Option) );
		}
	}


HighlightOption();

if (Pad1.Down == TAP_BUTTON)
	{
	Countdown_To_Intro = TITLE_IDLE_TIME;
	Debug_Config.Debug_Trigger = 0;
	PlaySound(SFXCorrect);
	Selected_Option++;
	if (Selected_Option > 2)
		{
		Selected_Option = 0;
		}
	}

if (Pad1.Up == TAP_BUTTON)
	{
	Countdown_To_Intro = TITLE_IDLE_TIME;
	Debug_Config.Debug_Trigger = 0;
	PlaySound(SFXCorrect);
	Selected_Option--;
	if (Selected_Option < 0)
		{
		Selected_Option = 2;
		}
	}

if (Pad1.Left == TAP_BUTTON && Selected_Option < 2)
	{
	Countdown_To_Intro = TITLE_IDLE_TIME;
	Debug_Config.Debug_Trigger = 0;

	if (Selected_Option == 0) // Difficulty.
		{
		PlaySound(SFXCorrect);
		Game_Config.Difficulty--;
		if (Game_Config.Difficulty < 0) // < Easy
			{
			Game_Config.Difficulty = 2; // Hard
			}
		}
	else if (Selected_Option == 1)// Vibration.
		{
		if (PadGetState(0x00) == 6)
			{
			PlaySound(SFXCorrect);
			Game_Config.Vibration ^= 1;
			if (Game_Config.Vibration == 1)
				{
				DS_Both_Rumble();
				}
			}
		else
			{
			PlaySound(SFXWrong);
			Game_Config.Vibration = 0;
			}
		}
	}

if ( (Pad1.Right == TAP_BUTTON) || (Pad1.Circle == TAP_BUTTON) || (Pad1.Cross == TAP_BUTTON) )
	{
	Countdown_To_Intro = TITLE_IDLE_TIME;
	Debug_Config.Debug_Trigger = 0;

	if (Selected_Option == 0) // Difficulty.
		{
		PlaySound(SFXCorrect);
		Game_Config.Difficulty++;
		if (Game_Config.Difficulty > 2) // > Hard
			{
			Game_Config.Difficulty = 0; // Easy
			}
		}
	else if (Selected_Option == 1) // Vibration.
		{
		if (PadGetState(0x00) == 6)
			{
			PlaySound(SFXCorrect);
			Game_Config.Vibration ^= 1;
			if (Game_Config.Vibration == 1)
				{
				DS_Both_Rumble();
				}
			}
		else
			{
			PlaySound(SFXWrong);
			Game_Config.Vibration = 0;
			}
		}
	else if (Selected_Option == 2 && (!Pad1.Right) )// Screen adjust.
		{
		PlaySound(SFXConfirm);
		Options_Menu = 3;
		}
	}


if (Pad1.Square == TAP_BUTTON || Pad1.Triangle == TAP_BUTTON || Pad1.Start == TAP_BUTTON)
	{
	Countdown_To_Intro = TITLE_IDLE_TIME;
	PlaySound(SFXWrong);
	Selected_Option=1;
	Options_Menu = 1;
	}

if (Pad1.Select == TAP_BUTTON && Selected_Option == 2)
	{
	Debug_Config.Debug_Trigger++;
	if (Debug_Config.Debug_Trigger == 5)
		{
		PlaySound(SFXConfirm);
		Selected_Option = 0;
		Player1.Pause = 0;
		Init_Status(STATUS_DEBUGMENU);
		Debug_Config.Debug_Trigger = 0;
		}
	}
}


// ******************************************************************************************

// Display custom blinking text.

void Blinking_Text(char *MyText)
{

if ( (LoopCount>>4) % 2 == 0)
	{
	CenterText(112, 16, MyText, ColorWhite);
	}

}

// ******************************************************************************************

// Screen center option.

void Screen_Adjust(void)
{
LINE_F3 MyLine;
short PAL_Y;
char MyText[16];

// Correctly align lines in PAL video mode.
if (GetVideoMode() == 1)
	{
	PAL_Y = 8;
	}
else
	{
	PAL_Y = 0;
	}

//Top left corner.
SetLineF3(&MyLine);
setRGB0(&MyLine, 255, 255, 255);
setXY3(&MyLine, 0, 20+PAL_Y, 0, 0+PAL_Y, 20, 0+PAL_Y);
DrawPrim(&MyLine);

//Top right corner.
SetLineF3(&MyLine);
setRGB0(&MyLine, 255, 255, 255);
setXY3(&MyLine, 300, 0+PAL_Y, 319, 0+PAL_Y, 319, 20+PAL_Y);
DrawPrim(&MyLine);

//Bottom left corner.
SetLineF3(&MyLine);
setRGB0(&MyLine, 255, 255, 255);
setXY3(&MyLine, 0, 220+PAL_Y, 0, 239+PAL_Y, 20, 239+PAL_Y);
DrawPrim(&MyLine);

//Bottom right corner.
SetLineF3(&MyLine);
setRGB0(&MyLine, 255, 255, 255);
setXY3(&MyLine, 319, 220+PAL_Y, 319, 239+PAL_Y, 300, 239+PAL_Y);
DrawPrim(&MyLine);

//Center cross.
//First half.
SetLineF3(&MyLine);
setRGB0(&MyLine, 255, 255, 255);
setXY3(&MyLine, 140, 120+PAL_Y, 160, 120+PAL_Y, 160, 100+PAL_Y);
DrawPrim(&MyLine);
//Second half.
SetLineF3(&MyLine);
setRGB0(&MyLine, 255, 255, 255);
setXY3(&MyLine, 180, 120+PAL_Y, 160, 120+PAL_Y, 160, 140+PAL_Y);
DrawPrim(&MyLine);

// Stop countdown for attract mode.
Countdown_To_Intro = TITLE_IDLE_TIME;

sprintf(MyText, "X: %d, Y: %d", db[0].disp.screen.x, db[0].disp.screen.y);
CenterText(30, 8, MyText, ColorWhite);

CenterText(200, 8, "SELECT: Reset, START: OK", ColorWhite);

if (Pad1.Right == TAP_BUTTON && db[0].disp.screen.x < 25)
	{
	db[0].disp.screen.x++;
	db[1].disp.screen.x = db[0].disp.screen.x;
	}

if (Pad1.Left == TAP_BUTTON && db[0].disp.screen.x > -25)
	{
	db[0].disp.screen.x--;
	db[1].disp.screen.x = db[0].disp.screen.x;
	}

if (Pad1.Up == TAP_BUTTON && db[0].disp.screen.y > -25)
	{
	db[0].disp.screen.y--;
	db[1].disp.screen.y = db[0].disp.screen.y;
	}

if (Pad1.Down == TAP_BUTTON && db[0].disp.screen.y < 25)
	{
	db[0].disp.screen.y++;
	db[1].disp.screen.y = db[0].disp.screen.y;
	}

if (Pad1.Select == TAP_BUTTON)
	{
	setRECT(&db[0].disp.screen, SCREEN_X, SCREEN_Y, 0, FRAME_Y);
	setRECT(&db[1].disp.screen, SCREEN_X, SCREEN_Y, 0, FRAME_Y);	
	}
// Go back to options menu.
if (Pad1.Start == TAP_BUTTON)
	{
	PlaySound(SFXConfirm);
	Options_Menu = 2;
	}

}

// ******************************************************************************************

// Title screen and options menu.


void Title_Screen(void)
{
char DebugStar[1];


if (Title_Music_Playing == 0)
	{
	PlaySound(SFXTitle);
	Title_Music_Playing = 1;
	}

// Draw Background.
PlayBSFrame(BSTitle, BSLOOP);


switch ( Options_Menu )
	{

	case 0: // Blinking Press Start
	Blinking_Text( TXT_PressStart[SelectedLanguage] );
//	CenterText(218, 8, "PlayStation version, 2023", ColorYellow);

	if (Pad1.Start == TAP_BUTTON)
		{
		PlaySound(SFXConfirm);
		Countdown_To_Intro = TITLE_IDLE_TIME;
		Options_Menu = 1; // Main menu
		}

// Hidden options for watching movies.
	if ( Pressed(RIGHT_KEY) && Pressed(SELECT_KEY) && Pressed(DOWN_KEY) && Pressed(L2_KEY) && Pressed(R1_KEY))
		{
		SsUtAllKeyOff(0);
		Game_Status = STATUS_WATCHMOVIES;;
		}
	if ( Pressed(LEFT_KEY) && Pressed(SELECT_KEY) && Pressed(UP_KEY) && Pressed(L1_KEY) && Pressed(R2_KEY))
		{
		SsUtAllKeyOff(0);
		Game_Status = STATUS_SECRET;
		}

	break;

	case 1: // Main menu.
		Main_Menu();
	break;

	case 2: // Options menu.
		Options_Screen();
	break;

	case 3: // Screen adjust.
		Screen_Adjust();
	break;
	}


// For debugging only, comment this.
//FntPrint(fIdA, "\n\n~c990 Countdown: %d", Countdown_To_Intro );

//FntFlush(fIdA);

// Play intro again if there's no user input for a few seconds.

if ( ( LoopCount % (FRAMES_PER_SECOND/2) ) == 0)
	{
	Countdown_To_Intro--;
	if (Countdown_To_Intro == 0)
		{
		Init_Status(STATUS_INTRO_MOVIE);
		}
	}

// Hint debug mode is enabled.
	if (Debug_Config.Debug_Mode == YES)
		{
		sprintf(DebugStar, "%c", ' '-15);
		CenterText(210, 16, DebugStar, ColorYellow);
		}

}


// ******************************************************************************************

// Debug menu for testing movies.

void Debug_Menu(void)
{

switch (Debug_Config.Debug_BS)
	{
	case 1:
	PlayBSFrame(BSBackground, BSNOLOOP);
	break;

	case 2:
	PlayBSFrame(BSEnding, BSNOLOOP);
	break;

	case 3:
	PlayBSFrame(BSGameOver, BSNOLOOP);
	break;

	case 4:
	PlayBSFrame(BSTitle, BSLOOP);
	break;
	}

if (Debug_Config.Debug_BS > 0)
	{
	FntPrint(fIdA, "\n  FRAME: %d", BSCurrentFrame);
	}
else
	{
	FntPrint(fIdA, "\n");
	}


FntPrint(fIdA, "\n			 DEBUG MENU");

FntPrint(fIdA, "\n\n	DEBUG MODE: [%s]", OnOff_Entries[Debug_Config.Debug_Mode]);
FntPrint(fIdA, "\n\n	PLAY STR MOVIE: [%0d/%d]", Debug_Config.Debug_STR+1, TOTAL_STR_MOVIES);
FntPrint(fIdA, "\n\n	START FRAME: [%d]", Debug_Config.Debug_StartFrame);
FntPrint(fIdA, "\n\n	PLAY BS MOVIE: [%0d/%0d]", Debug_Config.Debug_BS, TOTAL_BS_MOVIES);
FntPrint(fIdA, "\n\n	24bit STR: [%s]", OnOff_Entries[StrInfoBase.mode]);
FntPrint(fIdA, "\n\n	Language: [%s]", Language[SelectedLanguage]);
FntPrint(fIdA, "\n\n	BEEPS: [%s]", OnOff_Entries[Game_Config.Sound]);
FntPrint(fIdA, "\n\n	SENSITIVITY: [%d]", Game_Config.Sensitivity);

if (Selected_Option == 1)
	{
	FntPrint(fIdA, "\n\n	Played Frames: [%d/%d]", dec.frameCount, All_STR_Movies[Debug_Config.Debug_STR]->Frames);
	}
else
	{
	FntPrint(fIdA, "\n\n");
	}

FntPrint(fIdA, "\n	  Last error code: %d", _get_errno());
FntPrint(fIdA, "\n	Build date: %s. %s", __DATE__, CurrentVideoMode[GetVideoMode()]);
FntPrint(fIdA, "\n\n		 PRESS START TO EXIT");
FntFlush(fIdA);

Puts8p(30, 48+(Selected_Option*16), ">", ColorWhite);

if (Pad1.Down == TAP_BUTTON)
	{
	PlaySound(SFXCorrect);
	Selected_Option++;
	if (Selected_Option > 7)
		{
		Selected_Option = 0;
		}
	}

if (Pad1.Up == TAP_BUTTON)
	{
	PlaySound(SFXCorrect);
	Selected_Option--;
	if (Selected_Option < 0)
		{
		Selected_Option = 7;
		}
	}
if (Pad1.Right == TAP_BUTTON)
	{
	PlaySound(SFXCorrect);
	switch (Selected_Option)
		{
		case 0: // Debug mode.
		Debug_Config.Debug_Mode ^= 1;
		break;

		case 1: // STR movies.
		dec.frameCount = 0;
		Debug_Config.Debug_STR++;
		if (Debug_Config.Debug_STR+1 > TOTAL_STR_MOVIES)
			Debug_Config.Debug_STR = 0;
		Debug_Config.Debug_StartFrame = 0;
		break;

		case 2: // Starting frame.
		if ( Debug_Config.Debug_StartFrame < All_STR_Movies[Debug_Config.Debug_STR]->Frames - 1 )
			Debug_Config.Debug_StartFrame++;

		break;

		case 3: // BS movies.
		Debug_Config.Debug_BS++;
		if (Debug_Config.Debug_BS > TOTAL_BS_MOVIES)
			Debug_Config.Debug_BS = 0;
		BSCurrentFrame = 0;
		break;

		case 4: // 24bit mode.
		StrInfoBase.mode ^= 1;
		break;

		case 5: // Language.
		SelectedLanguage++;
		if (SelectedLanguage > 7)
			SelectedLanguage = 0;
		Init_Menu_Entries();
		break;

		case 6: // Sound.
		Game_Config.Sound ^= 1;
		break;

		case 7: // Stick sensitivity.
		Game_Config.Sensitivity++;
		limitRange(Game_Config.Sensitivity, 25, 120);
		break;
		}
	}

if (Pad1.Left == TAP_BUTTON)
	{
	PlaySound(SFXCorrect);
	switch (Selected_Option)
		{
		case 0: // Debug mode.
		Debug_Config.Debug_Mode ^= 1;
		break;

		case 1: // STR movies.
		dec.frameCount = 0;
		Debug_Config.Debug_STR--;
		if (Debug_Config.Debug_STR < 0)
			Debug_Config.Debug_STR = TOTAL_STR_MOVIES-1;
		Debug_Config.Debug_StartFrame = 0;
		break;

		case 2: // Starting frame.
		if ( Debug_Config.Debug_StartFrame > 0 )
			Debug_Config.Debug_StartFrame--;

		break;

		case 3: // BS movies.
		Debug_Config.Debug_BS--;
		if (Debug_Config.Debug_BS < 0)
			Debug_Config.Debug_BS = TOTAL_BS_MOVIES;
		BSCurrentFrame = 0;
		break;

		case 4: // 24bit mode.
		StrInfoBase.mode ^= 1;
		break;

		case 5: // Language
		SelectedLanguage--;
		if (SelectedLanguage < 0)
			SelectedLanguage = 7;
		Init_Menu_Entries();
		break;

		case 6: // Sound.
		Game_Config.Sound ^= 1;
		break;

		case 7: // Stick sensitivity.
		Game_Config.Sensitivity--;
		limitRange(Game_Config.Sensitivity, 25, 120);
		break;
		}
	}

if (Pad1.Sword == TAP_BUTTON)
	{
	PlaySound(SFXCorrect);
	switch (Selected_Option)
		{
		case 0: // Debug mode.
		Debug_Config.Debug_Mode ^= 1;
		break;
/*
		case 1: // Play STR movie.
		CheckButtons(); // To avoid inmediatly aborting the playback.
		PlayStream(All_STR_Movies[Debug_Config.Debug_STR], Debug_Config.Debug_StartFrame);
// Just to make sure last frame is played.
//		VSync(60);
//		CopyScreen(dec.rectId);
//		printf("\nMovie frames: %d, played frames: %d", All_STR_Movies[Debug_Config.Debug_STR]->Frames, STRCurrentFrame);
		Player1.Pause = 0;
		break;
*/
		case 4: // 24bit mode.
		StrInfoBase.mode ^= 1;
		break;

		case 5: // Language.
		SelectedLanguage++;
		if (SelectedLanguage > 7)
			SelectedLanguage = 0;
		Init_Menu_Entries();
		break;

		case 6: // Sound.
		Game_Config.Sound ^= 1;
		break;
		}
	}

if ( ( Pad1.Cross == TAP_BUTTON || Pad1.Circle == TAP_BUTTON ) && Selected_Option == 1)
	{
	CheckButtons(); // To avoid inmediatly aborting the playback.
	PlayStream(All_STR_Movies[Debug_Config.Debug_STR], Debug_Config.Debug_StartFrame);
// Just to make sure last frame is played.
//	VSync(60);
//	CopyScreen(dec.rectId);
//	printf("\nMovie frames: %d, played frames: %d", All_STR_Movies[Debug_Config.Debug_STR]->Frames, STRCurrentFrame);
	Player1.Pause = 0;
	}

if (Pad1.R_1 == TAP_BUTTON)
	{
	switch (Selected_Option)
		{
		case 1: // Play STR movie.
		PlaySound(SFXCorrect);
		if ( Debug_Config.Debug_STR + 10 < TOTAL_STR_MOVIES )
			Debug_Config.Debug_STR += 10;
		Debug_Config.Debug_StartFrame = 0;
		break;

		case 2: // Starting frame.
		PlaySound(SFXCorrect);
		if ( Debug_Config.Debug_StartFrame + 10 < All_STR_Movies[Debug_Config.Debug_STR]->Frames - 1 )
			Debug_Config.Debug_StartFrame += 10;
		break;
		}
	}

if (Pad1.L_1 == TAP_BUTTON)
	{
	switch (Selected_Option)
		{
		case 1: // Play STR movie.
		PlaySound(SFXCorrect);
		if ( (Debug_Config.Debug_STR+1) - 10 > 0 )
			Debug_Config.Debug_STR -= 10;
		Debug_Config.Debug_StartFrame = 0;
		break;

		case 2:
		PlaySound(SFXCorrect);
		if ( Debug_Config.Debug_StartFrame - 10 >= 0 )
			Debug_Config.Debug_StartFrame -= 10;
		break;
		}
	}

if (Pad1.R_2 == TAP_BUTTON)
	{
	switch (Selected_Option)
		{
		case 1: // Play STR movie.
		PlaySound(SFXCorrect);
		if ( Debug_Config.Debug_STR + 100 < TOTAL_STR_MOVIES )
			Debug_Config.Debug_STR += 100;
		Debug_Config.Debug_StartFrame = 0;
		break;

		case 2:
		PlaySound(SFXCorrect);
		if ( Debug_Config.Debug_StartFrame + 100 < All_STR_Movies[Debug_Config.Debug_STR]->Frames - 1 )
			Debug_Config.Debug_StartFrame += 100;
		break;
		}
	}

if (Pad1.L_2 == TAP_BUTTON)
	{
	switch (Selected_Option)
		{
		case 1: // Play STR movie.
		PlaySound(SFXCorrect);
		if ( (Debug_Config.Debug_STR+1) - 100 > 0 )
			Debug_Config.Debug_STR -= 100;
		Debug_Config.Debug_StartFrame = 0;
		break;

		case 2:
		PlaySound(SFXCorrect);
		if ( Debug_Config.Debug_StartFrame - 100 >= 0 )
			Debug_Config.Debug_StartFrame -= 100;
		break;
		}
	}

if (Pad1.Start == TAP_BUTTON)
	{
	PlaySound(SFXConfirm);

	Init_Status(STATUS_TITLE);
	}

if (Pad1.Select == TAP_BUTTON)
	{
	Debug_Config.Debug_Trigger++;
	if (Debug_Config.Debug_Trigger == 5)
		{
		PlaySound(SFXConfirm);
		Init_Status(STATUS_PADTEST);
		Debug_Config.Debug_Trigger = 0;
		}
	}

// Go to disc validation screen.
if ( Pad1.L_1 == TAP_BUTTON && Pad1.R_1 == TAP_BUTTON)
	{
	Game_Status = STATUS_VERIFY;
	}

}


// ******************************************************************************************

// Verify disc files. Accesed by holding down SELECT while booting.

void Verify_Screen(void)
{
static short CDCorrect;
short i;

FntPrint(fIdA, "\n	FILE	SECTOR	SIZE");

switch (Verify_Complete)
	{
	case 0:

	CdSearchFile(&VerifyCDFile, "\\SYSTEM.CNF;1");
	Read_Files[0].Position = CdPosToInt(&VerifyCDFile.pos);
	Read_Files[0].Size = VerifyCDFile.size;

	CdSearchFile(&VerifyCDFile, "\\DRAGONSL.AIR;1");
	Read_Files[1].Position = CdPosToInt(&VerifyCDFile.pos);
	Read_Files[1].Size = VerifyCDFile.size;

	CdSearchFile(&VerifyCDFile, "\\DRAGONSL.PAL;1");
	Read_Files[2].Position = CdPosToInt(&VerifyCDFile.pos);
	Read_Files[2].Size = VerifyCDFile.size;

	CdSearchFile(&VerifyCDFile, "\\ASSETS.DAT;1");
	Read_Files[3].Position = CdPosToInt(&VerifyCDFile.pos);
	Read_Files[3].Size = VerifyCDFile.size;

	CdSearchFile(&VerifyCDFile, "\\MOVIES.BIN;1");
	Read_Files[4].Position = CdPosToInt(&VerifyCDFile.pos);
	Read_Files[4].Size = VerifyCDFile.size;

	CdSearchFile(&VerifyCDFile, "\\TWDEMO.STR;1");
	Read_Files[5].Position = CdPosToInt(&VerifyCDFile.pos);
	Read_Files[5].Size = VerifyCDFile.size;

	CdSearchFile(&VerifyCDFile, "\\DUMMY.DAT;1");
	Read_Files[6].Position = CdPosToInt(&VerifyCDFile.pos);
	Read_Files[6].Size = VerifyCDFile.size;

	Verify_Complete = 1;
	CDCorrect = 1;
	for (i=0; i<7; i++)
		{
		if ( (Read_Files[i].Position != Expected_Files[i]->Position) || (Read_Files[i].Size != Expected_Files[i]->Size) )
			{
			CDCorrect = 0;
			break;
			}
		}
	
	break;

	default:

	FntPrint(fIdA, "\n\nSYSTEM.CNF : %d/%d, %d/%d", Read_Files[0].Position, Expected_Files[0]->Position, Read_Files[0].Size, Expected_Files[0]->Size);
	FntPrint(fIdA, "\n\nDRAGONSL.AIR : %d/%d, %d/%d", Read_Files[1].Position, Expected_Files[1]->Position, Read_Files[1].Size, Expected_Files[1]->Size);
	FntPrint(fIdA, "\n\nDRAGONSL.PAL : %d/%d, %d/%d", Read_Files[2].Position, Expected_Files[2]->Position, Read_Files[2].Size, Expected_Files[2]->Size);
	FntPrint(fIdA, "\n\nASSETS.DAT : %d/%d, %d/%d", Read_Files[3].Position, Expected_Files[3]->Position, Read_Files[3].Size, Expected_Files[3]->Size);
	FntPrint(fIdA, "\n\nMOVIES.BIN : %d/%d, %d/%d", Read_Files[4].Position, Expected_Files[4]->Position, Read_Files[4].Size, Expected_Files[4]->Size);
	FntPrint(fIdA, "\n\nTWDEMO.STR : %d/%d, %d/%d", Read_Files[5].Position, Expected_Files[5]->Position, Read_Files[5].Size, Expected_Files[5]->Size);
	FntPrint(fIdA, "\n\nDUMMY.DAT : %d/%d, %d/%d", Read_Files[6].Position, Expected_Files[6]->Position, Read_Files[6].Size, Expected_Files[6]->Size);

	if (CDCorrect == 1)
		{
		FntPrint(fIdA, "\n\n			~c090DISC IS CORRECT~c999");
		}
	else
		{
		FntPrint(fIdA, "\n\n			~c900WRONG DISC~c999");
		}
	}

FntPrint(fIdA, "\nERRNO: %d. Build date:%s.%s", _get_errno(), __DATE__, CurrentVideoMode[GetVideoMode()]);
FntPrint(fIdA, "\n	PRESS START TO CONTINUE.");
FntFlush(fIdA);

// Continue to previous state.
if (Pad1.Start == TAP_BUTTON)
	{
	Game_Status = Prev_Game_Status;
	Init_Status(Game_Status);
	}

// Pad testing screen.
if ( Pressed(L1_KEY) && Pressed(R1_KEY) && Pressed(SELECT_KEY) )
	{
	Init_Status(STATUS_PADTEST);
	}

}