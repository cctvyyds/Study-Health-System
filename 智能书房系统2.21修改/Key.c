#include "STC89Cxx.h"
#include "Delay.h"

/**
  * @brief  获取独立按键键码
  * @param  无
  * @retval 按下按键的键码，范围：0~2，无按键按下时返回值为0
  */
unsigned char Key()
{
	unsigned char KeyNumber=0;
	
	if(P13==0){Delay(20);while(P13==0);KeyNumber=1;Delay(10);}
	if(P14==0){Delay(20);while(P14==0);KeyNumber=2;Delay(10);}
	
	
	return KeyNumber;
}
