/*该文件为信号量结构头文件*/

#ifndef __KERN_SYNC_SEM_H__
#define __KERN_SYNC_SEM_H__

#include<defs.h>
#include<atomic.h>
#include<wait.h>

typedef struct { //定义信号量的数据结构
    int value; //信号量当前值
    wait_queue_t wait_queue; //信号量对应的等待队列
} semaphore_t;

void sem_init(semaphore_t *sem,int value); //信号量的从初始化，参数value为信号量初值
void up(semaphore_t *sem); //V操作
void down(semaphore_t *sem); //P操作
bool try_down(semaphore_t *sem);//信号量>0降1，成功返回1 ???没用过


#endif 