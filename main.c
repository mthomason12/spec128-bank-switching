/*  
* Spectrum 128 Bank Switching Example.
*
* Author: Matt Thomason (matt@warpedcore.net).
* This code is placed in the public domain.  Do with it what you will.
*
* With thanks to Xalior for https://github.com/StalePixels/trampoline_examples that does this on the Spectrum Next
* And to Robin Verhagen-Guest for pointing me at that repo.
*/



#ifdef __SPECTRUM
#include <arch/zx.h>
#include <arch/zx/esxdos.h>
#endif
#ifdef __ZXNEXT
#include <arch/zxn.h>
#include <arch/zxn/esxdos.h>
#endif
#include <input.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "paging.h"
#include "bank3.h"
#include "bank4.h"
#include "bank6.h"
#include "structs.h"

//function declarations
int main(void);
uint8_t switchBank(uint8_t destBank);
void execFar(void (*fn)(void), uint8_t destBank);
void execFarUint16(void (*fn)(uint16_t), uint16_t i16, uint8_t destBank);
void clearScreen(void);

//start our code at 0x6000, which is as low as I'm confident we can go
//Yeah, yeah, moan at me about it being contended memory
#pragma output CRT_ORG_CODE = 0x6000

//control code for placing the cursor
#define PRINT_AT_CR    "\x16%c%c"


/**
 * Main routine
*/
int main(void) {
  uint8_t prevbank;
  struct dataStruct data;
  char testString[] = "This string came from our main code.\n";

  //yes, I could puts the rows without parameters rather than printf, but it felt like 
  //this look cleaner.
  printf("Bank Switching Test\n");  
  printf("\n");    
  printf("Here we are in the main code segment.  We're not bank switching yet.\n");
  printf("Switching in bank 1.\n");
  prevbank = switchBank(1); 
  printf("Well, that was cool, but kinda pointless.\n");
  printf("Calling a function in bank 3.\n");
  execFar(bank3function,3);
  printf("That was cooler.  But we can do more!\n");
  printf("Press any key.\n");
  in_wait_key();  
  clearScreen();
  printf("Calling a function in bank 4 with a parameter of 24.\n");
  execFarUint16(bank4function,24,4);  
  printf("We've got more. Press any key.\n");
  in_wait_key();
  clearScreen();
  printf("Calling a function in bank 4 and passing it a pointer to a struct that contains the string 'hello world' and the number 44.\n");  
  strcpy(data.dataString, "hello world");
  data.dataNum = 44;
  //Cast the pointers to uint16_t.  Or you could add code for execFarPointer if you prefer.
  execFarUint16((void(*)(uint16_t))bank6function,(uint16_t)&data,6); 
  printf("We got back the string %s and the number %d\n",data.dataString,data.dataNum);
  printf("Press any key to terminate, and ignore the 0 that gets printed, that's just the return value of main().\n");
  in_wait_key();  
  clearScreen();
  return 0;
}

void clearScreen() {
  zx_cls(PAPER_WHITE);
  printf(PRINT_AT_CR,1,1);
}

/**
 * Switch to a different memory bank.  Returns previously used bank number, or 0 if an invalid bank was requested
 * Leaving out banks 2,5,7, but you can add them in - don't forget to also edit page.asm. Don't get scared
 * by the assembly language, it's pretty easy to figure out how to add the extra pages.
 * Bank 2 is always at &8000, so we don't need it.
 * Bank 5 is Screen#1 at &4000
 * Bank 7 is Screen#2 
*/
unsigned char switchBank(uint8_t destBank) {
  switch (destBank)
  {
    case 0:
      setb0(); 
      break;       
    case 1:
      setb1();    
      break;      
    case 3:
      setb3();
      break;      
    case 4:
      setb4();
      break;      
    case 6:
      setb6();            
      break;      
  }
  return (unsigned char*)23388;
}

/**
 * Call a function in another bank.
 * Note that every function comes back here to the main code when it's done, and leaves
 * the bank switched in, in case we still need anything from it after the call.
 * Of course, that's only until we switch it again.  Making sure you don't
 * try to access a bank that's already been switched out for another, and
 * preventing any unnecessary switching are left as exercises for the reader.
*/
void execFar(void (*fn)(void), uint8_t destBank) {
    switchBank(destBank);
    fn();
}

/**
 * Call a function in another bank that takes a uint16_t parameter.  We're using uint16 because it's
 * the same size as a pointer on a Z80, and therefore can be used for pretty much anything by simply
 * passing a pointer to the data we want to pass (as long as that data is in main memory, or in the
 * destination bank already.)
 * Now, sure, we could probably write execFarWithUint16AndReturn with a return value, but we could
 * also just pass a pointer to a struct that contains multiple values and space for information to
 * be returned, and that saves writing more of these execFar routines.
*/
void execFarUint16(void (*fn)(uint16_t), uint16_t i16, uint8_t destBank) {
    switchBank(destBank);
    fn(i16);
}



