#include "apilib.h"

void HariMain(void){
    char buf[150 * 50];
    int win;
    win = api_openwin(buf, 150, 50, -1, "hello");
    api_boxfilwin(win,  8, 36, 141, 43, 6 /*blue*/);
    api_putstrwin(win, 28, 28, 0 /*black*/, 14, "hello, world 3");
    for (;;) {
        if (api_getkey(1) == 0x0a) {
            break;
        }
    }
    api_closewin(win);
    api_end();
}
