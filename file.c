#include<stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include<stdlib.h>
#include<string.h>
#define MAX_SIZE 1000

void Find(char* current_dir, int depth, char* file){
	if(depth < 0){
		printf("Not found in the dir = %s\n", current_dir);
		return;
	}
	DIR* dir;
	dir = opendir(current_dir);
	if(dir == NULL){
		return;
	}

	struct stat s;
	struct dirent *entry;
	char new_dir[MAX_SIZE]="";
	entry = readdir(dir);
	while(entry != NULL){
		strcpy(new_dir, current_dir);
		strcat(new_dir, "/");
		strcat(new_dir, entry->d_name);
		stat(new_dir, &s);
		if(S_ISREG(s.st_mode)){
			if(strcmp(entry->d_name, file)==0){
				printf("%s - найдено в %s\n", file,  current_dir);
				return;
			}
		}
		else if(S_ISDIR(s.st_mode) && (strcmp(entry->d_name, ".") && strcmp(entry->d_name, ".."))){
			Find(new_dir, --depth, file);
		}
		entry = readdir(dir);
	}
	closedir(dir);
}

int main(int argc, char* argv[]){
	int depth = atoi(argv[2]);
	char f[MAX_SIZE];
	strcpy(f, argv[3]);
	char cur[MAX_SIZE];
	strcpy(cur, argv[1]);
	Find(cur, depth, f);
	return 0;
}
