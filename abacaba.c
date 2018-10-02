#include<stdio.h>
#include<string.h>
#include<stdlib.h>
// после бинарных операторов и запятых ставье пробел: char k = 'a'; strcat(s, ns); и т.п.

void GenerateString(int n,char* string){
	int i;
	char k='a';
	char new_string[1<<n];
	string[0]='a';
	printf("a\n");
	for (i=1;i<n;i++){
		k+=1;
		strcpy(new_string,string);
		string[strlen(string)]=k;
		strcat(string,new_string);
		printf("%s\n",string);
	}
}


int main(){
	char* string;
	int n;
	scanf("%d",&n);
	string=malloc(sizeof(*string)*((1<<n)-1));
	GenerateString(n,string);
	free(string);
	return 0;
}
