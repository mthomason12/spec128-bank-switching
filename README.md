# Spectrum 128K Memory Bank Switching Example

Using C, compiled with Z88DK with -clib=sdcc_iy
Tested using ZEsarUX v.X (24/09/2023) set to Sinclair ZX Spectrum+ 128k

It should run fine on a +2.  The +2A/+3 differ slightly in which banks are contended, but as long as you're not doing anything timing-critical it should work on those too.  I've started on making it work on the Next, too, but that's a work in progress - it should still work on there in 128 emulation mode though, and will get that tested ASAP.

This doesn't use any neat compiler tricks like the classic lib does with __banked, but instead does the bank switching manually where you can see it.

This does mean that you can't currently call a function in one bank from a function in another bank. Everything has to go through the program code in the main memory segment (&6000-&BFFF). As that's where the banking functions are actually put, it should be fine, but passing pointers around between banked segments will fail if they're at &C000 or above. 

Makefile only tested on Windows (yell if it doesnt work elsewhere and I'll try to fix it!), but you'll need to install GNU Make from https://gnuwin32.sourceforge.net/packages/make.htm and ensure it's on 
your path.

Read the comments in each file - including the Makefile - to see how it works.

It can probably be done *much* better (and I welcome code patches and pull requests), but this is me trying to figure things out after not touching C for 20 years and not writing code on a Spectrum for more than 30 years (and back then all I did was BASIC).

I used the proportional font mode just because I think it looks neat.

And finally, you'll notice there's a "0" printed at the top left when the program exits. The value returned from the "main" function always does this on a .sna, but not on a .tap.  No idea why.

Original Repo location at https://github.com/mthomason12/spec128-bank-switching

