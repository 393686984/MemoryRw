#include "pch.h"
#include"DriverLoad.h"
#include<winioctl.h>



#define READCODE CTL_CODE(FILE_DEVICE_UNKNOWN,0x801,METHOD_OUT_DIRECT,FILE_ANY_ACCESS)//¶ÁÄÚ´æ

#define WRITECODE CTL_CODE(FILE_DEVICE_UNKNOWN,0x802,METHOD_OUT_DIRECT,FILE_ANY_ACCESS)//Ð´ÄÚ´æ



typedef struct _ReadInfo
{
	ULONG64 ProcessID;
	ULONG64 pSource;
	ULONG64 pTarget;
	ULONG64 Size;
}ReadInfo, * PReadInfo;

typedef struct _WriteInfo
{
	ULONG64 ProcessID;
	ULONG64 pSource;
	ULONG64 pTarget;
	ULONG64 Size;
}WriteInfo, * PWriteInfo;

VOID ReadMemory(ULONG64 ProcessID, ULONG64 SurrceAddr, void* TargetAddr, ULONG64 Size);

VOID WriteMemory(ULONG64 ProcessID, void* SurrceAddr, ULONG64 TargetAddr, ULONG64 Size);
