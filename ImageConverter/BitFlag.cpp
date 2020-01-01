#include "BitFlag.h"
#include <iostream>

void printb(unsigned int v)
{
	unsigned int mask = (int)1 << (sizeof(v) * CHAR_BIT - 1);
	do putchar(mask & v ? '1' : '0');
	while (mask >>= 1);
}
