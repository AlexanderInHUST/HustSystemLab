//
// Created by 唐艺峰 on 2017/11/30.
//

#include "expr3.h"

int main(int argc, char * args[]) {
    int share_m_id = shmget(1, BUF_LENGTH * BUF_UNIT_SIZE, IPC_CREAT | 0666);
    int key1_id = semget(2, BUF_LENGTH, IPC_CREAT | 0666);
    int key2_id = semget(3, BUF_LENGTH, IPC_CREAT | 0666);

    union semun arg1, arg2;
    arg1.val = 0;
    arg2.val = 1;
    for (int i = 0; i < BUF_LENGTH; i++) {
        semctl(key1_id, i, SETVAL, arg1);
        semctl(key2_id, i, SETVAL, arg2);
    }

    int pid1, pid2;
    pid1 = fork();
    if (pid1 == 0) {
        int result = execl("./read_buf", "read_buf", args[1], NULL);
        exit(abs(result));
    } else {
        pid2 = fork();
        if (pid2 == 0) {
            int result = execl("./write_buf", "write_buf", args[2], NULL);
            exit(abs(result));
        }
    }

    wait(0);
    wait(0);

    semctl(key1_id, 0, IPC_RMID, 0);
    semctl(key2_id, 0, IPC_RMID, 0);
    shmctl(share_m_id, IPC_RMID, 0);
}