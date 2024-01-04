#include <stdio.h>

/**
 * Note the complete absence of pragmas here, the bank relocation is done on the compiler 
 * command-line in the makefile.
 * 
 * Maybe it's possible here instead, but if so I can't figure it out :)
 * 
 * You can check the generated bankswitch.map to make sure things went into the correct place.
 * There should be something like the following line:
 * 
 * _bank3function                  = $C000 ; addr, public, , bank3_c, BANK_3, bank3.c:417
 * 
 * This shows that bank3function (below) is located at $C000 (beginning of the banked area), 
 * came from bank3.c, and is in named area BANK_3
 * 
*/

void bank3function(void)
{
    printf("We're in bank 3, at %p\n",bank3function);
    printf("Well, that was fun. Back we go to the main program!\n");
}
