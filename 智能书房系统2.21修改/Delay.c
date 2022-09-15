/*模板
void Delay(unsigned int xms)//@12MHz
{
	unsigned char i, j;
	while(xms--)
	{
		i = 2;
		j = 239;
		do
		{
			while (--j);
		} while (--i);
	}
}
*/
#include "intrins.h"
void Delay(unsigned int xms)		//@11.0592MHz
{
	unsigned char i, j;
    while(xms--){

    _nop_();
	i = 2;
	j = 199;
	do
    	{
		while (--j);
	    } while (--i);
		
	            }
	
}
