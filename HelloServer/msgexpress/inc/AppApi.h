#ifndef _APPAPI_H_
#define _APPAPI_H_

#include "msgexpress.h"

///@brief �ͻ��˳����ʼ������,����QServerĿ¼,����0��ʾ�ɹ����������Ӧ���˳�
MSGEXPRESS_API int  DesktopAppInit(wchar_t* serverpath,bool safeguard=false);
MSGEXPRESS_API int  DesktopAppRelease();
MSGEXPRESS_API int  KillServer();

#endif