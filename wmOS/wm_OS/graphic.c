//Tracing process
#include "bootpack.h"

void init_palette(void){
	static unsigned char table_rgb[16 * 3] = {
		0x00, 0x00, 0x00,	/*  0: */
		0xff, 0x00, 0x00,	/*  1: */
		0x00, 0xff, 0x00,	/*  2: */
		0xff, 0xff, 0x00,	/*  3: */
		0x00, 0x00, 0xff,	/*  4: */
		0xff, 0x00, 0xff,	/*  5: */
		0x00, 0xff, 0xff,	/*  6: */
		0xff, 0xff, 0xff,	/*  7: */
		0xc6, 0xc6, 0xc6,	/*  8: */
		0x84, 0x00, 0x00,	/*  9: */
		0x00, 0x84, 0x00,	/* 10: */
		0x84, 0x84, 0x00,	/* 11: */
		0x00, 0x00, 0x84,	/* 12: */
		0x84, 0x00, 0x84,	/* 13: */
		0x00, 0x84, 0x84,	/* 14: */
		0x84, 0x84, 0x84	/* 15: */
	};
	unsigned char table2[216 * 3];
    int r, g, b;
    set_palette(0, 15, table_rgb);
    for (b = 0; b < 6; b++) {
        for (g = 0; g < 6; g++) {
            for (r = 0; r < 6; r++) {
                table2[(r + g * 6 + b * 36) * 3 + 0] = r * 51;
                table2[(r + g * 6 + b * 36) * 3 + 1] = g * 51;
                table2[(r + g * 6 + b * 36) * 3 + 2] = b * 51;
            }
        }
    }
    set_palette(16, 231, table2);
	return;
}

void set_palette(int start, int end, unsigned char *rgb){
	int i, eflags;
	eflags = io_load_eflags();
	io_cli(); 			
	io_out8(0x03c8, start);
	for (i = start; i <= end; i++){
		io_out8(0x03c9, rgb[0] / 4);
		io_out8(0x03c9, rgb[1] / 4);
		io_out8(0x03c9, rgb[2] / 4);
		rgb += 3;
	}
	io_store_eflags(eflags);
	return;
}

void boxfill8(unsigned char *vram, int xsize, unsigned char c, int x0, int y0, int x1, int y1){
	int x, y;
	for (y = y0; y <= y1; y++){
		for (x = x0; x <= x1; x++)
			vram[y * xsize + x] = c;
	}
	return;
}

void init_screen8(char *vram, int x, int y){
	//background
	boxfill8(vram, x, C_BACKBROUND, 0, 0, x - 1, y - 29);
    putfonts8_asc(vram, x, 600, 600, COL8_FFFFFF, "wm_OS");
	//taskbar
	boxfill8(vram, x, COL8_C6C6C6, 0, y - 28, x - 1, y - 28);
	boxfill8(vram, x, COL8_FFFFFF, 0, y - 27, x - 1, y - 27);
	boxfill8(vram, x, COL8_C6C6C6, 0, y - 26, x - 1, y -  1);
	//start
	boxfill8(vram, x, COL8_FFFFFF, 3, y - 24, 59, y - 24);
	boxfill8(vram, x, COL8_FFFFFF, 2, y - 24,  2, y - 4);
	boxfill8(vram, x, COL8_848484, 3, y - 4, 59, y - 4);
	boxfill8(vram, x, COL8_848484, 59, y - 23, 59, y - 5);
	boxfill8(vram, x, COL8_000000, 2, y - 3, 59, y - 3);
	boxfill8(vram, x, COL8_000000, 60, y - 24, 60, y - 3);
	//date
	boxfill8(vram, x, COL8_848484, x - 47, y - 24, x - 4, y - 24);
	boxfill8(vram, x, COL8_848484, x - 47, y - 23, x - 47, y - 4);
	boxfill8(vram, x, COL8_FFFFFF, x - 47, y - 3, x - 4, y - 3);
	boxfill8(vram, x, COL8_FFFFFF, x - 3, y - 24, x - 3, y - 3);
	return;
}

void putfont8(char *vram, int xsize, int x, int y, char c, char *font){
    int i;
    char *p, d;
    for (i = 0; i < 16; i++) {
        p = vram + (y + i) * xsize + x;
        d = font[i];
        if ((d & 0x80) != 0) p[0] = c; 
        if ((d & 0x40) != 0) p[1] = c; 
        if ((d & 0x20) != 0) p[2] = c; 
        if ((d & 0x10) != 0) p[3] = c; 
        if ((d & 0x08) != 0) p[4] = c; 
        if ((d & 0x04) != 0) p[5] = c; 
        if ((d & 0x02) != 0) p[6] = c; 
        if ((d & 0x01) != 0) p[7] = c; 
    }
    return;
}

void putfonts8_asc(char *vram, int xsize, int x, int y, char c, unsigned char *s){
    extern char hankaku[4096];
    for (; *s != 0x00; s++) {
        putfont8(vram, xsize, x, y, c, hankaku + *s * 16);
        x += 8;
    }

}

void putblock8_8(char *vram, int vxsize, int pxsize,int pysize, int px0, int py0, char *buf, int bxsize){
    int x, y;
    for (y = 0; y < pysize; y++) {
        for (x = 0; x < pxsize; x++) {
            vram[(py0 + y) * vxsize + (px0 + x)] = buf[y * bxsize + x];
        }
    }
    return;
}

void init_mouse_cursor8(char *mouse, char bc){
    static char cursor[16][16] = {
        "................",
        "*************...",
        "*OOOOOOOOO*.....",
        "*OOOOOOOO*......",
        "*OOOOOOO*.......",
        "*OOOOOO*........",
        "*OOOOOO*........",
        "*OOOOOOO*.......",
        "*OOO**OOO*......",
        "*OO*..*OOO*.....",
        "*O*....*OOO*....",
        "**......*OOO*...",
        "*........*OOO*..",
        "..........*OOO*.",
        "...........*OO*.",
        "............***."
    };
    
	int x, y;
    for (y = 0; y < 16; y++) {
        for (x = 0; x < 16; x++) {
            if (cursor[y][x] == '*') {
                mouse[y * 16 + x] = COL8_000000;
            }
            if (cursor[y][x] == 'O') {
                mouse[y * 16 + x] = COL8_FFFFFF;
            }
            if (cursor[y][x] == '.') {
                mouse[y * 16 + x] = bc;
            }
        }
    }
    return;
}
