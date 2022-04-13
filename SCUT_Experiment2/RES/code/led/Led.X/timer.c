/*
 * File:   timer.c
 * Author: Hasee
 *
 * Created on February 28, 2022, 4:50 PM
 */

#include "port.h"
#include "timer.h"

static int count_10ms = 0; //溢出次数

static timer_callback_t callback = 0;
/**
 * @brief 定时器初始化
 *
 * @param timer_proc
 * @param base_clip 10ms 作为基底
 */
void start_clock(timer_callback_t timer_proc, uint32_t base_clip)
{
    INTCON = 0b11100000;
    T2CON = 0b01111111;
    TMR2IE = 1;
    PR2 = 256 - 217; // 10ms
    count_10ms = base_clip;
    callback = timer_proc;
}

// void interrupt timer_never_use_name(void)
// {
//     static uint8_t in_count_10ms = 0;
//     if (TMR2IF == 1)
//     {
//         TMR2IF = 0;

//         if (++in_count_10ms > count_10ms)
//         {
//             in_count_10ms = 0;
//             if (callback)
//             {
//                 callback();
//             }
//         }
//     }
// }



/*----------------函数功能：
	    中断 定时器1
--------------------------*/

// __CONFIG(0xFF32);//芯片配置字，看门狗关，上电延时开，掉电检测关，低压编程关
// //__CONFIG(HS&WDTDIS&LVPDIS);



/*-----------主函数--------------*/
void start_clock_ex(timer_callback_t timer_proc, uint32_t base_clip)
{	
	// The corresponding data direction register is TRISA. 
	// Setting  a TRISA bit (= 1) will make the corresponding PORTA pi an input. 
	// Clearing a TRISA bit (= 0) will make the corresponding PORTA pin an output.
	TRISD=0xfe;				//设置数据方向 RD7-RD1为输入，RD0为输出



	// 1 = Port pin is > VIH，即高电平  ;  0 = Port pin is < VIL，即低电平
	PORTD=0X00;				//端口赋初值


	
	/********定时器TMR1初始化**********/
	// Timer1 can operate in one of two modes: (1)As a Timer ;(2)As a Counter
	// The operating mode is determined by the clock select bit, TMR1CS 
	// In Timer mode, Timer1 increments every instruction cycle. 
	// In Counter mode, it increments on every rising edge of the external clock input
	// Counter mode is selected by setting  bit TMR1CS. 1 = External clock from pin RC0/T1OSO/T1CKI (on the rising edge)
	// Timer mode   is selected by clearing the TMR1CS. 0 = Internal clock (FOSC/4)	
	TMR1CS=0;				// TMR1时钟源选择内部指令周期（fosc/4）
	


	// T1CKPS1:T1CKPS0: Timer1 Input Clock Prescale Select bits  预分频器
	//预分频 1:1，对应的编码为00
	//T1CKPS0=0;			// 00 = 1:1 prescale value
	//T1CKPS1=0;
	//预分频 1:8，对应的编码为11
	T1CKPS0=1;				// 11 = 1:8 prescale value
	T1CKPS1=1;



	// Timer1 External Clock Input Synchronization Control bit
	// When TMR1CS = 1. 1 = Do not synchronize external clock input.   0 = Synchronize external clock input 
	// When TMR1CS = 0. This bit is ignored. Timer1 uses the internal clock when TMR1CS = 0.
	// The synchronize control bit, T1SYNC. has no effect since the internal clock is always in sync
	// T1SYNC=0;			// 由于TMR1CS = 0，所以这一位被忽略了



	// Timer1 can be enabled/disabled by setting/clearing control bit, TMR1ON
	// TMR1ON: Timer1 On bit.   1 = Enables Timer1;  0 = Stops Timer1
	TMR1ON=1;				//打开计数定时器TMR1,状态为ON



	// The Timer1 module is a 16-bit timer/counter consisting of two 8-bit registers (TMR1H and TMR1L)
	// which are readable and writable. 
	//16位计数寄存器给初值，在这里没有考虑中断所造成的时钟延迟13个指令周期
	TMR1H=(65536-100)/256; 	//定时100us*8(八分频)，计数寄存器就会溢出
	TMR1L=(65536-100)%256; 			


	
	// The TMR1 interrupt, if enabled,is generated on overflow 
	// which is latched in interrupt flag bit, TMR1IF 
	TMR1IF=0;				//溢出中断标志位清零



	// This interrupt can be enabled/disabled by setting/clearing TMR1 interrupt enable bit, TMR1IE 
	TMR1IE=1;				//溢出中断标志允许位 置一



	PEIE=1;					//外设中断允许位 置一



	//*********开全局中断设置
	//定时器T0设置了中断允许，此处要开全局中断
	GIE=1;					//总中断允许

    count_10ms = base_clip;
    callback = timer_proc;
}


/*************中断服务程序***************/
void interrupt ISR(void)//PIC单片机的所有中断都是这样一个入口
{
    static i = 0;
    // TMR1IF标志位为在计数寄存器由全1变为全0的时候，自动得到置一，即TMR1IF=1.
	if(TMR1IF==1)			// 需要进一步判断是否为定时器1的溢出中断标志位    
	{
		//定时器中断后，要重置初值，以备下次中断
		TMR1H=(65536-100)/256; 		
		TMR1L=(65536-100)%256; 



		//溢出中断标志位清零     如果TMR1IF出现上升沿，则产生中断，所以中断发生之后要清零。
		TMR1IF=0;			

		

		// 执行中断处理程序，执行中断产生时想要执行的功能
		if(++i>count_10ms)		//800us中断一次，再计次1250次后就是1s
		{
			i=0;
			if (callback)
            {
                callback();
            }
		}
		
	}
}
