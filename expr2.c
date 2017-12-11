//
// Created by 唐艺峰 on 2017/11/30.
//

#include <sys/sem.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "lock_operation.h"

volatile int sum = 0;
int sem_id;

void * thread1_job(void * args) {
    for (int i = 1; i <= 100; i++) {
        P_operation(sem_id, 0);
        sum += i;
        V_operation(sem_id, 1);
    }
    return NULL;
}

void * thread2_job(void * args) {
    for(int i = 1; i <= 100; i++) {
        P_operation(sem_id, 1);
        printf("%d\n", sum);
        V_operation(sem_id, 0);
    }
    return NULL;
}

int main(int argc, char * args[]) {

    sem_id = semget(IPC_PRIVATE, 2, IPC_CREAT | 0666);
    if (sem_id == -1) {
        printf("semget error!");
        exit(1);
    }

    union semun arg1, arg2;
    arg1.val = 1;
    arg2.val = 0;
    if(semctl(sem_id, 0, SETVAL, arg1) == -1 || semctl(sem_id, 1, SETVAL, arg2) == -1) {
        printf("semctl error!");
        exit(1);
    }

    pthread_t thread1, thread2;
    pthread_create(&thread1, NULL, thread1_job, NULL);
    pthread_create(&thread2, NULL, thread2_job, NULL);
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    semctl(sem_id, 0, IPC_RMID, 0);
}