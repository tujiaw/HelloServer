#ifndef _CACHEAPI_H_
#define _CACHEAPI_H_

#include <string>
#include <functional>
#include "msgexpress.h"
#include "../protobuf/protobuf.h"

using namespace std;

struct CallbackArg
{
	int retcode;
	string errmsg;
	string value;
	void* userdata;
};

struct Callback
{
	std::function<void(const CallbackArg&)> cb;
	void* userdata;
};

namespace  MemCache{

MSGEXPRESS_API int  Initialize(const char*  configPath=NULL);
MSGEXPRESS_API int  Initialize(std::string addr,unsigned short port);
MSGEXPRESS_API int  Release();
MSGEXPRESS_API bool IsConnected();
MSGEXPRESS_API int ClearDB();
MSGEXPRESS_API int Select(unsigned char db,std::string* errstr=0);
MSGEXPRESS_API int Set(std::string key,std::string value,std::string* errstr=0);
MSGEXPRESS_API int Get(std::string key,std::string& value,std::string* errstr=0);
MSGEXPRESS_API int Del(std::string key,std::string* errstr=0);
MSGEXPRESS_API int SaveData(const Storage::SaveDataRequest& request,Storage::SaveDataResponse& resp,std::string* errstr=0);
MSGEXPRESS_API int QueryData(const Storage::QueryDataRequest& request,Storage::QueryDataResponse& resp,std::string* errstr=0);
MSGEXPRESS_API void Set(unsigned char dataset,const string& key,const string& value,void* userdata, std::function<void(const CallbackArg&)> cb);
MSGEXPRESS_API void Get(unsigned char dataset,const string& key,void* userdata, std::function<void(const CallbackArg&)> cb);
};

namespace  LocalCache{

MSGEXPRESS_API int  Initialize();
MSGEXPRESS_API int  Release();
MSGEXPRESS_API int Set(std::string key,std::string value,std::string* errstr=0);
MSGEXPRESS_API int Get(std::string key,std::string& value,std::string* errstr=0);
MSGEXPRESS_API int Del(std::string key,std::string* errstr=0);
};

#endif