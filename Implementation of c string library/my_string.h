#ifndef _MY_STRING_H_
#define _MY_STRING_H_
#include <stdio.h>
#include <stdlib.h>
typedef unsigned int uint ;
void *Memcpy (void *dest, const void *src, uint n);
void *Memmove (void *dest, const void *src, uint n);
void *Memchr (const void *s, int c, uint n);
int Memcmp (const void *s1, const void *s2, uint n);
void *Memset (void *, int c, uint n);
char *Strcat (char *dest, const char *src);
char *Strncat (char *dest, const char *src, uint n);
char *Strchr (const char *, int c);
char *Strrchr (const char *, int c);
int Strcmp (const char *, const char *);
int Strncmp (const char *, const char *, uint n);
//I implemented like strcpy didn't get the purpose of it
uint Strxfrm(char *, const char *, uint);
uint sel_Strcspn(const char *str1, const char *str2,int is_strcspn);
uint Strcspn(const char *, const char *);
char *Strpbrk(const char *, const char *);
char *Strstr(const char *, const char *);
char *Strtok(char *, const char *);
char* Strerror(int errnum);
uint Strlen(const char* s);

#endif
