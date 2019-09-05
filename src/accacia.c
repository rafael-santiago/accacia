/*
 *                                      Copyright 2006 rafael santiago.
 *
 * This is free software. You can redistribute it and/or modify under
 * the terms of the GNU General Public License version 2.
 *
 * "accacia.c" by Rafael Santiago < voidbrainvoid@yahoo.com.br >
 *  Thu 27 Jul 2006 08:33:51 PM BRT
 *
 */
#include "accacia.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#if !defined(_WIN32)
# include <sys/ioctl.h>
# include <fcntl.h>
# include <termios.h>
#else
# include <conio.h>
#endif
#include <string.h>

static unsigned char g_accacia_enabled = 1;

#if defined(_WIN32)
    HANDLE g_accacia_wincon_handle = INVALID_HANDLE_VALUE;
    CONSOLE_SCREEN_BUFFER_INFO g_accacia_wincon_default_attr;
    WORD g_accacia_wincon_curr_tstyle = AC_TSTYLE_DEFAULT;
    COORD g_accacia_saved_coords;
# define ACCACIA_WINCON_HANDLE_PREPARE {\
    if (g_accacia_wincon_handle == INVALID_HANDLE_VALUE) {\
        if ((g_accacia_wincon_handle = GetStdHandle(STD_OUTPUT_HANDLE)) != INVALID_HANDLE_VALUE) {\
            GetConsoleScreenBufferInfo(g_accacia_wincon_handle, &g_accacia_wincon_default_attr);\
        }\
    }\
}
#endif

void accacia_enable(void) {
    g_accacia_enabled = 1;
}

void accacia_disable(void) {
    g_accacia_enabled = 0;
}

void accacia_gotoxy(const int x, const int y) {
#if defined(_WIN32)
    COORD screen;
    ACCACIA_WINCON_HANDLE_PREPARE
#endif
    if (!g_accacia_enabled) {
        return;
    }
#if !defined(_WIN32)
    printf("\033[%d;%dH", y, x);
# if defined(__FreeBSD__) || defined(__OpenBSD__)
    fflush(stdout);
# endif
#else
    screen.X = x;
    screen.Y = y;
    SetConsoleCursorPosition(g_accacia_wincon_handle, screen);
#endif
}

void accacia_clrscr(void) {
#if !defined(_WIN32)
    if (!g_accacia_enabled) {
        printf("\n");
        return;
    }
    printf("\033[2J");
    accacia_gotoxy(1, 1);
# if defined(__FreeBSD__) || defined(__OpenBSD__)
    fflush(stdout);
# endif
#else
    ACCACIA_WINCON_HANDLE_PREPARE
    system("@cls");
#endif
}

void accacia_cursorup(const int x) {
#if !defined(_WIN32)
    if (!g_accacia_enabled) {
        printf("\n");
        return;
    }
    printf("\033[%dA", x);
# if defined(__FreeBSD__) || defined(__OpenBSD__)
    fflush(stdout);
# endif
#endif
}

void accacia_cursordown(const int x) {
#if !defined(_WIN32)
    if (!g_accacia_enabled) {
        printf("\n");
        return;
    }
    printf("\033[%dB", x);
# if defined(__FreeBSD__) || defined(__OpenBSD__)
    fflush(stdout);
# endif
#endif
}

void accacia_cursorforward(const int y) {
#if !defined(_WIN32)
    if (!g_accacia_enabled) {
        printf("\n");
        return;
    }
    printf("\033[%dC", y);
# if defined(__FreeBSD__) || defined(__OpenBSD__)
    fflush(stdout);
# endif
#endif
}

void accacia_cursorbackward(const int y) {
#if !defined(_WIN32)
    if (!g_accacia_enabled) {
        printf("\n");
        return;
    }
    printf("\033[%dD", y);
# if defined(__FreeBSD__) || defined(__OpenBSD__)
    fflush(stdout);
# endif
#endif
}

void accacia_delline(void) {
#if !defined(_WIN32)
    if (!g_accacia_enabled) {
        printf("\n");
        return;
    }
    printf("\033[K");
# if defined(__FreeBSD__) || defined(__OpenBSD__)
    fflush(stdout);
# endif
    WORD x;
    CONSOLE_SCREEN_BUFFER_INFO info;
    ACCACIA_WINCON_HANDLE_PREPARE
    GetConsoleScreenBufferInfo(g_accacia_wincon_handle, &info);
    printf("\r");
    for (x = 1; x < info.dwSize.X; x++) {
        printf(" ");
    }
    printf("\r");
#endif
}

void accacia_savecursorposition(void) {
#if !defined(_WIN32)
    if (!g_accacia_enabled) {
        return;
    }
    printf("\033[s");
# if defined(__FreeBSD__) || defined(__OpenBSD__)
    fflush(stdout);
# endif
    CONSOLE_SCREEN_BUFFER_INFO info;
    ACCACIA_WINCON_HANDLE_PREPARE
    GetConsoleScreenBufferInfo(g_accacia_wincon_handle, &info);
    g_accacia_saved_coords = info.dwCursorPosition;
#endif
}

