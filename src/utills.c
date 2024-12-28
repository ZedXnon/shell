#include "utills.h"

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