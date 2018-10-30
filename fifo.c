#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<string.h>
#include<fcntl.h>
#define MAX_STRING_SIZE	1000
#define name1 "a.fifo"
#define name2 "aa.fifo"


void Write(int fd[], char str[]){
	while(1){
		fgets(str, MAX_STRING_SIZE, stdin);
		write(fd[0], str, MAX_STRING_SIZE);
	}
}

void Read(int fd[], char str[]){
	while(1){
		read(fd[1], str, MAX_STRING_SIZE);
		printf("%s", str);
	}
}

int main(int argc, char *argv[]){
        int fd[2];
	pid_t pid;
	char str[MAX_STRING_SIZE];
	mknod(name1, S_IFIFO | 0666, 0);
	mknod(name2 ,S_IFIFO | 0666, 0);
	if (strcmp(argv[1], "0")){
		pid = fork();
		if (pid > 0){
			fd[0] = open(name1, O_WRONLY);
			Write(fd, str);
		} else {
			fd[1] = open(name2, O_RDONLY);		
			Read(fd, str);
		}
		exit(-1);

	} else if (strcmp(argv[1], "1")){
		pid = fork();
		if (pid > 0){
			fd[1] = open(name1, O_RDONLY);
			Read(fd, str);
		} else {
			fd[0] = open(name2, O_WRONLY);
			Write(fd, str);
		}
		exit(-1);
	
	} else {
		printf("Ошибка");
	}
	return 0;
}



