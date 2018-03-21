#ifndef _ISUBSCRIPTION_H_
#define _ISUBSCRIPTION_H_

#include <string>
#include "msgexpress.h"
#include "package.h"

class ISubscription
{
public:
	virtual ~ISubscription(){}
public:
	virtual void AddIndex(int index)=0;
	virtual bool AddString(int key,std::string value,MsgExpress::Operator oper=MsgExpress::Equal)=0;
	virtual bool AddRaw(int key,const char * str,size_t size,MsgExpress::Operator oper=MsgExpress::Equal)=0;
	virtual bool AddInt32(int key,int value,MsgExpress::Operator oper=MsgExpress::Equal)=0;
	virtual bool AddUInt32(int key,unsigned int value,MsgExpress::Operator oper=MsgExpress::Equal)=0;
	virtual bool AddInt64(int key,int64_t value,MsgExpress::Operator oper=MsgExpress::Equal)=0;
	virtual bool AddUInt64(int key,uint64_t value,MsgExpress::Operator oper=MsgExpress::Equal)=0;
	virtual bool AddFloat(int key,float value,MsgExpress::Operator oper=MsgExpress::Equal)=0;
	virtual bool AddDouble(int key,double value,MsgExpress::Operator oper=MsgExpress::Equal)=0;
	virtual bool AddDatetime(int key,time_t value,MsgExpress::Operator oper=MsgExpress::Equal)=0;

	virtual void GetSubData(MsgExpress::SubscribeData& sub)=0;
};

MSGEXPRESS_API ISubscription* CreateSubscription(int id,int topic,unsigned int addr=0);
MSGEXPRESS_API void FreeSubscription(ISubscription*);
#endif
