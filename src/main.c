#include "include/neige.h"

#include <stdio.h>
#include <stdlib.h>

char *read_file (const char *file_path){
  char *buffer = 0;
  long length;
  FILE *file = fopen(file_path, "rb");

  if (file){
    fseek (file, 0, SEEK_END);
    length = ftell (file);
    fseek (file, 0, SEEK_SET);
    buffer = malloc (length);
    if (buffer){
      fread (buffer, 1, length, file);
    }
    fclose (file);
  }
  else {
    printf("COULD NOT OPEN FILE");
    exit(1);
  }

  return buffer;
}

int main(int argc, char const *argv[]){
  if (argc < 2){
    printf("Must specify the file to open");
    return 1;
  }
  
  char *file_content = read_file(argv[1]);
  neige_compile(file_content);
}