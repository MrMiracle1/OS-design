#ifndef __FS_SWAPFS_H__
#define __FS_SWAPFS_H__

#include <mm/memlayout.h>
#include <mm/swap.h>

void swapfs_init();
int swapfs_read(swap_entry_t entry, struct Page *page);
int swapfs_write(swap_entry_t entry, struct Page *page);

#endif