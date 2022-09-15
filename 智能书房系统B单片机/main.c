
#include "STC89Cxx.h"
#include "UART.h"
#include "Timer0.h"
#include "Delay.h"



unsigned char SBUF_review =0 ;
//����1
sbit key1=P1^0;
sbit key2=P1^1;
sbit key3=P1^2;
//����2
sbit key4=P1^3;
sbit key5=P1^4;//�������ƽ����İ�ť
//ָʾ��
sbit LED_1 = P2^0;//����1
sbit LED_2 = P2^1;//����2



void main()
{
LED_1 = 1;
LED_2 = 1;
 UART_Init();
 
while (1)
{
    static unsigned char flag_1 = 0;//����1��ɱ�־λ
    static unsigned char flag_2 = 0;//����2��ɱ�־λ
 if (SBUF_review == 3)
 {       
      
     if(key1==0 && key2==0 && key3  ==0  && flag_1 ==0  )
     {	 LED_1 = 0;//����1ָʾ����
         LED_2 = 1;  //����2ָʾ����
           Delay(10000);
           if(key1==0 && key2==0 && key3  ==0 )
                {   LED_1 = 1;  //����1ָʾ����
                    flag_1 = 1;//����1���
                }
     }
     if(key4==0 && key5==0 && flag_2 == 0)
                    {  
                       LED_1 = 1;//����1ָʾ����
                       LED_2 = 0;  //����2ָʾ����
                          Delay(10000);
                         if(key4==0 && key5==0)
                        {  
                             flag_2 = 1;//����2���
                             LED_2 = 1;  //����2ָʾ����
                        }
                    }
       if( flag_1 == 0 && flag_2 == 0)
       {
        LED_1 = 0;//����1ָʾ����
        LED_2 = 0;  //����2ָʾ����
       }

       if(flag_1 == 1 && flag_2 == 0)    
         {
              LED_2 = 0;  //����2ָʾ����
              LED_1 = 1;  //����1ָʾ����
         }  else if (flag_1 == 0 && flag_2 == 1)
                   {
                   LED_2 = 1;  //����2ָʾ����
                   LED_1 = 0;  //����1ָʾ����
                   }       

        if(flag_1 == 1 && flag_2 == 1)
            { 
             UART_SendByte(2);
              LED_2 = 1;  //����2ָʾ����
              LED_1 = 1;  //����1ָʾ����
              SBUF_review = 0 ;//����������0
                flag_1 = 0;
                flag_2 = 0;
             }
 }
    if (SBUF_review == 0)
    {
         LED_1 = 1;//����1ָʾ����
         LED_2 = 1;  //����2ָʾ����
    }
 }
}

void UART_Routine() interrupt 4
{
	if(RI==1)
	{
        SBUF_review = SBUF;  //�������ݸ�ֵ
		RI=0;   //�رս���
        
	}
}

/*
void Timer0_Routine() interrupt 1    // 500us��ʱ���ж�
{


    TL0 = 0x33;		//���ö�ʱ��ʼֵ
	TH0 = 0xFE;		//���ö�ʱ��ʼֵ

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