void accacia_restorecursorposition(void) {
#if !defined(_WIN32)
    if (!g_accacia_enabled) {
        return;
    }
    printf("\033[u");
# if defined(__FreeBSD__) || defined(__OpenBSD__)
    fflush(stdout);
# endif
    ACCACIA_WINCON_HANDLE_PREPARE
    SetConsoleCursorPosition(g_accacia_wincon_handle, g_accacia_saved_coords);
#endif
}

void accacia_textcolor(const ACCACIA_TEXT_COLOR color) {
#if !defined(_WIN32)
    int diff;
    int temp_color = color;
    if (!g_accacia_enabled) {
        return;
    }
    if (color > 37) {
        diff   = color - 37;
        temp_color -= diff;
    } else if (color<30) {
        diff   = 30 - color;
        temp_color += diff;
    }
    printf("\033[%dm", temp_color);
# if defined(__FreeBSD__) || defined(__OpenBSD__)
    fflush(stdout);
# endif
#else
    ACCACIA_WINCON_HANDLE_PREPARE
    SetConsoleTextAttribute(g_accacia_wincon_handle, color | g_accacia_wincon_curr_tstyle);
#endif
}

void accacia_textbackground(const ACCACIA_BACKGROUND_COLOR color) {
#if !defined(_WIN32)
    int temp_color = color;
    if (!g_accacia_enabled) {
        return;
    }
    if (color > 47) {
        temp_color = color | 40;
    } else if (color < 40) {
        temp_color += 40;
        temp_color = temp_color | 40;
    }
    printf("\033[%dm", temp_color);
# if defined(__FreeBSD__) || defined(__OpenBSD__)
    fflush(stdout);
# endif
#else
    ACCACIA_WINCON_HANDLE_PREPARE
    SetConsoleTextAttribute(g_accacia_wincon_handle, color);
#endif
}

void accacia_screennormalize(void) {
#if !defined(_WIN32)
    if (!g_accacia_enabled) {
        return;
    }
    printf("\033[m");
# if defined(__FreeBSD__) || defined(__OpenBSD__)
    fflush(stdout);
# endif
#else
    ACCACIA_WINCON_HANDLE_PREPARE
    SetConsoleTextAttribute(g_accacia_wincon_handle, g_accacia_wincon_default_attr.wAttributes);
#endif
}

void accacia_textstyle(const ACCACIA_TEXT_STYLE style) {
#if !defined(_WIN32)
    if (!g_accacia_enabled) {
        return;
    }
    printf("\033[%dm", style);
# if defined(__FreeBSD__) || defined(__OpenBSD__)
    fflush(stdout);
# endif
#else
    ACCACIA_WINCON_HANDLE_PREPARE
    g_accacia_wincon_curr_tstyle = style;
#endif
}

void accacia_drawbox(const int x, const int y, const int width, const int height, const ACCACIA_BACKGROUND_COLOR color) {
    int i, j, xtemp = x, ytemp = y;
    if (!g_accacia_enabled) {
        return;
    }
    accacia_textbackground(color);
    for(i = 0;i < width; i++, xtemp++) {
        for(j = 0, ytemp = y; j < height; j++, ytemp++) {
            accacia_gotoxy(xtemp, ytemp);printf(" ");
        }
    }
    accacia_gotoxy(x, y);
}

void accacia_drawboxwcharfill(const int x, const int y, const int width, const int height, const char charfill,
                              const ACCACIA_TEXT_COLOR tcolor, const ACCACIA_BACKGROUND_COLOR bcolor) {
    int i, j, xtemp = x, ytemp = y;
    if (!g_accacia_enabled) {
        return;
    }
    accacia_textbackground(bcolor);
    accacia_textcolor(tcolor);
    for(i = 0; i < width; i++, xtemp++) {
        for(j = 0, ytemp = y; j < height; j++, ytemp++) {
            accacia_gotoxy(xtemp, ytemp);printf("%c",charfill);
        }
    }
    accacia_gotoxy(x,y); 
}

void accacia_drawtopmargin(const int x, const int y, const int width, const char *title,
                           const ACCACIA_TEXT_COLOR titlecolor, const ACCACIA_BACKGROUND_COLOR margincolor,
                           const ACCACIA_BACKGROUND_COLOR boxcolor) {
    int i;
    if (!g_accacia_enabled) {
        return;
    }
    accacia_textbackground(margincolor);
    accacia_gotoxy(x, y);
    for(i = 0; i < width; printf(" "), i++);
    if(strlen(title) > 0) {
        accacia_gotoxy(x, y);
        accacia_textcolor(titlecolor);
        printf("%s", title);
    }
    accacia_textbackground(boxcolor);
    accacia_gotoxy(x, y+1);
}

void accacia_drawbottommargin(const int x, const int y, const int width, const int height,
                              const char *title, const ACCACIA_TEXT_COLOR titlecolor,
                              const ACCACIA_BACKGROUND_COLOR margincolor, const ACCACIA_BACKGROUND_COLOR boxcolor) {
    int i;
    if (!g_accacia_enabled) {
        return;
    }
    accacia_textbackground(margincolor);
    accacia_gotoxy(x, y + height);
    for(i = 0; i < width; printf(" "), i++);
    if(strlen(title) > 0) {
        accacia_gotoxy(x, y + height);
        accacia_textcolor(titlecolor);
        printf("%s", title);
    }
    accacia_textbackground(boxcolor);
    accacia_gotoxy(x, y);
}

