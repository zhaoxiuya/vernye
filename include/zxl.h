#pragma once
#include <stdarg.h>
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

void zxl_impl(ZXLV level, const char* file,const char* func, int line, const char* fmt, ...);
