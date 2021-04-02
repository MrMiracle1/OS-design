/* 该文件为等待队列结构的头文件*/

#ifndef __KERN_SYNC_WAIT_H__
#define __KERN_SYNC_WAIT_H__

#include<libs/stl/list.h>
#include<libs/stddef.h>

typedef struct{//等待队列结构
    list_entry wait_head//队列头
} wait_queue_t;

struct proc_struct;

typedef struct {
    struct proc_struct *proc;//等待进程的指针
    uint32_t wakeup_flags;//进程被放入等待队列的原因
    wait_queue_t *wait_queue;//wait结构属于等待队列
    list_entry wait_link;//对应的list节点
}wait_t;

//实现wait_t中成员的指针向wait_t 指针的转化 ???
#define le2wait(le,member) \
    to_struct((le),wait_t,member)

void wait_init(wait_t *wait,struct proc_struct *proc); //wait初始化
void wait_queue_init(wait_queue_t *queue);//等待队列初始化
void wait_queue_add(wait_queue_t *queue,wait_t *wait);//等待队列增加
void wait_queue_del(wait_queue_t *queue,wait_t *wait);//等待队列减少

wait_t *wait_queue_next(wait_queue_t *queue,wait_t *wait);//获取下一个wait节点
wait_t *wait_queue_prev(wait_queue_t *queue,wait_t *wait);//获取前一个wait节点
wait_t *wait_queue_first(wait_queue_t *queue);//获取第一个等待节点
wait_t *wait_queue_last(wait_queue *queue);//获取最后一个等待节点

bool wait_queue_empty(wait_queue_t *queue);//判断等待队列为空
bool wait_in_queue(wait_t *wait);//???
void wakeup_wait(wait_queue_t *queue,wait_t *wait,uint32_t wakeup_flags,bool del);//将wait从等待队列中删除
void wakeup_first(wait_queue_t *queue,uint32_t wakeup_flags,bool del);//唤醒队列头wait
void wakeup_queue(wait_queue_t *queue,uint32_t wakeup_flags,bool del);//唤醒队列中所有进程

void wait_current_set(wait_queue_t *queue,wait_t *wait,uint32_t wait_state);//让wait与进程关联，且让当前进程关联的wait进入等待队列queue，当前进程睡眠

#define wait_current_del(queue,wait)                        \
    do{                                                     \
        if(wait_in_queue(wait)){                            \
            wait_queue_del(queue,wait);                     \
        }                                                   \
    } while(0)



#endif