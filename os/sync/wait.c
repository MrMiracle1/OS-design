/* 该文件为等待队列结构的源文件*/

#include<proc/proc.h>
#include<libs/stddef.h>
#include<libs/stl/list.h>
#include<../wait.h>
#include<sync.h>


void wait_init(wait_t *wait,struct proc_struct *proc){
    wait->proc=proc;//wait与进程绑定
    wait->wakeup_flags=WT_INTERRUPTED;//等待原因设置为可打断
    list_init(&(wait->wait_link));//list节点初始化
}

void wait_queue_init(wait_queue_t *queue){
    list_init(&queue->wait_head);//等待队列初始化
}

void wait_queue_add(wait_queue_t *queue,wait_t *wait){
    assert(list_empty(&(wait->wait_link))&&wait->proc!=NULL);//确定wait节点有效 ???list_empty
    wait->wait_queue=queue//标识所属序列
    list_add_before(&(queue->wait_head),&(wait->wait_link));//再list前端加入节点
}

void wait_queue_next(wait_queue_t *queue,wait_t *wait){
    assert(!list_empty(&(wait->wait_link))&&wait->wait_queue==queue);
    list_del_init(&(wait->wait_link));//队列中删除wait
}

wait_t* wait_queue_next(wait_queue_t *queue,wait_t *wait){
    assert(!list_empty(&(wait->wait_link))&&wait->wait_queue==queue);
    list_entry *le=list_next(&wait->wait_link);//获得下一个节点
    if(le!=&(queue->wait_head)){//如果不为队列头
        return le2wait(le,wait_link);//将list节点转化为wait节点
    }
    return NULL;//若为队列头返回空
} 

wait_t* wait_queue_prev(wait_queue_t *queue,wait_t *wait){
    assert(!list_empty(&(wait->wait_link))&&wait->wait_queue==queue);
    list_entry *le=list_prev(&(wait->wait_link));//获得下一个节点
    if(le!=&(queue->wait_head)){//如果不为队列头
        return le2wait(le,wait_link);//将list节点转化为wait节点
    }
    return NULL;//若为队列头返回空
} 

wait_t* wait_queue_first(wait_queue_t *queue){
    list_entry *le=list_next(&(queue->wait_head));//获得下一个节点
    if(le!=&(queue->wait_head)){//如果不为队列头
        return le2wait(le,wait_link);//将list节点转化为wait节点
    }
    return NULL;//若为队列头返回空
}

wait_t* wait_queue_last(wait_queue_t *queue){
    list_entry *le=list_prev(&(queue->wait_head));//获得下一个节点
    if(le!=&(queue->wait_head)){//如果不为队列头
        return le2wait(le,wait_link);//将list节点转化为wait节点
    }
    return NULL;//若为队列头返回空
} 

bool wait_queue_empty(wait_queue_t *queue){
    return list_rmpty(&(queue->wait_head));
}

bool wait_queue_empty(wait_queue_t *queue){
    return list_rmpty(&(queue->wait_head));
}

void wakeup_wait(wait_queue_t *queue,wait_t *wait,uint32_t wakeup_flags,bool del){
    if(del)//若要将节点从队列中删除
    {
        wait_queue_del(queue,wait);//将wait节点从队列中删除
    }
    wait->wakeup_flags=wakeup_flags;//更改等待原因
    wakeup_proc(wait->proc);//唤醒对应进程
}

void wakeup_first(wait_queue_t *queue,uint32_t wakeup_flags,bool del){
    wait_t *wait;
    if((wait=wait_queue_first(queue))!=NULL){//获取等待队列中的第一个节点，将其删除
       if (del) {
            do {//将队列中进程逐一唤醒
                wakeup_wait(queue, wait, wakeup_flags, 1);
            } while ((wait = wait_queue_first(queue)) != NULL);
        }
    }
    else{
        do{
            wakeup_wait(queue,wait,wakeup_flags,0);
        }while((wait=wait_queue_next(queue,wait))!=NULL);
    }
}

void wakeup_queue(wait_queue_t *queue,uint32_t wakeup_flags,bool del)
{
    wait_t *wait;
    if((wait=wait_queue_first(queue))!=NULL){//获取等待队列中的第一个节点，将其删除
        wakeup_wait(queue,wait,wakeup_flags,del);
    }
}

wait_current_set(wait_queue_t *queue,wait_t *wait,uint32_t wait_state){//???
    assert(current!=NULL);
    wait_init(wait,current);
    current->state=PROC_SLEEPING;
    currnet->wait_state=wait_state;
    wait_queue_add(queue,wait);
}





