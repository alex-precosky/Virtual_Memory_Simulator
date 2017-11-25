

all: vmm

CC=gcc
CLIBS=-lc
CFLAGS=-g -Werror-implicit-function-declaration -pedantic -std=c99

#If you need to add additional source files add them at the end of the 
#following line and then do a make depend. Don't forget to commit the 
#new version of the makefile. The warnings about stddef.h can be 
#ignored
SRC=main.c tlb.o paging.o
OBJ = $(SRC:.c=.o)



vmm: $(OBJ)
	$(CC) -g -o vmm $(OBJ)

depend: $(SRC)
	makedepend $(SRC)

clean:
	rm -f *.o
	rm -f vmm

.PHONY: run

# DO NOT DELETE

main.o: /usr/include/stdio.h /usr/include/features.h
main.o:  /usr/include/sys/cdefs.h
main.o: /usr/include/bits/wordsize.h 
main.o: /usr/include/wchar.h
main.o: /usr/include/fcntl.h 
main.o:  /usr/include/time.h
main.o:  /usr/include/sys/types.h
main.o: /usr/include/endian.h /usr/include/bits/endian.h
main.o: /usr/include/bits/byteswap.h 
main.o: /usr/include/sys/select.h 
main.o: /usr/include/sys/sysmacros.h 
main.o: /usr/include/sys/uio.h  /usr/include/unistd.h
main.o:  /usr/include/getopt.h
main.o: /usr/include/inttypes.h /usr/include/stdint.h
main.o:  /usr/include/stdlib.h
main.o: /usr/include/alloca.h
main.o: /usr/include/errno.h 
main.o:  /usr/include/sys/stat.h main.h
