//Программа для обмена информации через FIFO между неродственными процессами
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
	
  if((fd = open(name, O_WRONLY)) <0) {
			printf("Не удалось создать файл FIFO\n");
			exit(-1);
	}
  printf("Процесс-отправитель начинает запись в FIFO\n");
	size = write(fd,"Текстовая строка для FIFO", BYTES);
	if(size != BYTES) {
			printf("Не удалось записать строку целиком\n");
			exit(-1);
		}
		if(close(fd) < 0) {
			printf("Не удалось закрыть FIFO\n");
			exit(-1);
		}
		printf("Отправитель записал строку в FIFO и завершил работу\n");
	  return 0;
}
