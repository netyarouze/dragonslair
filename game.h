
// Game status.
#define STATUS_LOADING 0
#define STATUS_FADEOUT 1
#define STATUS_LANGUAGE_SELECTION 2
#define STATUS_INTRO_MOVIE 3
#define STATUS_TITLE 4
#define STATUS_GAMEPLAY 5
#define STATUS_DEATH 6
#define STATUS_DIRK 7
#define STATUS_CONTINUE 8
#define STATUS_GAMEOVER 9
#define STATUS_ENDING 10
#define STATUS_CREDITS 11
#define STATUS_SECRET 12
#define STATUS_WATCHMOVIES 13
#define STATUS_ALT_EXIT 14
#define STATUS_VERIFY 95
#define STATUS_PADTEST 96
#define STATUS_DEBUGGING 97
#define STATUS_DEBUGMENU 98
#define STATUS_ERRORSCREEN 99

typedef struct{
short Lives;
short Credits;
short CurrentStage;
short CurrentScene;
short CurrentCheckpoint;
int StartingFrame;
short CurrentAction;
short Deaths;
short CreditsUsed;
short Pause;
short Score;
short InstantDeathFlag;
short SkipSceneFlag;
} PLAYER;

#define EASY_DIFFICULTY 0
#define NORMAL_DIFFICULTY 1
#define HARD_DIFFICULTY 2

#define INITIAL_LIVES 5

#define YES 1
#define NO 0

#define DEFAULT_EXIT 0
#define ALT_EXIT 1

// Frame range for pressing the right button.

#define DEFAULT_FRAMES 10

// Flag used to acknowledge the correct action is performed while playing.
#define KEEP_PLAYING 0

#ifdef GAME_C

// For setting up player variables during game.
#define INIT_PLAYER_NEWGAME 0
#define INIT_PLAYER_DEATH 1
#define INIT_PLAYER_CONTINUE 2
#define INIT_PLAYER_STAGECLEAR 3
#define INIT_PLAYER_DEBUGGING 4

// Interactions during game.
#define NO_ACTION 0
#define ACTION_UP 1
#define ACTION_DOWN 2
#define ACTION_LEFT 3
#define ACTION_RIGHT 4
#define ACTION_SWORD 5


// Increase this value as required when adding new stages.
#define MAX_SCENE 15

#define MAX_INSTANT_DEATH_SCENE 10

#define MAX_STAGES 31

typedef struct{
int Frame;
short Time;
MOVIE_FILE *Movie[6]; // 0: No action, 1: up, 2: down, 3: left, 4: right, 5: Sword.
int RumbleFrame;
short RumbleType;
}SCENE;

typedef struct{
MOVIE_FILE *Movie;
MOVIE_FILE *DirkMovie;
short ID;
int Checkpoint;
short InstantDeath;
short TotalScenes;
short InstantDeathScenes;
SCENE *Scene[MAX_SCENE];
}STAGE;

typedef struct{
int StartingFrame;
int EndingFrame;
MOVIE_FILE *Movie[6]; // 0: No action, 1: up, 2: down, 3: left, 4: right, 5: Sword.
}INSTANT_DEATH_SCENE;

INSTANT_DEATH_SCENE CurrentInstantDeathScene[MAX_INSTANT_DEATH_SCENE];

MOVIE_FILE *DeathMovie;

ASSETS_FILE Assets = {SECTOR_ASSETS_DAT, 499};

extern GAME_OPTIONS Game_Config;

PLAYER Player1 = {0,0,0,0,0,0,0,0,0,0,0,0,0};

extern PAD_BUTTONS Pad1;

extern u_short LoopCount;

extern long fIdA;

extern short Width, Height;

extern short Game_Status;

short Next_Game_Status;

short Prev_Game_Status;

//u_char *CDReadResult;

extern short cdb;

// Primitives for storing screenshot when doing fade out.
POLY_FT4 FadeLeft, FadeRight;

// For the fade out.
short FadeBrightness;

extern short Countdown_To_Intro; // Trigger intro movie when idle on title screen.

extern short Title_Music_Playing; // For playing the title music just once.

extern short StopPlayingMovie; // For leaving the movie playback loop in MOVIE.C

extern short BSCurrentFrame;

extern short Options_Menu;

extern short Selected_Option;

// For the end credits.
int Credits_Y;

extern DS_MOTOR Big_Motor;
extern DS_MOTOR Small_Motor;

extern RUMBLE_FUNCTION Rumble_Motor[];

// For the hidden movie player.
short MovieIndex;

#endif // GAME_C


#ifdef MOVIE_C

extern PLAYER Player1;

extern u_short LoopCount;

extern short Prev_Game_Status;

#endif // MOVIE_C
