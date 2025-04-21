#include <stdio.h>

int main(int argc, char* argv[], char* envp[]) {
	if (argc >=2) {
		printf("Количество аргументов, переданных программе: %d\n", argc);
		printf("\n");
		for (int i=0; i < argc; i++)
			printf("Аргумент[%d]: %s\n", i, argv[i]);
		printf("\n");
	}

	else{
		printf("Список переменных среды,в которой запущена программа:\n");
		
		int j=0;
		
		while (envp[j]!=NULL) {
			printf("%d %s\n", j, envp[j]);
			j++;
		}
	}	
	return 0;
}	
