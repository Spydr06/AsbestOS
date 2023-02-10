#ifndef KERNEL_LOG_H
#define KERNEL_LOG_H

typedef enum {
    KLOG_NONE,

    KLOG_OK,
    KLOG_INFO,
    KLOG_WARN,
    KLOG_FAIL,
} KLogLevel_T;

void klog(KLogLevel_T level, const char* fmt, ...);

#endif /* KERNEL_LOG_H */
