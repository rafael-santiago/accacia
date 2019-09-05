/*
 *                                      Copyright 2006 rafael santiago.
 *
 * This is free software. You can redistribute it and/or modify under
 * the terms of the GNU General Public License version 2.
 *
 * "accacia.h" by Rafael Santiago < voidbrainvoid@yahoo.com.br >
 *
 */
#ifndef ACCACIA_H_
#define ACCACIA_H_

#if !defined(_WIN32)
# include <unistd.h>
#else
# include <windows.h>
#endif

#if !defined(_WIN32)

#define accacia_delay(n) usleep(n * 1000)

typedef enum ACCACIA_TEXT_COLOR_DEFINES {
 AC_TCOLOR_BLACK   = 30,
 AC_TCOLOR_RED     = 31,
 AC_TCOLOR_GREEN   = 32,
 AC_TCOLOR_YELLOW  = 33,
 AC_TCOLOR_BLUE    = 34,
 AC_TCOLOR_MAGENTA = 35,
 AC_TCOLOR_CYAN    = 36,
 AC_TCOLOR_WHITE   = 37
}ACCACIA_TEXT_COLOR;

typedef enum ACCACIA_BACKGROUND_COLOR_DEFINES {
 AC_BCOLOR_BLACK   = 40,
 AC_BCOLOR_RED     = 41,
 AC_BCOLOR_GREEN   = 42,
 AC_BCOLOR_YELLOW  = 43,
 AC_BCOLOR_BLUE    = 44,
 AC_BCOLOR_MAGENTA = 45,
 AC_BCOLOR_CYAN    = 46,
 AC_BCOLOR_WHITE   = 47 
}ACCACIA_BACKGROUND_COLOR;

typedef enum ACCACIA_TEXT_STYLES_DEFINES {
 AC_TSTYLE_DEFAULT        =  0,
 AC_TSTYLE_BOLD           =  1,
 AC_TSTYLE_NOT_BOLD       = 22,
 AC_TSTYLE_UNDERLINED     =  4,
 AC_TSTYLE_NOT_UNDERLINED = 24,
 AC_TSTYLE_BLINKING       =  5,
 AC_TSTYLE_NOT_BLINKING   = 25,
 AC_TSTYLE_INVERS         =  7,
 AC_TSTYLE_NOT_INVERS     = 27
}ACCACIA_TEXT_STYLE;

#else

#define accacia_delay(n) Sleep(n)

typedef enum ACCACIA_TEXT_COLOR_DEFINES {
 AC_TCOLOR_BLACK   = 0,
 AC_TCOLOR_RED     = FOREGROUND_RED,
 AC_TCOLOR_GREEN   = FOREGROUND_GREEN,
 AC_TCOLOR_YELLOW  = FOREGROUND_RED | FOREGROUND_GREEN,
 AC_TCOLOR_BLUE    = FOREGROUND_BLUE,
 AC_TCOLOR_MAGENTA = FOREGROUND_RED | FOREGROUND_BLUE,
 AC_TCOLOR_CYAN    = FOREGROUND_GREEN | FOREGROUND_BLUE,
 AC_TCOLOR_WHITE   = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE
}ACCACIA_TEXT_COLOR;

typedef enum ACCACIA_BACKGROUND_COLOR_DEFINES {
 AC_BCOLOR_BLACK   = 0,
 AC_BCOLOR_RED     = BACKGROUND_RED,
 AC_BCOLOR_GREEN   = BACKGROUND_GREEN,
 AC_BCOLOR_YELLOW  = BACKGROUND_RED | BACKGROUND_GREEN,
 AC_BCOLOR_BLUE    = BACKGROUND_BLUE,
 AC_BCOLOR_MAGENTA = BACKGROUND_RED | BACKGROUND_BLUE,
 AC_BCOLOR_CYAN    = BACKGROUND_GREEN | BACKGROUND_BLUE,
 AC_BCOLOR_WHITE   = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE
}ACCACIA_BACKGROUND_COLOR;

