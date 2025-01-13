
#include <dirent.h>
#include <fcntl.h>
#include "commands.h"
#include "utills.h"

struct linux_dirent64 {
    unsigned long long d_ino;
    long long d_off;
    unsigned short d_reclen;
    unsigned char d_type;
    char d_name[];
};

void print_dir()
{
	char buffer[1024];
	
	getcwd(buffer, sizeof(buffer));
	write_string(buffer);
}

void cat(char *file)
{
	char buffer[buffer_size + 1];
	int read_bytes = 0;
	int fd;

	buffer[buffer_size] = '\0';
	if ((fd = open(file, O_RDONLY)) == -1)
		write_string("\nError opening file\n");
	else 
	{
		while ((read_bytes = read(fd, buffer, buffer_size)))
		{
			buffer[read_bytes] = '\0';
			write_string(buffer);
		}
		 if (read_bytes == -1)
        write_string("\nError reading file\n");
	}
	close(fd);
}

void ls()
{
	int i;
	DIR *dir = opendir(".");
	struct dirent *entry;
	i = 0;
	while ((entry = readdir(dir)) != NULL) 
	{
		if (str_cmp(entry->d_name, ".") == 0 || str_cmp(entry->d_name, "..") == 0)
			continue;
		i++;
    	write_string(entry->d_name);
		write_string("\t");
		if (i % 4 == 0)
			write_string("\n");
	}
closedir(dir);
}

void help()
{
    write_string("This is a list of the shells commands: \n\n\t\
help - The command used to display this text.\n\t\
pwd  - shows the current working directory.\n\t\
echo - prints the text after echo to the standard output.\n\t\
cat  - displays the contents of a file of ascii text.\n\t\
ls   - displays a list of the directories and files from the current directory.\n");
}