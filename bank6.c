#include <stdio.h>
#include <string.h>
#include "structs.h"

/**
 * Oh look! There's a variable in bank 6!.  You could pass a pointer to this back to the
 * main code, but bear in mind you can only use it while this is the currently switched-in
 * bank.
 */
unsigned char bankedDataString[20] = "Thank you!";

void bank6function(void *dataPtr)
{
    struct dataStruct *data;
    data = dataPtr;
    printf("We're here in bank 6, at address %p\n",bank6function);
    printf("We got the string %s and the number %d\n",data->dataString, data->dataNum);  
    printf("Lets send back 'thank you' and 6656\n");
    strcpy(data->dataString, bankedDataString);
    data->dataNum=6656;
    printf("And once again back we go to the main program!\n");
}
