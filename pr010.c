//Программа для обмена информации через FIFO между родственными процессами
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#define BYTES 44
int main() {
	int fd, result;
	size_t size;
	char resstring[BYTES];
  char name[]="file.fifo";
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
		if((fd = open(name, O_RDONLY)) <0) {
			printf("Не удалось открыть FIFO для записи\n");
			exit(-1);
		}
		size = write(fd,"Текстовая строка для FIFO", BYTES);
		if(size != BYTES) {
			printf("Не удалось записать строку целиком\n");
			exit(-1);
		}
		if(close(fd) < 0) {
			printf("Не удалось закрыть FIFO\n");
			exit(-1);
		}
		printf("Родительский процесс записал строку в FIFO и завершил работу\n");
	}
	else {
		if((fd = open(name, O_RDONLY)) <0) {
			printf("Не удалось открыть FIFO для чтения\n");
			exit(-1);
		}
		size = read(fd, resstring, BYTES);
		if(size < 0) {
			printf("Произошла ошибка при чтении из FIFO\n");
			exit(-1);
		}
		printf("Содержание прочитаной строки: %s\n", resstring);
		if(close(fd) < 0) {
			printf("Не удалось закрыть FIFO\n");
			exit(-1);
		}
	}
	return 0;
}
