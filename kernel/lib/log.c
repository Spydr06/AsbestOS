#include "log.h"
#include "../dev/char/console.h"
#include <stdio.h>

static void klog_level(KLogLevel_T level)
{
    switch(level)
    {
    case KLOG_OK:
        fb_color(FB_GREEN, FB_BLACK);
        fb_write(" OK ", 4);
        break;
    case KLOG_INFO:
        fb_color(FB_WHITE, FB_BLACK);
        fb_write("INFO", 4);
        break;
    case KLOG_WARN:
        fb_color(FB_LT_BROWN, FB_BLACK);
        fb_write("WARN", 4);
        break;
    case KLOG_FAIL:
        fb_color(FB_LT_RED, FB_BLACK);
        fb_write("FAIL", 4);
        break;
    default:
        break;
    }
}

void klog(KLogLevel_T level, const char* fmt, ...)
{
    fb_color(FB_LT_GREY, FB_BLACK);
    if(level) {
        fb_write("[", 1);
        klog_level(level);
        fb_color(FB_LT_GREY, FB_BLACK);
        fb_write("] ", 2);
    }
    else
        fb_write("       ", 7);

    va_list ap;
    va_start(ap, fmt);
    vprintf(fmt, ap);
    va_end(ap);

    fb_write("\n", 1);
}
