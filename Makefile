

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
main.o: /usr/include/stdc-predef.h /usr/include/sys/cdefs.h
main.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
main.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
main.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
main.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
main.o: /usr/include/fcntl.h /usr/include/bits/fcntl.h
main.o: /usr/include/bits/fcntl-linux.h /usr/include/time.h
main.o: /usr/include/bits/stat.h /usr/include/sys/types.h
main.o: /usr/include/endian.h /usr/include/bits/endian.h
main.o: /usr/include/bits/byteswap.h /usr/include/bits/byteswap-16.h
main.o: /usr/include/sys/select.h /usr/include/bits/select.h
main.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
main.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
main.o: /usr/include/sys/uio.h /usr/include/bits/uio.h /usr/include/unistd.h
main.o: /usr/include/bits/posix_opt.h /usr/include/bits/environments.h
main.o: /usr/include/bits/confname.h /usr/include/getopt.h
main.o: /usr/include/inttypes.h /usr/include/stdint.h
main.o: /usr/include/bits/wchar.h /usr/include/stdlib.h
main.o: /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h
main.o: /usr/include/alloca.h /usr/include/bits/stdlib-float.h
main.o: /usr/include/errno.h /usr/include/bits/errno.h
main.o: /usr/include/linux/errno.h /usr/include/asm/errno.h
main.o: /usr/include/asm-generic/errno.h
main.o: /usr/include/asm-generic/errno-base.h /usr/include/sys/stat.h main.h
