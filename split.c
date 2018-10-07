#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_STRING_SIZE 100
#define MAX_TOKENS_COUNT 100
#define MAX_DELIMITERS_SIZE 10

// FIXIT: я в упражнении про abacaba писал замечания, и здесь они тоже присутствуют. посмотрите мой комментарий к abacaba и 
// поправьте данное упражнение, пожалуйста

void Split(char* string, char* delimiters, char*** tokens, int* tokensCount){
	int i=0;
	*tokens[i]=strtok(string,delimiters);
	while ((*tokens)[i]!=NULL){
		i++;
		(*tokens)[i]=strtok(NULL,delimiters);
	}
	*tokensCount=i;
}

int main(){
	int i=0,j=0;
	char string[MAX_STRING_SIZE];
	int tokensCount=0;
	char delimiters[MAX_DELIMITERS_SIZE];
	fgets(string,MAX_STRING_SIZE,stdin);
	fgets(delimiters,MAX_DELIMITERS_SIZE,stdin);
	char **tokens;
	tokens=(char**)malloc(MAX_TOKENS_COUNT*sizeof(char*));
	for (i=0;i<MAX_TOKENS_COUNT;i++){
		tokens[i]=(char*)malloc(MAX_STRING_SIZE*sizeof(char));}

	Split(string,delimiters,&tokens,&tokensCount);

	for (i=0;i<tokensCount;i++){
		printf("%s\n",tokens[i]);
	}
	free(tokens);
	return 0;
}
