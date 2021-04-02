#ifndef __BOOT_ASM_H__
#define __BOOT_ASM_H__

/* 两个字，四个字节，总共8字节*/
#define SEG_NULLASM
    .word 0, 0;
    .byte 0, 0, 0, 0

#define SEG_ASM(type, base, lim)
    .word (((lim) >> 12) & 0xffff), ((base) & 0xffff);
    .byte (((base) >> 16) & 0xff), (0x90 | (type)),
        (0xC0 | (((lim) >> 28) & 0xf)), (((base) >> 24) & 0xff)

/* 段类型bit */
#define STA_X       0x8 //可执行段
#define STA_E       0x4 //扩展(不可执行段)
#define STA_C       0x4 //代码段 (executable only)
#define STA_W       0x2 // Writeable (non-executable segments)
#define STA_R       0x2 // Readable (executable segments)
#define STA_A       0x1 // Accessed

#endif