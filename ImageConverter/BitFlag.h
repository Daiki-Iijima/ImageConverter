#pragma once

#define BIT_FLAG1	0x0001
#define BIT_FLAG2	0x0002
#define BIT_FLAG4	0x0004
#define BIT_FLAG8	0x0008
#define BIT_FLAG16	0x0010
#define BIT_FLAG32	0x0020
#define BIT_FLAG64	0x0040
#define BIT_FLAG128 0x0080

//  2進数表示のためのメソッド
void printb(unsigned int v);