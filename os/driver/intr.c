#include <libs/asm/io.h>
#include <libs/asm/segment.h>
#include <libs/asm/memory.h>
#include <libs/asm/system.h>

void intr_enable(){
    sti(); //汇编指令，允许中断发生
}

void intr_disable(){
    cli(); //汇编指令，禁止中断发生
}