#include <libs/asm/io.h>
#include <libs/asm/segment.h>
#include <libs/asm/memory.h>
#include <libs/asm/system.h>

void intr_enable(){
    sti();
}

void intr_disable(){
    cli();
}