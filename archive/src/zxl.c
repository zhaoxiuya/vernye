#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <time.h>
#include "zxl.h"

ZXLV ZXLV_MIN = ZXLV_TRACE;

void zhxLog_impl(ZXLV level, const char* file,
const char* func, int line, const char* fmt, ...) {
    static const char* zhxLogLevelTb[] = {
        "TRACE", "DEBUG", "INFO", "WARN", "ERROR", "FATAL"
    };
    static int zhxLogLevelColor[] = {34, 36, 32, 33, 31, 35};
    if(level < ZXLV_MIN) return;
    time_t t = time(NULL);
    struct tm *nowTime = localtime(&t);
    char timeStr[32];
    strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", nowTime);
    va_list args;
    va_start(args, fmt);
    fprintf(stderr, "\033[%dm", zhxLogLevelColor[level]);
    fprintf(stderr, "[%s] %-5s %s/%d(%s): ", timeStr, zhxLogLevelTb[level], file, line, func);
    vfprintf(stderr, fmt, args);
    fprintf(stderr, "\033[0m\n");
    va_end(args);
    return;
}