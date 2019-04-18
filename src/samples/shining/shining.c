/*
 *                                 (C) Copyright Rafael Santiago 2014
 *
 * This is free software. You can redistribute it and/or modify under
 * the terms of the GNU General Public License version 2.
 */
#include <accacia.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

int main(int argc, char **argv) {
    const char *text2type = "all work and no play makes jack a dull boy";
    const char *tp = text2type;
    int c = 0, t = 1000;
    ACCACIA_TEXT_COLOR ac[7] = {
        AC_TCOLOR_RED,
        AC_TCOLOR_GREEN,
        AC_TCOLOR_YELLOW,
        AC_TCOLOR_BLUE,
        AC_TCOLOR_MAGENTA,
        AC_TCOLOR_CYAN,
        AC_TCOLOR_WHITE
    };
    srand(time(0));
    while (!accacia_kbhit()) {
        c = rand() % 7;
        if (rand() % 2) {
            accacia_textstyle(AC_TSTYLE_BOLD);
        } else {
            accacia_textstyle(AC_TSTYLE_DEFAULT);
        }
        accacia_textcolor(ac[c]);
        c = rand() % 2;
        printf("%c", (c) ? *tp : toupper(*tp));
        c = rand() % 3;
        while (c-- > 0) {
            printf(" ");
        }
        if (*tp == 0) {
            tp = text2type;
        } else {
            tp++;
        }
        accacia_delay((rand() % 5) * t);
        if (rand() % 2) {
            t /= 10;
        } else {
            t += 10;
        }
    }
    accacia_screennormalize();
    return 0;
}