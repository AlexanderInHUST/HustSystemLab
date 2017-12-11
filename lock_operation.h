//
// Created by 唐艺峰 on 2017/11/30.
//

#ifndef COMPUTERSYSTEMLAB_LOCK_OPERATION_H
#define COMPUTERSYSTEMLAB_LOCK_OPERATION_H

#include <sys/sem.h>

void P_operation(int sem_id, unsigned short sem_index);
void V_operation(int sem_id, unsigned short sem_index);

#endif //COMPUTERSYSTEMLAB_LOCK_OPERATION_H
