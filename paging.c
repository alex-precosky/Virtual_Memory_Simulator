
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

  return 1;
}

physical_page_list_t Init_Physical_Page_List(int physicalAddressSizeBytes, int pageSizeBytes)
{
  physical_page_list_t physical_page_list;

  physical_page_list.num_pages = physicalAddressSizeBytes / pageSizeBytes;
  physical_page_list.pages = malloc(physical_page_list.num_pages * sizeof(physical_page_t));

  for(int i = 0; i < physical_page_list.num_pages; i++)
    {
      physical_page_list.pages[i].is_valid = 0;
      physical_page_list.pages[i].last_used = 0;
    }

  return physical_page_list;
}

int Get_LRU_Page_Number()
{
  // TODO replace with a proper calculation
  return 0;
}
