        ORG     0000H       ;
        MOV     A,  #0FEH   ;FEH为点亮第一个发光二极管的代码
LOOP:   MOV     P1, A       ;点亮P1.0位控制的发光二极管
        LCALL   DELAY       ;调用延迟一段时问的子程序
        RL      A           ;“0”左移一位
        SJMP    LOOP        ;不断循环
DELAY:  MOV     R1, #0FFH   ;延时子程序人口
LP   :  MOV     R2, #80H
LP1  :  NOP                 ;
        NOP
        DJNZ    R2, LP1 
        DJNZ    R1, LP
        RET                 ;子程序返回
        END 