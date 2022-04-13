ORG 0000H               ;复位地址
    AJMP MAINT          ;跳转至主程序
ORG 000BH               ;定时器0的中断向量地址
    AJMP TOINT          ;跳转到真正的定时器程序处

ORG 40H                 ;定位Main
MAIN:                   ;主程序入口
    MOV 30H,#0000H      ;软件计数器清0
    MOV TMOD,#01H       ;定时/计数器0工作于方式1
    MOV TH0,#3CH        ;配置时钟初始值
    MOV TL0,#000BH      ;即数15536
    SETB EA             ;开总中断允许
    SETB ET0            ;开定时/计数器0允许
    SETB TR0            ;定时/计数器0开始运行
    SJMP $				;死循环

TOINT:					;定时器0的中断处理程序
    INC  30H            ;30H的值自增
    MOV  A,30H          ;填入地址30H
    CJNE A, #6, LOOP 	;30H单元中的值到了6了吗?
    CPL  P1.0 			;到了,取反P10
    MOV  30H,#0 		;清软件计数器
LOOP:
    MOV TH0,#15H        ;重现填充初始值
    MOV TL0,#9FH        ;重置定时常数
    RETI
END
