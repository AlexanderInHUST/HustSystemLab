//
// Created by 唐艺峰 on 2017/11/30.
//

#include "expr3.h"

int main(int argc, char * args[]) {
    int share_m_id = shmget(1, BUF_LENGTH * BUF_UNIT_SIZE, IPC_CREAT | 0666);
    int key1_id = semget(2, BUF_LENGTH, IPC_CREAT | 0666);
    int key2_id = semget(3, BUF_LENGTH, IPC_CREAT | 0666);
    int file_fd;
    unsigned short count = 0;
    int n;
    file_fd = open(args[1], O_CREAT | O_RDWR, S_IRWXU | S_IRWXG | S_IRWXO);
    if (file_fd == -1) {
        printf("write open file error!");
        exit(1);
    }

    char * share_m = (char *)shmat(share_m_id, NULL, SHM_R);
    while (1) {
        char * pos = count * BUF_UNIT_SIZE + share_m;
        P_operation(key1_id, count);
        n = *((int *)pos);
        write(file_fd, pos + 4, n);
        printf("%d bytes has been written.\n", n);
        V_operation(key2_id, count);
        count = (unsigned short) ((count + 1) % BUF_LENGTH);
        if (n == -1 || n < BUF_UNIT_SIZE - sizeof(int)) {
            shmdt(share_m);
            fsync(file_fd);
            close(file_fd);
            printf("write done.\n");
            exit(0);
        }
    }
}