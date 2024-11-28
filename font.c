/*

These functions are based on the source code from "SAMPLE\PREFSMPL" inside the developer's CD credited to Yoshi ( Mar,31,1995 ).

Several changes have been made for Dragon's Lair.

*/

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

// Embed our custom debug font.
#include "debugfnt.h"

#define FONT_C

#include "font.h"


//****************************************************************************************


int ReadMyTIM( u_long *addr )
{ 		

TIM_IMAGE tim;

// Check for error.
if ( OpenTIM(addr) != 0 )
	{
//	printf("\nError opening tim.\n");
	return 1;
	}

// Check for error.

if ( ReadTIM(&tim) == 0 )
	{
//	printf("\nError reading tim.\n");
	return 1;
	}

LoadImage(tim.prect,tim.paddr); 

//Load clut
if( (tim.mode >> 3) & 0x01 ) 
  {
  LoadImage(tim.crect, tim.caddr);
  }	

DrawSync(0);

// No error.
return 0;
}// end ReadTIM  


//****************************************************************************************


static DR_MODE  mode16, mode8;
static SPRT_16  sprt16;
static SPRT_8  sprt8;


void InitFont16p(int tx, int ty, int cx, int cy)
{

  SetDrawMode(&mode16, 0, 0, GetTPage(0,1,tx,ty), 0);
  SetSprt16(&sprt16);
  SetSemiTrans(&sprt16, 1);
  SetShadeTex(&sprt16, 0);
  sprt16.clut = GetClut(cx,cy);
}


//****************************************************************************************



void Puts16p(int x, int y, char *s, RGBColor FntColor)
{
  int	code, u, v, y_tmp;

y_tmp = y;

  DrawPrim(&mode16);
  while (*s) {
    code = *s - '0' + 48;
    v = (code%16)*16;
    u = (code/16)*16;

// Exceptions. Properly align characters with accents and other special ones.

if (SelectedLanguage != 1) // Not Japanese.
	{

	if ( (code >= 'À' && code <= 'Ä') || (code >= 'à' && code <= 'ä') || (code >= 'È' && code <= 'Ö') || (code >= 'è' && code <= 'ö') || (code >= 'Ù' && code <= 'Ü') || (code >= 'ù' && code <= 'þ') || (code == '¢' || code == '¥'))
		{
		y = y_tmp-2;
		}
	else if (code == '£' || code == 'ÿ' || code == 'Ç' || code == 'ç')
		{
		y = y_tmp+2;
		}
	else
		{
		y = y_tmp;
		}
	}


    setUV0(&sprt16, u, v);
    setXY0(&sprt16, x, y);
    setRGB0(&sprt16, FntColor.Red, FntColor.Green, FntColor.Blue);


    DrawPrim(&sprt16);
		
    s++;

if (SelectedLanguage != 1) // Not Japanese.
	{
	x += 16;
	}
else // Japanese " and º
	{
	if (code == '¾' || code == '¿')
		{
		x += 8;
		}
	else
		{
		x += 16;
		}
	}
  }
}


//****************************************************************************************



void InitFont8p(int tx, int ty, int cx, int cy)
{

  SetDrawMode(&mode8, 0, 0, GetTPage(0, 1, tx, ty), 0);
  SetSprt8(&sprt8);
  SetSemiTrans(&sprt8, 1);
  SetShadeTex(&sprt8, 0);
  sprt8.clut = GetClut(cx,cy);
}


//****************************************************************************************


Puts8p(int x, int y, char *s, RGBColor FntColor)
{
  int	code, u, v, y_tmp;

y_tmp = y;
	
  DrawPrim(&mode8);
  while (*s) {
    code = *s - '0' + 48;

    v = ((code%16)*16)/2;
    u = ((code/16)*16)/2;

// Exceptions.

if (SelectedLanguage != 1) // Not Japanese.
	{
	if ( code == 'ã' || code == 'õ' )
		{
		y = y_tmp-1;
		}
	else if (code == '£' || code == 'ÿ' || code == 'Ç' || code == 'ç')
		{
		y = y_tmp+2;
		}
	else
		{
		y = y_tmp;
		}
	}


    setUV0(&sprt8, u, v);
    setXY0(&sprt8, x, y);
    setRGB0(&sprt8, FntColor.Red, FntColor.Green, FntColor.Blue);

    DrawPrim(&sprt8);
		
    s++;

if (SelectedLanguage != 1) // Not Japanese.
	{
	x += 8;
	}
else // Japanese " and º
	{
	if (code == '¾' || code == '¿' )
		{
		x += 4;
		}
	else
		{
		x += 8;
		}
	}
  }
}


//****************************************************************************************


void CenterText(short y, short Size, char *MyText, RGBColor FntColor)
{
short x;

// Ignore invalid inputs.

if (Size == 8 || Size == 16)
	{
// Accurately align uneven strings.
	if (strlen(MyText) % 2 != 0)
		{
		x = Size/2;
		}
	else
		{
		x = 0;
		}

// Screen width is 320.

	if (Size == 8)
		{
		Puts8p(160 - x - ( strlen(MyText)/2 * Size), y, MyText, FntColor);
		}
	else
		{
		Puts16p(160 - x - ( strlen(MyText)/2 * Size), y, MyText,FntColor);
		}
	}
}


//****************************************************************************************


void HighlightOption(void)
{
if (ColorFlash.Blue == 0)
	{
	ColorFlash.Green+=15;
	}
else
	{
	ColorFlash.Green-=15;
	}

if (ColorFlash.Green >= 255)
	{
	ColorFlash.Blue  = 1;
	}
else if (ColorFlash.Green <= 0)
	{
	ColorFlash.Blue  = 0;
	}
}

//****************************************************************************************


void AlignRight(short y, short Size, char *MyText, RGBColor FntColor)
{

// Ignore invalid inputs.

if (Size == 8 || Size == 16)
	{

// Screen width is 320.

	if (Size == 8)
		{
		Puts8p(320 - Size - ( strlen(MyText) * Size), y, MyText, FntColor);
		}
	else
		{
		Puts16p(320 - Size - ( strlen(MyText) * Size), y, MyText,FntColor);
		}
	}
}


//****************************************************************************************
