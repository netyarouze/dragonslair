#include "sectors.h"

// Used for starting movie playback on a specific frame. Not accurate since frame size is not constant.
#define SECTORS_PER_FRAME 12


// Movie type.

#define MOVIE_INTRO 0 // Opening movie.
#define MOVIE_STAGE 1 // Full level movie.
#define MOVIE_ALT_EXIT 2 // End level for elevator scene.
#define MOVIE_DEATH 3 // Death animation.
#define MOVIE_DIRK 4 // Dirk animation after each death.

#ifdef MOVIE_C

// Default values of our movie files.

StrInfo StrInfoBase = {
"", STR_MODE16, STR_BORDERS_OFF, FRAME_X, SCREEN_X, SCREEN_Y, FRAME_X, 240, 0, 0, 127,
};

int STRCurrentFrame;

int STRPreviousFrame;

short StopPlayingMovie;

extern short Game_Status;

#endif

#ifdef GAME_C

extern DecEnv dec; // For the fadeout when playing movies.

extern int STRCurrentFrame;

//			Type,	  Sector,		Frames.
MOVIE_FILE STR_Intro = {MOVIE_INTRO, SECTOR_DLDEMO_STR, 524};

//Stage 1.

MOVIE_FILE STR_Stage1 = {MOVIE_STAGE, SECTOR_DLR01_STR, 342};
MOVIE_FILE STR_Stage1b = {MOVIE_DIRK, SECTOR_DLR01B_STR, 42};
MOVIE_FILE STR_Stage1d1 = {MOVIE_DEATH, SECTOR_DLR01D1_STR, 18};
MOVIE_FILE STR_Stage1d2 = {MOVIE_DEATH, SECTOR_DLR01D2_STR, 23};
MOVIE_FILE STR_Stage1d3 = {MOVIE_DEATH, SECTOR_DLR01D3_STR, 39};

//Stage 2

MOVIE_FILE STR_Stage2 = {MOVIE_STAGE, SECTOR_DLR02_STR, 216};
MOVIE_FILE STR_Stage2b = {MOVIE_DIRK, SECTOR_DLR02B_STR, 42};
MOVIE_FILE STR_Stage2d1 = {MOVIE_DEATH, SECTOR_DLR02D1_STR, 36};
MOVIE_FILE STR_Stage2d2 = {MOVIE_DEATH, SECTOR_DLR02D2_STR, 24};
MOVIE_FILE STR_Stage2d3 = {MOVIE_DEATH, SECTOR_DLR02D3_STR, 36};
MOVIE_FILE STR_Stage2d4 = {MOVIE_DEATH, SECTOR_DLR02D4_STR, 18};

//Stage 3

MOVIE_FILE STR_Stage3 = {MOVIE_STAGE, SECTOR_DLR03_STR, 154};
MOVIE_FILE STR_Stage3b = {MOVIE_DIRK, SECTOR_DLR03B_STR, 37};
MOVIE_FILE STR_Stage3d1 = {MOVIE_DEATH, SECTOR_DLR03D1_STR, 36};

//Stage 4

MOVIE_FILE STR_Stage4 = {MOVIE_STAGE, SECTOR_DLR04_STR, 176};
MOVIE_FILE STR_Stage4b = {MOVIE_DIRK, SECTOR_DLR04B_STR, 42};
MOVIE_FILE STR_Stage4d1 = {MOVIE_DEATH, SECTOR_DLR04D1_STR, 32};
MOVIE_FILE STR_Stage4d2 = {MOVIE_DEATH, SECTOR_DLR04D2_STR, 36};

//Stage 5

MOVIE_FILE STR_Stage5 = {MOVIE_STAGE, SECTOR_DLR05_STR, 278};
MOVIE_FILE STR_Stage5b = {MOVIE_DIRK, SECTOR_DLR05B_STR, 42};
MOVIE_FILE STR_Stage5d1 = {MOVIE_DEATH, SECTOR_DLR05D1_STR, 12};
MOVIE_FILE STR_Stage5d2 = {MOVIE_DEATH, SECTOR_DLR05D2_STR, 24};
MOVIE_FILE STR_Stage5d3 = {MOVIE_DEATH, SECTOR_DLR05D3_STR, 24};
MOVIE_FILE STR_Stage5d4 = {MOVIE_DEATH, SECTOR_DLR05D4_STR, 39};
MOVIE_FILE STR_Stage5d5 = {MOVIE_DEATH, SECTOR_DLR05D5_STR, 17};
MOVIE_FILE STR_Stage5d6 = {MOVIE_DEATH, SECTOR_DLR05D6_STR, 24};
MOVIE_FILE STR_Stage5d7 = {MOVIE_DEATH, SECTOR_DLR05D7_STR, 30};

