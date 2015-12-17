#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <sqlite3.h>
#include "utils.c"
#include "dico.c"
#include "search.c"

#include "sql.c"

int main()
{
	char* word = (char*) malloc(sizeof(char)*32);
	char* username = (char*) malloc(sizeof(char)*10);
	char* wordTmp = (char*) malloc(sizeof(char)*32);
	int i, length = 0 ;
	int* findLetters =  (int*) malloc(sizeof(int)*32);
	int winner = 0, test=0, cpt=10, score=0;
	findLetters = initialize(32, findLetters);
	tab_score gamer;
	tab_score * res;

	// initialize game
	word = dico();
	length = strlen(word) -1;

	db_create("C:\\Users\\Antoine\\Desktop\\c\\Pendu2\\data.sqlite");

	printf("give me your username please");
	scanf("%s", username);

	char * foo;

	foo="hello world 1956";

	printf("%s\n",foo );

	gamer.username = username;
	gamer.score = 0;

	while(cpt>0)
	{
		printf("test word or letter \n");
		scanf("%s", wordTmp);

		wordTmp = upper_string(wordTmp); 

		// match
		findLetters = match(wordTmp, word, findLetters, &test);

		printf("stat goodletter %d, length word %d \n", count(findLetters), length);

		// winner or looser
		if(count(findLetters) == length){
			char response=0;
			gamer.score = 100;
			db_set("C:\\Users\\Antoine\\Desktop\\c\\Pendu2\\data.sqlite", gamer);
			printf("you are a winner, your score is 100, do you want to continue ? y/n \n");
			scanf("%s", &response);
			if(response == 'y')
			{
				findLetters = initialize(count(findLetters), findLetters);
				word = dico();
				length = strlen(word) -1;
				cpt = 10; 
				continue;
			}else{
				break;
			}
				
		}

		cpt--;

		if(test) 
			printf("ok this letter inside a word, you still have %d shot(s), and your score is %d \n ", cpt, count(findLetters));
		else 
			printf("this character or word is not matched with a secret word, you still have %d shot(s) \n", cpt);

		test = 0;

		}

		res = db_get("C:\\Users\\Antoine\\Desktop\\c\\Pendu2\\data.sqlite", gamer.username);

		printf("your pseudo: %s and your score: %d \n", res->username, res->score );

	return 0;
}