// ConsoleApplication3.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <stdio.h>
#include <string.h>
#include <intrin.h>
#include <stdlib.h>


int _tmain(int argc, _TCHAR* argv[])
{
	char CpuString[32];
	char CpuBrandString1[0x40] = { 0 };
	char AdjustString[40] = { 0 };
	char CpuBrandString[0x40];
	int CpuInfo[4] = { -1 };
	int i,j=0;
	

	/*
	__cpuid(CpuInfo, 0);
	nIds = CpuInfo[0];
	memset(CpuString, 0, sizeof(CpuString));//初始化
	*(int*)(CpuString) = CpuInfo[1];
	*(int*)(CpuString+8) = CpuInfo[2];
	*(int*)(CpuString+4) = CpuInfo[3];
	printf("CPUID:\t");
	printf("%s\n", CpuString);
	*/
	
	for (i = 0x80000002; i <=0x80000004; i++)
	{
		__cpuid(CpuInfo, i);
		/*
		printf("CpuInfo[0]:%x\n", CpuInfo[0]);
		printf("CpuInfo[1]:%x\n", CpuInfo[1]);
		printf("CpuInfo[2]:%x\n", CpuInfo[2]);
		printf("CpuInfo[3]:%x\n", CpuInfo[3]);*/
		if (i == 0x80000002)
		{		
			memcpy(CpuBrandString, CpuInfo, sizeof(CpuInfo));//int型的CpuInfo会被强制转化为char，所以32位的int变为16char的长度
			CpuInfo[1] = CpuInfo[1] & 0xff;
			CpuInfo[3] = CpuInfo[3] & 0xff;
			memcpy(CpuBrandString1, CpuInfo, sizeof(CpuInfo));
		}
		else if (i == 0x80000003)
		{
			memcpy(CpuBrandString+16, CpuInfo, sizeof(CpuInfo));//int型的CpuInfo会被强制转化为char，所以32位的int变为16char的长度
			CpuInfo[0] = CpuInfo[0] & 0xffffff00;
			CpuInfo[2] = CpuInfo[2] & 0x0000ffff;
			CpuInfo[3] = 0;
			memcpy(CpuBrandString1+16, CpuInfo, sizeof(CpuInfo));
		}
		else if (i == 0x80000004)
		{
			memcpy(CpuBrandString+32, CpuInfo, sizeof(CpuInfo));//int型的CpuInfo会被强制转化为char，所以32位的int变为16char的长度
			CpuInfo[0] = 0;
			CpuInfo[1] = 0;
			CpuInfo[2] = 0;
			CpuInfo[3] = 0;
			memcpy(CpuBrandString1+32, CpuInfo, sizeof(CpuInfo));
		}
	}	

	
	for (i = 0; i < 64; i++)
	{
		if (CpuBrandString1[i] == 0 || CpuBrandString1[i] == -52)
		{
			continue;
		}
		else
		{
			AdjustString[j++] = CpuBrandString1[i];
		}
		/*
		if (CpuBrandString1[i] != 0 || CpuBrandString1[i] != -52)
		{
			printf_s("%c", CpuBrandString1[i]);
		}*/
	}

	printf_s("Brand:\t%s\n", AdjustString);

	__cpuid(CpuInfo, 1);
	printf("family:\t%X\t", CpuInfo[0] >> 8 & 0xf);
	printf("Model:\t%X\t", CpuInfo[0] >> 4 & 0xf);
	printf("stepping:\t%X\n", CpuInfo[0] & 0xf);

	printf_s("Brand:\t%s\n", CpuBrandString);
	

	return 0;
}

