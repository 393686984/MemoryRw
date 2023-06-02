
#include<windows.h>
#include <winioctl.h>

#define DEVICE_LINK_NAME L"\\\\.\\CommIoRw" 


BOOL LoadDriver(const  char* lpszDriverName, const  char* sysFileName/*ÈçDriver.sys*/);


BOOL UnloadDriver(const  char* lpszDriverName);

//Æô¶¯Çý¶¯

BOOL InitDriver();

//Í£Ö¹
BOOL DriverUnload();