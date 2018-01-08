#ifndef _CUTILS_KLOG_H_
#define _CUTILS_KLOG_H_

#include <sys/cdefs.h>
#include <stdarg.h>

__BEGIN_DECLS

void klog_init(void);
int  klog_get_level(void);
void klog_set_level(int level);
/* TODO: void klog_close(void); - and make klog_fd users thread safe. */
void klog_write(int level, const char *fmt, ...)
    __attribute__ ((format(printf, 2, 3)));
void klog_vwrite(int level, const char *fmt, va_list ap);

__END_DECLS

#define KLOG_ERROR_LEVEL   3
#define KLOG_WARNING_LEVEL 4
#define KLOG_NOTICE_LEVEL  5
#define KLOG_INFO_LEVEL    6
#define KLOG_DEBUG_LEVEL   7

#define KLOG_ERROR(tag,x...)   klog_write(KLOG_ERROR_LEVEL, "<3>" tag ": " x)
#define KLOG_WARNING(tag,x...) klog_write(KLOG_WARNING_LEVEL, "<4>" tag ": " x)
#define KLOG_NOTICE(tag,x...)  klog_write(KLOG_NOTICE_LEVEL, "<5>" tag ": " x)
#define KLOG_INFO(tag,x...)    klog_write(KLOG_INFO_LEVEL, "<6>" tag ": " x)
#define KLOG_DEBUG(tag,x...)   klog_write(KLOG_DEBUG_LEVEL, "<7>" tag ": " x)

#define KLOG_DEFAULT_LEVEL  3  /* messages <= this level are logged */

#endif
