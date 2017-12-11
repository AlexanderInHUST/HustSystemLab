//
// Created by 唐艺峰 on 2017/12/11.
//

#ifndef COMPUTERSYSTEMLAB_EXPR4_H
#define COMPUTERSYSTEMLAB_EXPR4_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <unistd.h>
#include <fcntl.h>

struct DirMem {
    char ** dirs;
    char ** files;
    int dirNum;
    int fileNum;
};

void handleFiles(char * fileName, char * address);
int traversalCurDir(char * dirName);
void handleDirs(char * address, int fileNum);

#endif //COMPUTERSYSTEMLAB_EXPR4_H
