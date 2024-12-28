#define buffer_size 1024
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include "utills.h"
#include "commands.h"

static void check_command(char *terminal_text);

int main()
{
	int	status = 1;
	char buffer[buffer_size];
	int no_chars = 0;

	while (status)
	{
		write(1, "> ", 2);
		no_chars = read(0, buffer, buffer_size) - 1;
		buffer[buffer_size - 1] = '\0';
		buffer[no_chars] = '\0';
		check_command(buffer);
		write(1, "\n", 1);
	}
	return (0);
}

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
}

// need to add another command to edit files/ create them
// need to add a command history with keyboard keys.
// need to add tab autocompletion in alphabetical order 