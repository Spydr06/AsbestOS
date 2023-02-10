#include "keyboard.h"
#include "console.h"
#include "../dev.h"

#include <stdbool.h>
#include <ctype.h>

static const char convtab_capslock[] = {
    '\0', '\e', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b', '\t',
    'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '[', ']', '\n', '\0', 'A', 'S',
    'D', 'F', 'G', 'H', 'J', 'K', 'L', ';', '\'', '`', '\0', '\\', 'Z', 'X', 'C', 'V',
    'B', 'N', 'M', ',', '.', '/', '\0', '\0', '\0', ' '
};

static const char convtab_shift[] = {
    '\0', '\e', '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+', '\b', '\t',
    'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', '\n', '\0', 'A', 'S',
    'D', 'F', 'G', 'H', 'J', 'K', 'L', ':', '"', '~', '\0', '|', 'Z', 'X', 'C', 'V',
    'B', 'N', 'M', '<', '>', '?', '\0', '\0', '\0', ' '
};

static const char convtab_shift_capslock[] = {
    '\0', '\e', '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+', '\b', '\t',
    'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '{', '}', '\n', '\0', 'a', 's',
    'd', 'f', 'g', 'h', 'j', 'k', 'l', ':', '"', '~', '\0', '|', 'z', 'x', 'c', 'v',
    'b', 'n', 'm', '<', '>', '?', '\0', '\0', '\0', ' '
};

static const char convtab_default[] = {
    '\0', '\e', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b', '\t',
    'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n', '\0', 'a', 's',
    'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', '\0', '\\', 'z', 'x', 'c', 'v',
    'b', 'n', 'm', ',', '.', '/', '\0', '\0', '\0', ' '
};

void sys_key_handler(IFrame_T* frame)
{
    uint8_t scan_code = inb(0x60);

    static bool shift_active = false;
    static bool capslock_active = false;
    static bool ctrl_active = false;

    switch(scan_code) {
        case KEY_LEFT_SHIFT:
        case KEY_RIGHT_SHIFT:
            shift_active = true;
            break;
        case KEY_LEFT_SHIFT_RELEASED:
        case KEY_RIGHT_SHIFT_RELEASED:
            shift_active = false;
            break;
        case KEY_CAPS_LOCK:
            capslock_active = !capslock_active;
            break;
        case KEY_CONTROL:
            ctrl_active = true;
            break;
        case KEY_CONTROL_RELEASED:
            ctrl_active = false;
            break;            
        default:
            break;
        }

    char c = '\0';
    if(scan_code <= NUM_KEYS) 
    {
        if(!capslock_active && !shift_active)
            c = convtab_default[scan_code];
        else if(!capslock_active && shift_active)
            c = convtab_shift[scan_code];
        else if(capslock_active && !shift_active)
            c = convtab_capslock[scan_code];
        else if(capslock_active && shift_active)
            c = convtab_shift_capslock[scan_code];

        if(ctrl_active)
            c = toupper(c) - 0x40;
    }
    
    if(c)
        console_write(&c, 1);
}
