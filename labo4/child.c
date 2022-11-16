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

void sigquit()
{
    exit(0);
}

char * u = 0;

void reader (){
	signal (SIGUSR1, reader);
	int c;
	msync(u, 500*sizeof(int), MS_SYNC| MS_INVALIDATE);
	for (int i = 0 ; i < 500*sizeof(int); i++) {
		c = u[i] ;
		if (c == '\n') {
			write (fileno(stdout), &c, sizeof(char));
			break;
		}
		if ((c == EOF)) {
			break;
		}
		if ((c!='a') && (c!='e') && (c!='i') && (c!='u') && (c!='y') && (c!='o') && 
		(c!='A') && (c!='E') && (c!='I') && (c!='U') && (c!='Y') && (c!='O')) {
			write (fileno(stdout), &c, sizeof(char));
		}
	}
}

int main (int argc, const char *argv[]){
	int a = atoi(argv[1]);
	int fd_for_input = 0;
	if ( a == 1) {
		fd_for_input = open("back1.txt", O_RDWR);
	}
	else {
		fd_for_input = open("back2.txt", O_RDWR);	
	}
	struct stat sb;
	if (fstat(fd_for_input, &sb) ==  -1) {
		perror ("Не удалось узнать длинну файла \n");
	}
	char *file_mem =  mmap(NULL, 500*sizeof(int),  PROT_WRITE |PROT_READ , MAP_SHARED ,fd_for_input,0);
	u = file_mem;
	if (file_mem == NULL) {
		perror ("Ошибка mmap\n");
	}
	signal (SIGUSR1, reader);
	signal (SIGUSR2, sigquit);
	for (;;);
}
