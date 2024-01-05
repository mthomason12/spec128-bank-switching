# Note - I suck at making Makefiles, so this is written for clarity rather than efficiency
# This has only been tested on windows

FINAL=bankswitch
FILELIST=main.c page.asm
BUILDDIR=build
OBJLIST=bank3.o bank4.o bank6.o

CC=zcc
CFLAGS=+zx -vn -m -startup=9 -clib=sdcc_iy  

#Handle different commands on Windows
ifeq ($(OS),Windows_NT)
    RM = del /Q /F
    RMD = rmdir /Q /S
	MD = mkdir
	COPY = copy
	SILENT = 2> nul
else
    RM = rm -f
    RMD = rm -f -r
	MD = mkdir
	COPY = cp
	SILENT = >/dev/nul
endif


all: 
#First, make our banked binaries.  The command line ensures these get marked with the correct
#segments for when the final compile assembles these all into the .sna
#You'll end up with a .bin for each of these too, which you can load manually if you're not
#making a .sna
	$(CC) $(CFLAGS) -o bank3.o bank3.c --codesegBANK_3 --constsegBANK_3 --datasegBANK_3 -c 
	$(CC) $(CFLAGS) -o bank4.o bank4.c --codesegBANK_4 --constsegBANK_4 --datasegBANK_4 -c 
	$(CC) $(CFLAGS) -o bank6.o bank6.c --codesegBANK_6 --constsegBANK_6 --datasegBANK_6 -c 
#Now make the main program, link the banked .objs, and do a -create-app to roll it into a neat .sna
#The compiler ensures the .sna puts each bank in the right place.
#You could alternatively do a -subtype=tap, but then you'd only get the code from the main program, with
#each bank as a .bin that you'd have to write your own loader for.
#Right at the start of the main program before you actually do anything else ought to be fine, but I
#haven't tested this yet - will update this when I do!
	$(CC) $(CFLAGS) -o $(FINAL) $(FILELIST) $(OBJLIST) -subtype=sna -pragma-include:zpragma.inc -create-app



clean:
	$(RM) *.o
	$(RM) *.sna
	$(RM) *.map	
	$(RM) *.bin			