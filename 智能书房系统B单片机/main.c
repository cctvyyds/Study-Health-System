
#include "STC89Cxx.h"
#include "UART.h"
#include "Timer0.h"
#include "Delay.h"



unsigned char SBUF_review =0 ;
//姿势1
sbit key1=P1^0;
sbit key2=P1^1;
sbit key3=P1^2;
//姿势2
sbit key4=P1^3;
sbit key5=P1^4;//用于姿势矫正的按钮
//指示灯
sbit LED_1 = P2^0;//姿势1
sbit LED_2 = P2^1;//姿势2



void main()
{
LED_1 = 1;
LED_2 = 1;
 UART_Init();
 
while (1)
{
    static unsigned char flag_1 = 0;//姿势1完成标志位
    static unsigned char flag_2 = 0;//姿势2完成标志位
 if (SBUF_review == 3)
 {       
      
     if(key1==0 && key2==0 && key3  ==0  && flag_1 ==0  )
     {	 LED_1 = 0;//姿势1指示灯亮
         LED_2 = 1;  //姿势2指示灯灭
           Delay(10000);
           if(key1==0 && key2==0 && key3  ==0 )
                {   LED_1 = 1;  //姿势1指示灯灭
                    flag_1 = 1;//姿势1完成
                }
     }
     if(key4==0 && key5==0 && flag_2 == 0)
                    {  
                       LED_1 = 1;//姿势1指示灯灭
                       LED_2 = 0;  //姿势2指示灯亮
                          Delay(10000);
                         if(key4==0 && key5==0)
                        {  
                             flag_2 = 1;//姿势2完成
                             LED_2 = 1;  //姿势2指示灯灭
                        }
                    }
       if( flag_1 == 0 && flag_2 == 0)
       {
        LED_1 = 0;//姿势1指示灯亮
        LED_2 = 0;  //姿势2指示灯亮
       }

       if(flag_1 == 1 && flag_2 == 0)    
         {
              LED_2 = 0;  //姿势2指示灯亮
              LED_1 = 1;  //姿势1指示灯灭
         }  else if (flag_1 == 0 && flag_2 == 1)
                   {
                   LED_2 = 1;  //姿势2指示灯灭
                   LED_1 = 0;  //姿势1指示灯亮
                   }       

        if(flag_1 == 1 && flag_2 == 1)
            { 
             UART_SendByte(2);
              LED_2 = 1;  //姿势2指示灯灭
              LED_1 = 1;  //姿势1指示灯灭
              SBUF_review = 0 ;//接受数据置0
                flag_1 = 0;
                flag_2 = 0;
             }
 }
    if (SBUF_review == 0)
    {
         LED_1 = 1;//姿势1指示灯灭
         LED_2 = 1;  //姿势2指示灯灭
    }
 }
}

void UART_Routine() interrupt 4
{
	if(RI==1)
	{
        SBUF_review = SBUF;  //接收数据赋值
		RI=0;   //关闭接收
        
	}
}

/*
void Timer0_Routine() interrupt 1    // 500us定时器中断
{


    TL0 = 0x33;		//设置定时初始值
	TH0 = 0xFE;		//设置定时初始值

    T0Count++;
    if(T0Count==20000)
        {
            T0Count = 0;
            T0Count_flag = 1;
        }
      if(key1==0 && key2==0 && key3  ==0  )
     {	
       if( T0Count_flag == 1)
          {	
            
          }
     }
 if(T0Count==20000)
        {
            T0Count = 0;

        }
}*/