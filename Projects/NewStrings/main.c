#include "new_string.h"
#include <stdio.h>
#include <stddef.h>
#include <string.h>

int main() {

   char* source = "";
   char* destination = "";

char* whatever = new_strstr(source, destination);

   printf("%s\n", whatever);
   
   return 0;
 
}
