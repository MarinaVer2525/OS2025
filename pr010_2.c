//Программа для чтения из FIFO
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#define BYTES 44
int main() {
	int fd;
	size_t size;
	char resstring[BYTES];
  char name[]="file.fifo";
	
  if((fd = open(name, O_RDONLY)) <0) {
			printf("Не удалось открыть FIFO на чтение\n");
			exit(-1);
	}
  printf("Процесс-приемник готов к чтению информации из FIFO\n");
	size = read(fd, resstring, BYTES);
	if(size < 0) {
			printf("Не удалось прочитать строку целиком\n");
			exit(-1);
	}
  printf("содержание прочитаной строки: %s\n", resstring); 
	if(close(fd) < 0) {
			printf("Не удалось закрыть FIFO\n");
			exit(-1);
		}
		printf("Процесс-приемник завершил работу\n");
	  return 0;
}
