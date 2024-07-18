
void compress();

void descompress();

void main (void){

  int menu = 1;

  while ( menu ){

    printf("1. Compress file  \n");
    printf("2. descompress file  \n");
    printf("0. exit.  \n");
    
    scanf("Your action: %d\n", &menu);

    if ( menu == 1 ) compress();

    else 
      if ( menu == 2 ) descompress();

    else 
      if ( !menu ) return;

    else printf("Non valid option\n");

  }


}