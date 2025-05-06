//Работа с pipe()
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
	int fd[2];
	size_t size;
	char string[] = "3.008.2.24. ISITVO.\n";
	char resstring[20];
	//создание канала связи (pipe)
	if(pipe(fd) < 0) {
		printf("Не удадось создать пайп\n");
		exit(-1);
	}
	size = write(fd[1], string, 20);
	if(size != 20) {
		printf("Не удадось записать всю строку в пайп\n");
		exit(-1);
	}
	size = read(fd[0], resstring, 20);
	if(size != 20) {
		printf("Не удадось прочитать всю строку из пайпа\n");
		exit(-1);
	}
	printf("Прочитанная строка: %s\n", resstring);
	if(close(fd[1]) < 0) {
		printf("Не удадось закрыть выходной поток\n");
		exit(-1);
	}
	if(close(fd[0]) < 0) {
		printf("Не удадось закрыть входной поток\n");
		exit(-1);
	}
	return 0;
}
