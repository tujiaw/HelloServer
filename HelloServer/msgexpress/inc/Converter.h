#ifndef _CONVERTER_H_
#define _CONVERTER_H_

#include <string>
#include "../inc/package.h"

using namespace std;

class MSGEXPRESS_API Converter
{
public:
	static string toString(int value);
	static string toString(unsigned int value);
	static string toString(int64_t value);
	static string toString(uint64_t value);
    static string toString(float value);
	static string toString(double value);

    static int toInt32(const string& value);
    static unsigned int toUInt(const string& value);
    static int64_t toInt64(const string& value);
    static uint64_t toUInt64(const string& value);
    static float toFloat(const string& value);
    static double toDouble(const string& value);
};


#endif