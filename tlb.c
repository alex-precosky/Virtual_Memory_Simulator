
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

}

// Check to see if the virtual page number is in the in the TLB
// If it is return the physical page number otherwise return TLBFAULT;
uint32_t checkTLB(int accessCnt, uint32_t virtualPageNumber) {
  return TLBFAULT;
}


// Add this mapping to the TLB
void updateTLB(int accessCnt, uint32_t virtualPageNumber, 
	       uint32_t physicalPageNumber) {
  
}
