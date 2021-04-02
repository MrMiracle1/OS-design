/*该文件为信号量结构源文件*/

#include <libs/ctype.h>
#include <wait.h>
#include <atomic.h>//???
#include <sem.h>
//#include <proc.h>
#include <sync.h>
#include <assert.h>

void sem_init(semaphore_t *sem,int value){
    sem->value=value; //给信号量赋初值
    wait_queue_init(&(sem->wait_queue)); //等待队列初始化
}

static __noinline uint32_t __up(semaphore_t *sem,uint32_t wait_state){  //???_noinline
    bool intr_flag;//???有啥用
    local_intr_save(intr_flag);//关中断
    {
        wait_t *wait;
        if((wait=wait_queue_first(&(sem->wait_queue)))==NULL){//等待队列为空
            sem->value++;//信号量值增加
        }
        else{//等待队列不为空
            assert(wait->proc_wait_state==wait_state)//断言进程等待原因是等待信号量
            wakeup_wait(&(sem->wait_queue),wait,wait_state,1);//唤醒进程
        }
    }
    local_intr_restore(inter_flag);//开中断
}

static __noinline uint32_t __down(semaphore_t *sem,uint32_t wait_state){ //???state
    bool intr_flag;//???
    local_intr_save(intr_flag); //关中断
    if(sem-value>0){ //信号量可用
        sem->value--;//信号量值减少
        local_intr_restore(intr_flag); //开中断
        return 0;
    }
    wait_t __wait,*wait=&__wait; //???*& __
    wait_current_set(&(sem->wait_queue),wait,wait_state);//当前进程加入等待序列
    local_intr_restore(intr_flag); //开中断

    schedule(); //运行调度器选择其他进程执行，当前进程等待被唤醒

    //被V操作唤醒
    local_intr_save(intr_flag);//关中断
    wait_current_del(&(sem->wait_queue),wait);//当前进程从等待队列删除
    local_intr_restore(intr_flag);//开中断

    if(wait->wakeup_flag!=wait_state){ //如果等待原因不是信号量
        return wait->wakeup_flags//返回非0
    }
    return 0; 
}


void up(semaphore_t *sem){
    __up(sem,WT_KSEM);
}

void down(semaphore_t *sem){
    uint32_t flags=__down(sem,WT_KSEM);
    assert(flags==0);//断言唤醒原因为信号量
}

bool try_down(semaphore_t *sem){
    bool intr _flag,ret=0;
    local_intr_save(intr_flag);//关中断
    if(sem->value>0){
        sem->value--,ret=1;
    }
    local_intr_restore(intr_flag);//开中断
    return ret;
}