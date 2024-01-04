#include <stdio.h>
#include <string.h>
#include "structs.h"

unsigned char bankedDataString[] = "Thank you!";

void bank6function(struct dataStruct *dataPtr)
{
    printf("We're here in bank 6, at address %p\n",bank6function);
    printf("We got the string %s and the number $d",dataPtr->dataString, dataPtr->dataNum);  
    printf("Lets send back 'thank you' and 6656");
    strcpy(dataPtr->dataString, bankedDataString);
    dataPtr->dataNum=6656;
    printf("And once again back we go to the main program!\n");
}
