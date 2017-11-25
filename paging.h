//
//  paging.h
//  A4
//
//  Created by Donald  Acton on 2017-09-30.
//  Copyright © 2017 Donald  Acton. All rights reserved.
//

#ifndef PAGING_H
#define PAGING_H 1
#include <sys/types.h>
#include <unistd.h>
#include <inttypes.h>


int pagein(uint32_t virtualPageNumber,
	   uint32_t physicalPageNumber,
	   char * physicalMemoryStart,
	   uint32_t  pageSize,
	   int  backingStorefd);

// You probably want to add structure definitions for page table entries and for
// tracking physical page usage along with functions to do things like:
// * initialize the paging system
// * check to see if a virtual page is mapped in and at what location
// * locate the page to to replace
// Structure for the physical memory and pages
typedef struct physical_page_s
{
    int is_valid;
    int last_used;
    uint32_t mapped_vpn;
    unsigned char *data;
} physical_page_t;

typedef struct physical_page_list_s 
{
    unsigned int num_pages;
    physical_page_t *pages;
} physical_page_list_t;


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


void Init_Page_Table(int tableEntries);
int Is_VPN_Valid(int VPN);
int Lookup_PPN_For_Valid_VPN( int VPN );

void Init_Physical_Page_List(int physicalAddressSizeBytes, int pageSizeBytes);
 int Get_LRU_Page_Number();

// file globals
static page_table_t page_table;
static physical_page_list_t physical_page_list;

#endif
