#pragma once
#include <stdarg.h>

#define ZXL_TRACE(fmt, ...)\
    zhxLog_impl(ZXLV_TRACE, basename(__FILE__), __func__, __LINE__, fmt, ##__VA_ARGS__)
#define ZXL_DEBUG(fmt, ...)\
    zhxLog_impl(ZXLV_DEBUG, basename(__FILE__), __func__, __LINE__, fmt, ##__VA_ARGS__)
#define ZXL_INFO(fmt, ...)\
    zhxLog_impl(ZXLV_INFO, basename(__FILE__), __func__, __LINE__, fmt, ##__VA_ARGS__)
#define ZXL_WARN(fmt, ...)\
    zhxLog_impl(ZXLV_WARN, basename(__FILE__), __func__, __LINE__, fmt, ##__VA_ARGS__)
#define ZXL_ERROR(fmt, ...)\
    zhxLog_impl(ZXLV_ERROR, basename(__FILE__), __func__, __LINE__, fmt, ##__VA_ARGS__)
#define ZXL_FATAL(fmt, ...)\
    zhxLog_impl(ZXLV_FATAL, basename(__FILE__), __func__, __LINE__, fmt, ##__VA_ARGS__)
#define ZXL_INIT(MIN_ZXLV) (ZXLV_MIN = (MIN_ZXLV))

typedef enum {
    ZXLV_TRACE,// blue
    ZXLV_DEBUG,// cyan
    ZXLV_INFO, // green
    ZXLV_WARN, // yellow
    ZXLV_ERROR,// red
    ZXLV_FATAL // purple
} ZXLV;

extern ZXLV ZXLV_MIN;

void zhxLog_impl(ZXLV level, const char* file,const char* func, int line, const char* fmt, ...);
