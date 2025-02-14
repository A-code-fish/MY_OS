/* mouse code */

#include "bootpack.h"

struct FIFO32 *mousefifo;
int mousedata0;

void enable_mouse(struct FIFO32 *fifo, int data0, struct MOUSE_DEC *mdec){
    mousefifo = fifo;
    mousedata0 = data0;
    /* Mouse effective */
    wait_KBC_sendready();
    io_out8(PORT_KEYCMD, KEYCMD_SENDTO_MOUSE);
    wait_KBC_sendready();
    io_out8(PORT_KEYDAT, MOUSECMD_ENABLE);
    /* If all goes well, ACK(0xfa) will be sent */
    mdec->phase = 0; /* Wait for the phase 0xfa */
    return;
}

int mouse_decode(struct MOUSE_DEC *mdec, unsigned char dat){
    if (mdec->phase == 0) {
        /* Wait for the mouse's 0xfa phase */
        if (dat == 0xfa) {
            mdec->phase = 1;
        }
        return 0;
    }
    if (mdec->phase == 1) {
        /* The phase of waiting for the first byte of the mouse */
        if ((dat & 0xc8) == 0x08) {
            /* If the first byte is correct */
            mdec->buf[0] = dat;
            mdec->phase = 2;
        }
        return 0;
    }
    if (mdec->phase == 2) {
        /* The phase of waiting for the second byte of the mouse */
        mdec->buf[1] = dat;
        mdec->phase = 3;
        return 0;
    }
    if (mdec->phase == 3) {
        /* The phase of waiting for the third byte of the mouse */
        mdec->buf[2] = dat;
        mdec->phase = 1;
        mdec->btn = mdec->buf[0] & 0x07;
        mdec->x = mdec->buf[1];

        mdec->y = mdec->buf[2];
        if ((mdec->buf[0] & 0x10) != 0) {
            mdec->x |= 0xffffff00;
        }
        if ((mdec->buf[0] & 0x20) != 0) {
            mdec->y |= 0xffffff00;
        }
        mdec->y = - mdec->y; /* The y direction of the mouse is opposite to the screen symbol */
        return 1;
    }
    return -1;
}

/* Interrupt from PS/2 mouse */
void inthandler2c(int *esp){
    int data;
    io_out8(PIC1_OCW2, 0x64);   /* Inform PIC1 IRQ-12 has been processed */
    io_out8(PIC0_OCW2, 0x62);   /* Inform PIC0 IRQ-02 has been processed */
    data = io_in8(PORT_KEYDAT);
    fifo32_put(mousefifo, data + mousedata0);
    return;
}

