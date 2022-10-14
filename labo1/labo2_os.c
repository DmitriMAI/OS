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

char* get_fileaname() {
    int len = 0;
    int capacity = 1;
    char *s = (char*) malloc(sizeof(char));
    char c = getchar();
    while (c != '\n') {
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
	enum {
		READ = 0,
		WRITE = 1
	};

	char * first_file = NULL;
	first_file = get_fileaname();
	if (first_file == NULL) {
		perror ("Большое имя файла или нет памяти");
		return -1;
	}
	int out = open (first_file,O_WRONLY| O_CREAT | O_TRUNC , 0666);
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
	int out2 = open (second_file,O_WRONLY| O_CREAT | O_TRUNC , 0666);
	if (out2 == -1) {
		perror ("А нет такого файла :( \n");
		return -1;
	}
	int fd[2];
	if(pipe2(fd, O_CLOEXEC) == -1) {
		perror("pipe");
 		return -1;
	}
	int fd2[2];
	if(pipe2(fd2, O_CLOEXEC) == -1) {
		perror("pipe");
 		return -1;
	}
	int id = fork();
	if (id == 0){
		close(fd[WRITE]);
		dup2 ( fd[READ],fileno(stdin));
		dup2 ( out,fileno(stdout));
		execl("child.out", "child.out",NULL);
		perror ("execl");
	}
	int id2 = fork();
	if (id2 == 0){
		close(fd2[WRITE]);
		dup2 ( fd2[READ],fileno(stdin));
		dup2 ( out2,fileno(stdout));
		execl("child.out", "child.out",NULL);
		perror ("execl");
	}	
	if (id > 0) {
		int c;
		int flag = 0;
		while  ((c = getchar()) != EOF) {
			if (flag % 2 == 0){
				write (fd[WRITE], &c, sizeof(int));			
			} else {
				write (fd2[WRITE], &c, sizeof(int));
			}
			if (c == '\n'){	
				flag ++;
			}
		}
		close (fd2[WRITE]);
		close (fd[WRITE]);
		wait(NULL);
	}
}








