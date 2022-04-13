/*
 * File:   keyboard.c
 * Author: Hasee
 *
 * Created on February 26, 2022, 6:08 PM
 */

#include "port.h"

static uint8_t key_x = 0;
static uint8_t key_y = 0;

#define rp1 A4
#define rp2 A5
#define rp3 E0
#define rp4 E1
#define init_rp() set_A_digital_mode()

#define cp1 A0
#define cp2 A1
#define cp3 A2
#define cp4 A3
#define init_cp() set_A_digital_mode()

uint8_t scan_x()
{
    init_rp();
    uint8_t res = 0;
    set_pin(rp1, 1);
    set_pin(rp2, 1);
    set_pin(rp3, 1);
    set_pin(rp4, 1);
    set_pin(cp1, 0);
    set_pin(cp2, 0);
    set_pin(cp3, 0);
    set_pin(cp4, 0);
    if (get_pin(rp1) == 0)
        res = 1;
    else if (get_pin(rp2) == 0)
        res = 2;
    else if (get_pin(rp3) == 0)
        res = 3;
    else if (get_pin(rp4) == 0)
        res = 4;

    return res;
}

uint8_t scan_y()
{
    init_rp();
    uint8_t res = 0;
    set_pin(rp1, 0);
    set_pin(rp2, 0);
    set_pin(rp3, 0);
    set_pin(rp4, 0);
    set_pin(cp1, 1);
    set_pin(cp2, 1);
    set_pin(cp3, 1);
    set_pin(cp4, 1);
    if (get_pin(cp1) == 0)
        res = 1;
    else if (get_pin(cp2) == 0)
        res = 2;
    else if (get_pin(cp3) == 0)
        res = 3;
    else if (get_pin(cp4) == 0)
        res = 4;

    return res;
}

void scan_keyboard()
{
    key_x = scan_x();
    key_y = scan_y();
}
uint8_t get_key_x()
{
    return key_x;
}
uint8_t get_key_y()
{
    return key_y;
}
bool is_key_pressed()
{
    return key_x == 0 || key_y == 0;
}
