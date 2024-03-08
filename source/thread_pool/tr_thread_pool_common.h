/**
 * @author polaris
 * @description tr_thread_pool_log.h created on 2024-03-09
 */

#ifndef LIBTREASURE_TR_THREAD_POOL_COMMON_H
#define LIBTREASURE_TR_THREAD_POOL_COMMON_H

#include "treasure_log.h"

#if defined(__cplusplus) || defined(c_plusplus)
extern "C" {
#endif

#define TR_TP_MODULE_NAME "tr_thread_pool"

#define TR_TP_LOGD(fmt, args...) TREASURE_LOGD(TR_TP_MODULE_NAME, fmt, ##args)
#define TR_TP_LOGI(fmt, args...) TREASURE_LOGI(TR_TP_MODULE_NAME, fmt, ##args)
#define TR_TP_LOGW(fmt, args...) TREASURE_LOGW(TR_TP_MODULE_NAME, fmt, ##args)
#define TR_TP_LOGE(fmt, args...) TREASURE_LOGE(TR_TP_MODULE_NAME, fmt, ##args)
#define TR_TP_LOGF(fmt, args...) TREASURE_LOGF(TR_TP_MODULE_NAME, fmt, ##args)

#ifndef TR_TP_RET_SET_IF
#define TR_TP_RET_SET_IF(cond, err, msg, ret)   \
    if (cond) {                                 \
        errno = err;                            \
        TR_TP_LOGE(msg);                        \
        return ret;                             \
    }
#endif

#ifndef TR_TP_RET_IF_NULL
#define TR_TP_RET_IF_NULL(ptr, ret)     \
    if (ptr == NULL) {                  \
        TR_TP_LOGE(#ptr " is NULL.");   \
        return ret;                     \
    }
#endif



#if defined(__cplusplus) || defined(c_plusplus)
}
#endif

#endif /* LIBTREASURE_TR_THREAD_POOL_COMMON_H */
