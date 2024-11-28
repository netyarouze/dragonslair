
#define TITLE_IDLE_TIME 30

typedef struct{
short Difficulty;
short Vibration;
short Sound;
short Sensitivity;
}GAME_OPTIONS;


#ifdef OPTIONS_C

GAME_OPTIONS Game_Config = {NORMAL_DIFFICULTY,NO,YES,STICK_THRESHOLD};

extern PAD_BUTTONS Pad1;

extern u_short LoopCount;

short AutoStart = 10; // For quering idle status and triggering demo.

short Title_Music_Playing; // For playing the title music just once.

short Countdown_To_Intro; // Trigger intro movie when idle on title screen.

short Options_Menu = 0;

short Selected_Option = 0;

short Previous_Option;

extern PLAYER Player1;

extern short Game_Status;
extern short Prev_Game_Status;

char CurrentVideoMode[2][5] = {"NTSC", "PAL"};
#endif