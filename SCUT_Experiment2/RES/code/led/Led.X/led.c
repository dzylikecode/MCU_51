/*
 * File:   led.c
 * Author: Hasee
 *
 * Created on February 27, 2022, 8:06 PM
 */

#include "port.h"

#define Set_Byte_Logical Set_Led1_Col
#define X0 C3
#define X1 C2
#define X2 C1
#define X3 C0
#define X4 C4
#define X5 C5
#define X6 C6
#define X7 C7

#define FLIP
#include "template.h"

#define Set_Byte_Logical Set_Led2_Col
#define X0 D0
#define X1 D1
#define X2 D2
#define X3 D3
#define X4 D4
#define X5 D5
#define X6 D6
#define X7 D7

#define FLIP
#include "template.h"

#define Set_Byte_Logical Set_Led_Row

#define X0 A4
#define X1 A5
#define X2 E0
#define X3 E1
#define X4 A3
#define X5 A2
#define X6 A1
#define X7 A0

#include "template.h"

void plotxy(uint8_t x, uint8_t y, uint8_t led)      //用于测试
{
    uint8_t row = 1 << y;
    uint8_t col = 1 << x;
    Set_Led_Row(row);
    if (led == 0)
    {
        Set_Led1_Col(col);
    }
    else
    {
        Set_Led2_Col(col);
    }
}

static void delay(uint16_t ms) {            //消影延时函数
    uint16_t i;
    for (i = 0; i < ms; i++) {
    }
}

void clear_screen(void)     //消影
{
    Set_Led_Row(0x00);
    Set_Led1_Col(0x00);
    Set_Led2_Col(0x00);
}

void show_frame(uint8_t ch1[], uint8_t ch2[])       //显示帧
{
    for (uint8_t i = 0; i < 8; i++)
    {
        Set_Led_Row(1 << i);
        Set_Led1_Col(ch1[7 - i]);           //逆序显示
        Set_Led2_Col(ch2[7 - i]);
        // 消影
        Set_Led_Row(0x00);
        delay(10);
        clear_screen();
    }
}



