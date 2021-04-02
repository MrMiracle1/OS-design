/*该文件用于定义同步机制中开关可屏蔽终端（INTR）的操作*/
#ifndef __KERN_SYNC_SYNC_H__
#define __KERN_SYNC_SYNC_H__

#include <libs/asm/system.h>
#include <mm/mmu.h>

static inline bool __intr_save(void){
    if(read_eflags()&FL_IF){ //查询EFLAGS寄存器，标志位能响应可屏蔽中断
        intr_disable();//关中断 ???为什么要先在intr.h中引用cli
        return 1;
    }
    return 0;
}

static inline void __intr_restore(bool flag){
    if(flag){
        intr_enable(); //开中断
    }
}






#define local_intr_save(x) do{x=__intr_save();}while(0)//关中断 x置1成功关中断，置0失败
#define local_intr_restore(x) __intr_restore(x);

#endif