//Stage 6

MOVIE_FILE STR_Stage6 = {MOVIE_STAGE, SECTOR_DLR06_STR, 177};
MOVIE_FILE STR_Stage6b = {MOVIE_DIRK, SECTOR_DLR06B_STR, 42};
MOVIE_FILE STR_Stage6d1 = {MOVIE_DEATH, SECTOR_DLR06D1_STR, 18};
MOVIE_FILE STR_Stage6d2 = {MOVIE_DEATH, SECTOR_DLR06D2_STR, 18};
MOVIE_FILE STR_Stage6d3 = {MOVIE_DEATH, SECTOR_DLR06D3_STR, 24};

//Stage 7

MOVIE_FILE STR_Stage7 = {MOVIE_STAGE, SECTOR_DLR07_STR, 159};
MOVIE_FILE STR_Stage7b = {MOVIE_DIRK, SECTOR_DLR07B_STR, 42};
MOVIE_FILE STR_Stage7d1 = {MOVIE_DEATH, SECTOR_DLR07D1_STR, 46};
MOVIE_FILE STR_Stage7d2 = {MOVIE_DEATH, SECTOR_DLR07D2_STR, 26};
MOVIE_FILE STR_Stage7d3 = {MOVIE_DEATH, SECTOR_DLR07D3_STR, 54};

// Stage 8

MOVIE_FILE STR_Stage8 = {MOVIE_STAGE, SECTOR_DLR08_STR, 183};
MOVIE_FILE STR_Stage8b = {MOVIE_DIRK, SECTOR_DLR08B_STR, 42};
MOVIE_FILE STR_Stage8d1 = {MOVIE_DEATH, SECTOR_DLR08D1_STR, 23};
MOVIE_FILE STR_Stage8d2 = {MOVIE_DEATH, SECTOR_DLR08D2_STR, 18};
MOVIE_FILE STR_Stage8d3 = {MOVIE_DEATH, SECTOR_DLR08D3_STR, 48};

// Stage 9

MOVIE_FILE STR_Stage9 = {MOVIE_STAGE, SECTOR_DLR09_STR, 292};
MOVIE_FILE STR_Stage9b = {MOVIE_DIRK, SECTOR_DLR09B_STR, 42};
MOVIE_FILE STR_Stage9d1 = {MOVIE_DEATH, SECTOR_DLR09D1_STR, 18};
MOVIE_FILE STR_Stage9d2 = {MOVIE_DEATH, SECTOR_DLR09D2_STR, 12};
MOVIE_FILE STR_Stage9d3 = {MOVIE_DEATH, SECTOR_DLR09D3_STR, 24};
MOVIE_FILE STR_Stage9d4 = {MOVIE_DEATH, SECTOR_DLR09D4_STR, 25};
MOVIE_FILE STR_Stage9d5 = {MOVIE_DEATH, SECTOR_DLR09D5_STR, 12};
MOVIE_FILE STR_Stage9d6 = {MOVIE_DEATH, SECTOR_DLR09D6_STR, 32};

//Stage 10

MOVIE_FILE STR_Stage10 = {MOVIE_STAGE, SECTOR_DLR10_STR, 281};
MOVIE_FILE STR_Stage10b = {MOVIE_DIRK, SECTOR_DLR10B_STR, 42};
MOVIE_FILE STR_Stage10d1 = {MOVIE_DEATH, SECTOR_DLR10D1_STR, 27};
MOVIE_FILE STR_Stage10d2 = {MOVIE_DEATH, SECTOR_DLR10D2_STR, 42};
MOVIE_FILE STR_Stage10d3 = {MOVIE_DEATH, SECTOR_DLR10D3_STR, 17};

//Stage 11

MOVIE_FILE STR_Stage11 = {MOVIE_STAGE, SECTOR_DLR11_STR, 136};
MOVIE_FILE STR_Stage11b = {MOVIE_DIRK, SECTOR_DLR11B_STR, 42};
MOVIE_FILE STR_Stage11d1 = {MOVIE_DEATH, SECTOR_DLR11D1_STR, 40};

//Stage 12

