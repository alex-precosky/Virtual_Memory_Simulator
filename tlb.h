
//
//  tlb.h
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


#ifndef TLB_H
#define TLB_H

typedef struct cache_line_s
{

  int is_valid;
  int index;
  intptr_t tag;
  int PPN;
  int last_access;

} cache_line_t;

typedef struct cache_s
{
  int num_lines;
  int pageSizeBits;
  cache_line_t* lines;
} cache_t;

static cache_t cache;

void TLBinit(uint32_t pageSize);

uint32_t checkTLB(int accessCnt, uint32_t virtualPageNumber);

void updateTLB(int accessCnt, uint32_t virtualPageNumber, 
	       uint32_t physicalPageNumber);

void evictTLB(uint32_t physicalPageNumber);

#endif
