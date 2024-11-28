
typedef struct{
short Debug_Trigger;
short Debug_Mode;
short Debug_STR;
short Debug_BS;
short Debug_StartFrame;
short Debug_Info;
}DEBUG_OPTIONS;

typedef struct{
short Stage;
short Checkpoint;
short UnlimitedLives;
short Alternate;
}DEBUG_STAGE;

#ifdef OPTIONS_C

#include "sectors.h"

DEBUG_OPTIONS Debug_Config = {0,0,0,0,0, 1};

// For verifying integrity of files in disc.

short Verify_Complete = 0;
CdlFILE VerifyCDFile;

// Here, size is stored in bytes, not sectors.
ASSETS_FILE File_SYSTEM_CNF = {SECTOR_SYSTEM_CNF, 69};
ASSETS_FILE File_DRAGONSL_AIR = {SECTOR_DRAGONSL_AIR, 272384};
ASSETS_FILE File_DRAGONSL_PAL = {SECTOR_DRAGONSL_PAL, 272384};
ASSETS_FILE File_ASSETS_DAT = {SECTOR_ASSETS_DAT, 1021912};
ASSETS_FILE File_MOVIES_BIN = {SECTOR_DLDEMO_STR, 383580160};


ASSETS_FILE File_TWDEMO_STR = {SECTOR_TWDEMO_STR, 14583808};

ASSETS_FILE File_DUMMY_DAT = {SECTOR_DUMMY_DAT, 33554432};

ASSETS_FILE *Expected_Files[7] = {
&File_SYSTEM_CNF,
&File_DRAGONSL_AIR,
&File_DRAGONSL_PAL,
&File_ASSETS_DAT,
&File_MOVIES_BIN,
&File_TWDEMO_STR,
&File_DUMMY_DAT,
};

ASSETS_FILE Read_Files[7];

#define TOTAL_STR_MOVIES 198


extern MOVIE_FILE STR_Intro;

extern MOVIE_FILE STR_Stage1;
extern MOVIE_FILE STR_Stage1b;
extern MOVIE_FILE STR_Stage1d1;
extern MOVIE_FILE STR_Stage1d2;
extern MOVIE_FILE STR_Stage1d3;

extern MOVIE_FILE STR_Stage2;
extern MOVIE_FILE STR_Stage2b;
extern MOVIE_FILE STR_Stage2d1;
extern MOVIE_FILE STR_Stage2d2;
extern MOVIE_FILE STR_Stage2d3;
extern MOVIE_FILE STR_Stage2d4;

extern MOVIE_FILE STR_Stage3;
extern MOVIE_FILE STR_Stage3b;
extern MOVIE_FILE STR_Stage3d1;

extern MOVIE_FILE STR_Stage4;
extern MOVIE_FILE STR_Stage4b;
extern MOVIE_FILE STR_Stage4d1;
extern MOVIE_FILE STR_Stage4d2;

extern MOVIE_FILE STR_Stage5;
extern MOVIE_FILE STR_Stage5b;
extern MOVIE_FILE STR_Stage5d1;
extern MOVIE_FILE STR_Stage5d2;
extern MOVIE_FILE STR_Stage5d3;
extern MOVIE_FILE STR_Stage5d4;
extern MOVIE_FILE STR_Stage5d5;
extern MOVIE_FILE STR_Stage5d6;
extern MOVIE_FILE STR_Stage5d7;

extern MOVIE_FILE STR_Stage6;
extern MOVIE_FILE STR_Stage6b;
extern MOVIE_FILE STR_Stage6d1;
extern MOVIE_FILE STR_Stage6d2;
extern MOVIE_FILE STR_Stage6d3;

extern MOVIE_FILE STR_Stage7;
extern MOVIE_FILE STR_Stage7b;
extern MOVIE_FILE STR_Stage7d1;
extern MOVIE_FILE STR_Stage7d2;
extern MOVIE_FILE STR_Stage7d3;

extern MOVIE_FILE STR_Stage8;
extern MOVIE_FILE STR_Stage8b;
extern MOVIE_FILE STR_Stage8d1;
extern MOVIE_FILE STR_Stage8d2;
extern MOVIE_FILE STR_Stage8d3;

extern MOVIE_FILE STR_Stage9;
extern MOVIE_FILE STR_Stage9b;
extern MOVIE_FILE STR_Stage9d1;
extern MOVIE_FILE STR_Stage9d2;
extern MOVIE_FILE STR_Stage9d3;
extern MOVIE_FILE STR_Stage9d4;
extern MOVIE_FILE STR_Stage9d5;
extern MOVIE_FILE STR_Stage9d6;

