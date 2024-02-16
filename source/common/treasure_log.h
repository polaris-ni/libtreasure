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

#define TREASURE_LOG_CLOSE INT32_MAX
#define TREASURE_LOG_DEBUG 1
#define TREASURE_LOG_INFO 2
#define TREASURE_LOG_WARN 3
#define TREASURE_LOG_ERROR 4
#define TREASURE_LOG_FETAL 5

#ifndef __FILE_NAME__
#define __FILE_NAME__ __FILE__
#endif

#define TREASURE_LOGD(module, fmt, args...) treasure_log(TREASURE_LOG_DEBUG, module, __FILE_NAME__, __LINE__, fmt, ##args)
#define TREASURE_LOGI(module, fmt, args...) treasure_log(TREASURE_LOG_INFO, module, __FILE_NAME__, __LINE__, fmt, ##args)
#define TREASURE_LOGW(module, fmt, args...) treasure_log(TREASURE_LOG_WARN, module, __FILE_NAME__, __LINE__, fmt, ##args)
#define TREASURE_LOGE(module, fmt, args...) treasure_log(TREASURE_LOG_ERROR, module, __FILE_NAME__, __LINE__, fmt, ##args)
#define TREASURE_LOGF(module, fmt, args...) treasure_log(TREASURE_LOG_FETAL, module, __FILE_NAME__, __LINE__, fmt, ##args)

void treasure_log(int32_t level, const char *module, const char *filename,
                  uint32_t line, const char *fmt, ...);

#if defined(__cplusplus) || defined(c_plusplus)
}
#endif
#endif /* LIBTREASURE_TREASURE_LOG_H */
