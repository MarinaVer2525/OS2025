//Программа №1 для иллюстрации работы с разделяемой памятью

#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <errno.h>

int main() {
	//Указатель на адрес, по которому будет находиться разделяемая память 
	int *array;
	//IPC-дескриптор для обращения к области разделяемой памяти
	int shmid;
	//Флаг, указывающий на необходимость создания нового массива в разделяемой памяти 
	int new = 1;
	//имя файла предназначеное для генерации ipc-ключа
	char pathname[] = "pr011a.c";
	//Переменная для хранения IPC-ключа
	long i;
	key_t key;

	//Генерация IPC-ключа
	if((key = ftok(pathname, 0))<0) {
		printf("Не удалось сгенерировать IPC-ключ\n");
		exit(-1);
	}
	//Создание разделяемой памяти в эсклюзивном режиме
	if((shmid = shmget(key, 3*sizeof(int), 0666 | IPC_CREAT | IPC_EXCL))<0) {
		if(errno != EEXIST) {
			printf("не удалось создать область разделяемой памяти\n");
			exit(-1);
		}
		else {
			if((shmid = shmget(key, 3*sizeof(int), 0))<0) {
				printf("Не удалось найти разделяемую память\n");
				exit(-1);
			}
			new = 0;
		}
	}
	if((array = (int *)shmat(shmid, NULL, 0)) == (int *)(-1)) {
		printf("Не можем присоединить область раздеяемой памяти к адресному пространству текущего процесса\n");
		exit(-1);
	}
	if(new) {
		array[0] = 1;
		array[1] = 0;
		array[2] = 1;
	}
	else {
		 array[0] += 1;
		 for(i=0;i<500000000L;i++);
		 array[2] += 1;
	}
	printf("Первая программа была запущена %d раз, вторая программа была запущена %d раз, общее количество запусков - %d\n", array[0], array[1], array[2]);
	if(shmdt(array) < 0) {
		printf("Не удалось отсоеденить облась разделяемой памяти");
		exit(-1);
	}
	return 0;
}
