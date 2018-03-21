#ifndef _APPAPI_H_
#define _APPAPI_H_

#include "msgexpress.h"

///@brief 客户端程序初始化函数,传入QServer目录,返回0表示成功，否则程序应该退出
MSGEXPRESS_API int  DesktopAppInit(wchar_t* serverpath,bool safeguard=false);
MSGEXPRESS_API int  DesktopAppRelease();
MSGEXPRESS_API int  KillServer();

#endif