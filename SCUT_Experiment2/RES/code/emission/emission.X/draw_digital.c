/*
 * File:   draw_digital.c
 * Author: Hasee
 *
 * Created on February 26, 2022, 8:10 PM
 */
#include "port.h"

char character[] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f, 0x77, 0x7c, 0x39, 0x5e, 0x79, 0x71};

#define digit_a_p D6
#define digit_b_p D5
#define digit_c_p D4
#define digit_d_p D3
#define digit_e_p D2
#define digit_f_p D1
#define digit_g_p D0
#define digit_dp_p D7

#define segment_on(x) (!(x))
#define set_digit_segment(symbol, value) set_pin(digit_##symbol##_p, \
                                                 segment_on(value))

void draw_character(uint8_t shape)
{
    set_digit_segment(dp, shape & 0x80);
    set_digit_segment(a, shape & 0x40);
    set_digit_segment(b, shape & 0x20);
    set_digit_segment(c, shape & 0x10);
    set_digit_segment(d, shape & 0x08);
    set_digit_segment(e, shape & 0x04);
    set_digit_segment(f, shape & 0x02);
    set_digit_segment(g, shape & 0x01);
}

void putch(char ch)
{
    int8_t index = -1;
    switch (ch)
    {
    case '0':
        index = 0;
        break;
    case '1':
        index = 1;
        break;
    case '2':
        index = 2;
        break;
    case '3':
        index = 3;
        break;
    case '4':
        index = 4;
        break;
    case '5':
        index = 5;
        break;
    case '6':
        index = 6;
        break;
    case '7':
        index = 7;
        break;
    case '8':
        index = 8;
        break;
    case '9':
        index = 9;
        break;
    case 'A':
        index = 10;
        break;
    case 'B':
        index = 11;
        break;
    case 'C':
        break;
    case 'D':
        index = 12;
        break;
    case 'E':
        index = 13;
        break;
    case 'F':
        index = 14;
        break;
    default:
        index = -1;
        break;
    }
    if (index != -1)
    {
        draw_character(character[index]);
    }
}
#define TEMP_1_1 C3
#define TEMP_1_2 C2
#define TEMP_1_3 C0
#define TEMP_1_4 B5
#define TEMP_2_1 B4
#define TEMP_2_2 C7
#define TEMP_2_3 C5
#define TEMP_2_4 C4

#define X0 TEMP_1_1
#define X1 TEMP_1_2
#define X2 TEMP_1_3
#define X3 TEMP_1_4
#define X4 TEMP_2_1
#define X5 TEMP_2_2
#define X6 TEMP_2_3
#define X7 TEMP_2_4

#define Set_Byte_Logical Set_Digital
#include "template.h"

void gotoxy(uint8_t x, uint8_t y)
{
    if (y != 0)
    {
        y = 0;
    }
    if (x >= 8)
    {
        x = 7;
    }
    Set_Digital(1 << (7 - x));
}

void clear_screen(void)
{
    Set_Digital(0x00);
}

void putstr(const char *str, uint8_t count)
{
    uint8_t i = 0;
    if (count > 8)
    {
        count = 8;
    }
    while (i < count)
    {
        clear_screen();
        gotoxy(i, 0);
        putch(str[count - i - 1]);
        i++;
    }
}
