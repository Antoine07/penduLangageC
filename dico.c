
#include <time.h>

char *dico()
{
    FILE* fileName = NULL;
    fileName = fopen("dico.txt", "r");
    
    char* word = (char*) malloc(sizeof(char)*32);
    char character=0;
    int lengthWord=0, nbWords=0, alea=0, i=0;

    srand(time(NULL));

    if(fileName != NULL)
    {
        for(i=0; i<32;i++) word[i] = 0; // memory reset 

        do{
            character = fgetc(fileName);
            if(character == '\n') nbWords++; //number of words into file

        }while(character != EOF);

        rewind(fileName);
        alea = (rand() % nbWords)+1;
        nbWords=alea; // rand

        do{
            character = fgetc(fileName);
            if(nbWords==1){
                word[lengthWord] = character;
                lengthWord++;
            }
            if(character == '\n') nbWords--;

        }while(nbWords>0);

        return word;

    }else{
       return 0;
    }

}
