/****************************************************************
 * 任务：实现按下矩阵按键，数码管就显示矩阵按键代表的字符
 *       总计16个按键，对应着0，1，...，9，a，...，f
 *  
 * **************************************************************
*/
#include <intrins.h>
#include <reg52.h>

typedef unsigned int u32; //定义可移植的类型
typedef unsigned char u8; //定义可移植的类型

#define PSEG P0 //控制数码管显示的I/O口
#define PKEY P1 //矩阵按键的I/O口

sbit C0 = P2 ^ 0; //控制第1个数码管输出的片选

void delayms(u32); //延时函数声明
u8 scan(void); //按键扫面函数声明

u8 code seg[] = { 0xc0, 0xf9, 0xa4, 0xb0, 0x99, //数码管段选为0 1 2 3 4
    0x92, 0x82, 0xf8, 0x80, 0x90, //5 6 7 8 9
    0x88, 0x83, 0xc6, 0xa1, 0x86, 0x8e }; //a, b, c, d, e, f

void main(void)
{
    u8 key; //声明变量 按键
    C0 = 1; //第1个数码管被选中
    while (1) {
        key = scan(); //读取键盘值
        if (key != 16) //判断按键是否有效，不为16则有效
            PSEG = seg[key]; //控制数码管段选，显示数码
    }
}

void delayms(u32 j)
{
    u8 i;
    while (j--) { //执行 j 次,一次大概5ms
        i = 250; //大概2.5ms
        while (--i) //100 约为 1 ms
            ;
        i = 249; //大概 2.5ms
        while (--i) //100 约为 1 ms
            ;
    }
}

u8 scan(void)
{
    u8 k = 16, m, n, in;
    PKEY = 0xf0; //行赋值0，列赋值1
    if ((PKEY & 0xf0) != 0xf0) { //如果按键按下，则某一列的1变成0
        for (m = 0; m < 4; m++) { //循环行扫描
            PKEY = ~(0x01 << m); //指定一行赋0，其他行列赋值1
            for (n = 0; n < 4; n++) { //循环判断列的状态
                in = PKEY; //暂存PKEY的状态
                in = in >> (4 + n); //将对应列的状态移位到最低位
                if ((in & 0x01) == 0) { //如果由原来的1变为0，说明按键按下
                    delayms(10); //消抖
                    if ((in & 0x01) == 0) { //再次判断是否按下
                        k = n + m * 4; //当前行和列确定按键的位置
                        break;
                    }
                }
            }
            if (k != 16) //k不等于16说明有按键已经按下
                break;
        }
    }
    return k; //返回按键按下的位置
}
