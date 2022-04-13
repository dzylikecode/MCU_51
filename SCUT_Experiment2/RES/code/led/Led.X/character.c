/*
 * File:   character.c
 * Author: Hasee
 *
 * Created on February 28, 2022, 5:09 PM
 */

#include "port.h"
#include "show.h"

//字库
const char S[] = { 0x00, 0x3c, 0x66, 0x60, 0x3c, 0x06, 0x66, 0x3c };

const char C[] = { 0x00, 0x3c, 0x66, 0x60, 0x60, 0x60, 0x66, 0x3c };

const char U[] = { 0x00, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x3e };

const char T[] = { 0x00, 0x7e, 0x5a, 0x18, 0x18, 0x18, 0x18, 0x18 };

const char mu[] = { 0x10, 0x10, 0xfe, 0x38, 0x74, 0xd2, 0x91, 0x10 };

const char ji[] = { 0x3c, 0x24, 0x24, 0x24, 0x24, 0x45, 0x45, 0x87 };

const char dian[] = { 0x10, 0x7e, 0x52, 0x7e, 0x52, 0x7e, 0x11, 0x1f };

const char love[] = { 0x00, 0x66, 0xff, 0xff, 0x7e, 0x3c, 0x18, 0x00 };

const char empty[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

const char I[] = { 0x00, 0x3c, 0x18, 0x18, 0x18, 0x18, 0x18, 0x3c };

const char* animation[][2] = {
    //字库数组
    { S, C },
    { U, T },
    { mu, ji },
    { dian, love },
    { empty, empty },
};

const char* animation_x[] = {
    love,
    0,
    love,
    S,
    C,
    U,
    T,
    mu,
    0,
    ji,
    0,
    dian,
    love,
    empty,
    empty,
    I,
    love,
    S,
    C,
    U,
    T,
    empty,
    empty,
};

const char* animation_y[][2] = {
    { love, love },
    { S, C },
    { U, T },
    { 0, 0 },
    { mu, ji },
    { 0, 0 },
    { dian, love },
    { empty, empty },
};

#define SCROLL_COLS sizeof(animation_x) / sizeof(animation_x[0])
#define SCROLL_ROWS sizeof(animation_y) / sizeof(animation_y[0])

#define ROW_ALL (sizeof(animation) / sizeof(animation[0])) //行数

uint8_t get_ch_row()
{
    return ROW_ALL;
}

/**
 * @brief 获取每一行字符
 *
 * @param buff1
 * @param buff2
 * @param pos 帧和位置
 */
void get_frame(char* buff1, char* buff2, uint8_t pos)
{
    uint8_t ch_y = pos / 8; //获取第几个字
    uint8_t ch_y_mod = pos % 8; //第几个字的第几行
    char* temp_ch_0 = animation[ch_y][0]; //取出对应第几个字
    char* temp_ch_1 = animation[ch_y][1];
    for (uint8_t i = 0; i < 8; i++) {
        buff1[i] = temp_ch_0[ch_y_mod];
        buff2[i] = temp_ch_1[ch_y_mod];
        ch_y_mod++;
        if (ch_y_mod == 8) //如果到达最后一行,取下一个字
        {
            ch_y_mod = 0;
            ch_y++;
            temp_ch_0 = animation[ch_y][0];
            temp_ch_1 = animation[ch_y][1];
        }
    }
}

uint8_t get_animation_x_cols()
{
    uint8_t zero_count = 0;
    uint8_t nzero_count = 0;
    for (uint8_t i = 0; i < SCROLL_COLS; i++) {
        if (animation_x[i] == 0) {
            zero_count++;
        } else {
            nzero_count++;
        }
    }
    return zero_count + nzero_count * 8;
}

uint8_t get_animation_y_rows()
{
    uint8_t zero_count = 0;
    uint8_t nzero_count = 0;
    for (uint8_t i = 0; i < SCROLL_ROWS; i++) {
        if (animation_y[i][0] == 0) {
            zero_count++;
        } else {
            nzero_count++;
        }
    }
    return zero_count + nzero_count * 8;
}

#define STATIC
#define Get_Animate_Index get_animation_x
#define ANIMATION(x) animation_x[x]
#include "template.h"

#define STATIC
#define Get_Animate_Index get_animation_y
#define ANIMATION(x) animation_y[x][0]
#include "template.h"

static void set_buff_col(char buff[], uint8_t col, char* ch, uint8_t ch_col)
{
    for (uint8_t i = 0; i < 8; i++) {
        uint8_t temp_bit = get_bit(ch[i], 7 - ch_col); //设计的最高为逻辑0开始
        if (temp_bit)
            set_bit(buff[i], 7 - col); //设计的最高为逻辑0开始
        else
            cls_bit(buff[i], 7 - col); //设计的最高为逻辑0开始
    }
}

static void scroll_x(char* buff, uint8_t pos_x)
{
    uint8_t temp_ch_index = 0;
    uint8_t ch_x = 0;
    for (uint8_t i = 0; i < 8; i++) {
        temp_ch_index = get_animation_x(pos_x, &ch_x);
        pos_x++;
        set_buff_col(buff, i, animation_x[temp_ch_index], ch_x);
    }
}

void get_frame_scroll_x(char* buff1, char* buff2, uint8_t pos)
{
    scroll_x(buff1, pos);
    scroll_x(buff2, pos + 8);
}

void get_frame_scroll_y(char* buff1, char* buff2, uint8_t pos)
{
    uint8_t temp_ch_index = 0;
    uint8_t ch_y = 0;
    for (uint8_t i = 0; i < 8; i++) {
        temp_ch_index = get_animation_y(pos, &ch_y);
        pos++;
        buff1[i] = animation_y[temp_ch_index][0][ch_y];
        buff2[i] = animation_y[temp_ch_index][1][ch_y];
    }
}

void empty_frame(char* buff1, char* buff2)
{
    for (uint8_t i = 0; i < 8; i++) {
        buff1[i] = 0x00;
        buff2[i] = 0x00;
    }
}