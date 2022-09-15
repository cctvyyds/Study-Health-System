#include "STC89Cxx.h"

/**
  * @brief  串口初始化，4800bps@12.000MHz
  * @param  无
  * @retval 无
  */
/*void UART_Init()
{
	SCON=0x50;
	PCON |= 0x80;
	TMOD &= 0x0F;		//设置定时器模式
	TMOD |= 0x20;		//设置定时器模式
	TL1 = 0xF3;		//设定定时初值
	TH1 = 0xF3;		//设定定时器重装值
	ET1 = 0;		//禁止定时器1中断
	TR1 = 1;		//启动定时器1
	EA=1;
	ES=1;
}*/
/**
  * @brief  串口初始化，9600bps@11.0592MHz
  * @param  无
  * @retval 无
  */
void  UART_Init()		//9600bps@11.0592MHz
{
	PCON |= 0x80;		//使能波特率倍速位SMOD
	SCON = 0x50;		//8位数据,可变波特率
	TMOD &= 0x0F;		//设置定时器模式
	TMOD |= 0x20;		//设置定时器模式
	TL1 = 0xFA;		//设置定时初始值
	TH1 = 0xFA;		//设置定时重载值
	ET1 = 0;		//禁止定时器1中断
	TR1 = 1;		//定时器1开始计时
    EA=1;            //打开总中断
	ES=1;            //串行口中断允许控制位
}

/**
  * @brief  串口发送一个字节数据
  * @param  Byte 要发送的一个字节数据
  * @retval 无
  */
void UART_SendByte(unsigned char Byte)
{
	SBUF=Byte;
	while(TI==0);
	TI=0;
}

/*串口中断函数模板
void UART_Routine() interrupt 4
{
	if(RI==1)
	{
		
		RI=0;
	}
}
*/
