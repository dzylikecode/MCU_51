ORG 0000H                   ;定位内存地址
		LJMP MAIN           ;主函数跳转
		ORG 0003H           ;定位中断向量
		LJMP INTER0         ;跳转中断服务
ORG 100H		            ;定位Main的存放地址
MAIN:	JB P3.2,MAIN1		;查询外部I/O口是否有输入，有则跳转处理
		CLR TCON.0			;清除中断请求
		SJMP MAIN2  		;跳转至中断配置
		
MAIN1:	SETB TCON.0 		;打开中断请求
MAIN2:	ORL	IE,#81H 		;配置总的中断，打开INT0中断允许位
		ORL	IP,#02H 		;配置中断优先级
		SJMP MAIN  			;循环等待终端
							;中断服务程序
INTER0:	CLR EA 				;禁止中断
		CLR P0.0			;点亮灯
		LCALL DELY 	        ;延时一段时间
		SETB P0.0  			;关闭灯
		LCALL DELY 			;延长一段时间
		SETB EA				;打开中断
		RETI 				;中断返回

							;延时函数
DELY:	MOV R6,#250 		;外层循环250次		
DELY1:	MOV R7,#250 		;内层循环250次
DELY2:	DJNZ R7,DELY2
		DJNZ R6,DELY1
		RET 				;函数返回
		END
