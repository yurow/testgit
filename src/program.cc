#include <iostream>
#include "stdio.h"
#include <cctype>
#include <memory>
#include <stack>
#include <bitset>
#include <string.h>

using namespace std;

typedef struct FrameHeader {
	unsigned int sync:11; //同步信息
	unsigned int version:2; //版本
	unsigned int layer:2; //层
	unsigned int error_protection:1; // CRC校验

	unsigned int bitrate_index:4; //位率
	unsigned int sampling_frequency:2; //采样频率
	unsigned int padding:1; //帧长调节
	unsigned int _private:1; //保留字

	unsigned int mode:2; //声道模式
	unsigned int mode_extension:2; //扩充模式
	unsigned int copyright:1; // 版权
	unsigned int original:1; //原版标志
	unsigned int emphasis:2; //强调模式
} HEADER, *LPHEADER;

void outbinary(int val,int len){
	bitset<11> myset(val);
	cout << myset << endl;
}

void    ReverseBit(unsigned int* pValue)
{
    unsigned int n = *pValue;
    n = (n&0x55555555)<<1|(n&0xAAAAAAAA)>>1;
     n = (n&0x33333333)<<2|(n&0xCCCCCCCC)>>2;
     n = (n&0x0F0F0F0F)<<4|(n&0xF0F0F0F0)>>4;
     n = (n&0x00FF00FF)<<8|(n&0xFF00FF00)>>8;
     n = (n&0x0000FFFF)<<16|(n&0xFFFF0000)>>16;
    *pValue = n;
}

unsigned int reverse(unsigned x)
{
	unsigned int m = 0, i;
    unsigned mask = x;
    for (i=0; i<32; i++)
    {
        m = (m << 1) + (mask & 1);
        mask >>= 1;
    }
    return m;
}

unsigned int reverse1(unsigned x)
{
	unsigned int t = 0;
	t = x << 24;
	t += ((x << 8) & 0xFF0000);
	t += ((x >> 8) & 0xFF00);
	t += (x >> 24);
	return t;
}


void    ShowBit(unsigned int x, int n)
{
    if (--n) ShowBit(x>>1, n);
    printf("%d", x%2);
}

int main(int argc, char ** argv) {
	const auto_ptr<string>file(new string("/home/yurow/wait.mp3"));
	auto_ptr<FILE>fp(fopen(file->c_str(), "rb"));
	if (!fp.get())
		return 0;

	unsigned int wave = 0;
	fread(&wave,sizeof(wave),1,fp.get());
	wave= reverse1(wave);

	unsigned int syn = (wave & 0xFFE00000) >> (32-11);
	unsigned int version = (wave & 0x00180000) >> (32-13);
	unsigned int layer = (wave & 0x00060000) >> (32-15);
	unsigned int error_protection = (wave & 0x00010000)>> (32-16);

	unsigned int bitrate_index = (wave & 0x0000F000)>>(32-20); //位率
	unsigned int sampling_frequency = (wave & 0x00000C00)>>(32-22);
	unsigned int padding= (wave & 0x00000200)>>(32-23);
	unsigned int _private= (wave & 0x00000100)>>(32-24);

	unsigned int mode= (wave & 0x000000C0)>>(32-26);
	unsigned int mode_extension= (wave & 0x00000030)>>(32-28);
	unsigned int copyright= (wave & 0x00000008)>>(32-29);
	unsigned int original= (wave & 0x00000004)>>(32-30);
	unsigned int emphasis= wave & 0x00000003;

	cout << syn << endl;
	cout << version << endl;
	cout << layer << endl;
	cout << error_protection << endl;
	cout << bitrate_index << endl;
	cout << sampling_frequency << endl;
	cout << padding << endl;
	cout << _private << endl;
	cout << mode << endl;
	cout << mode_extension << endl;
	cout << copyright << endl;
	cout << original << endl;
	cout << emphasis << endl;

	ShowBit(syn,11);
	ShowBit(version,2);
	ShowBit(layer,2);
	ShowBit(error_protection,1);
	ShowBit(bitrate_index,4);
	ShowBit(sampling_frequency,2);
	ShowBit(padding,1);
	ShowBit(_private,1);
	ShowBit(mode,2);
	ShowBit(mode_extension,2);
	ShowBit(copyright,1);
	ShowBit(original,1);
	ShowBit(emphasis,2);
}