typedef enum ACCACIA_TEXT_STYLES_DEFINES {
 AC_TSTYLE_DEFAULT        =  0,
 AC_TSTYLE_BOLD           =  FOREGROUND_INTENSITY,
 AC_TSTYLE_NOT_BOLD       = 22,
 AC_TSTYLE_UNDERLINED     =  4,
 AC_TSTYLE_NOT_UNDERLINED = 24,
 AC_TSTYLE_BLINKING       =  5,
 AC_TSTYLE_NOT_BLINKING   = 25,
 AC_TSTYLE_INVERS         =  7,
 AC_TSTYLE_NOT_INVERS     = 27
}ACCACIA_TEXT_STYLE;

#endif

void accacia_gotoxy(const int x, const int y);

void accacia_clrscr(void);

void accacia_cursorup(const int x);

void accacia_cursordown(const int x);

void accacia_cursorforward(const int y);

void accacia_cursorbackward(const int y);

void accacia_delline(void);

void accacia_savecursorposition(void);

void accacia_restorecursorposition(void);

void accacia_textcolor(const ACCACIA_TEXT_COLOR color);

void accacia_textbackground(const ACCACIA_BACKGROUND_COLOR color);

void accacia_screennormalize(void);

void accacia_textstyle(const ACCACIA_TEXT_STYLE style);

void accacia_drawbox(const int x, const int y, const int width, const int height, const ACCACIA_BACKGROUND_COLOR color);

void accacia_drawboxwcharfill(const int x, const int y, const int width, const int height, const char charfill, const ACCACIA_TEXT_COLOR tcolor, const ACCACIA_BACKGROUND_COLOR bcolor);

void accacia_drawtopmargin(const int x, const int y, const int width, const char *title, const ACCACIA_TEXT_COLOR titlecolor, const ACCACIA_BACKGROUND_COLOR margincolor, const ACCACIA_BACKGROUND_COLOR boxcolor);

void accacia_drawbottommargin(const int x, const int y, const int width, const int height, const char *title, const ACCACIA_TEXT_COLOR titlecolor, const ACCACIA_BACKGROUND_COLOR margincolor, const ACCACIA_BACKGROUND_COLOR boxcolor);

void accacia_drawleftmargin(const int x, const int y, const int height, const ACCACIA_BACKGROUND_COLOR margincolor, const ACCACIA_BACKGROUND_COLOR boxcolor);

void accacia_drawrightmargin(const int x, const int y, const int width, const int height, const ACCACIA_BACKGROUND_COLOR margincolor, const ACCACIA_BACKGROUND_COLOR boxcolor);

void accacia_drawboxgine(const int x, const int y, const int width, const int height, const ACCACIA_BACKGROUND_COLOR boxcolor, const ACCACIA_BACKGROUND_COLOR margincolor, const char *toptitle, const ACCACIA_TEXT_COLOR toptitlecolor, const char *bottomtitle, const ACCACIA_TEXT_COLOR bottomtitlecolor, const int margintop, const int marginbottom, const int marginleft, const int marginright);

void accacia_drawboxwcharfillgine(const int x, const int y, const int width, const int height, const char charfill, const ACCACIA_TEXT_COLOR ccolor, const ACCACIA_BACKGROUND_COLOR boxcolor, const ACCACIA_BACKGROUND_COLOR margincolor, const char *toptitle, const ACCACIA_TEXT_COLOR toptitlecolor, const char *bottomtitle, const ACCACIA_TEXT_COLOR bottomtitlecolor, const int margintop, const int marginbottom, const int marginleft, const int marginright);

void accacia_gets(char *buf);

int accacia_kbhit(void);

unsigned char accacia_getch(void);

char accacia_getkey(void);

void accacia_enable(void);

void accacia_disable(void);

#endif

