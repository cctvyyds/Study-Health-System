#include "STC89Cxx.h"

/**
  * @brief  定时器0初始化，500微秒@11.0592MHz
  * @param  无
  * @retval 无
  */

void Timer0Init(void)		//500微秒@11.0592MHz
{

	TMOD &= 0xF0;		//设置定时器模式
	TMOD |= 0x01;		//设置定时器模式
	TL0 = 0x33;		//设置定时初始值
	TH0 = 0xFE;		//设置定时初始值
	TF0 = 0;		//清除TF0标志
	TR0 = 1;		//定时器0开始计时
	ET0=1;          //T0的中断允许位，1允许
	EA=1;            //总中断允许控制位
	PT0=1;           //中断优先级处理高优先级，只设置IP寄存器
}


/*定时器中断模板
void Timer0_Routine() interrupt 1    // 500us定时器中断
{
	static unsigned int T0Count;// 动态扫描的索引，定义为局部静态变量
	static unsigned int T0Count_1;
    TL0 = 0x33;		//设置定时初始值
	TH0 = 0xFE;		//设置定时初始值
	T0Count++;
    
    if(T0Count ==1000)
    {
        T0Count = 0;
    }

}
*/
