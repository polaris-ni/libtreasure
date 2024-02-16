/*
 * @author polaris
 * @description treasure_log.c created on 2024-01-31
 */

#include "treasure_log.h"
#include <stdio.h>
#include <stdarg.h>

#ifndef TREASURE_LOG_LINE_MAX_LEN
#define TREASURE_LOG_LINE_MAX_LEN 256
#endif

#ifndef TREASURE_LOG_MIN_LEVEL
#define TREASURE_LOG_MIN_LEVEL TREASURE_LOG_INFO
#endif

__attribute__((weak)) void treasure_log(int32_t level, const char *module, const char *filename, uint32_t line,
                                        const char *fmt, ...) {
    if (level < TREASURE_LOG_MIN_LEVEL) {
        return;
    }
    static const char tags[] = {'D', 'I', 'W', 'E', 'F'};
    static char buf[TREASURE_LOG_LINE_MAX_LEN] = {0};
    static char format[TREASURE_LOG_LINE_MAX_LEN] = {0};
    int32_t ret = snprintf(format, sizeof(format), "[%c] %s:%s:%u > %s\r\n", tags[level - 1],
                           module, filename, line, fmt);
    if (ret < 0) {
        return;
    }
    size_t len = sizeof(buf);
    va_list args;
    va_start(args, fmt);
    ret = vsnprintf(buf, sizeof(buf), format, args);
    va_end(args);
    if (ret < 0) {
        return;
    }
    printf("%s", buf);
}