MOVIE_FILE STR_Stage12 = {MOVIE_STAGE, SECTOR_DLR12_STR, 94};
MOVIE_FILE STR_Stage12b = {MOVIE_DIRK, SECTOR_DLR12B_STR, 42};
MOVIE_FILE STR_Stage12d1 = {MOVIE_DEATH, SECTOR_DLR12D1_STR, 24};
MOVIE_FILE STR_Stage12d2 = {MOVIE_DEATH, SECTOR_DLR12D2_STR, 30};

//Stage 13

MOVIE_FILE STR_Stage13 = {MOVIE_STAGE, SECTOR_DLR13_STR, 174};
MOVIE_FILE STR_Stage13b = {MOVIE_DIRK, SECTOR_DLR13B_STR, 42};
MOVIE_FILE STR_Stage13d1 = {MOVIE_DEATH, SECTOR_DLR13D1_STR, 30};
MOVIE_FILE STR_Stage13d2 = {MOVIE_DEATH, SECTOR_DLR13D2_STR, 18};

// Stage 14

MOVIE_FILE STR_Stage14 = {MOVIE_STAGE, SECTOR_DLR14_STR, 244};
MOVIE_FILE STR_Stage14b = {MOVIE_DIRK, SECTOR_DLR14B_STR, 46};
MOVIE_FILE STR_Stage14d1 = {MOVIE_DEATH, SECTOR_DLR14D1_STR, 24};
MOVIE_FILE STR_Stage14d2 = {MOVIE_DEATH, SECTOR_DLR14D2_STR, 32};
MOVIE_FILE STR_Stage14d3 = {MOVIE_DEATH, SECTOR_DLR14D3_STR, 18};

// Stage 15

MOVIE_FILE STR_Stage15 = {MOVIE_STAGE, SECTOR_DLR15_STR, 292};
MOVIE_FILE STR_Stage15b = {MOVIE_DIRK, SECTOR_DLR15B_STR, 43};
MOVIE_FILE STR_Stage15d1 = {MOVIE_DEATH, SECTOR_DLR15D1_STR, 24};
MOVIE_FILE STR_Stage15d2 = {MOVIE_DEATH, SECTOR_DLR15D2_STR, 16};

// Stage 16

MOVIE_FILE STR_Stage16 = {MOVIE_STAGE, SECTOR_DLR16_STR, 225};
MOVIE_FILE STR_Stage16b = {MOVIE_DIRK, SECTOR_DLR16B_STR, 42};
MOVIE_FILE STR_Stage16d1 = {MOVIE_DEATH, SECTOR_DLR16D1_STR, 18};
MOVIE_FILE STR_Stage16d2 = {MOVIE_DEATH, SECTOR_DLR16D2_STR, 10};
MOVIE_FILE STR_Stage16d3 = {MOVIE_DEATH, SECTOR_DLR16D3_STR, 18};
MOVIE_FILE STR_Stage16d4 = {MOVIE_DEATH, SECTOR_DLR16D4_STR, 36};

// Stage 17

MOVIE_FILE STR_Stage17 = {MOVIE_STAGE, SECTOR_DLR17_STR, 172};
MOVIE_FILE STR_Stage17b = {MOVIE_DIRK, SECTOR_DLR17B_STR, 42};
MOVIE_FILE STR_Stage17d1 = {MOVIE_DEATH, SECTOR_DLR17D1_STR, 30};
MOVIE_FILE STR_Stage17d2 = {MOVIE_DEATH, SECTOR_DLR17D2_STR, 23};

//Stage 18

MOVIE_FILE STR_Stage18 = {MOVIE_STAGE, SECTOR_DLR18_STR, 176};
MOVIE_FILE STR_Stage18b = {MOVIE_DIRK, SECTOR_DLR18B_STR, 42};
MOVIE_FILE STR_Stage18d1 = {MOVIE_DEATH, SECTOR_DLR18D1_STR, 30};
MOVIE_FILE STR_Stage18d2 = {MOVIE_DEATH, SECTOR_DLR18D2_STR, 37};

//Stage 19

MOVIE_FILE STR_Stage19 = {MOVIE_STAGE, SECTOR_DLR19_STR, 278};
MOVIE_FILE STR_Stage19b = {MOVIE_DIRK, SECTOR_DLR19B_STR, 42};
MOVIE_FILE STR_Stage19d1 = {MOVIE_DEATH, SECTOR_DLR19D1_STR, 12};
MOVIE_FILE STR_Stage19d2 = {MOVIE_DEATH, SECTOR_DLR19D2_STR, 24};
MOVIE_FILE STR_Stage19d3 = {MOVIE_DEATH, SECTOR_DLR19D3_STR, 24};
MOVIE_FILE STR_Stage19d4 = {MOVIE_DEATH, SECTOR_DLR19D4_STR, 40};
MOVIE_FILE STR_Stage19d5 = {MOVIE_DEATH, SECTOR_DLR19D5_STR, 18};
MOVIE_FILE STR_Stage19d6 = {MOVIE_DEATH, SECTOR_DLR19D6_STR, 24};
MOVIE_FILE STR_Stage19d7 = {MOVIE_DEATH, SECTOR_DLR19D7_STR, 30};

