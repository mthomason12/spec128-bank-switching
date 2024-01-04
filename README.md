# Spectrum 128K Memory Banking Example

Using C, compiled with Z88DK with -clib=sdcc_iy

This doesn't use any neat compiler tricks like the classic lib does with __banked,
but instead does the bank switching manually where you can see it.

This does mean that you can't currently call a function in one bank from a function in another bank.
Everything has to go through the program code in the main memory segment (&6000-&BFFF).

Read the comments in each file - including the Makefile - to see how it works.

It can probably be done *much* better (and I welcome code patches and pull requests), but this is me 
trying to figure things out after not touching C for 20 years and not writing code on a Spectrum for 
more than 30 years (and back then all I did was BASIC).

And finally, you'll notice there's a "0" printed at the top left.  The value returned from the "main" function always does this on a .sna, but not on a .tap.  No idea why.

Original Repo location at https://github.com/mthomason12/spec128-bank-switching

