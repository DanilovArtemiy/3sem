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
	
	// FIXIT: отдельная константа для 100
	char str[100] = {};
	myfile = fopen("text.txt", "r");
	int i = 0, j = 0, len = 0;
	pid_t pid = fork();
	while(1){
		// Видимо стоит переименовать MAX_COMMAND_COUNT в MAX_COMMAND_LENGTH
		if (fgets(str, MAX_COMMAND_COUNT, myfile) != NULL){
			strcat(action, str);
			time[i] = atoi(str);
			i++;
		}
		else {
			break;
		}
	}
	
	/* Цикл выше можно напистать короче: 
		while (fgets(str, MAX_COMMAND_COUNT, myfile)) 
		{
			strcat(action, str);
			time[i] = atoi(str);
			i++;
		}
	*/
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
		// Кажется можно просто запускать команды вот так execvp(arg[1], arg + 1); вместо сдвигания массива на 1 элемент
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
				// вот здесь лучше написать exit(0) на всякий случай. если команду запустить не получится, то и исходный родительский и этот дочерний процесс продолжат запускать новые поцессы, чего явно не хочется
			} else {
				sleep(time[i] + DEAD_TIME);
				if (waitpid(pid, &status, WNOHANG)){
					exit(-1);
				} else {
					kill(pid, SIGKILL);
					exit(-1);
				}
				// лучше exit(-1) написать здесь, т.к. он все равно в обоих ветках if вызывается
			}
		} 
		free(arg);
	}
	free(tokens);
	return 0;
}

