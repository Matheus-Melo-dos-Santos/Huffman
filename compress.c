/*
  Compress - huffman 
*/
#include "struct.c"

void frequencyCount(size_t *frequency, uint_8 *file, size_t size);

void compress(){

  printf("Write name of file: \n");
  char* fileName;

  scanf("%s", fileName);

  FILE* file = open(fileName, 'rb');

  if ( file == NULL ) {
    printf("File %s not found\n", fileName);
    return;
  }

  fseek(file, 0, SEEK_END);
  size_t fileSize = ftell(file);
  fseek(file, 0, SEEK_SET);  

  uint_8 *buffer = (uint_8*) malloc(fileSize * sizeof(uint_8));

  if( buffer == NULL){

    printf("Error allocating memory\n");
    fclose( (uint_8) ,file);
    return;

  }

  size_t read_size = fread(buffer, sizeof(uint_8), fileSize, file);
  if( read_size != fileSize){

    printf("Error reading file\n");
    free(buffer);
    fclose(file);
    return;

  }

  fclose(file);
  size_t frequency[256] = {0};
  frequencyCount(frequency, buffer, fileSize);

}

void frequencyCount(size_t *frequency, uint_8 *file, size_t size){

  for( size_t i = 0; i < size; i++ ){
    frequency[file[i]] +=1;
  }

}