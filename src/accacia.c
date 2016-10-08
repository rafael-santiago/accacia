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
#include <sys/ioctl.h>
#include <fcntl.h>
#include <termios.h>
#include <string.h>

void accacia_gotoxy(const int x, const int y) {
    printf("\033[%d;%dH", y, x);
#if defined(__FreeBSD__)
    fflush(stdout);
#endif
}

void accacia_clrscr() {
    printf("\033[2J");
    accacia_gotoxy(1, 1);
#if defined(__FreeBSD__)
    fflush(stdout);
#endif
}

void accacia_cursorup(const int x) {
    printf("\033[%dA", x);
#if defined(__FreeBSD__)
    fflush(stdout);
#endif
}

void accacia_cursordown(const int x) {
    printf("\033[%dB", x);
#if defined(__FreeBSD__)
    fflush(stdout);
#endif
}

void accacia_cursorforward(const int y) {
    printf("\033[%dC", y);
#if defined(__FreeBSD__)
    fflush(stdout);
#endif
}

void accacia_cursorbackward(const int y) {
    printf("\033[%dD", y);
#if defined(__FreeBSD__)
    fflush(stdout);
#endif
}

void accacia_delline() {
    printf("\033[K");
#if defined(__FreeBSD__)
    fflush(stdout);
#endif
}

void accacia_savecursorposition() {
    printf("\033[s");
#if defined(__FreeBSD__)
    fflush(stdout);
#endif
}

void accacia_restorecursorposition() {
    printf("\033[u");
#if defined(__FreeBSD__)
    fflush(stdout);
#endif
}

void accacia_textcolor(const ACCACIA_TEXT_COLOR color) {
    int diff;
    int temp_color = color;
    if (color > 37) {
        diff   = color - 37;
        temp_color -= diff;
    } else if (color<30) {
        diff   = 30 - color;
        temp_color += diff;
    }
    printf("\033[%dm", temp_color);
#if defined(__FreeBSD__)
    fflush(stdout);
#endif
}

void accacia_textbackground(const ACCACIA_BACKGROUND_COLOR color) {
    int temp_color = color;
    if (color > 47) {
        temp_color = color | 40;
    } else if (color < 40) {
        temp_color += 40;
        temp_color = temp_color | 40;
    }
    printf("\033[%dm", temp_color);
#if defined(__FreeBSD__)
    fflush(stdout);
#endif
}

void accacia_screennormalize() {
    printf("\033[m");
#if defined(__FreeBSD__)
    fflush(stdout);
#endif
}

void accacia_textstyle(const ACCACIA_TEXT_STYLE style) {
    printf("\033[%dm", style);
#if defined(__FreeBSD__)
    fflush(stdout);
#endif
}

void accacia_drawbox(const int x, const int y, const int width, const int height, const ACCACIA_BACKGROUND_COLOR color) {
    int i, j, xtemp = x, ytemp = y;
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
    accacia_textbackground(margincolor);
    for(; ytemp <= y + height; accacia_gotoxy(x, ytemp), printf(" "), ytemp++);
    accacia_textbackground(boxcolor);
    accacia_gotoxy(x + 1, y);
}

void accacia_drawrightmargin(const int x, const int y, const int width, const int height,
                             const ACCACIA_BACKGROUND_COLOR margincolor, const ACCACIA_BACKGROUND_COLOR boxcolor) {
    int ytemp = y;
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
}

unsigned char accacia_getch() {
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
}

char accacia_getkey(void) {
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
}