//Stage 20

MOVIE_FILE STR_Stage20 = {MOVIE_STAGE, SECTOR_DLR20_STR, 172};
MOVIE_FILE STR_Stage20b = {MOVIE_DIRK, SECTOR_DLR20B_STR, 42};
MOVIE_FILE STR_Stage20d1 = {MOVIE_DEATH, SECTOR_DLR20D1_STR, 18};
MOVIE_FILE STR_Stage20d2 = {MOVIE_DEATH, SECTOR_DLR20D2_STR, 24};
MOVIE_FILE STR_Stage20d3 = {MOVIE_DEATH, SECTOR_DLR20D3_STR, 23};

//Stage 21

MOVIE_FILE STR_Stage21 = {MOVIE_STAGE, SECTOR_DLR21_STR, 257};
MOVIE_FILE STR_Stage21b = {MOVIE_DIRK, SECTOR_DLR21B_STR, 42};
MOVIE_FILE STR_Stage21d1 = {MOVIE_DEATH, SECTOR_DLR21D1_STR, 30};
MOVIE_FILE STR_Stage21p1 = {MOVIE_ALT_EXIT, SECTOR_DLR21P1_STR, 60};
MOVIE_FILE STR_Stage21p2 = {MOVIE_ALT_EXIT, SECTOR_DLR21P2_STR, 60};

//Stage 22

MOVIE_FILE STR_Stage22 = {MOVIE_STAGE, SECTOR_DLR22_STR, 289};
MOVIE_FILE STR_Stage22b = {MOVIE_DIRK, SECTOR_DLR22B_STR, 42};
MOVIE_FILE STR_Stage22d1 = {MOVIE_DEATH, SECTOR_DLR22D1_STR, 18};
MOVIE_FILE STR_Stage22d2 = {MOVIE_DEATH, SECTOR_DLR22D2_STR, 12};
MOVIE_FILE STR_Stage22d3 = {MOVIE_DEATH, SECTOR_DLR22D3_STR, 24};
MOVIE_FILE STR_Stage22d4 = {MOVIE_DEATH, SECTOR_DLR22D4_STR, 26};
MOVIE_FILE STR_Stage22d5 = {MOVIE_DEATH, SECTOR_DLR22D5_STR, 12};
MOVIE_FILE STR_Stage22d6 = {MOVIE_DEATH, SECTOR_DLR22D6_STR, 36};

//Stage 23

MOVIE_FILE STR_Stage23 = {MOVIE_STAGE, SECTOR_DLR23_STR, 244};
MOVIE_FILE STR_Stage23b = {MOVIE_DIRK, SECTOR_DLR23B_STR, 42};
MOVIE_FILE STR_Stage23d1 = {MOVIE_DEATH, SECTOR_DLR23D1_STR, 24};
MOVIE_FILE STR_Stage23d2 = {MOVIE_DEATH, SECTOR_DLR23D2_STR, 32};
MOVIE_FILE STR_Stage23d3 = {MOVIE_DEATH, SECTOR_DLR23D3_STR, 18};

//Stage 24

MOVIE_FILE STR_Stage24 = {MOVIE_STAGE, SECTOR_DLR24_STR, 415};
MOVIE_FILE STR_Stage24b = {MOVIE_DIRK, SECTOR_DLR24B_STR, 42};
MOVIE_FILE STR_Stage24d1 = {MOVIE_DEATH, SECTOR_DLR24D1_STR, 12};
MOVIE_FILE STR_Stage24d2 = {MOVIE_DEATH, SECTOR_DLR24D2_STR, 42};

//Stage 25

MOVIE_FILE STR_Stage25 = {MOVIE_STAGE, SECTOR_DLR25_STR, 76};
MOVIE_FILE STR_Stage25b = {MOVIE_DIRK, SECTOR_DLR25B_STR, 42};
MOVIE_FILE STR_Stage25d1 = {MOVIE_DEATH, SECTOR_DLR25D1_STR, 54};
MOVIE_FILE STR_Stage25d2 = {MOVIE_DEATH, SECTOR_DLR25D2_STR, 18};

