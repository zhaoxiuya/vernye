#pragma once
#include <stdarg.h>

#define ZXL_TRACE(fmt, ...)\
    zhxLog_impl(ZXLV_TRACE, __FILE__, __func__, __LINE__, fmt, ##__VA_ARGS__)
#define ZXL_DEBUG(fmt, ...)\
    zhxLog_impl(ZXLV_DEBUG, __FILE__, __func__, __LINE__, fmt, ##__VA_ARGS__)
#define ZXL_INFO(fmt, ...)\
    zhxLog_impl(ZXLV_INFO, __FILE__, __func__, __LINE__, fmt, ##__VA_ARGS__)
#define ZXL_WARN(fmt, ...)\
    zhxLog_impl(ZXLV_WARN, __FILE__, __func__, __LINE__, fmt, ##__VA_ARGS__)
#define ZXL_ERROR(fmt, ...)\
    zhxLog_impl(ZXLV_ERROR, __FILE__, __func__, __LINE__, fmt, ##__VA_ARGS__)
#define ZXL_FATAL(fmt, ...)\
    zhxLog_impl(ZXLV_FATAL, __FILE__, __func__, __LINE__, fmt, ##__VA_ARGS__)
#define ZXL_INIT(MIN_ZXLV) (ZXLV_MIN = (MIN_ZXLV))

typedef enum {
    ZXLV_TRACE,// 파랑
    ZXLV_DEBUG,// 청록
    ZXLV_INFO, // 초록
    ZXLV_WARN, // 노랑
    ZXLV_ERROR,// 빨강
    ZXLV_FATAL // 보라
} ZXLV;

extern ZXLV ZXLV_MIN;

void zhxLog_impl(ZXLV level, const char* file,const char* func, int line, const char* fmt, ...);