#include "utills.h"

int is_printable(char c)
{
	return (c >= 26 && c <= 126);
}

int str_cmp(const char *s1, const char *s2)
{
    int i = 0;
    while (s1[i] && s2[i] && s1[i] == s2[i])
        i++;
    return s1[i] - s2[i];
}

int str_cmpp(const char *s1, const char *s2, int num)
{
    int i = 0;
    while (s1[i] && s1[i] == s2[i] && i < num - 1)
        i++;
    return s1[i] - s2[i];
}

size_t get_str_len(const char *str)
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

char *strdup(const char *string)
{
	char *copy;
	int i = 0;
	int len = get_str_len(string);
	copy = (char *)malloc(sizeof(char) * (len + 1));
	copy[len] = '\0';
	while (i < len)
	{
		copy[i] = string[i];
		i++;
	}
	return (copy);
}

void str_cpy(const char *str1, char *str2)
{
	int i = 0;
	while (str1[i])
	{
		str2[i] = str1[i]; 
		i++;
	}
	str2[i] = '\0'; 
}