
//
//  tlb.c
//  A4
//
//  Created by Donald  Acton on 2017-09-30.
//  Copyright © 2017 Donald  Acton. All rights reserved.
//
#include "tlb.h"

// The following are a few hints to get you going. Feel free
// to change names, to add more functions, to change parameter types,
// to change the number of parameters, to change the return value, or to
// not use any of these functions at all. 
// 


// Add code here to implement the TLB functionality
void TLBinit(uint32_t pageSize) {
  cache.num_lines = 16;
  cache.lines = malloc( cache.num_lines * sizeof(cache_line_t) );
  cache.pageSizeBits = pageSize;

  for(int i = 0; i < cache.num_lines; i++)
    cache.lines[i].is_valid = 0;

}

// Check to see if the virtual page number is in the in the TLB
// If it is return the physical page number otherwise return TLBFAULT;
uint32_t checkTLB(int accessCnt, uint32_t virtualPageNumber) {
  int index = virtualPageNumber & 0xF;
  int tag = virtualPageNumber & 0xF0;


  for(int i = 0; i < cache.num_lines; i++)
    {
      cache_line_t* line = &cache.lines[i];

      if(line->is_valid && line->tag==tag && line->index==index)
	{
	  line->last_access = accessCnt;
	  return line->PPN;
	}

    }

  return TLBFAULT;
}


// Add this mapping to the TLB
void updateTLB(int accessCnt, uint32_t virtualPageNumber, 
	       uint32_t physicalPageNumber) {

  
  int index = virtualPageNumber & 0xF;
  int tag = virtualPageNumber & 0xF0;

  for(int i = 0; i < cache.num_lines; i++)
    {
      cache_line_t* line = &cache.lines[i];
      
      if(line->is_valid == 0)
	{
	  line->is_valid = 1;
	  line->index = index;
	  line->tag = tag;
	  line->PPN = physicalPageNumber;
	  line->last_access = accessCnt;


	  return;
	}
    }


  // if we got here, then the cache is full so choose the oldest entry
  int lowest_last_used = 999999;
  int lowest_last_used_index = 0;
  for(int i = 0; i < cache.num_lines; i++)
    {
      cache_line_t* line = &cache.lines[i];
      
      if( line->last_access < lowest_last_used)
	{
	  lowest_last_used = line->last_access;
	  lowest_last_used_index = i;
	}
    }

  cache_line_t* line = &cache.lines[lowest_last_used_index];
  line->is_valid = 1;
  line->index = index;
  line->tag = tag;
  line->PPN = physicalPageNumber;
  line->last_access = accessCnt;


}


// remove this mapping from the TLB
void evictTLB(uint32_t physicalPageNumber)
{
  for(int i = 0; i < cache.num_lines; i++)
    {
      cache_line_t* line = &cache.lines[i];

      if(line->PPN == physicalPageNumber)
	{
	  line->is_valid = 0;
	}
    }

}
