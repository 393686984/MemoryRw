
#include<windows.h>
#include <winioctl.h>

#define DEVICE_LINK_NAME L"\\\\.\\CommIoRw" 


BOOL LoadDriver(const  char* lpszDriverName, const  char* sysFileName/*��Driver.sys*/);


BOOL UnloadDriver(const  char* lpszDriverName);

//��������

BOOL InitDriver();

//ֹͣ
BOOL DriverUnload();