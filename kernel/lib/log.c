#include "log.h"
#include "../dev/char/console.h"
#include <stdio.h>

static void klog_level(KLogLevel_T level)
{
    switch(level)
    {
    case KLOG_OK:
        console_color(FB_GREEN, FB_BLACK);
        console_write(" OK ", 4);
        break;
    case KLOG_INFO:
        console_color(FB_WHITE, FB_BLACK);
        console_write("INFO", 4);
        break;
    case KLOG_WARN:
        console_color(FB_LT_BROWN, FB_BLACK);
        console_write("WARN", 4);
        break;
    case KLOG_FAIL:
        console_color(FB_LT_RED, FB_BLACK);
        console_write("FAIL", 4);
        break;
    default:
        break;
    }
}

void klog(KLogLevel_T level, const char* fmt, ...)
{
    console_color(FB_LT_GREY, FB_BLACK);
    if(level) {
        console_write("[", 1);
        klog_level(level);
        console_color(FB_LT_GREY, FB_BLACK);
        console_write("] ", 2);
    }
    else
        console_write("       ", 7);

    va_list ap;
    va_start(ap, fmt);
    vprintf(fmt, ap);
    va_end(ap);

    console_write("\n", 1);
}
