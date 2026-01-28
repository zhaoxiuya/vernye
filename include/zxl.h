#pragma once
#include <stdarg.h>
<<<<<<< HEAD

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
=======
#include <libgen.h>
#include <type.h>

#define zxl_trace(fmt, ...)\
    zxl_impl(ZXLV_TRACE, basename(__FILE__), __func__, __LINE__, fmt, ##__VA_ARGS__)
#define zxl_debug(fmt, ...)\
    zxl_impl(ZXLV_DEBUG, basename(__FILE__), __func__, __LINE__, fmt, ##__VA_ARGS__)
#define zxl_info(fmt, ...)\
    zxl_impl(ZXLV_INFO, basename(__FILE__), __func__, __LINE__, fmt, ##__VA_ARGS__)
#define zxl_warn(fmt, ...)\
    zxl_impl(ZXLV_WARN, basename(__FILE__), __func__, __LINE__, fmt, ##__VA_ARGS__)
#define zxl_error(fmt, ...)\
    zxl_impl(ZXLV_ERROR, basename(__FILE__), __func__, __LINE__, fmt, ##__VA_ARGS__)
#define zxl_fatal(fmt, ...)\
    zxl_impl(ZXLV_FATAL, basename(__FILE__), __func__, __LINE__, fmt, ##__VA_ARGS__)

#define zxl_init(zxlv)\
    ZXLV_FILTER = zxlv

typedef enum {
    ZXLV_NONE  = 0,     //
    ZXLV_TRACE = 1,     // blue
    ZXLV_DEBUG = 2,     // cyan
    ZXLV_INFO  = 4,     // green
    ZXLV_WARN  = 8,     // yellow
    ZXLV_ERROR = 16,    // red
    ZXLV_FATAL = 32,    // purple
} ZXLV;

extern ZXLV ZXLV_FILTER;

void zxl_impl(ZXLV level, const u8* file,const u8* func, int line, const u8* fmt, ...);
>>>>>>> master
