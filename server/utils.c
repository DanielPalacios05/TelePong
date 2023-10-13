#include <stdlib.h>
#include <string.h>
#include <stdarg.h>


void concat(char * result, int num, ...) {
  va_list args;
  va_start(args, num);
  for (int i = 0; i < num; i++) {
    strcat(result, va_arg(args, char* ));
  }
  va_end(args);
}

void convertInt2Char(int number, char* text, size_t text_size){    

    int written_characters = snprintf(text, text_size, "%d", number);

    if (written_characters >= sizeof(text)) {
        printf("Error: Buffer overflow\n");
    }
}