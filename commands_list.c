#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#define DEAD_TIME 10
#define MAX_COMMAND_COUNT 100


void Split (char* string, char* delimiters, char*** tokens, int* tokensCount){
	int i = 0;
	(*tokens[i]) = strtok(string, delimiters);
	while ((*tokens)[i] != NULL){
		i++;
		(*tokens)[i] = strtok(NULL, delimiters);
	}
	*tokensCount = i;
}

int main(){
	int status;
	int c = 0;
	int time[MAX_COMMAND_COUNT];
	char action[MAX_COMMAND_COUNT] = {};
	int tokensCount = 0;
	FILE* myfile;
	char delimiters_for_string[1] = {'\n'};
	char delimiters[3] = {'\t', '\n', ' '};
	char str[100] = {};
	myfile = fopen("text.txt", "r");
	int i = 0, j = 0, len = 0;
	pid_t pid = fork();
	while(1){
		if (fgets(str, MAX_COMMAND_COUNT, myfile) != NULL){
			strcat(action, str);
			time[i] = atoi(str);
			i++;
		}
		else {
			break;
		}
	}
	char **tokens;
	tokens = (char**)malloc(MAX_COMMAND_COUNT * sizeof(char*));
	for (i = 0; i < MAX_COMMAND_COUNT; i++){
		tokens[i] = (char*)malloc(MAX_COMMAND_COUNT * sizeof(char));
	}

	Split(action, delimiters_for_string, &tokens, &tokensCount);
	for (i = 0; i < tokensCount; i++){
		char **arg;
		arg = (char**)malloc(MAX_COMMAND_COUNT * sizeof(char*));
		int f = 0;
		for (f = 0; f < MAX_COMMAND_COUNT; f++){
			arg[f] = (char*)malloc(MAX_COMMAND_COUNT * sizeof(char));
		}
		Split(tokens[i], delimiters, &arg, &j);
		int k = 0;
		for (k = 0; k < MAX_COMMAND_COUNT - 1; k++){
			arg[k] = arg[k + 1];
		}
		pid = fork();
		if (pid == 0){
			pid = fork();
			if (pid == 0){
				sleep(time[i]);
				execvp(arg[0], arg);
			} else {
				sleep(time[i] + DEAD_TIME);
				if (waitpid(pid, &status, WNOHANG)){
					exit(-1);
				} else {
					kill(pid, SIGKILL);
					exit(-1);
				}
			}
		} 
		free(arg);
	}
	free(tokens);
	return 0;
}

