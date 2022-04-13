#include <reg52.h>
#include <intrins.h>

typedef unsigned char u8;

u8 data dis_digit;
u8 code dis_code[11]={0xc0,0xf9,0xa4,0xb0,0x99,//数码管段选为0 1 2 3 4 
                0x92,0x82,0xf8,0x80,0x90,0xff};//5 6 7 8 9 off

u8
