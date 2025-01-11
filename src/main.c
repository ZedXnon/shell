#include <unistd.h>
#include <termios.h>
#include "utills.h"
#include "commands.h"
#include "main.h"
#include <stdio.h>

// need to change the funcitonality so that instead of reading the entire string from the terminal into a buffer
// I will sintead read each byte one at a time and analyse them to see if they are characters or if they are arrow or tab keys.
// if it is a char it needs to get added to the next position inside a buffer 
// if it is a special key it then needs to manipulate the cursor if its the arrow keys and move through the command history so everytime I press enter there needs to be soemthing that not only prints the text but also puts it in an array of pointers to arrays of chars that contain the command hsotry and basically the arrow keys will move through the index of the buffer.
// the command history array will be a fixed size which means I should pick a good number probably 20 for now I can always inicrease later.
// going through the buffer needs to compleltey remove what is currently inside the terminal but also save it so bascially the current part of the terminal that is being edited needs to be placed into the array for the command history by default
/*
There needs to be a way of navigating through the command hsitory at any point of entering text and analysing it

*/
int main()
{
	size_t i;
	int	status = 1;
	char buffer[buffer_size + 1];
	int read_bytes = 0;
	char c;
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
                		write_string("Up arrow detected!\n");
           			} 	
					else if (c == 'B') 
					{
            	    	write_string("Down arrow detected!\n");
            		} 
					else if (c == 'C') 
					{
						write(STDIN_FILENO, "\x1b[C", 3);
						i++;
            	    	//write_string("Right arrow detected!\n");
            		} 
					else if (c == 'D' && i > 0) 
					{
						write(STDIN_FILENO, "\x1b[D", 3);
						i--;
            	    	//write_string("Left arrow detected!\n");
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
				if (c == 37 && i > 0)
					i--;
				if (c == 39)
					i++;
				else if (is_printable(c))
				{
					write(STDIN_FILENO, &c, 1);
					buffer[i] = c;
					i++;
				}
			}
		}
		write(1, "\n", 1);
		buffer[i] = '\0';
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

// need to add another command to edit files/ create them
// need to add a command history with keyboard keys.
// need to add tab autocompletion in alphabetical order 