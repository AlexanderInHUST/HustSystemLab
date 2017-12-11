//
// Created by 唐艺峰 on 2017/11/30.
//

#include "lock_operation.h"

void P_operation(int sem_id, unsigned short sem_index) {
    struct sembuf sem;
    sem.sem_num = sem_index;
    sem.sem_op = -1;
    sem.sem_flg = 0;
    semop(sem_id, &sem, 1);
}

void V_operation(int sem_id, unsigned short sem_index) {
    struct sembuf sem;
    sem.sem_num = sem_index;
    sem.sem_op = 1;
    sem.sem_flg = 0;
    semop(sem_id, &sem, 1);
}