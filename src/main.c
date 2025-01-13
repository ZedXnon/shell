#include <unistd.h>
#include <termios.h>
#include "utills.h"
#include "commands.h"
#include "main.h"
#include <stdio.h>

int main()
{
	size_t i;
	int	status = 1;
	char buffer[buffer_size + 1];
	char *command_history[HISTORY_LENGTH];
	int read_bytes = 0;
	int history_index = 0;
	int history_offset = 0;
	int current_position = 0;
	char c;
	while (history_index < HISTORY_LENGTH)
	{
		command_history[history_index] = NULL;
		history_index++;
	}
	history_index = 0;
	set_raw_mode();
	buffer[buffer_size] = '\0';
	while (status)
	{
		i = 0;
		write(1, "> ", 2);
		c = ' ';
		while (c != '\n')
		{
			read_bytes = read(STDIN_FILENO, &c, 1);
			if (!read_bytes)
			{
				status = 0;
				break;
			}
			if (c == '\x1b')  // If it's the escape character
        	{
				read(STDIN_FILENO, &c, 1);
				if (c == '[')
				{
            		read(STDIN_FILENO, &c, 1);
            		if (c == 'A') 
					{
						if (current_position == 0)
						{
							// save current buffer into temp buffer
						}
						if (history_offset < HISTORY_LENGTH - 1 && current_position > 0)
						{
							if (current_position > 0)
								current_position--;
							else
								current_position = HISTORY_LENGTH - 1;
							history_offset++;
                			write_string("\x1b[2K\r> ");
							str_cpy(command_history[current_position], buffer);
							write_string(command_history[current_position]);
							i = get_str_len(command_history[current_position]);
						}
						//up arrow
           			} 	
					else if (c == 'B') 
					{
						if (history_offset > 0)
						{
							if (current_position < HISTORY_LENGTH - 1)
								current_position++;
							else
								current_position = 0;
							history_offset--;
							write_string("\x1b[2K\r> ");
							if (history_offset > 1)
							{
								str_cpy(command_history[current_position], buffer);
								write_string(command_history[current_position]);
								i = get_str_len(command_history[current_position]);
							}
						}
            	    	// Down Arrow
            		} 
					else if (c == 'C') 
					{
						write(STDIN_FILENO, "\x1b[C", 3);
						i++;
            	    	// Right Arrow
            		} 
					else if (c == 'D' && i > 0) 
					{
						write(STDIN_FILENO, "\x1b[D", 3);
						i--;
            	    	// Left Arrow
            		}
            	}
        	} 
			else
			{
				if (c == 127)
				{
					if (i > 0)
					{
					i--;
					buffer[i] = ' ';
					write(STDIN_FILENO, "\x1b[D", 3);
					write(STDIN_FILENO, " ", 1);
					write(STDIN_FILENO, "\x1b[D", 3);
					}
				}
				else if (is_printable(c))
				{
					write(STDIN_FILENO, &c, 1);
					buffer[i] = c;
					i++;
				}
			}
		}
		history_offset = 0;
		write(1, "\n", 1);
		buffer[i] = '\0';
		if (command_history[history_index] != NULL)
			free(command_history[history_index]);
		command_history[history_index] = strdup(buffer);
		if (history_index < HISTORY_LENGTH - 1)
			history_index++;
		else
			history_index = 0;
		current_position = history_index;
		check_command(buffer);
	}
	return (0);
}

// Checks the entered text against inbuilt commands.
static void check_command(char *terminal_text)
{
	if (str_cmp(terminal_text, "test") == 0)
		write(1, "Test has been found.", 20);
	else if (str_cmp(terminal_text, "pwd") == 0)
		print_dir();
	else if (str_cmpp(terminal_text, "echo ", 5) == 0)
		write_string(terminal_text + 5);
	else if (str_cmpp(terminal_text, "cat ", 4) == 0)
		cat(terminal_text + 4);
	else if (str_cmp(terminal_text, "ls") == 0)
		ls();
	else if (str_cmp(terminal_text, "help") == 0)
		help();
	else
		return;
	write_string("\n");
}

// Sets the terminal to raw mode to allow for more controll
void set_raw_mode()
{
    struct termios newt;
    tcgetattr(STDIN_FILENO, &newt);  // Get the current terminal settings
    newt.c_lflag &= ~(ICANON | ECHO);  // Disable canonical mode and echoing
    newt.c_cc[VMIN] = 1;  // At least 1 byte for reading
    newt.c_cc[VTIME] = 0; // No timeout
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);  // Apply the new settings immediately
}
