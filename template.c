#include "badusb.h"
#include "keymap.h"
#include <intrins.h>
void free_all_and_wait(){
	unsigned char i, j, k;

	_nop_();
	_nop_();
	i = 1;
	j = 216;
	k = 35;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
	free_all();
}
void main(){
	Key_Init();