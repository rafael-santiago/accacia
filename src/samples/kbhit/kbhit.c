/*
 *                                 (C) Copyright Rafael Santiago 2014
 *
 * This is free software. You can redistribute it and/or modify under
 * the terms of the GNU General Public License version 2.
 */
#include <accacia.h>
#include <stdio.h>

int main(int argc, char **argv) {
    unsigned char k = 'i';
    printf("Type Esc to exit...\n");
    do {
        if (accacia_kbhit()) {
            k = accacia_getch();
        }
    } while (k != 27);
    printf("\n");
    return 0;
}
