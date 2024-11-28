/*

Files included in ASSETS.DAT, loaded from CD.

*/

#define ASSETS_ADDRESS 0x80090000

// BitStream files (not TIM):

// Title screen animation.
#define TITLE00_BS 0x80090000
#define TITLE01_BS 0x80094d7c
#define TITLE02_BS 0x80099978
#define TITLE03_BS 0x8009e65c
#define TITLE04_BS 0x800a3350
#define TITLE05_BS 0x800a80dc
#define TITLE06_BS 0x800acd78
#define TITLE07_BS 0x800b1938
#define TITLE08_BS 0x800b64a4
#define TITLE09_BS 0x800bb234
#define TITLE10_BS 0x800c00cc
#define TITLE11_BS 0x800c3c04
#define TITLE12_BS 0x800c8a20
#define TITLE13_BS 0x800cd864
#define TITLE14_BS 0x800d2504
#define TITLE15_BS 0x800d72cc
#define TITLE16_BS 0x800dbf5c

// Resurrection animation.
#define RESU00_BS 0x800e0b5c
#define RESU01_BS 0x800e52cc
#define RESU02_BS 0x800e9fa0
#define RESU03_BS 0x800ee6b8
#define RESU04_BS 0x800f315c
#define RESU05_BS 0x800f7f04
#define RESU06_BS 0x800fcb4c
#define RESU07_BS 0x8010163c
#define RESU08_BS 0x8010610c
#define RESU09_BS 0x8010ac3c

// Language selection background.
#define BG_BS 0x8010f57c

// Ending background.
#define ENDING_BS 0x80113e58

// Sound effects:
#define SFX_VH 0x801181f8
#define SFX_VB 0x80119a18

// Font sets. TIM files:
// Japanese font.
#define FONT16J_TIM 0x801756d8 // 16x16.
#define FONT8J_TIM 0x80185758 // 8x8.

// Western font.
#define FONT16W_TIM 0x8017d718 // 16x16.
#define FONT8W_TIM 0x80187798 // 8x8.

#define REUSABLE_ADDRESS 0x80119a18
#define END_OF_DATA 0x801897d8

/*

Once the sounds and textures have been initialized, space from address SFX_VB 0x80119a18 to END_OF_DATA 0x800efd2c can be cleared and reused.

*/