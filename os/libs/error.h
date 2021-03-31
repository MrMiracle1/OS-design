#ifndef _ERROR_H
#define _ERROR_H


#define ERROR_UNSPECIFIED        1    // 未知
#define ERROR_BAD_PROC            2    // 坏程序
#define ERROR_INVAL                3    // 非法
#define ERROR_NO_MEM            4    // OOM
#define ERROR_NO_FREE_PROC        5    // 超出当前进程地址空间
#define ERROR_FAULT                6    // 错误
#define ERROR_SWAP_FAULT        7   // SWAP READ/WRITE fault
#define ERROR_INVAL_ELF         8   // Invalid elf file
#define ERROR_KILLED            9   // Process is killed
#define ERROR_PANIC             10  // Panic Failure
#define ERROR_TIMEOUT           11  // Timeout
#define ERROR_TOO_BIG           12  // Argument is Too Big
#define ERROR_NO_DEV            13  // No such Device
#define ERROR_NA_DEV            14  // Device Not Available
#define ERROR_BUSY              15  // Device/File is Busy
#define ERROR_NOENT             16  // No Such File or Directory
#define ERROR_ISDIR             17  // Is a Directory
#define ERROR_NOTDIR            18  // Not a Directory
#define ERROR_XDEV              19  // Cross Device-Link
#define ERROR_UNIMP             20  // Unimplemented Feature
#define ERROR_SEEK              21  // Illegal Seek
#define ERROR_MAX_OPEN          22  // Too Many Files are Open
#define ERROR_EXISTS            23  // File/Directory Already Exists
#define ERROR_NOTEMPTY          24  // Directory is Not Empty

/* 最大错误数 */
#define MAXERROR            24

#endif /* !__LIBS_ERROR_H__ */