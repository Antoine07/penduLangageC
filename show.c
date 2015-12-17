
int match_character(char ch, char word[]);

void match(char characters[], char word[], int goodLetters[])
{

    int i, j, test = 0;
    
    for (i = 0 ; word[i] != '\0' ; i++)
    {
        if(match_character(word[i], characters))
        {
            printf("%c",word[i]);
            goodLetters[i] = 1;
        }
        else 
            printf("*");
    }
            
}

int match_character(char ch, char word[])
{
    int i;

    for(i = 0 ; word[i] != '\0' ; i++){
        if(ch==word[i]){
           return 1;
        } 
    }

    return 0;

}