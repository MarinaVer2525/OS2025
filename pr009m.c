//Программа для однонаправленной связи между родственными процессами
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#define BYTES 103
int main() {
	int fd[2], result;
	size_t size;
	char resstring[BYTES];
	if(pipe(fd) < 0) {
		printf("Не удалось создать пайп\n");
		exit(-1);
	}
	//Передает дочерний процесс
	result = fork();
	if(result < 0) {
		printf("Не удалось создать дочерний процесс\n");
		exit(-1);
	}
	else if(result > 0) {
		//Находится в процессе-родителе
		if(close(fd[0]) < 0) {
			printf("Не удалось закрыть входной поток\n");
			exit(-1);
		}
		size = write(fd[1],"Информация для дочернего процесса от процесса-родителя", BYTES);
		if(size != BYTES) {
			printf("Не удалось записать строку целиком\n");
			exit(-1);
		}
		if(close(fd[1]) < 0) {
			printf("Не удалось закрыть выходной поток\n");
			exit(-1);
		}
		printf("Родительский процесс завершил работу\n");
	}
	else {
		if(close(fd[1]) < 0) {
			printf("Не удалось закрыть выходной поток\n");
			exit(-1);
		}
		size = read(fd[0], resstring, BYTES);
		if(size < 0) {
			printf("Произошла ошибка при чтении из пайпа\n");
			exit(-1);
		}
		printf("Сообщение от родителя: %s\n", resstring);
		if(close(fd[0]) < 0) {
			printf("Не удалось закрыть входной поток\n");
			exit(-1);
		}
	}
	return 0;
}
