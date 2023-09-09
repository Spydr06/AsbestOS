#include <memory.h>
#include "boot/limine.h"

static volatile struct limine_framebuffer_request framebuffer_request = {
    .id = LIMINE_FRAMEBUFFER_REQUEST,
    .revision = 0
};

extern void _halt(void);

void kmain(void) {
    if(framebuffer_request.response == NULL || framebuffer_request.response->framebuffer_count < 1) {
        _halt();
    }

    struct limine_framebuffer *framebuffer = framebuffer_request.response->framebuffers[0];
    // Note: we assume the framebuffer model is RGB with 32-bit pixels.
    for (size_t i = 0; i < 100; i++) {
        uint32_t *fb_ptr = framebuffer->address;
        fb_ptr[i * (framebuffer->pitch / 4) + i] = 0xffffff;
    }
};
