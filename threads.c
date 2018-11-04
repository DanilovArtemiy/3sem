#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>
#include<time.h>
#define ELEMENTS 100000000
#define MAX_RANDOM_NUMBER 10


//в 1 поток программа работает в 2 раза быстрее, чем в N потоков

// FIXIT: 1) нужно обязательно проверить, что код при одном и том же массиве на входе
// выдает одно и то же среднее и дисперсию при любом числе потоков
// 2) 		pthread_create(&thid, (pthread_attr_t*)NULL, Arifm, &s);
//		pthread_join(thid, (void**)NULL);
// У вас следующей строкой после создания нити, стоит строка, которая дожидается его завершения.
// фактически у вас последовательный код, который должен работать примерно столько же ... не в 2 раза дольше

struct Params{
	int **a;
	int strings;
	int elem_in_string;
	int *result;
	int *resultx2;
};


void *Arifm(void *dummy){
	struct Params s = *((struct Params*)dummy);
	int i = 0;
	for (i = 0; i < s.elem_in_string; i++){
		s.result[s.strings] += s.a[s.strings][i];
		s.resultx2[s.strings] = s.resultx2[s.strings] + s.a[s.strings][i] * s.a[s.strings][i];
	}
	return NULL;
}

int main(){
	srand(time(0));
	double sum = 0,sumx2 = 0;
	struct Params s;
	int n,i=0,j=0;
	scanf("%d", &n);
	s.a = (int**)malloc(n * sizeof(int*));
	s.result = (int*)malloc(n * sizeof(int));
	s.resultx2 = (int*)malloc(n * sizeof(int));
	for (i = 0; i < n; i++){
		s.result[i] = 0;
		s.resultx2[i] = 0;
		s.a[i]=(int*)malloc((ELEMENTS/n+n)*sizeof(int));
	}
	for (i = 0; i < (n - 1); i++){
		for (j = 0; j < (ELEMENTS / n); j++){
			s.a[i][j] = rand() % MAX_RANDOM_NUMBER;
		}
	}
	for (i = 0; i < ELEMENTS - (n - 1) * (ELEMENTS / n); i++){
		s.a[n-1][i] = rand() & MAX_RANDOM_NUMBER;
	}
	clock_t begin = clock();
	for (i = 0; i < n; i++){
		pthread_t thid;
		s.strings = i;
		if (i != (n - 1)){
			s.elem_in_string = ELEMENTS / n;
		}
		else {
			s.elem_in_string = ELEMENTS - (n - 1) * (ELEMENTS / n);
		}

		pthread_create(&thid, (pthread_attr_t*)NULL, Arifm, &s);
		pthread_join(thid, (void**)NULL);
	}
	for (i = 0;i < n; i++){
		sum += (double)s.result[i];
		sumx2 += (double)s.resultx2[i];
	}
	clock_t end = clock();
	double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("%lf\n", time_spent);
	printf("СРЕДНЕЕ:%lf\n", sum / ELEMENTS);
	printf("ДИСПЕРСИЯ:%lf\n", (sumx2 / ELEMENTS - ((sum / ELEMENTS) * (sum / ELEMENTS))));
	free(s.result);
	free(s.resultx2);
	for (i = 0; i < n; i++){
		free(s.a[i]);
	}
	free(s.a);
	return 0;
}

