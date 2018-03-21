
#pragma once
#include <string>
#include <sstream>


#pragma pack(push, 1)

union BrokerId
{
public:
    /// 消息版本.
    struct
    {
        unsigned char GroupId:6;    ///< 组号
        unsigned char StationId:2;  ///< 组内编号
    };
    unsigned char Id;

    bool operator<(const BrokerId& b) const
    {
        return Id < b.Id;
    }

    bool operator==(const BrokerId& b) const
    {
        return Id == b.Id;
    }

    bool operator!=(const BrokerId& b) const
    {
        return ! (Id == b.Id);
    }

    unsigned char getGroup1stBrokerId() { return Id - StationId; }
    unsigned char isSameGroup(BrokerId id) { return GroupId == id.GroupId; }
    unsigned char isGroupOtherBroker(BrokerId id) { return GroupId == id.GroupId && StationId != id.StationId; }

};

inline std::ostream& operator<<( std::ostream& osIn, const BrokerId& L )
{
    osIn << 'G' << (unsigned short)L.GroupId << 'S' << (unsigned short)L.StationId;
    return osIn;
}

union  AppAddress
{
    friend std::ostream& operator<<( std::ostream& osIn, const AppAddress& L );
public:
    struct
    {
#if __BYTE_ORDER == __LITTLE_ENDIAN
        unsigned short AddressNo;   ///< 组内编号
        BrokerId Broker;            ///< BrokerId
        unsigned char Reserve;      ///< 保留
#elif __BYTE_ORDER == __BIG_ENDIAN
        unsigned char Reserve;      ///< 保留
        unsigned BrokerId Broker_Id;///< BrokerId
        unsigned short AddressNo;   ///< 组内编号
#endif
    };
    unsigned int Id;

    AppAddress()
        : Reserve(0)
    {
    }

    AppAddress(unsigned int id)
        : Id(id)
    {
    }

	AppAddress(const AppAddress& addr)
		: Id(addr.Id)
	{
	}

    AppAddress(BrokerId brokerId, unsigned short addressNo)
        : Broker(brokerId)
        , AddressNo(addressNo)
        , Reserve(0)
    {
    }

    void reset(BrokerId brokerId, unsigned short addressNo)
    {
        Broker = brokerId;
        AddressNo = addressNo;
    }

    bool operator<(const AppAddress& b) const
    {
        return Id < b.Id;
    }

	bool operator<=(const AppAddress& b) const
	{
		return Id <= b.Id;
	}

	bool operator>(const AppAddress& b) const
	{
		return Id > b.Id;
	}

	bool operator>=(const AppAddress& b) const
	{
		return Id >= b.Id;
	}

    bool operator==(const AppAddress& b) const
    {
        return Id == b.Id;
    }

    bool operator!=(const AppAddress& b) const
    {
        return Id != b.Id;
    }

	operator unsigned int() const
	{
		return Id;
	}

	std::string toString() const
	{
		std::ostringstream os;
		os << Broker << 'A' << AddressNo;
		return os.str();
	}
};

class AppAddressHash
{
public:
	std::size_t operator () (const AppAddress &addr) const{
		return addr.Id;
	}
};


inline std::ostream& operator<<( std::ostream& osIn, const AppAddress& L )
{
    osIn << L.toString().c_str();
    return osIn;
}

#pragma pack(pop)

