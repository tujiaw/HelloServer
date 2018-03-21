#ifndef _IPUBLISH_H_
#define _IPUBLISH_H_

#include <vector>
#include <string>
#include "msgexpress.h"
#include "package.h"

class IDataItem
{
public:
	virtual ~IDataItem(){}
public:
	virtual int GetKey()const=0;
	virtual MsgExpress::DataType GetType()const=0;
	virtual int GetDataNumber()const=0;

	virtual std::string GetString(int index=0)const=0;
	virtual std::string GetRaw(int index=0)const=0;
	virtual int GetInt32(int index=0)const=0;
	virtual unsigned int GetUInt32(int index=0)const=0;
	virtual int64_t GetInt64(int index=0)const=0;
	virtual uint64_t GetUInt64(int index=0)const=0;
	virtual float GetFloat(int index=0)const=0;
	virtual double GetDouble(int index=0)const=0;
	virtual time_t GetDatetime(int index=0)const=0;

};



class IPublishHelper
{
public:
	virtual ~IPublishHelper(){}
public:
	virtual bool AddString(int key,const std::string& value)=0;
	virtual bool AddBinary(int key,const void * value,size_t size)=0;
	virtual bool AddInt32(int key,int value)=0;
	virtual bool AddUInt32(int key,unsigned int value)=0;
	virtual bool AddInt64(int key,int64_t value)=0;
	virtual bool AddUInt64(int key,uint64_t value)=0;
	virtual bool AddFloat(int key,float value)=0;
	virtual bool AddDouble(int key,double value)=0;
	virtual bool AddDatetime(int key,time_t value)=0;
	virtual bool AddBool(int key,bool value)=0;
	virtual bool AddComplex(int key,int64_t a,const std::string& b)=0;
    virtual MsgExpress::DataItem* GetItem(int key)=0;
};


typedef  shared_ptr<IPublishHelper> PublishHelperPtr;
MSGEXPRESS_API PublishHelperPtr CreatePublishHelper(MsgExpress::PublishData* pub,bool load=false);
MSGEXPRESS_API PublishHelperPtr CreatePublishHelper(MsgExpress::SubscribeData* sub,int topic,int subId);
#endif
