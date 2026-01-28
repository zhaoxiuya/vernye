#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <time.h>
#include "zxl.h"

ZXLV ZXLV_FILTER = ZXLV_NONE;

void zxl_impl(ZXLV level, const char* file, \
    const char* func, int line, const char* fmt, ...) {
    static const char* zxlv_name[] = {
        "TRACE", "DEBUG", "INFO", "WARN", "ERROR", "FATAL"
    };
    static int zxlv_color[] = { 34, 36, 32, 33, 31, 35 };
    if ((level | ZXLV_FILTER) == 0) return;
    time_t t = time(NULL);
    struct tm *now_tm = localtime(&t);
    char time_str[32];
    strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", now_tm);
    va_list args;
    va_start(args, fmt);
    fprintf(stderr, "\033[%dm", zxlv_color[__builtin_ctz(level)]);
    fprintf(stderr, "[%s] %-5s %s:%04d(%s): ",\
        time_str, zxlv_name[__builtin_ctz(level)], file, line, func);
    vfprintf(stderr, fmt, args);
    fprintf(stderr, "\033[0m\n");
    va_end(args);
    if (level == ZXLV_FATAL ) exit(EXIT_FAILURE);
    return;
}
