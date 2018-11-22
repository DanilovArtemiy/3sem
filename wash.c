#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/shm.h>
#include<sys/sem.h>
#include<unistd.h>
#include<sys/wait.h>
#define TABLE_LIMIT 10
#define MAX_STRING_SIZE 100
#define MAX_COMMAND 100

struct Dishes{
	char name[MAX_STRING_SIZE];
	int time;
};

int main(){
	int semid;
	struct Dishes dishes[MAX_COMMAND];
	char str[MAX_STRING_SIZE] = "";
	char string[MAX_STRING_SIZE] = "";
	char reverse_str[MAX_STRING_SIZE] = "";
	char pathname[] = "msg.c";
	key_t key;
	struct sembuf buf;
	char* p;
	int msqid,i = 0, j = 0;
	FILE* myfile;
	key = ftok(pathname, 0);
	semid = semget(key,1, 0666|IPC_CREAT);
	msqid = msgget(key, 0666|IPC_CREAT);
	myfile = fopen("rules.txt", "r");
	while(1){
		if (fgets(str,MAX_STRING_SIZE,myfile) != NULL){
			int len = strlen(str);
			for (j = 0; j < len; j++){
				reverse_str[j] = str[len - 1 - j];
			}
			dishes[i].time = atoi(reverse_str);
			for (j = 0; j < len - 3; j++){
				dishes[i].name[j] = str[j];
			}
			i++;
		} else {
			break;
		}
		
	}
	int MAX_DISHES = i;
	struct mymsgbuf{
		long mtype;
		char mname[MAX_STRING_SIZE];
	} mybuf;
	buf.sem_op = TABLE_LIMIT - 1;
	buf.sem_flg = 0;
	buf.sem_num = 0;
	semop(semid, &buf, 1);
	for (i = 0; i < MAX_DISHES; i++){
		sleep(dishes[i].time);
		mybuf.mtype = 1;
		strcpy(mybuf.mname, dishes[i].name);
		printf("помыл %s\n", dishes[i].name); 
		msgsnd(msqid, &mybuf, sizeof(mybuf) - sizeof(long), 0);
		buf.sem_op = -1;
		buf.sem_flg = 0;
		buf.sem_num = 0;
		semop(semid, &buf, 1);
	}	
	printf("ВСЁ ПОМЫЛ");
	return 0;
}

		
	
	



