#include "STC89Cxx.h"
sbit PWM=P1^2;//舵机
extern unsigned char num_count = 0;//周期计数变量
unsigned int t=0;
unsigned int a=0;//计时标志位
unsigned int time=0;
unsigned int jiaodu = 0;//舵机角度控制
/**
  * @brief  舵机开，左转90
  * @param  无
  * @retval 无
  */
void PWM_up(void)//舵机开，左转90
{   
jiaodu = 1;
}
/**
  * @brief  舵机关，转到0
  * @param  无
  * @retval 无
  */
 void PWM_off(void)//舵机关，转到0
{
   jiaodu = 3;
}

void Timer0_Routine() interrupt 1    // 500us定时器中断
{
	static unsigned int T0Count;// 动态扫描的索引，定义为局部静态变量
    TL0 = 0x33;		//设置定时初始值
	TH0 = 0xFE;		//设置定时初始值
	T0Count++;
	if(a==1)
	{
   t++;
	if(t==60000)//周期时间
		time++;
}
	
	
		
     if(T0Count>=40)//舵机周期20ms
		T0Count=0;
	
  if(T0Count <= jiaodu)
   PWM = 1;//高电平占空比由变量jiaodu控制，jiaodu=1时高电平0.5ms,jiaodu=5时高电平2.5ms
  if(T0Count > jiaodu && T0Count <= 40)
   PWM = 0;//低电平占空比，jiaodu=1时低电平19.5ms，jiaodu=5时低电平17.5ms


}