void accacia_drawleftmargin(const int x, const int y, const int height, const ACCACIA_BACKGROUND_COLOR margincolor,
                            const ACCACIA_BACKGROUND_COLOR boxcolor) {
    int ytemp = y;
    if (!g_accacia_enabled) {
        return;
    }
    accacia_textbackground(margincolor);
    for(; ytemp <= y + height; accacia_gotoxy(x, ytemp), printf(" "), ytemp++);
    accacia_textbackground(boxcolor);
    accacia_gotoxy(x + 1, y);
}

void accacia_drawrightmargin(const int x, const int y, const int width, const int height,
                             const ACCACIA_BACKGROUND_COLOR margincolor, const ACCACIA_BACKGROUND_COLOR boxcolor) {
    int ytemp = y;
    if (!g_accacia_enabled) {
        return;
    }
    accacia_textbackground(margincolor);
    for(; ytemp <= y + height; accacia_gotoxy(x + width - 1, ytemp), printf(" "), ytemp++);
    accacia_textbackground(boxcolor);
    accacia_gotoxy(x, y);
}

void accacia_drawboxgine(const int x, const int y, const int width, const int height,
                         const ACCACIA_BACKGROUND_COLOR boxcolor, const ACCACIA_BACKGROUND_COLOR margincolor,
                         const char *toptitle, const ACCACIA_TEXT_COLOR toptitlecolor, const char *bottomtitle,
                         const ACCACIA_TEXT_COLOR bottomtitlecolor, const int margintop, const int marginbottom,
                         const int marginleft, const int marginright) {
    if (!g_accacia_enabled) {
        return;
    }
    accacia_drawbox(x, y, width, height, boxcolor);
    if (marginleft) {
        accacia_drawleftmargin(x, y, height, margincolor, boxcolor);
    }
    if (margintop) {
        accacia_drawtopmargin(x, y, width, toptitle, toptitlecolor, margincolor, boxcolor);
    }
    if (marginright) {
        accacia_drawrightmargin(x, y, width, height, margincolor, boxcolor);
    }
    if (marginbottom) {
        accacia_drawbottommargin(x, y, width, height, bottomtitle, bottomtitlecolor, margincolor, boxcolor);
    }
}

void accacia_drawboxwcharfillgine(const int x, const int y, const int width, const int height, const char charfill,
                                  const ACCACIA_TEXT_COLOR ccolor, const ACCACIA_BACKGROUND_COLOR boxcolor,
                                  const ACCACIA_BACKGROUND_COLOR margincolor, const char *toptitle,
                                  const ACCACIA_TEXT_COLOR toptitlecolor, const char *bottomtitle,
                                  const ACCACIA_TEXT_COLOR bottomtitlecolor, const int margintop,
                                  const int marginbottom, const int marginleft, const int marginright) {
    if (!g_accacia_enabled) {
        return;
    }
    accacia_drawboxwcharfill(x, y, width, height, charfill, ccolor, boxcolor);
    if (marginleft) {
        accacia_drawleftmargin(x, y, height, margincolor, boxcolor);
    }
    if (margintop) {
        accacia_drawtopmargin(x, y, width, toptitle, toptitlecolor, margincolor, boxcolor);
    }
    if (marginright) {
        accacia_drawrightmargin(x, y, width, height, margincolor, boxcolor);
    }
    if (marginbottom) {
        accacia_drawbottommargin(x, y, width, height, bottomtitle, bottomtitlecolor, margincolor, boxcolor);
    }
}

void accacia_gets(char *buf) {
    fgets(buf, sizeof(buf) * 8, stdin);
    buf[strlen(buf)-1] = 0;
}

int accacia_kbhit() {
#if !defined(_WIN32)
    int res;
    struct termios attr, oldattr;
    getc(stdout);
    //  Pete Wilson's based code
    tcgetattr(STDIN_FILENO, &attr);
    oldattr = attr;
    attr.c_lflag = ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &attr);
    ioctl(STDIN_FILENO, FIONREAD, &res);
    tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);
    return res;
#else
    return kbhit();
#endif
}

unsigned char accacia_getch(void) {
#if !defined(_WIN32)
    unsigned char c;
    struct termios attr, oldattr;
    getc(stdout);
    tcgetattr(STDIN_FILENO,&attr);
    oldattr = attr;
    attr.c_lflag = ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &attr);
    read(STDIN_FILENO, &c, 1);
    tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);
    return c;
#else
    return getch();
#endif
}

char accacia_getkey(void) {
#if !defined(_WIN32)
    int res;
    struct termios attr, oldattr;
    getc(stdout);
    tcgetattr(STDIN_FILENO, &attr);
    oldattr = attr;
    attr.c_lflag = ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &attr);
    res = accacia_getch();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);
    return res;
#else
    return 0;
#endif
}
