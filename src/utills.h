#ifndef UTILLS_H
#define UTILLS_H

#include <unistd.h>
#include <stdlib.h>

#define buffer_size 1024

int str_cmp(const char *s1, const char *s2);
int str_cmpp(const char *s1, const char *s2, int num);
size_t get_str_len(const char *str);
void write_string(char *str);
int is_printable(char c);
char *strdup(const char *string);
void str_cpy(const char *str1, char *str2);

#endif