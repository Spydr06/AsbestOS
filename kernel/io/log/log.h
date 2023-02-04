#ifndef KERNEL_LOG_H
#define KERNEL_LOG_H

enum klog_severity {
    KLOG_NONE,

    KLOG_OK,
    KLOG_INFO,
    KLOG_WARN,
    KLOG_FAIL,
};

void klog(enum klog_severity severity, const char* fmt, ...);

#endif /* KERNEL_LOG_H */
