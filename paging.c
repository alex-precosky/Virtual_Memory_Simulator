
//
//  paging.c
//  A4
//
//  Created by Donald  Acton on 2017-09-30.
//  Copyright © 2017 Donald  Acton. All rights reserved.
//

#include "main.h"
#include "paging.h"
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// You must use this function to pagein a page from the
// backing store . The function takes the
// virtualPageNumber (not the virtual address) and reads the page in 
// from that location and puts it into the page location specified 
// by the physical page number. Access to the backing store (i.e. paging file)
// is through the file descriptor passed in the parameter bakingStorefd. 
// The size of the page is given in pageSize. (Hint pass in the the page size in bytes)
// The value returned is 1 if it worked and 0 if it failed. Note that one
// possible failure is the result of a read error, so be sure to check for
// that.

int pagein(uint32_t virtualPageNumber,
	   uint32_t physicalPageNumber,
	   char * physicalMemoryStart,
	   uint32_t  pageSize,
	   int  backingStorefd ) {


  int offset = pageSize * virtualPageNumber;

  char* buf = physicalMemoryStart + physicalPageNumber*pageSize;

  int error  = lseek(backingStorefd, offset, SEEK_SET);
  if( error==-1 )
    return 0;

  error = read(backingStorefd, buf, pageSize);
  if( error==-1 )
    return 0;


  // Update the physical page list. Check if there was a physical page previously in there
  if(physical_page_list.pages[physicalPageNumber].is_valid)
    {
      int oldVPN = physical_page_list.pages[physicalPageNumber].mapped_vpn;
      page_table.page_table_entries[oldVPN].is_valid = 0;
    }

  physical_page_list.pages[physicalPageNumber].mapped_vpn = virtualPageNumber;
  physical_page_list.pages[physicalPageNumber].is_valid = 1;

  // Update the page table
  page_table.page_table_entries[virtualPageNumber].is_valid = 1;
  page_table.page_table_entries[virtualPageNumber].PPN = physicalPageNumber;

  return 1;
}

void Init_Page_Table(int tableEntries)
{
  page_table.page_table_entries = (page_table_entry_t *) malloc(tableEntries * sizeof(page_table_entry_t));
  int i;
  for (i = 0; i < tableEntries; i++) {
    //pageTable->page_table_entries[i] = (page_table_entry_t) malloc(sizeof(page_table_entry_t));
    page_table.page_table_entries[i].is_valid = 0;
    page_table.page_table_entries[i].PPN = 0;
  }
}

int Is_VPN_Valid(int VPN)
{
  page_table_entry_t pageTableEntry = page_table.page_table_entries[VPN];

  int is_valid = pageTableEntry.is_valid;

  return is_valid;
}

int Lookup_PPN_For_Valid_VPN( int VPN )
{
  page_table_entry_t pageTableEntry = page_table.page_table_entries[VPN];

  return pageTableEntry.PPN; 
}

void Init_Physical_Page_List(int physicalAddressSizeBytes, int pageSizeBytes)
{


  physical_page_list.num_pages = physicalAddressSizeBytes / pageSizeBytes;
  physical_page_list.pages = malloc(physical_page_list.num_pages * sizeof(physical_page_t));

  for(int i = 0; i < physical_page_list.num_pages; i++)
    {
      physical_page_list.pages[i].is_valid = 0;
      physical_page_list.pages[i].last_used = 0;
    }

}

int Get_LRU_Page_Number()
{
  // TODO replace with a proper calculation
  return 0;
}

