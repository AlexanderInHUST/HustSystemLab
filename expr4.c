//
// Created by 唐艺峰 on 2017/12/11.
//

#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include "expr4.h"

void traversalCurDir(char *dirName) {
    DIR *curDir = opendir(dirName);
    chdir(dirName);
    struct dirent *each;
    long fileSize = 0;
    long long maxSize = 0;
    while ((each = readdir(curDir)) != 0) {
        if (each->d_name[0] == '.') {
            continue;
        }
        struct stat *buf = (struct stat *) malloc(sizeof(struct stat));
        stat(each->d_name, buf);
        fileSize += buf->st_blocks * S_BLKSIZE;
        if (buf->st_size > maxSize) {
            maxSize = buf->st_size;
        }
        free(buf);
    }
    handleDirs(dirName, fileSize / 512);
    closedir(curDir);

    curDir = opendir(dirName);
    while ((each = readdir(curDir)) != 0) {
        if (each->d_name[0] == '.') {
            continue;
        }
        struct stat *buf = (struct stat *) malloc(sizeof(struct stat));
        stat(each->d_name, buf);
        handleFiles(buf, each->d_name, maxSize);
        free(buf);
    }
    closedir(curDir);

    curDir = opendir(dirName);
    while ((each = readdir(curDir)) != 0) {
        if (each->d_name[0] == '.') {
            continue;
        }
        if (each->d_type == DT_DIR) {
            char *addrs = (char *) malloc(sizeof(char) * (strlen(dirName) + strlen(each->d_name) + 2));
            strcpy(addrs, dirName);
            strcat(addrs, "/");
            strcat(addrs, each->d_name);
            traversalCurDir(addrs);
            free(addrs);
        }
    }
    closedir(curDir);
}

void handleDirs(char *address, long fileSize) {
    printf("\n%s:\n", address);
    if (fileSize != 0) {
        printf("total %ld\n", fileSize);
    }
}

void handleFiles(struct stat *file, char *name, long long maxSize) {
    handleFileKind(file->st_mode);
    handleFilePermission(file->st_mode);
    handleFileUser(file->st_uid);
    handleFileSize(file->st_size, maxSize);
    handleDate(file->st_mtimespec);
    printf("%s\n", name);
}

void handleDate(struct timespec birth) {
    struct tm t;
    char date_time[64];
    strftime(date_time, sizeof(date_time), "%Y-%m-%d %H:%M:%S", localtime_r(&birth.tv_sec, &t));
    printf("%s ", date_time);
}

void handleFileUser(uid_t st_uid) {
    struct passwd *user;
    struct group *group;
    user = getpwuid(st_uid);
    group = getgrgid(user->pw_gid);
    printf("%s %s ", user->pw_name, group->gr_name);
}

void handleFileSize(off_t st_size, off_t maxSize) {
    char maxArrays[50], curArrays[50];
    sprintf(maxArrays, "%lld", maxSize);
    sprintf(curArrays, "%lld", st_size);
    size_t blank = strlen(maxArrays) - strlen(curArrays);
    for (int i = 0; i < blank; i++) {
        putchar(' ');
    }
    printf("%s ", curArrays);
}

void handleFilePermission(int fileMode) {
    int filePermission = fileMode & 0777;
    int readMask = 0400;
    int writeMask = 0200;
    int executeMask = 0100;
    for (int i = 0; i < 3; i++) {
        if (filePermission & readMask) {
            putchar('r');
        } else {
            putchar('-');
        }
        if (filePermission & writeMask) {
            putchar('w');
        } else {
            putchar('-');
        }
        if (filePermission & executeMask) {
            putchar('x');
        } else {
            putchar('-');
        }
        readMask >>= 3;
        writeMask >>= 3;
        executeMask >>= 3;
    }
    putchar(' ');
}

void handleFileKind(int fileMode) {
    int fileKind = fileMode & 0770000;
    switch (fileKind) {
        case S_IFDIR: {
            putchar('d');
            break;
        }
        case S_IFCHR: {
            putchar('c');
            break;
        }
        case S_IFBLK: {
            putchar('b');
            break;
        }
        case S_IFREG: {
            putchar('-');
            break;
        }
        case S_IFLNK: {
            putchar('l');
            break;
        }
        case S_IFSOCK: {
            putchar('s');
            break;
        }
        case S_IFIFO: {
            putchar('p');
            break;
        }
        default:
            break;
    }
}

int main(int argc, char *args[]) {
    traversalCurDir(args[1]);
}