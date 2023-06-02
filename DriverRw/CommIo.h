#include<ntifs.h>

#define READCODE CTL_CODE(FILE_DEVICE_UNKNOWN,0x801,METHOD_OUT_DIRECT,FILE_ANY_ACCESS)

#define WRITECODE CTL_CODE(FILE_DEVICE_UNKNOWN,0x802,METHOD_OUT_DIRECT,FILE_ANY_ACCESS)

#define DEVICENAME L"\\Device\\CommIoRw"

#define SYMBOLNAME L"\\??\\CommIoRw"

NTSTATUS DriverIrpCtl(PDEVICE_OBJECT pDevice, PIRP pIrp);

NTSTATUS CreateDriver(PDEVICE_OBJECT pDevice, PIRP pIrp);

NTSTATUS CloseDriver(PDEVICE_OBJECT pDevice, PIRP pIrp);


typedef struct _ReadInfo
{
	ULONG64 ProcessID;
	ULONG64 pSource;
	ULONG64 pTarget;
	ULONG64 Size;
}ReadInfo, * PReadInfo;//读内存结构

typedef struct _WriteInfo
{
	ULONG64 ProcessID;
	ULONG64 pSource;
	ULONG64 pTarget;
	ULONG64 Size;
}WriteInfo, * PWriteInfo; //写内存结构