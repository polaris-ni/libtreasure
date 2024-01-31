/*
 * @author polaris
 * @description treasure_log.h created on 2024-01-31
 */

#ifndef LIBTREASURE_TREASURE_LOG_H
#define LIBTREASURE_TREASURE_LOG_H

#include <stdint.h>

#if defined(__cplusplus) || defined(c_plusplus)
extern "C" {
#endif

enum treasure_log_level {
    TREASURE_LOG_CLOSE = 0,
    TREASURE_LOG_DEBUG = 1,
    TREASURE_LOG_INFO = 2,
    TREASURE_LOG_WARN = 3,
    TREASURE_LOG_ERROR = 4,
    TREASURE_LOG_FETAL = 5,
};

#define TREASURE_LOGD(module, fmt...) treasure_log(TREASURE_LOG_DEBUG, module, __FILE__, __LINE__, fmt, __VA_ARGS__)
#define TREASURE_LOGI(module, fmt...) treasure_log(TREASURE_LOG_INFO, module, __FILE__, __LINE__, fmt, __VA_ARGS__)
#define TREASURE_LOGW(module, fmt...) treasure_log(TREASURE_LOG_WARN, module, __FILE__, __LINE__, fmt, __VA_ARGS__)
#define TREASURE_LOGE(module, fmt...) treasure_log(TREASURE_LOG_ERROR, module, __FILE__, __LINE__, fmt, __VA_ARGS__)
#define TREASURE_LOGF(module, fmt...) treasure_log(TREASURE_LOG_FETAL, module, __FILE__, __LINE__, fmt, __VA_ARGS__)

void treasure_log(int32_t level, const char *module, const char *filename,
                  uint32_t line, const char *fmt, ...);

#if defined(__cplusplus) || defined(c_plusplus)
}
#endif
#endif /* LIBTREASURE_TREASURE_LOG_H */
