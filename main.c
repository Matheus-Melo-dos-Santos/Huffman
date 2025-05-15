#include "zip.c"

int main (void){

  int menu;
  do
  {

    printf("1 - zip\n");
    printf("2 - unzip\n");
    printf("0 - exit\n");

    scanf("%d", &menu);

    if (menu < 0 || menu >2){

      printf("invalid option\n try a valid option\n");

    }

    if (menu == 1)
    {
    
      zip();

    }

    if(!menu) break;

  } while (menu);


  return 0;
} 