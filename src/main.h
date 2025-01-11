#ifndef MAIN_H
#define MAIN_H

#define KEY_UP			"\x1b[A"
#define KEY_DOWN		"\x1b[B"
#define KEY_RIGHT		"\x1b[C"
#define KEY_LEFT		"\x1b[D"
#define KEY_TAB			"\t"
#define KEY_ENTER		"\r"
#define KEY_BACKSPACE	"\b"

static void check_command(char *terminal_text);
void set_raw_mode();

#endif