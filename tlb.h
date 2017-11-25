
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

void TLBinit(uint32_t pageSize);

uint32_t checkTLB(int accessCnt, uint32_t virtualPageNumber);

void updateTLB(int accessCnt, uint32_t virtualPageNumber, 
	       uint32_t physicalPageNumber);

#endif
