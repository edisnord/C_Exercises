//
// Created by edish on 22-10-10.
//

#ifndef TEST_CHAPTER8_H
#define TEST_CHAPTER8_H

#include "syscall.h"
#include "fcntl.h"
#include <unistd.h>
#include "stdarg.h"
#include "stdbool.h"

//cat exercise, 8-1
//ssize_t cat(int argv, unsigned char **buf, char *args[]);

//fopen and fillbuf, 8-2
#define NULL 0
#define EOF (-1)
#define BUFSIZ 1024
#define OPEN_MAX 20
#define PERMS 0666

typedef struct _iobuf {
    size_t cnt;
    char *ptr;
    char *base;
    struct flag {
        int read: 1;
        int write: 1;
        int unbuf: 1;
        int eof: 1;
        int err: 1;
    } flag;
    int fd;
} FILE;

extern FILE _iob[OPEN_MAX] = { {0, (char *) 0, (char *) 0, {1, 0, 0, 0, 0}, 0},
                               {0, (char *) 0, (char *) 0, {0,1,0,0,0}, 1},
                               {0, (char *) 0, (char *) 0, {0, 1, 1, 0, 0}, 2} };

#define stdin   (&_iob[0])
#define stdout  (&_iob[1])
#define stderr  (&_iob[2])

bool checkFlags(FILE *file, ...);

int _fillbuf(FILE *file);

//8-3
int _flushbuf(char a, FILE *file);

int fflush(FILE* file);

int fclose(FILE* file);
//8-3

//8-4
int fseek(FILE* file, long offset, int origin);
//8-4

//8-6
void* calloc2(unsigned int n, unsigned long size);
//8-6

FILE* fopen(char* name, const char *mode);

#define getc(p) --(p)->cnt >= 0 \
                ? (unsigned char) *(p)->ptr++ : _fillbuf((p))
#define putc(x,p) --(p)->cnt >= 0 \
                ? *(p)->ptr++ = (x): _flushbuf((x), (p))

#define getchar() getc(stdin)
#define putchar(x) putc((x), stdout)

#endif //TEST_CHAPTER8_H
