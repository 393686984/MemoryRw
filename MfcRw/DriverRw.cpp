#include"Pch.h"
#include "DriverRw.h"

//驱动读取
HANDLE   hDevice = 0;

BOOL InitDriver()
{
	hDevice = CreateFileW(DEVICE_LINK_NAME, GENERIC_WRITE | GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);
	return hDevice ? true : false;
}

//停止驱动
BOOL DriverUnload()
{
	CloseHandle(hDevice);

	return hDevice ? true : false;
}



VOID ReadMemory(ULONG64 ProcessID, ULONG64 SurrceAddr, void* TargetAddr, ULONG64 Size)
{
	ReadInfo Info;
	Info.ProcessID = ProcessID;
	Info.pSource = SurrceAddr;
	Info.pTarget = (ULONG64)TargetAddr;
	Info.Size = Size;

	DeviceIoControl(hDevice, READCODE, &Info, sizeof(ReadInfo), 0, 0, 0, 0);
}
//驱动写入
VOID WriteMemory(ULONG64 ProcessID, void* SurrceAddr, ULONG64 TargetAddr, ULONG64 Size)
{
	WriteInfo Info;
	Info.ProcessID = ProcessID;
	Info.pSource = (ULONG64)SurrceAddr;
	Info.pTarget = TargetAddr;
	Info.Size = Size;
	DeviceIoControl(hDevice, WRITECODE, &Info, sizeof(WriteInfo), 0, 0, 0, 0);
}