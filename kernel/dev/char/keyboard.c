#include "keyboard.h"

static char keymap_us[NUM_KEYS] = {
    [KEY_NULL] = '\0',
    [KEY_ESCAPE] = '\0',
    [KEY_1] = '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=',
    [KEY_BACKSPACE] = '\b',
    [KEY_TAB] = '\t',
    [KEY_Q] = 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']',
    [KEY_ENTER] = '\n',
    [KEY_CONTROL] = '\0',
    [KEY_A] = 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'',
    [KEY_LEFT_SHIFT] = '\0',
    [KEY_BACKSLASH] = '\\',
    [KEY_Z] = 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/',
    [KEY_RIGHT_SHIFT] = '\0',
    [KEY_ASTERISK] = '*',
    [KEY_SPACE] = ' ',
    0
};

char kb_get_char(uint8_t scan_code)
{
    if(scan_code < 0x81)
        return keymap_us[scan_code];
    else
        return '\0';
}
