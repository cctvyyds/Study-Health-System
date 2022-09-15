#include "STC89Cxx.h"

void reset (void)//51单片机软件复位
{
    ((void (code *) (void)) 0x0000) ();
}
 

/*51单片机无自带的看门狗，没有提供软件复位的函数和机制，要想实现软件复位，只能通过强制将PC指针指到0x0000位置，

通过以下函数将PC指针强制指到0x0000：

void reset(void)
{undefined
    ((void (code *) (void)) 0x0000) ();
}

可以使用下面的程序跳到0000H实现软复位，下面的程序实际上是一个函数指针，指针指向了0000H地址。

（（void （code *） （void）） 0x0000） （）;

下面的例子将实现软件自复位

void reset （void）
{
    （（void （code *） （void）） 0x0000） （）;
}
 
void main （void）
{
    reset （）;
}
你可能注意到以上的软复位程序并不能清除8051的中断系统和某些8051的外围设备，当您在中断程序中调用上面的软件复位程序后，中断将再不能触发。因此，以上的软复位程序不能在中断子程序中调用。

STC的单片机有软件复位指令，即ISP_CONTR，地址在0E7H 单元(即str ISP_CONTR=0xE7)，MOVISP_CONTR,#00100000B（C语言为ISP_CONTR=0x20），内狗也是一条指令MOV WDT_CONTR,#00111100B！
STC 51系列单片机Datasheet中指出：传统的8051 单片机由于硬件上未支持此功能，用户必须用软件模拟实现，实现起来较麻烦。现STC 新推出的增强型8051 根据客户要求增加了ISP_CONTR 特殊功能寄存器,实现了此功能。用户只需简单的控制ISP_CONTR 特殊功能寄存器的其中两位 SWBS / SWRST 就可以系统复位了。
————————————————
版权声明：本文为CSDN博主「EmbededCoder」的原创文章，遵循CC 4.0 BY-SA版权协议，转载请附上原文出处链接及本声明。
原文链接：https://blog.csdn.net/u012308586/article/details/100655798*/