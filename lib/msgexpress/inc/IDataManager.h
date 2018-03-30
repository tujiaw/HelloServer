#ifndef _IDATAMANAGER_H_
#define _IDATAMANAGER_H_

#include <string>
#include "msgexpress.h"
#include "../protobuf/protobuf.h"
#include "package.h"

using namespace std;

class IDataManager
{
public:
	~IDataManager(){}
public:
	virtual void LoadDB()=0;
    virtual void GetSetInfo(Storage::SetInfoRequest* req,Storage::SetInfoResponse* resp)=0;
	virtual void SetSetInfo(Storage::SetInfoResponse* resp)=0;
	virtual int PutData(Storage::SaveDataRequest* req,string& err,google::protobuf::uint64& id)=0;
	virtual int DelData(Storage::DeleteDataRequest* req,string& err)=0;
	virtual int QueryData(Storage::QueryDataRequest* req,string& err,vector<PublishPtr>& dataset)=0;
	virtual void SyncData(PublishPtr data)=0;
};

MSGEXPRESS_API IDataManager* CreateDataManager();
MSGEXPRESS_API void FreeDataManager(IDataManager*);

#endif