//Stage 26

MOVIE_FILE STR_Stage26 = {MOVIE_STAGE, SECTOR_DLR26_STR, 224};
MOVIE_FILE STR_Stage26b = {MOVIE_DIRK, SECTOR_DLR26B_STR, 42};
MOVIE_FILE STR_Stage26d1 = {MOVIE_DEATH, SECTOR_DLR26D1_STR, 18};
MOVIE_FILE STR_Stage26d2 = {MOVIE_DEATH, SECTOR_DLR26D2_STR, 12};
MOVIE_FILE STR_Stage26d3 = {MOVIE_DEATH, SECTOR_DLR26D3_STR, 18};
MOVIE_FILE STR_Stage26d4 = {MOVIE_DEATH, SECTOR_DLR26D4_STR, 36};

//Stage 27

MOVIE_FILE STR_Stage27 = {MOVIE_STAGE, SECTOR_DLR27_STR, 283};
MOVIE_FILE STR_Stage27b = {MOVIE_DIRK, SECTOR_DLR27B_STR, 42};
MOVIE_FILE STR_Stage27d1 = {MOVIE_DEATH, SECTOR_DLR27D1_STR, 27};
MOVIE_FILE STR_Stage27d2 = {MOVIE_DEATH, SECTOR_DLR27D2_STR, 38};
MOVIE_FILE STR_Stage27d3 = {MOVIE_DEATH, SECTOR_DLR27D3_STR, 18};

//Stage 28

MOVIE_FILE STR_Stage28 = {MOVIE_STAGE, SECTOR_DLR28_STR, 127};
MOVIE_FILE STR_Stage28b = {MOVIE_DIRK, SECTOR_DLR28B_STR, 42};
MOVIE_FILE STR_Stage28d1 = {MOVIE_DEATH, SECTOR_DLR28D1_STR, 30};
MOVIE_FILE STR_Stage28d2 = {MOVIE_DEATH, SECTOR_DLR28D2_STR, 18};
MOVIE_FILE STR_Stage28d3 = {MOVIE_DEATH, SECTOR_DLR28D3_STR, 24};

//Stage 29

MOVIE_FILE STR_Stage29 = {MOVIE_STAGE, SECTOR_DLR29_STR, 155};
MOVIE_FILE STR_Stage29b = {MOVIE_DIRK, SECTOR_DLR29B_STR, 42};
MOVIE_FILE STR_Stage29d1 = {MOVIE_DEATH, SECTOR_DLR29D1_STR, 36};
MOVIE_FILE STR_Stage29d2 = {MOVIE_DEATH, SECTOR_DLR29D2_STR, 15};
MOVIE_FILE STR_Stage29d3 = {MOVIE_DEATH, SECTOR_DLR29D3_STR, 21};

//Stage 30

MOVIE_FILE STR_Stage30 = {MOVIE_STAGE, SECTOR_DLR30_STR, 292};
MOVIE_FILE STR_Stage30b = {MOVIE_DIRK, SECTOR_DLR30B_STR, 42};
MOVIE_FILE STR_Stage30d1 = {MOVIE_DEATH, SECTOR_DLR30D1_STR, 24};
MOVIE_FILE STR_Stage30d2 = {MOVIE_DEATH, SECTOR_DLR30D2_STR, 16};

//Stage 31

MOVIE_FILE STR_Stage31 = {MOVIE_STAGE, SECTOR_DLR31_STR, 257};
MOVIE_FILE STR_Stage31b = {MOVIE_DIRK, SECTOR_DLR31B_STR, 42};
MOVIE_FILE STR_Stage31d1 = {MOVIE_DEATH, SECTOR_DLR31D1_STR, 30};
MOVIE_FILE STR_Stage31p1 = {MOVIE_ALT_EXIT, SECTOR_DLR31P1_STR, 60};
MOVIE_FILE STR_Stage31p2 = {MOVIE_ALT_EXIT, SECTOR_DLR31P2_STR, 60};

//Stage 32

