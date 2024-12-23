#define buffer_size 1024
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

static int 		str_cmpp(const char *s1, const char *s2, int num);
static int 		str_cmp(const char *s1, const char *s2);
static void 	check_command(char *terminal_text);
static size_t	get_str_len(char *str);
static void		write_string(char *str);
static void 	cat(char *file);
static void		print_dir();
static void help();

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

static int str_cmp(const char *s1, const char *s2)
{
    int i = 0;
    while (s1[i] && s2[i] && s1[i] == s2[i])
        i++;
    return s1[i] - s2[i];
}

static int str_cmpp(const char *s1, const char *s2, int num)
{
    int i = 0;
    while (s1[i] && s1[i] == s2[i] && i < num - 1)
        i++;
    return s1[i] - s2[i];
}
static void check_command(char *terminal_text)
{
	if (str_cmp(terminal_text, "test") == 0)
		write(1, "Test has been found.", 20);
	else if (str_cmp(terminal_text, "pwd") == 0)
		print_dir();
	else if (str_cmpp(terminal_text, "echo ", 5) == 0)
		write_string(terminal_text + 5);
	else if (str_cmpp(terminal_text, "cat  ", 4) == 0)
		cat(terminal_text + 4);
	else if (str_cmp(terminal_text, "help") == 0)
		help();
}

static size_t get_str_len(char *str)
{
	size_t i;

	i = 0;
	while(str[i])
		i++;
	return (i);
}

static void write_string(char *str)
{
	write(1, str, get_str_len(str));
}

static void print_dir()
{
	char buffer[1024];
	
	getcwd(buffer, sizeof(buffer));
	write_string(buffer);
}

static void cat(char *file)
{
	char buffer[buffer_size + 1];
	int read_bytes = 0;
	int fd;

	buffer[buffer_size] = '\0';
	if ((fd = open(file, 0)) == -1)
		write_string("\nFile Error\n");
	else 
	{
		while ((read_bytes = read(fd, buffer, buffer_size)))
		{
			write_string(buffer);
		}
	}
}

static void help()
{
	write_string("This is a list of the shells coammands: \n\n\t\thelp - The command used to display this text.\n\t\tpwd - shows the current working directory.\n\t\techo - prints the text after echo to the standard ouptut.\n\t\tcat - disaplays the contents of a file of ascii text.\n");
}