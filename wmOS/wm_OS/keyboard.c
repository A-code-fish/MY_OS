/* Keyboard code */

#include "bootpack.h"
// struct KEYBUF keybuf;
struct FIFO32 *keyfifo;
int keydata0;
void wait_KBC_sendready(void){
    /* Wait until the keyboard control circuit is ready */
    for (;;) {
        if ((io_in8(PORT_KEYSTA) & KEYSTA_SEND_NOTREADY) == 0) {
            break;
        }
    }
    return;
}

void init_keyboard(struct FIFO32 *fifo, int data0){
    /* Initialize the keyboard control circuit */
    keyfifo = fifo;
    keydata0 = data0;
    wait_KBC_sendready();
    io_out8(PORT_KEYCMD, KEYCMD_WRITE_MODE);
    wait_KBC_sendready();
    io_out8(PORT_KEYDAT, KBC_MODE);
    return;
}

/* Interrupt from PS/2 keyboard */
void inthandler21(int *esp){
    int data;
	io_out8(PIC0_OCW2, 0x61); /* Inform PIC IRQ-01 has been processed */
	data = io_in8(PORT_KEYDAT);
    fifo32_put(keyfifo, data + keydata0);
	return;
}