extern MOVIE_FILE STR_Stage10;
extern MOVIE_FILE STR_Stage10b;
extern MOVIE_FILE STR_Stage10d1;
extern MOVIE_FILE STR_Stage10d2;
extern MOVIE_FILE STR_Stage10d3;

extern MOVIE_FILE STR_Stage11;
extern MOVIE_FILE STR_Stage11b;
extern MOVIE_FILE STR_Stage11d1;

extern MOVIE_FILE STR_Stage12;
extern MOVIE_FILE STR_Stage12b;
extern MOVIE_FILE STR_Stage12d1;
extern MOVIE_FILE STR_Stage12d2;

extern MOVIE_FILE STR_Stage13;
extern MOVIE_FILE STR_Stage13b;
extern MOVIE_FILE STR_Stage13d1;
extern MOVIE_FILE STR_Stage13d2;

extern MOVIE_FILE STR_Stage14;
extern MOVIE_FILE STR_Stage14b;
extern MOVIE_FILE STR_Stage14d1;
extern MOVIE_FILE STR_Stage14d2;
extern MOVIE_FILE STR_Stage14d3;

extern MOVIE_FILE STR_Stage15;
extern MOVIE_FILE STR_Stage15b;
extern MOVIE_FILE STR_Stage15d1;
extern MOVIE_FILE STR_Stage15d2;

extern MOVIE_FILE STR_Stage16;
extern MOVIE_FILE STR_Stage16b;
extern MOVIE_FILE STR_Stage16d1;
extern MOVIE_FILE STR_Stage16d2;
extern MOVIE_FILE STR_Stage16d3;
extern MOVIE_FILE STR_Stage16d4;

extern MOVIE_FILE STR_Stage17;
extern MOVIE_FILE STR_Stage17b;
extern MOVIE_FILE STR_Stage17d1;
extern MOVIE_FILE STR_Stage17d2;

extern MOVIE_FILE STR_Stage18;
extern MOVIE_FILE STR_Stage18b;
extern MOVIE_FILE STR_Stage18d1;
extern MOVIE_FILE STR_Stage18d2;

extern MOVIE_FILE STR_Stage19;
extern MOVIE_FILE STR_Stage19b;
extern MOVIE_FILE STR_Stage19d1;
extern MOVIE_FILE STR_Stage19d2;
extern MOVIE_FILE STR_Stage19d3;
extern MOVIE_FILE STR_Stage19d4;
extern MOVIE_FILE STR_Stage19d5;
extern MOVIE_FILE STR_Stage19d6;
extern MOVIE_FILE STR_Stage19d7;

extern MOVIE_FILE STR_Stage20;
extern MOVIE_FILE STR_Stage20b;
extern MOVIE_FILE STR_Stage20d1;
extern MOVIE_FILE STR_Stage20d2;
extern MOVIE_FILE STR_Stage20d3;

extern MOVIE_FILE STR_Stage21;
extern MOVIE_FILE STR_Stage21b;
extern MOVIE_FILE STR_Stage21d1;
extern MOVIE_FILE STR_Stage21p1;
extern MOVIE_FILE STR_Stage21p2;

extern MOVIE_FILE STR_Stage22;
extern MOVIE_FILE STR_Stage22b;
extern MOVIE_FILE STR_Stage22d1;
extern MOVIE_FILE STR_Stage22d2;
extern MOVIE_FILE STR_Stage22d3;
extern MOVIE_FILE STR_Stage22d4;
extern MOVIE_FILE STR_Stage22d5;
extern MOVIE_FILE STR_Stage22d6;

extern MOVIE_FILE STR_Stage23;
extern MOVIE_FILE STR_Stage23b;
extern MOVIE_FILE STR_Stage23d1;
extern MOVIE_FILE STR_Stage23d2;
extern MOVIE_FILE STR_Stage23d3;

extern MOVIE_FILE STR_Stage24;
extern MOVIE_FILE STR_Stage24b;
extern MOVIE_FILE STR_Stage24d1;
extern MOVIE_FILE STR_Stage24d2;

extern MOVIE_FILE STR_Stage25;
extern MOVIE_FILE STR_Stage25b;
extern MOVIE_FILE STR_Stage25d1;
extern MOVIE_FILE STR_Stage25d2;

extern MOVIE_FILE STR_Stage26;
extern MOVIE_FILE STR_Stage26b;
extern MOVIE_FILE STR_Stage26d1;
extern MOVIE_FILE STR_Stage26d2;
extern MOVIE_FILE STR_Stage26d3;
extern MOVIE_FILE STR_Stage26d4;

extern MOVIE_FILE STR_Stage27;
extern MOVIE_FILE STR_Stage27b;
extern MOVIE_FILE STR_Stage27d1;
extern MOVIE_FILE STR_Stage27d2;
extern MOVIE_FILE STR_Stage27d3;

