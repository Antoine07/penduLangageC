
int match_character(char ch, char word[]);

int * match(char characters[], char word[], int *findLetters, int *test)
{

    int i, j;
    
    *test = 0;

    for (i = 0 ; word[i] != '\0' ; i++)
    {
        if(match_character(word[i], characters) || *(findLetters+i) == 1 )
        {
            printf("%c",word[i]);
            *(findLetters+i) = 1;
            *test = 1;
        }
        else{
        	printf("*");
        } 
            
    }

    printf("\n");

    return findLetters;
            
}

int match_character(char ch, char word[])
{
    int i;

    for(i = 0 ; word[i] != '\0' ; i++){
        if(ch ==word[i]){
           return 1;
        } 
    }

    return 0;

}