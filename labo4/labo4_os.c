#define _GNU_SOURCE             /* See feature_test_macros(7) */
#include <stdio.h>
#include <fcntl.h>              /* Obtain O_* constant definitions */
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
 #include <errno.h>
#include <sys/wait.h>
#include <sys/mman.h>



char* get_fileaname() {
    int len = 0;
    int capacity = 1;
    char *s = (char*) malloc(sizeof(char)); //null?
    char c = getchar();
    while (c != '\n') { //EOF?
        s[(len)++] = c;
        if (len >= capacity) {
            capacity *= 2;
            s = (char*) realloc(s, capacity * sizeof(char));
        }
		if (capacity > 256) {
		s = NULL;
		return s;
		}
        c = getchar();
    }
    s[len] = '\0';
    return s;
}

int main (){

	char * first_file = NULL;
	first_file = get_fileaname();
	if (first_file == NULL) {
		perror ("Большое имя файла или нет памяти");
		return -1;
	}
	int out = open (first_file,O_WRONLY| O_CREAT | O_TRUNC , 0777);
	if (out == -1) {
		perror ("А нет такого файла :( \n");
		return -1;
	}
	char * second_file = NULL;
	second_file = get_fileaname();
	if (second_file == NULL) {
		perror ("Купи память, на дворе 2022 \n");
		return -1;
	}
	int out2 = open (second_file,O_WRONLY| O_CREAT | O_TRUNC , 0777);
	if (out2 == -1) {
		perror ("А нет такого файла :( \n");
		return -1;
	}

	//////
	int fd_for_input = open("back1.txt", O_RDWR | O_CREAT | O_TRUNC , 0777);
	struct stat sb;
	ftruncate (fd_for_input , 500*sizeof(int)); // Изменяет длинну файла на нужную
	if (fstat(fd_for_input, &sb) ==  -1) {
		perror ("Не удалось узнать длинну файла \n");
	}
	//printf ("Длинна файла равна %ld", sb.st_size);
	char *file_mem =  mmap(NULL, sb.st_size, PROT_WRITE | PROT_READ , MAP_SHARED ,fd_for_input,0);

	int fd_for_input2 = open("back2.txt", O_RDWR | O_CREAT | O_TRUNC , 0777);
	struct stat sb2;
	ftruncate (fd_for_input2 , 500*sizeof(int)); // Изменяет длинну файла на нужную
	if (fstat(fd_for_input2, &sb2) ==  -1) {
		perror ("Не удалось узнать длинну файла \n");
	}
	//printf ("Длинна файла равна %ld", sb.st_size);
	char *file_mem2 =  mmap(NULL, sb2.st_size, PROT_WRITE | PROT_READ , MAP_SHARED ,fd_for_input2,0);

	int c;

	int id = fork();
	if (id == 0){
		if (dup2 ( out,fileno(stdout)) == -1) {
			perror ("dup2");
		}
		char str1[sizeof(int)];
		sprintf(str1, "%d", 1);
		execl("child.out","child.out",str1,NULL);
		perror ("execl");
	}
	int id2 = fork();
	if (id2 == 0){
		if (dup2 ( out2,fileno(stdout)) == -1) {
			perror ("dup2");
		}
		char str2[sizeof(int)];
		sprintf(str2, "%d", 2);
		execl("child.out","child.out",str2,NULL);
		perror ("execl");
	}
	if (id < 0) {
		perror ("fork\n");
		exit(0);
	}
	if (id2 < 0) {
		perror ("fork\n");
		exit(0);
	}
	if ((id > 0) && (id2 > 0)){
		close (out);
		int g = 0;
		for (int i = 0; i < sb.st_size; i++) {
			c = getchar();
			if ( c == EOF) {
				break;	
			}
			if (g == 0){
				file_mem[i] = (char)c;
			}
			if (g == 1) {
				file_mem2[i] = (char)c;
			}
			if (c == '\n') {
				if (g == 0){
					msync(file_mem, sb.st_size, MS_SYNC| MS_INVALIDATE);
					kill (id , SIGUSR1);
					g++;
					i = -1;
					continue;
				}
				if (g == 1){
					msync(file_mem2, sb2.st_size, MS_SYNC| MS_INVALIDATE);
					kill (id2 , SIGUSR1);
					g--;
					i = -1;
					continue;
				}				
			}
		}
		kill (id , SIGUSR2);
		kill (id2 , SIGUSR2);
		wait(NULL); // !NULL????
		remove ("back1.txt");
		remove ("back2.txt");
	}
}

// USE FORMATERS!!!