extern MOVIE_FILE STR_Stage28;
extern MOVIE_FILE STR_Stage28b;
extern MOVIE_FILE STR_Stage28d1;
extern MOVIE_FILE STR_Stage28d2;
extern MOVIE_FILE STR_Stage28d3;

extern MOVIE_FILE STR_Stage29;
extern MOVIE_FILE STR_Stage29b;
extern MOVIE_FILE STR_Stage29d1;
extern MOVIE_FILE STR_Stage29d2;
extern MOVIE_FILE STR_Stage29d3;

extern MOVIE_FILE STR_Stage30;
extern MOVIE_FILE STR_Stage30b;
extern MOVIE_FILE STR_Stage30d1;
extern MOVIE_FILE STR_Stage30d2;

extern MOVIE_FILE STR_Stage31;
extern MOVIE_FILE STR_Stage31b;
extern MOVIE_FILE STR_Stage31d1;
extern MOVIE_FILE STR_Stage31p1;
extern MOVIE_FILE STR_Stage31p2;

extern MOVIE_FILE STR_Stage32;
extern MOVIE_FILE STR_Stage32b;
extern MOVIE_FILE STR_Stage32d1;
extern MOVIE_FILE STR_Stage32d2;
extern MOVIE_FILE STR_Stage32d3;
extern MOVIE_FILE STR_Stage32d4;
extern MOVIE_FILE STR_Stage32d5;
extern MOVIE_FILE STR_Stage32d6;
extern MOVIE_FILE STR_Stage32d7;

extern MOVIE_FILE STR_Stage33;
extern MOVIE_FILE STR_Stage33b;
extern MOVIE_FILE STR_Stage33d1;
extern MOVIE_FILE STR_Stage33d2;
extern MOVIE_FILE STR_Stage33d3;
extern MOVIE_FILE STR_Stage33d4;
extern MOVIE_FILE STR_Stage33d5;

extern MOVIE_FILE STR_Stage34;
extern MOVIE_FILE STR_Stage34b;
extern MOVIE_FILE STR_Stage34d1;
extern MOVIE_FILE STR_Stage34d2;

extern MOVIE_FILE STR_Stage35;
extern MOVIE_FILE STR_Stage35b;
extern MOVIE_FILE STR_Stage35d1;
extern MOVIE_FILE STR_Stage35d2;

extern MOVIE_FILE STR_Stage36;
extern MOVIE_FILE STR_Stage36b;
extern MOVIE_FILE STR_Stage36d1;
extern MOVIE_FILE STR_Stage36d2;
extern MOVIE_FILE STR_Stage36d3;

extern MOVIE_FILE STR_Stage38;
extern MOVIE_FILE STR_Stage38b;
extern MOVIE_FILE STR_Stage38d1;
extern MOVIE_FILE STR_Stage38d2;
extern MOVIE_FILE STR_Stage38d3;
extern MOVIE_FILE STR_Stage38d4;
extern MOVIE_FILE STR_Stage38d5;
extern MOVIE_FILE STR_Stage38d6;

extern MOVIE_FILE STR_TWDemo;

