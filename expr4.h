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
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

void handleFiles(struct stat * file, char * name, long long maxSize);
void traversalCurDir(char * dirName);
void handleDirs(char *address, long fileSize);
void handleFileKind(int fileMode);
void handleFilePermission(int fileMode);
void handleFileUser(uid_t st_uid);
void handleFileSize(off_t st_size, off_t maxSize);
void handleDate(struct timespec birth);

#endif //COMPUTERSYSTEMLAB_EXPR4_H
