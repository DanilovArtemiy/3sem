#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>





int main(){
	int msqid, er;
	char pathname[] = "msg.c";
	key_t key;
	int i, len;
	struct mymsgbuf{
		long mtype;
		int a;
		int b;
		pid_t pid;
	} mybuf;
	struct msgbuf{
		long mtype;
		int result;
	} buf;
	key = ftok(pathname, 0);
	buf.result = -1;
	msqid = msgget(key, 0666|IPC_CREAT);
	mybuf.mtype = 1;
	mybuf.pid = getpid();
	scanf("%d %d", &mybuf.a, &mybuf.b);
	msgsnd(msqid, &mybuf, sizeof(mybuf)- sizeof(long), 0);
	msgrcv(msqid, &buf, sizeof(buf) - sizeof(long), getpid(), 0);
	printf("%d\n", buf.result);
	return 0;
}
