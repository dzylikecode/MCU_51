/*
 * File:   main.c
 * Author: Hasee
 *
 * Created on February 25, 2022, 7:21 PM
 */
#include "input.h"
#include "port.h"
#include "show.h"

void main(void)
{
    while (1)
    {
        scan_keyboard();
        static char buffer[9] = {"12345678"};
        static uint8_t buf_size = 2;
        if (is_key_pressed())
        {
            uint8_t pos_x = get_key_x();
            uint8_t pos_y = get_key_y();
            uint8_t index = pos_x + pos_y * 4;
            char ch = '0' + index;
            buffer[buf_size++] = ch;
        }
        static uint8_t i = 0;
        i++;
        i %= 8;
        gotoxy(i, 0);
        putch(buffer[i]);
    }
    return;
}
