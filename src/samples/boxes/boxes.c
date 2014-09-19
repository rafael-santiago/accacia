#include <accacia.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

struct box_geometrics {
    int x, y;
    int w, h;
    int direction_x;
    int direction_y;
    ACCACIA_BACKGROUND_COLOR c;
};

int main(int argc, char **argv) {
    struct box_geometrics boxes[BOXES_NR];
    size_t b;
    srand(time(0));
    for (b = 0; b < BOXES_NR; b++) {
        boxes[b].x = rand() % 120;
        boxes[b].y = rand() % 45;
        boxes[b].w = 2;
        boxes[b].h = 1;
        boxes[b].direction_x = 0;
        boxes[b].direction_y = 0;
        boxes[b].c = (ACCACIA_BACKGROUND_COLOR)((rand() % 6) + 41);
    }
    accacia_clrscr();
    accacia_textstyle(AC_TSTYLE_BOLD);
    do {
        accacia_textcolor(AC_TCOLOR_RED);
        accacia_gotoxy(1,1); printf("WARNING: this will be rather boring.... press any key...\n");
        accacia_delay(100);
        accacia_textcolor(AC_TCOLOR_BLACK);
        accacia_gotoxy(1,1); printf("WARNING: this will be rather boring.... press any key...\n");
        accacia_delay(100);
    } while(!accacia_kbhit());
    accacia_getch();
    accacia_clrscr();
    while (!accacia_kbhit()) {
        for (b = 0; b < BOXES_NR; b++) {
            accacia_drawbox(boxes[b].x, boxes[b].y, boxes[b].w, boxes[b].h, boxes[b].c);
            accacia_gotoxy(1,1);
            fflush(stdout);
        }
        accacia_delay(150);
        for (b = 0; b < BOXES_NR; b++) {
            accacia_drawbox(boxes[b].x, boxes[b].y, boxes[b].w, boxes[b].h, AC_BCOLOR_BLACK);
            if (boxes[b].x < 120 && boxes[b].direction_x == 0) {
                boxes[b].x += 1;
            } else {
                if (boxes[b].direction_x == 0) {
                    boxes[b].direction_x = 1;
                    boxes[b].c = (ACCACIA_BACKGROUND_COLOR)((rand() % 6) + 41);
                }
                if (boxes[b].x > 5) {
                    boxes[b].x -= 1;
                } else {
                    boxes[b].direction_x = 0;
                    boxes[b].c = (ACCACIA_BACKGROUND_COLOR)((rand() % 6) + 41);
                }
            }
            if (boxes[b].y < 45 && boxes[b].direction_y == 0) {
                boxes[b].y += 1;
            } else {
                if (boxes[b].direction_y == 0) {
                    boxes[b].direction_y = 1;
                    boxes[b].c = (ACCACIA_BACKGROUND_COLOR)((rand() % 6) + 41);
                }
                if (boxes[b].y > 3) {
                    boxes[b].y -= 1;
                } else {
                    boxes[b].direction_y = 0;
                    boxes[b].c = (ACCACIA_BACKGROUND_COLOR)((rand() % 6) + 41);
                }
            }
        }
    }
    accacia_clrscr();
    accacia_screennormalize();
    printf("Duh!\n");
    return 0;
}
