#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct Tree{

  struct Tree* next;
  struct Tree* left;
  struct Tree* right;
  int          frequency;
  void *       byte;

} Tree;

void createNullTree(Tree** root){
  
 (*root) = (Tree*) malloc(sizeof(Tree));
  
  if ( *root == NULL){
    perror("Memory allocatiion failed");
    free(*root);
    return;
  }

  (*root) -> next = NULL;
  (*root) -> left = NULL;
  (*root) -> right = NULL;
  (*root) -> byte = NULL;
  (*root) -> frequency = 0;

}

void createQueue(Tree** root, int* frequencyTale){
  
  for (int i = 0; i < 256; i++)
  {

    if(frequencyTale[i]){
      Tree* newElement = NULL;
      createNullTree(&newElement);

      (newElement) -> byte = (void*) malloc(sizeof(uint8_t));
      if(newElement-> byte == NULL){
        perror("memory allocation failed");
        return;
      }

      memcpy(newElement->byte, &i, sizeof(uint8_t));
      newElement -> frequency = frequencyTale[i];

      newElement -> next = (*root);
      (*root) = newElement;
   
    }

  }
  
}

void sortedInsert(Tree** head, Tree* newNode){

  if (newNode == NULL) return;

  if (*head == NULL || (*head)->frequency >= newNode->frequency){
    newNode -> next = (*head);
    (*head) = newNode;
  }
  else{

    Tree* current = *head;
    while(current->next != NULL && current->next->frequency < newNode -> frequency){
        current = current -> next;
    }
    newNode -> next = current -> next;
    current -> next = newNode; 

  }

}

void sortQueue(Tree** rt){

  if( (*rt) == NULL || (*rt) -> next == NULL ) return;
  
  Tree* sorted = NULL;
  Tree* current = *rt;

  while( current != NULL) {
    Tree* next = current -> next;
    sortedInsert(&sorted, current);
    current = next;
  }
  (*rt) = sorted;
}

void printLinkedList(Tree* rt){
  
  while( rt != NULL){
    uint8_t asc;
    memcpy(&asc, *rt->byte, sizeof(uint8_t));
    int id;
    id = (int) asc;

    printf("ASC:%c - decimal:%d - frequency: %d \n",asc, id, rt->frequency);
    rt = (rt->next);
  }
  
}

void cleanQueue( Tree** rt){

  if( (*rt) == NULL) return;
  
  Tree* p = (*rt);

  while ( p != NULL )
  {
    Tree* tmp = p;
    p = p -> next;

    free(tmp->byte);
    free(tmp);

  }
  
  (*rt) = NULL;
  
}

void selectFile(uint8_t** file, char* fileName, int* size){

    FILE* pFile = fopen(fileName, "rb");
    if (pFile == NULL) {
      perror("Error opening file");
      return;
    }

    fseek(pFile, 0 ,SEEK_END);
    *size = ftell(pFile);
    fseek(pFile, 0, SEEK_SET);

    *file = (uint8_t*) malloc((*size)*sizeof(uint8_t));
    if ( *file == NULL){
      perror("Memory allocation failed");
      free(file);
      return;
    }

    if (fread(*file, 1, *size, pFile) != *size) {
        perror("Error reading file");
        free(*file);
        *file = NULL;
        fclose(pFile);
        return;
    }

    fclose(pFile);

}

void renameFile(char* name, char** newName){

  int size = strlen(name) + 8;
  
  *newName =(char*) malloc(sizeof(char)*(size + 8));
   if ( *newName == NULL)
   {

      perror("Memory allocation failed");
      free(newName);
      return;

   }

  strcpy(*newName, name);
  strcat(*newName, ".huffman");
  printf("new file : %s\n", *newName);

}

void doFrequencyTable(int* ft, uint8_t* file, int size){
  for(int i = 0; i < size; i++){
      ft[file[i]]+=1;
  }

}

void teste(uint8_t* file, char* fileName){
  
    int size = strlen(file);
    for (int i = 0; i < size; i++)
    {
      file[i]+=1;
    }
    char* newFileName;
    renameFile(fileName, &newFileName);
    
    FILE* pFile = fopen(newFileName, "wb");

    if (pFile == NULL) {
      perror("Error opening file");
      return;
    }

    fwrite(file, sizeof(uint8_t), size, pFile );

    fprintf(pFile, "\n");
    for(int i = 0; i < size; i++){
      fprintf(pFile, "%c\n", file[i] );
    }

    fclose(pFile);
}

void teste_frequency_table(int* f){
  for(int i = 0; i < 256; i++){
    if(f[i]) printf("%c : %d\n", i, f[i]);
  }
}

void zip(){

    char      fileName[1024];
    int       size;
    uint8_t*  file;
    int       frequencyTable[256] = {0};
    Tree*     root = NULL;
    
    createNullTree(&root);

    printf("Enter the name of file: ");
    scanf("%1023s", fileName);
    printf("file name: %s\n", fileName);

    selectFile(&file, fileName, &size);
    doFrequencyTable(frequencyTable, file, size);    

    createQueue(&root, frequencyTable);
    //printLinkedList(*root);
    
    printf("sorting the queue\n");
    sortQueue(&root);
  
    //Isso aqui não é o problema;
    printLinkedList(root);

    teste_frequency_table(frequencyTable);
    teste(file, fileName);

}
