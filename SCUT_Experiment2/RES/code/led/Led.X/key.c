/*
 * File:   key.c
 * Author: Hasee
 *
 * Created on March 1, 2022, 3:11 PM
 */


#include "input.h"
#include "port.h"

#define KEY1 B4
#define KEY2 B5
#define KEY3 B1
#define KEY4 B2

uint8_t scan_key()
{
    uint8_t key_value = 0;
    // set_pin(KEY1, 1);
    // set_pin(KEY2, 1);
    // set_pin(KEY3, 1);
    // set_pin(KEY4, 1);
    if (get_pin(KEY1) == 0)
    {
        key_value = 1;
    }
    else if (get_pin(KEY2) == 0)
    {
        key_value = 2;
    }
    else if (get_pin(KEY3) == 0)
    {
        key_value = 3;
    }
    else if (get_pin(KEY4) == 0)
    {
        key_value = 4;
    }
    return key_value;
}

