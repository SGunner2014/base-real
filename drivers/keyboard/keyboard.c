#include "keyboard.h"
#include "../../core/cpu/isr.h"
#include "../../core/cpu/ports.h"
#include "../screen/screen_buffer.h"
#include "../console/console.h"
#include "../../libc/function.h"
#include "../../libc/string.h"
#include "../../kmain.h"

#define SCAN_MAX 57
#define RELEASE_KEY 0x80
#define L_SHIFT 0x2A
#define R_SHIFT 0x36
#define CAPS_LOCK 0x3A
#define BACKSPACE 0x0E
#define ENTER 0x1C

static char key_buffer[256];

const char *sc_name[] = {"ERROR", "Esc", "1", "2", "3", "4", "5", "6",
                         "7", "8", "9", "0", "-", "=", "Backspace", "Tab", "Q", "W", "E",
                         "R", "T", "Y", "U", "I", "O", "P", "[", "]", "Enter", "Lctrl",
                         "A", "S", "D", "F", "G", "H", "J", "K", "L", ";", "'", "`",
                         "LShift", "\\", "Z", "X", "C", "V", "B", "N", "M", ",", ".",
                         "/", "RShift", "Keypad *", "LAlt", "Spacebar"};
const char sc_ascii[] = {'?', '?', '1', '2', '3', '4', '5', '6',
                         '7', '8', '9', '0', '-', '=', '?', '?', 'q', 'w', 'e', 'r', 't', 'y',
                         'u', 'i', 'o', 'p', '[', ']', '?', '?', 'a', 's', 'd', 'f', 'g',
                         'h', 'j', 'k', 'l', ';', '\'', '#', '?', '\\', 'z', 'x', 'c', 'v',
                         'b', 'n', 'm', ',', '.', '/', '?', '?', '?', ' '};
const char sc_uppercase[] = {'?', '?', '!', '@', '#', '$', '%', '^',
                             '&', '*', '(', ')', '_', '+', '?', '?', 'Q', 'W', 'E', 'R', 'T', 'Y',
                             'U', 'I', 'O', 'P', '{', '}', '?', '?', 'A', 'S', 'D', 'F', 'G',
                             'H', 'J', 'K', 'L', ':', '@', '~', '?', '|', 'Z', 'X', 'C', 'V',
                             'B', 'N', 'M', '<', '>', '?', '?', '?', '?', ' '};

static void handle_keyboard_interrupt(registers_t *register_state)
{
    // scancode will be in port 0x60
    uint8_t scancode = port_byte_in(0x60);

    // See if we've released a key
    uint8_t released = RELEASE_KEY & scancode;
    if (released)
    {
        released = scancode ^ RELEASE_KEY;

        switch (released)
        {
        case L_SHIFT:
            kflags.lshift = 0;
            break;
        case R_SHIFT:
            kflags.rshift = 0;
            break;
        }

        UNUSED(register_state);
        return;
    }
    else
    {
        switch (scancode)
        {
        case L_SHIFT:
            kflags.lshift = 1;
            break;
        case R_SHIFT:
            kflags.rshift = 1;
            break;
        default:
            process_keypress(scancode);
        }
    }
}

void process_keypress(uint8_t scancode)
{
    if (scancode > SCAN_MAX)
        return;

    if (scancode == BACKSPACE)
    {
        int len = backspace(key_buffer);
        if (len > 0)
            print_backspace();
    }
    else if (scancode == ENTER)
    {
        write("\n");
        on_user_input(key_buffer);
        key_buffer[0] = '\0';
    }
    else
    {
        char letter;
        if (kflags.caps || kflags.lshift || kflags.rshift)
        {
            letter = sc_uppercase[(int)scancode];
        }
        else
        {
            letter = sc_ascii[(int)scancode];
        }

        char str[2] = {letter, '\0'};
        str_append(key_buffer, letter);
        write(str);
    }
}

// Initialises the keyboard
void init_keyboard()
{
    register_handler(IRQ_1, handle_keyboard_interrupt);
}