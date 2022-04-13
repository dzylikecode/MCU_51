/*
 * File:   main.c
 * Author: Hasee
 *
 * Created on February 27, 2022, 4:31 PM
 */

// PIC16F877A Configuration Bit Settings

// 'C' source line config statements

// CONFIG
#pragma config FOSC = HS   // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF  // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = ON  // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = OFF   // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF   // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF   // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF    // Flash Program Memory Code Protection bit (Code protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include "port.h"
#include "show.h"
#include "timer.h"
#include "input.h"

typedef enum
{ //设置四个状态,第四个是拓展
    event_show_3s,
    event_show_1s,
    event_clear,
    event_ex,
    event_none,
} event_t;

bool flag_1s = 0; //类似一秒中断
bool flag_3s = 0;

void timer_proc(void) //中断函数
{
    static uint8_t count_1s = 0;
    flag_1s = 1;
    if (++count_1s > 2)
    {
        count_1s = 0;
        flag_3s = 1;
    }
}

void main(void)
{
    set_A_digital_mode(); //配置A端口为数字输入
    uint8_t i = 0;
    set_pin(B0, 1);     //锁存器使能
    char str1[8] = {0}; //帧
    char str2[8] = {0};
    event_t event = event_none;
    start_clock_ex(timer_proc, 1250); // 1s
    uint8_t max_cols = get_animation_x_cols();
    uint8_t max_rows = get_animation_y_rows();
    while (1)
    {
        uint8_t key_value = scan_key(); //扫描按键
        switch (key_value)
        {
        case 0:
            break;
        case 1:
            i = 0;
            event = event_show_3s;
            break;
        case 2:
            i = 0;
            event = event_show_1s;
            break;
        case 4:
            i = 0;
            event = event_clear;
            break;
        case 3:
            event = event_ex;
            i = 0;
            break;
        }

        switch (event)
        {
        case event_show_3s:
            if (flag_3s)
            {

                get_frame(str1, str2, i * 8);
                i++;
                if (i > 4)
                {
                    i = 0;
                }
                flag_3s = 0;
            }

            break;

        case event_show_1s:
            if (flag_1s)
            {
                get_frame_scroll_y(str1, str2, i);
                i++;
                if (i > max_rows - 8)
                {
                    i = 0;
                }
                flag_1s = 0;
            }
            break;
        case event_clear:
            empty_frame(str1, str2); //清空
            break;
        case event_ex:
            if (flag_1s)
            {
                get_frame_scroll_x(str1, str2, i);
                i++;
                if (i > max_cols - 16)
                {
                    i = 0;
                }
                flag_1s = 0;
            }
            break;
        case event_none:
            break;
        }
        show_frame(str1, str2);
    }
    return;
}
