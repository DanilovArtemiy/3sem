#include<stdio.h>
#include<stdlib.h>
#include<string.h>


void Split(char* string,char* delimiters,char*** tokens,int* tokensCount){
	int k=0, add=0, start=0;
	int len = strlen(string);
	for (k=0;k<=len;k++){
		// FIXIT: так не пойдет, вы предполагаете, что разделителей ровно 2. посмотрите еще раз на strtok и используйте её
		if (string[k] == delimiters[0] || string[k] == delimiters[1]){
			string[k] = '\0';
			(*tokens)[(*tokensCount)++] = strdup(&string[start]);
			add++;
			start = add;
		}
		else{
		add++;
		}
	}
}	
int main(){
	int i=0,j=0;
	// FIXIT: 1) не должно быть магических констант в коде. Напишите #define MAX_STRING_SIZE 100 и используйте
	// Причем где-то у вас 100 означает MAX_TOKENS_COUNT 
	// 2) задание было чуть надумано и нужно было вынести выделение и освобождение памяти в отдельные ф-и. поправьте.
	char string[100] = {};
	int tokensCount=0;
	char delimiters[2]={'\t','\n'};
	fgets(string,100,stdin);
	char **tokens;
	tokens=(char**)malloc(100*sizeof(char*));
	for (i=0;i<100;i++){
		tokens[i]=(char*)malloc(100*sizeof(char));}

	Split(string,delimiters,&tokens,&tokensCount);

	for (i=0;i<tokensCount;i++){
		printf("%s\n",tokens[i]);
	}
	for (i=0;i<100;i++){
		free(tokens[i]);
	}
	free(tokens);
	return 0;
}
