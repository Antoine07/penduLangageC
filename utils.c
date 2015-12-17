int count (int letters[])
{
	int i, cpt=0;

	for(i=0; i<32; i++)
	{
		if(letters[i]==1) cpt++;
	}

	return cpt;
}

char* upper_string(char *str)
{
    int i = 0;
    for (i = 0 ; str[i] != '\0' ; i++)
    {
        str[i] = toupper(str[i]);
    }

    return str;
}

int* initialize(int nb, int * tab)
{
	int i = 0;
    for (i = 0 ; i <nb ; i++)
    {
        tab[i] =0;
    }

    return tab;
}


char * conc(char *str1, char *str2)
{
    int i, j, lengthStr1, lengthStr2;

    lengthStr1 = length(str1);
    lengthStr2 = length(str2);

    char * con = (char*)malloc((lengthStr1 + lengthStr2 +1) * sizeof(char));

    for(i=0; i < lengthStr1; i++)
    {
        *(con+i) = *(str1+i);
    }

    for(j=0; j < lengthStr2; j++)
    {
        *(con+lengthStr1+j) = *(str2+j);
    }

    *(con+lengthStr1+lengthStr2) = '\0';

    return con;

}

int length(char * str)
{
    int i=0;

    while(str[i]!='\0')
    {
        i++;
    }

    return i;
}