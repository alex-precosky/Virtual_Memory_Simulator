//
//  main.c
//  A4
//
//  Created by Donald  Acton on 2017-09-30.
//  Copyright © 2017 Donald  Acton. All rights reserved.
//

// A bunch of standard includes 
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <inttypes.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/stat.h>
#include "main.h"
#include "paging.h"

#define EXPECTED_ARG_COUNT 5

// At the end of each memory lookup you must call this function
// to print the relevant information. Note that the physical Address
// is the physical address for the virtual address relative to the start
// of the physical memory representation in main memory.

void printLookup(int memoryAccessNo, // Which memory access this is
		 uint32_t virtualAddress,  // Virtual address being accessed
		 uint32_t vpn,       // virtual page number
		 uint32_t vpo,       // virtual page offset
		 uint32_t ppn,       // physical page number
		 uint32_t  ppa,      // physical address
		 int       tlbHit,   // Pass in 1 on a hit 0 on a miss
                 int       pageFault, // pass in 1 on a pageFault 0 on a hit
		 char         data    // the data value
		 ) {

  printf("Access %5d: VA: %5d (0x%04x) VPN: %4d VPO: %4d ppn: %4d ppa: %4d (%04x) TLB:%d PF:%d --> %d\n",
	 memoryAccessNo,
	 virtualAddress, virtualAddress, vpn, vpo, ppn, (int) ppa, (int) ppa, tlbHit, pageFault, data);
}

// When all the addresses have been processed call this function to print a summary of what 
// happened
		 
void printStats(int memoryAccesses, // How many memory accesses were made
		int tlbMissCount,   // Number of TLB misses
		int pageFaults)     // Number of page faults
{
  printf("\nElapsed time: %5d\n", memoryAccesses);
  printf("TLB misses:   %5d\n", tlbMissCount);
  printf("Page faults:  %5d\n", pageFaults);
  printf("TLB hit rate:    %3.3f\n", (memoryAccesses - tlbMissCount)/((float) memoryAccesses));
  printf("Page fault rate: %3.3f\n",  pageFaults/((float) memoryAccesses));	 
}

int main(int argc, char **argv) {
  char * backingStoreName;

  
  char * addressesName;
  uint32_t  physicalAddressSize;
  uint32_t  pageSize;

  // Verify that the command line has an appropriate number
  // of arguments
  
  if (argc != EXPECTED_ARG_COUNT) {
        printf("Usage: %s BackingStore_FileName AddressesFile PhysicalAddressSize PageSize \n", argv[0]);
        return ERROR_RETURN;
    }
    
  backingStoreName = argv[1];
  addressesName = argv[2];
  
  // See man page for strtol() as to why
  // we check for errors by examining errno, see err
  errno = 0; 
  physicalAddressSize = (uint32_t) strtoul(argv[3], NULL, 10);
  if (errno != 0 || physicalAddressSize <= 0) {
    perror("Physical address size must be a number greater than 0");
    return ERROR_RETURN;
  }
  
  if (physicalAddressSize > MAXADDRESS_SPACE) {
    printf("Address size must be > 0 and <= %d\n", MAXADDRESS_SPACE);
    return ERROR_RETURN;
  }

  pageSize = (uint32_t) strtoul(argv[4], NULL, 10);
  if (errno != 0) {
    perror("Page size must be a number");
    return ERROR_RETURN;
  }
  
  if (pageSize > physicalAddressSize) {
    printf("The page size (%u) must be > 0 and <= the address space size (%u).\n",
	   pageSize, physicalAddressSize);
    return ERROR_RETURN;
  }
  

  printf("BackingStore = %s\n", backingStoreName);
  printf("Address file = %s\n", addressesName);
  printf("Address size = %u (2 to the power of %u)\n", 1 << physicalAddressSize,
	 physicalAddressSize);
  printf("Page size    = %u  (2 to the power of %u)\n", 1 << pageSize,
	 pageSize);




  int  backingStoreFD;
  FILE * addresses;
  
  // Open file with addresses to read
  addresses = fopen(addressesName, "r");
  if (!addresses) {
    printf("File %s failed to open\n", addressesName);
    return FAILURE;
  }
  
  // Open the backing store
  backingStoreFD = open(backingStoreName, O_RDONLY);
  if (-1 == backingStoreFD) {
    printf("Failed to open backing store file: %s\n", backingStoreName);
    return FAILURE;
    }
  

  // Modify and add code below here to achieve the assignment specifications
  // Feel free to change anything below here. You can change stuff above this 
  // comment but be careful. 
  
  // Initialize the page table and TLB systems
  int tableSize = 2^16;
  int tableEntries = tableSize / 2^pageSize;
  page_table_t *pageTable = (page_table_t *) malloc(sizeof(page_table_t));
  pageTable->page_table_entries = (page_table_entry_t *) malloc(tableEntries * sizeof(page_table_entry_t));
  int i;
  for (i = 0; i < tableEntries; i++) {
    //pageTable->page_table_entries[i] = (page_table_entry_t) malloc(sizeof(page_table_entry_t));
    pageTable->page_table_entries[i].is_valid = 0;
    pageTable->page_table_entries[i].PPN = 0;
  }

  // Figure out various page sizes and amount of physical memory to allocate
  char* physicalMemory = malloc(2^physicalAddressSize);

  int memoryAccessCount = 0;  // The number of access to memory, 1 is the first access

  // The following is how to read a line from the file
  char addrline[128];
  char *retVal;
  int pagefaultCount = 0;

  retVal = fgets(addrline, 128, addresses);
  if (retVal == NULL) {
    printf("Couldn't read first line of file %s", addressesName);
    return FAILURE;
    }
  
  for (;retVal; retVal = fgets(addrline, 128, addresses)) {
    uint32_t address;
    memoryAccessCount++;
    address = (uint32_t) strtoul(retVal, NULL, 10 );
    if (errno != 0) {
      printf("Invalid number on file line %d\n", memoryAccessCount);
      break;
    }

    // Decompose address
    uint32_t VPN = address >> pageSize;

    unsigned int mask = 0;
    int i;
    for (i = 0; i < pageSize; i++) {
      mask = (mask << 1) | 1;
    }

    uint32_t VPO = address & mask;

    printf("Mask: %d\n", mask);
    printf("VPN: %d\n", VPN);
    printf("VPO: %d\n", VPO);

    // Check TLB
    uint32_t PPN;

    // Check page table if need be
    page_table_entry_t *pageTableEntry = pageTable->page_table_entries + VPN;

    // Process a page fault if required
    if (pageTableEntry->is_valid == 0) {
      printf("invalid\n");
      PPN = 0;
      if (pagein(VPN, PPN, physicalMemory, pageSize, backingStoreFD)) {
        printf("Error when paging in\n");
      }
      printf("retreived page %d from disk");
      pageTableEntry->is_valid = 1;
      pageTableEntry->PPN = PPN;
    } else {
      PPN = pageTableEntry->PPN; 
    }

    // Read the byte 
    char byte = *(physicalMemory + PPN);
    printf("%d\n", byte);

    // You must call printLookup(memoryAccessCount, address, ....);
  }
  
  // Example printing : 512 byte pages
  // Virtual address 45238
  // Physical frame is 14
  memoryAccessCount = 10000;
  printLookup(memoryAccessCount, 45238, 88, 182, 14, 7350, 1, 0,  -2);
  pagefaultCount = 312;
  //You must call this to print the summary stats
  printStats(memoryAccessCount, 1987, pagefaultCount);

  return SUCCESS;
}


