
// Main.h 
// A4
//
//  Created by Donald  Acton on 2017-09-30.
//  Copyright © 2017 Donald  Acton. All rights reserved.
//


#ifndef MAIN_H

#define MAIN_H

#include <stdlib.h>
#include <inttypes.h>

#define ERROR_RETURN -1
#define MAXADDRESS_SPACE 16
#define PAGEFAULT (1 << (MAXADDRESS_SPACE + 1))
#define TLBFAULT PAGEFAULT
#define SUCCESS 0
#define FAILURE 200
#define HIT 1
#define MISS 0

// Structure for the page table, page table entry
typedef struct page_table_entry_s
{
    int is_valid;
    uint32_t PPN;
} page_table_entry_t;

typedef struct page_table_s
{
    page_table_entry_t *page_table_entries;
} page_table_t;




#endif
