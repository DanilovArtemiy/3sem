#include<stdio.h>
#include<stdlib.h>
#include<string.h>


void Split(char* string,char* delimiters,char*** tokens,int* tokensCount){
	int k=0, add=0, start=0;
	int len = strlen(string);
	for (k=0;k<=len;k++){
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
