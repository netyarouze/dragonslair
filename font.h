
typedef struct{
	short Red;
	short Green;
	short Blue;
} RGBColor;


#ifdef FONT_C

extern short SelectedLanguage;

RGBColor ColorWhite = {255, 255, 255};
RGBColor ColorYellow = {255, 255, 0};
RGBColor ColorRed = {255, 0, 0};
RGBColor ColorBlue = {0, 100, 255};
RGBColor ColorGreen = {0, 255, 0};
RGBColor ColorPink = {255, 0, 200};
RGBColor ColorFlash = {255, 0, 0}; // Highlighted option.

#else

extern RGBColor ColorWhite;
extern RGBColor ColorYellow;
extern RGBColor ColorRed;
extern RGBColor ColorBlue;
extern RGBColor ColorGreen;
extern RGBColor ColorPink;
extern RGBColor ColorFlash;

#endif