//
// Created by 唐艺峰 on 2017/12/11.
//

#include <sys/stat.h>
#include "expr4.h"

int traversalCurDir(char * dirName) {
    DIR * curDir = opendir(dirName);
    struct DirMem dirMem;
    struct dirent * each;
    dirMem.dirs = (char **) malloc(sizeof(char *));
    dirMem.files = (char **) malloc(sizeof(char *));
    dirMem.dirNum = 0;
    dirMem.fileNum = 0;
    int fileNum = 0;

    readdir(curDir);
    readdir(curDir);
    while ((each = readdir(curDir)) != 0) {
        if (each->d_type == DT_DIR) {
            char * addrs = (char *) malloc (sizeof(char) * (strlen(dirName) + strlen(each->d_name) + 2));
            strcpy(addrs, dirName);
            strcat(addrs, "/");
            strcat(addrs, each->d_name);
            dirMem.dirs[dirMem.dirNum] = (char *) malloc(sizeof(char) * (strlen(addrs) + 1));
            strcpy(dirMem.dirs[dirMem.dirNum], addrs);
            dirMem.dirNum++;
            dirMem.dirs = realloc(dirMem.dirs, sizeof(char *) * (dirMem.dirNum + 1));
            free(addrs);
        } else {
            dirMem.files[dirMem.fileNum] = (char *) malloc(sizeof(char) * (strlen(each->d_name) + 1));
            strcpy(dirMem.files[dirMem.fileNum], each->d_name);
            dirMem.fileNum++;
            dirMem.files = realloc(dirMem.files, sizeof(char *) * (dirMem.fileNum + 1));
        }
    }
    handleDirs(dirName, dirMem.fileNum);
    for (int i = 0; i < dirMem.fileNum; i++) {
        handleFiles(dirName, dirMem.files[i]);
    }
    for (int i = 0; i < dirMem.dirNum; i++) {
        fileNum += traversalCurDir(dirMem.dirs[i]);
        free(dirMem.dirs[i]);
    }
    free(dirMem.dirs);
    closedir(curDir);
    return fileNum;
}

void handleDirs(char * address, int fileNum) {
    printf("\n%s:\n", address);
    printf("total %d\n", fileNum);
}

void handleFiles(char * address, char * fileName) {
    struct stat * buf = (struct stat *) malloc(sizeof(struct stat));
    char * addrs = (char *) malloc (sizeof(char) * (strlen(address) + strlen(fileName) + 2));
    strcpy(addrs, address);
    strcat(addrs, "/");
    strcat(addrs, fileName);
    stat(addrs, buf);
    printf("%llu %s %s\n", buf->st_size, address, fileName);
    free(buf);
    free(addrs);
}

int main(int argc, char * args[]) {
    traversalCurDir(args[1]);
}