MOVIE_FILE *All_STR_Movies[TOTAL_STR_MOVIES] = {
// Intro.
&STR_Intro,
//Stage 1.
&STR_Stage1,
&STR_Stage1b,
&STR_Stage1d1,
&STR_Stage1d2,
&STR_Stage1d3,

&STR_Stage2,
&STR_Stage2b,
&STR_Stage2d1,
&STR_Stage2d2,
&STR_Stage2d3,
&STR_Stage2d4,

&STR_Stage3,
&STR_Stage3b,
&STR_Stage3d1,

&STR_Stage4,
&STR_Stage4b,
&STR_Stage4d1,
&STR_Stage4d2,

&STR_Stage5,
&STR_Stage5b,
&STR_Stage5d1,
&STR_Stage5d2,
&STR_Stage5d3,
&STR_Stage5d4,
&STR_Stage5d5,
&STR_Stage5d6,
&STR_Stage5d7,

&STR_Stage6,
&STR_Stage6b,
&STR_Stage6d1,
&STR_Stage6d2,
&STR_Stage6d3,

&STR_Stage7,
&STR_Stage7b,
&STR_Stage7d1,
&STR_Stage7d2,
&STR_Stage7d3,

&STR_Stage8,
&STR_Stage8b,
&STR_Stage8d1,
&STR_Stage8d2,
&STR_Stage8d3,

&STR_Stage9,
&STR_Stage9b,
&STR_Stage9d1,
&STR_Stage9d2,
&STR_Stage9d3,
&STR_Stage9d4,
&STR_Stage9d5,
&STR_Stage9d6,

&STR_Stage10,
&STR_Stage10b,
&STR_Stage10d1,
&STR_Stage10d2,
&STR_Stage10d3,

&STR_Stage11,
&STR_Stage11b,
&STR_Stage11d1,

&STR_Stage12,
&STR_Stage12b,
&STR_Stage12d1,
&STR_Stage12d2,

&STR_Stage13,
&STR_Stage13b,
&STR_Stage13d1,
&STR_Stage13d2,

&STR_Stage14,
&STR_Stage14b,
&STR_Stage14d1,
&STR_Stage14d2,
&STR_Stage14d3,

&STR_Stage15,
&STR_Stage15b,
&STR_Stage15d1,
&STR_Stage15d2,

&STR_Stage16,
&STR_Stage16b,
&STR_Stage16d1,
&STR_Stage16d2,
&STR_Stage16d3,
&STR_Stage16d4,

&STR_Stage17,
&STR_Stage17b,
&STR_Stage17d1,
&STR_Stage17d2,

&STR_Stage18,
&STR_Stage18b,
&STR_Stage18d1,
&STR_Stage18d2,

&STR_Stage19,
&STR_Stage19b,
&STR_Stage19d1,
&STR_Stage19d2,
&STR_Stage19d3,
&STR_Stage19d4,
&STR_Stage19d5,
&STR_Stage19d6,
&STR_Stage19d7,

&STR_Stage20,
&STR_Stage20b,
&STR_Stage20d1,
&STR_Stage20d2,
&STR_Stage20d3,

&STR_Stage21,
&STR_Stage21b,
&STR_Stage21d1,
&STR_Stage21p1,
&STR_Stage21p2,

&STR_Stage22,
&STR_Stage22b,
&STR_Stage22d1,
&STR_Stage22d2,
&STR_Stage22d3,
&STR_Stage22d4,
&STR_Stage22d5,
&STR_Stage22d6,

&STR_Stage23,
&STR_Stage23b,
&STR_Stage23d1,
&STR_Stage23d2,
&STR_Stage23d3,

&STR_Stage24,
&STR_Stage24b,
&STR_Stage24d1,
&STR_Stage24d2,

&STR_Stage25,
&STR_Stage25b,
&STR_Stage25d1,
&STR_Stage25d2,

&STR_Stage26,
&STR_Stage26b,
&STR_Stage26d1,
&STR_Stage26d2,
&STR_Stage26d3,
&STR_Stage26d4,

&STR_Stage27,
&STR_Stage27b,
&STR_Stage27d1,
&STR_Stage27d2,
&STR_Stage27d3,

&STR_Stage28,
&STR_Stage28b,
&STR_Stage28d1,
&STR_Stage28d2,
&STR_Stage28d3,

&STR_Stage29,
&STR_Stage29b,
&STR_Stage29d1,
&STR_Stage29d2,
&STR_Stage29d3,

&STR_Stage30,
&STR_Stage30b,
&STR_Stage30d1,
&STR_Stage30d2,

&STR_Stage31,
&STR_Stage31b,
&STR_Stage31d1,
&STR_Stage31p1,
&STR_Stage31p2,

&STR_Stage32,
&STR_Stage32b,
&STR_Stage32d1,
&STR_Stage32d2,
&STR_Stage32d3,
&STR_Stage32d4,
&STR_Stage32d5,
&STR_Stage32d6,
&STR_Stage32d7,

&STR_Stage33,
&STR_Stage33b,
&STR_Stage33d1,
&STR_Stage33d2,
&STR_Stage33d3,
&STR_Stage33d4,
&STR_Stage33d5,

&STR_Stage34,
&STR_Stage34b,
&STR_Stage34d1,
&STR_Stage34d2,

&STR_Stage35,
&STR_Stage35b,
&STR_Stage35d1,
&STR_Stage35d2,

&STR_Stage36,
&STR_Stage36b,
&STR_Stage36d1,
&STR_Stage36d2,
&STR_Stage36d3,

&STR_Stage38,
&STR_Stage38b,
&STR_Stage38d1,
&STR_Stage38d2,
&STR_Stage38d3,
&STR_Stage38d4,
&STR_Stage38d5,
&STR_Stage38d6,

&STR_TWDemo,

};

extern short BSCurrentFrame;

extern StrInfo StrInfoBase;

extern int STRCurrentFrame;

extern DecEnv dec;

#else

extern DEBUG_OPTIONS Debug_Config;

extern short Verify_Complete;
extern short Verify_Index;

DEBUG_STAGE Debug_Stage = {0,0,0,0};

#endif