MOVIE_FILE STR_Stage32 = {MOVIE_STAGE, SECTOR_DLR32_STR, 629};
MOVIE_FILE STR_Stage32b = {MOVIE_DIRK, SECTOR_DLR32B_STR, 42};
MOVIE_FILE STR_Stage32d1 = {MOVIE_DEATH, SECTOR_DLR32D1_STR, 12};
MOVIE_FILE STR_Stage32d2 = {MOVIE_DEATH, SECTOR_DLR32D2_STR, 12};
MOVIE_FILE STR_Stage32d3 = {MOVIE_DEATH, SECTOR_DLR32D3_STR, 12};
MOVIE_FILE STR_Stage32d4 = {MOVIE_DEATH, SECTOR_DLR32D4_STR, 12};
MOVIE_FILE STR_Stage32d5 = {MOVIE_DEATH, SECTOR_DLR32D5_STR, 30};
MOVIE_FILE STR_Stage32d6 = {MOVIE_DEATH, SECTOR_DLR32D6_STR, 32};
MOVIE_FILE STR_Stage32d7 = {MOVIE_DEATH, SECTOR_DLR32D7_STR, 40};

//Stage 33

MOVIE_FILE STR_Stage33 = {MOVIE_STAGE, SECTOR_DLR33_STR, 388};
MOVIE_FILE STR_Stage33b = {MOVIE_DIRK, SECTOR_DLR33B_STR, 42};
MOVIE_FILE STR_Stage33d1 = {MOVIE_DEATH, SECTOR_DLR33D1_STR, 24};
MOVIE_FILE STR_Stage33d2 = {MOVIE_DEATH, SECTOR_DLR33D2_STR, 24};
MOVIE_FILE STR_Stage33d3 = {MOVIE_DEATH, SECTOR_DLR33D3_STR, 53};
MOVIE_FILE STR_Stage33d4 = {MOVIE_DEATH, SECTOR_DLR33D4_STR, 30};
MOVIE_FILE STR_Stage33d5 = {MOVIE_DEATH, SECTOR_DLR33D5_STR, 18};

//Stage 34

MOVIE_FILE STR_Stage34 = {MOVIE_STAGE, SECTOR_DLR34_STR, 185};
MOVIE_FILE STR_Stage34b = {MOVIE_DIRK, SECTOR_DLR34B_STR, 42};
MOVIE_FILE STR_Stage34d1 = {MOVIE_DEATH, SECTOR_DLR34D1_STR, 18};
MOVIE_FILE STR_Stage34d2 = {MOVIE_DEATH, SECTOR_DLR34D2_STR, 36};

//Stage 35

MOVIE_FILE STR_Stage35 = {MOVIE_STAGE, SECTOR_DLR35_STR, 268};
MOVIE_FILE STR_Stage35b = {MOVIE_DIRK, SECTOR_DLR35B_STR, 42};
MOVIE_FILE STR_Stage35d1 = {MOVIE_DEATH, SECTOR_DLR35D1_STR, 18};
MOVIE_FILE STR_Stage35d2 = {MOVIE_DEATH, SECTOR_DLR35D2_STR, 12};

//Stage 36

MOVIE_FILE STR_Stage36 = {MOVIE_STAGE, SECTOR_DLR36_STR, 164};
MOVIE_FILE STR_Stage36b = {MOVIE_DIRK, SECTOR_DLR36B_STR, 42};
MOVIE_FILE STR_Stage36d1 = {MOVIE_DEATH, SECTOR_DLR36D1_STR, 18};
MOVIE_FILE STR_Stage36d2 = {MOVIE_DEATH, SECTOR_DLR36D2_STR, 18};
MOVIE_FILE STR_Stage36d3 = {MOVIE_DEATH, SECTOR_DLR36D3_STR, 18};

//Stage 38

MOVIE_FILE STR_Stage38 = {MOVIE_STAGE, SECTOR_DLR38_STR, 1151};
MOVIE_FILE STR_Stage38b = {MOVIE_DIRK, SECTOR_DLR38B_STR, 42};
MOVIE_FILE STR_Stage38d1 = {MOVIE_DEATH, SECTOR_DLR38D1_STR, 24};
MOVIE_FILE STR_Stage38d2 = {MOVIE_DEATH, SECTOR_DLR38D2_STR, 30};
MOVIE_FILE STR_Stage38d3 = {MOVIE_DEATH, SECTOR_DLR38D3_STR, 24};
MOVIE_FILE STR_Stage38d4 = {MOVIE_DEATH, SECTOR_DLR38D4_STR, 23};
MOVIE_FILE STR_Stage38d5 = {MOVIE_DEATH, SECTOR_DLR38D5_STR, 30};
MOVIE_FILE STR_Stage38d6 = {MOVIE_DEATH, SECTOR_DLR38D6_STR, 24};

MOVIE_FILE STR_TWDemo = {MOVIE_INTRO, SECTOR_TWDEMO_STR, 569};

#endif