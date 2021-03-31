#include <libs/ctype.h>
#include <asm/io.h>
#include <asm/memory.h>
#include <asm/segment.h>
#include <asm/system.h>
#include <libs/elf.h>

#define SECTSIZE    512
#define ELFHDR      ((struct elf_header*)0x10000)

/* 等待disk就绪 */
static void waitdisk(void){
    while((inb(0x1F7) & 0xC0) != 0x40);
}

/* 从start处读出一个扇区 */
static void readsect(void* start, uint32_t secno){
    waitdisk();

    outb(0x1F2, 1);
    outb(0x1F3, secno & 0xFF);
    outb(0x1F4, (secno >> 8) & 0xFF);
    outb(0x1F5, (secno >> 16) & 0xFF);
    outb(0x1F6, ((secno >> 24) & 0xF) | 0xE0);
    outb(0x1F7, 0x20);                      // cmd 0x20 - read sectors

    waitdisk();

    // 读一个sector
    insl(0x1F0, start, SECTSIZE / 4);
}

/* 从某个offset的内核代码中读出count个字节的虚拟地址 */
static void readseg(uptr_t va, uint32_t cnt, uint32_t offset){
    uptr_t end_va = va + cnt;

    va -= offset % SECTSIZE;

    uint32_t secno = (offset / SECTSIZE) + 1;

    for(; va < end_va ; va += SECTSIZE, secno++){
        readsect((void *)va, secno);
    }
}

/* bootmain 是 bootloader的entry */
void bootmain(){
    //读内核镜像
    readseg((uptr_t)ELFHDR, SECTSIZE * 8, 0);

    //检查是不是ELF格式的文件
    if(ELFHDR->elf_magic_number != ELF_MAGIC_NUMBER){
        goto bad;
    }
    
    struct prog_header *ph, *eph;
    
    ph = (struct prog_header *)((uptr_t)ELFHDR + ELFHDR->elf_phoff);
    eph = ph + ELFHDR->elf_phnum;

    for(; ph < eph ; ph++){
        readseg(ph->prog_va & 0xFFFFFF, ph->prog_memsz, ph->prog_offset);
    }
    
    // 现在调用ELF的entry point
    ((void (*)(void))(ELFHDR->elf_entry & 0xFFFFFF))();

bad:
    outw(0x8A00, 0x8A00);
    outw(0x8A00, 0x8E00);

    while(1);
}