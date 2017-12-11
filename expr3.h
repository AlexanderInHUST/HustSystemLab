//
// Created by 唐艺峰 on 2017/11/30.
//

#ifndef COMPUTERSYSTEMLAB_EXPR3_H_H
#define COMPUTERSYSTEMLAB_EXPR3_H_H

#include <stdio.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <memory.h>
#include "lock_operation.h"

#define BUF_UNIT_SIZE (512 * sizeof(char) + sizeof(int))
#define BUF_LENGTH 5

#endif //COMPUTERSYSTEMLAB_EXPR3_H_H
