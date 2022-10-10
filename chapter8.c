//
// Created by edish on 22-10-10.
//

#include <stdlib.h>
#include "chapter8.h"



//void error(int errnum) {
//    write(2, strerror(errno), strlen(strerror(errno)));
//    exit(errnum);
//}

//cat exercise, 8-1
//ssize_t cat(int argv, unsigned char **buf, char *args[]) {
//    ssize_t charCount = 0;
//    for (int i = 1; i < argv; ++i) {
//        int fd;
//        if ((fd = open(args[i], O_RDONLY, 0)) == -1) {
//            error(1);
//        }
//        struct stat file;
//        fstat(fd, &file);
//        charCount += file.st_size;
//        *buf = realloc(*buf, charCount);
//        if (*buf == NULL) {
//            error(2);
//        }
//        if (read(fd, *buf + charCount - file.st_size, file.st_size) <= 0) {
//            error(3);
//        }
//        close(fd);
//    }
//    (*buf)[charCount] = '\0';
//    return charCount;
//}
FILE *fopen(char *name, const char *mode) {
    int fd;
    FILE *fp = NULL;

    for (int i = 0; i < OPEN_MAX; ++i) {
        if (_iob[i].flag.read != 1 && _iob->flag.write != 1) {
            fp = &_iob[i];
            break;
        }
    }
    if (fp == NULL) {
        return NULL;
    }
    if(*mode != 'w' && *mode != 'r' && *mode != 'a')
        return NULL;
    if(*mode == 'w')
        fd = creat(name, PERMS);
    else if (*mode == 'a') {
        if ((fd = open(name, O_WRONLY, 0)) == -1)
            fd = creat(name, PERMS);
        lseek(fd, 0, 2);
    } else
        fd = open(name, O_RDONLY, 0);
    if(fd == -1)
        return NULL;

    fp->fd = fd;
    fp->base = NULL;
    fp->cnt = 0;
    fp->flag.write = *mode == 'w' ? 1 : 0;
    fp->flag.read = *mode == 'r' ? 1 : 0;
    return fp;
}

int _fillbuf(FILE* file){
    int bufsize;

    if(file->flag.eof == true){
        return EOF;
    }
    bufsize = file->flag.unbuf == true ? 1 : BUFSIZ;
    if (file->base == NULL)
        if((file->base = malloc(bufsize)) == NULL)
            return EOF;
    file->ptr = file->base;
    file->cnt = read(file->fd, file->ptr, bufsize);
    if(--file->cnt <= 0){
        if(file->cnt == -1)
            file->flag.eof = 1;
        else
            file->flag.err = 1;
        file->cnt = 0;
        return EOF;
    }
    return (unsigned char) *file->ptr++;
}