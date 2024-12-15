#define buffer_size 1024
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

static int str_cmpp(const char *s1, const char *s2, int num);
static int 	str_cmp(const char *s1, const char *s2);
static void check_command(char *terminal_text);
size_t 		get_str_len(char *str);
void		write_string(char *str);
void		print_dir();

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
	{
		write_string(terminal_text + 5);
	}
}

size_t get_str_len(char *str)
{
	size_t i;

	i = 0;
	while(str[i])
		i++;
	return (i);
}

void write_string(char *str)
{
	write(1, str, get_str_len(str));
}

void print_dir()
{
	char buffer[1024];
	
	getcwd(buffer, sizeof(buffer));
	write_string(buffer);
}
