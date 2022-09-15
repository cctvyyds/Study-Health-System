#include "STC89Cxx.h"
#include "intrins.h"
#include "UART.h"
#include "Delay.h"
#include "Timer0.h"
#include "Key.h"
#include "pwm.h"
#include "Reset.h"

#define uchar unsigned char //宏定义，.相当于用uchar代替长度较长的unsigned char
#define uint unsigned int
sbit LED=P1^1;
sbit HWX=P1^0;
sbit PWM=P1^2;

sbit key1=P1^3;
sbit key2=P1^4;

extern unsigned int a;
extern unsigned int t;
extern unsigned int time;
uchar num=0;   //周期数
uchar num_residue=0;   //剩余周期数
uchar SBUF_review = 0  ;//定义SBUF接收
uchar shuma[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};//数码管段码

/*方法1，
/**
  * @brief  确定人是否在区域内+防误判，有10s延时，可调
  * @param  无
  * @retval 无
  
uint HWX_2()
{
	unsigned char cd=0;//静态局部变量
	
	if(HWX==0)
  {
    Delay(10000);
    while(HWX==1);
    Delay(20);
    cd=0;
    }
	if(HWX==1)
  {
    Delay(20);
    while(HWX==0);
    Delay(20);
    cd=1;
    }
	
	return cd;
}
*/


/**
  * @brief  红外模块确定人是否在区域内+防误判，有延时，可调
  * @param  无
  * @retval 无
  *
  */
uint HWX_2()
    {
      static uint flag =0,lastflag = 0;
      lastflag = flag;
      if (HWX == 0)
      {
       Delay(100);
           if (HWX == 0)
           {
             flag = 0;
           }else
           {
            flag =1;
           }
      }else 
      { 
          flag =1;
      }
      if (flag && lastflag)
      {
       return 1;
      }else
      {
         return 0;
      }
    }


void key_1() //按键扫描函数//按键扫描1，用于记录周期数
{  
  if(key1==0)
 {
   Delay(50);
 
  if(key1==1)
  {
   num++;
   
  }
	}
 if(num>9)
 {
	 num=0;
 }

}
 

void main ()
{
  

  Timer0Init();//500um定时器开始工作
  
  while(1)
   { 
     PWM_up();//舵机开
   
   key_1(); //按键扫描函数周期扫描
  
   P2 = shuma[num];//数码管显示周期数
   
   if(key2 ==0)//不知道为什么，，HWM=1的时候按键2没反应，这样也挺好
    {   
			Delay(50);
			if(key2==1)
			{
        PWM_off();//舵机关
        break;//跳出该While循环
			}
     }
   } 
	 
	 
	 
	 
	 
	 
	  a=1;	
      num_count = 0;
      UART_Init();//串口初始化声明
    while(1)
    {
			num_residue=num-num_count;
      		
			 P2 = shuma[num_residue];//数码管显示剩余周期数

    if(num_residue==0)
    {
   PWM_up();//舵机开
    }
      
    

		
      if( HWX_2()==1)//红外线部分
       {	
       LED=0;
				 a=1;
       }else if( HWX_2()==0)
                {
              	LED=1;
									a=0;
                }//如果红外线没检测到人，灭灯
								
								
								
								
								
       if(time == 1)//如果过了一周期
    {
			a=0;//计时标志位清零
			t=0;
			time=0;//分钟数
       LED=1;//灭灯
     UART_SendByte(3);//串口发送3给B单片机
			while(1)
			{
      if(RI==1)
     {
      num_count++;
			 RI=0;
			 a=1;
			 break;
     }
	 }

    }
    } 
}



void UART_Routine() interrupt 4
{
	if(RI==1)
	{
    SBUF_review = SBUF;
		RI=0;
	}
}


//定时器中断在pwm.c里
 //,如果实际操作中舵机抖动，加这句ES=0;            //关闭串行口中断允许控制位



