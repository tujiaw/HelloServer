#ifndef _LOGGER_H
#define _LOGGER_H

#define LOG4CXX_STATIC

#ifdef _WIN32
#include <xstring>
#elif __linux__
#include <string>
#endif
#include <functional>
#include <log4cxx/logger.h>

#ifdef _WIN32
#ifdef MSGEXPRESS_EXPORTS
#define LOGGER_API __declspec(dllexport)
#elif MSGEXPRESS_IMPORTS
#define LOGGER_API __declspec(dllimport)
#else
#define LOGGER_API
#endif
#elif __linux__
#define LOGGER_API
#endif

typedef enum
{
    ll_debug,
    ll_info,
	ll_warn,
    ll_error,
    ll_fatal
}TLogLevel;

#ifdef _WIN32
LOGGER_API bool LogInit(const char * conffile);
LOGGER_API bool LogInit(const wchar_t * conffile);
#elif __linux__
LOGGER_API bool LogInit(const char * conffile);
#endif
LOGGER_API void SetLogCallback(std::function<void(std::string, std::string)>, int level);
LOGGER_API void SetLevel(int level);
LOGGER_API log4cxx::LoggerPtr GetLogger();
LOGGER_API void Log(TLogLevel level, const char* fmt, ...);
LOGGER_API void Log2(TLogLevel level, const char* str);

#define _LOGDEBUG(fmt, ...) {  { Log(ll_debug, fmt, ##__VA_ARGS__); }}
#define _LOGINFO(fmt, ...) {  {  Log(ll_info, fmt, ##__VA_ARGS__); }}
#define _LOGWARN(fmt, ...) {  { Log(ll_warn, fmt, ##__VA_ARGS__); }}
#define _LOGERROR(fmt, ...) {  { Log(ll_error, fmt, ##__VA_ARGS__); }}
#define _LOGFATAL(fmt, ...) {  { Log(ll_fatal, fmt, ##__VA_ARGS__); }}

#define LOGGER_DEBUG(message) { \
	if (GetLogger()->isDebugEnabled()) { \
		::log4cxx::helpers::MessageBuffer oss_; \
		Log2(TLogLevel::ll_debug,oss_.str(oss_ << message).c_str()); }}

#define LOGGER_INFO(message) { \
	if (GetLogger()->isInfoEnabled()) { \
		::log4cxx::helpers::MessageBuffer oss_; \
		Log2(TLogLevel::ll_info,oss_.str(oss_ << message).c_str()); }}

#define LOGGER_WARN(message) { \
	if (GetLogger()->isWarnEnabled()) { \
		::log4cxx::helpers::MessageBuffer oss_; \
		Log2(TLogLevel::ll_warn,oss_.str(oss_ << message).c_str()); }}

#define LOGGER_ERROR(message) { \
	if (GetLogger()->isErrorEnabled()) { \
		::log4cxx::helpers::MessageBuffer oss_; \
		Log2(TLogLevel::ll_error,oss_.str(oss_ << message).c_str()); }}

#define LOGGER_FATAL(message) { \
	if (GetLogger()->isFatalEnabled()) { \
		::log4cxx::helpers::MessageBuffer oss_; \
		Log2(TLogLevel::ll_fatal,oss_.str(oss_ << message).c_str()); }}
		
#define LOG4_DEBUG if(GetLogger()->isDebugEnabled()) _LOGDEBUG
#define LOG4_INFO if(GetLogger()->isInfoEnabled()) _LOGINFO
#define LOG4_WARN if(GetLogger()->isWarnEnabled()) _LOGWARN
#define LOG4_ERROR if(GetLogger()->isErrorEnabled()) _LOGERROR
#define LOG4_FATAL if(GetLogger()->isFatalEnabled()) _LOGFATAL


#endif