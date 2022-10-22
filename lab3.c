#include <stdio.h>
#include <stdlib.h>
#include <sys/times.h>
#include <time.h>
#include <pthread.h>

void *thread_body(void* args);

	typedef struct {
		int to_do;
		int radius;
	} arg_for_t;


int count_mutex = 0;
pthread_mutex_t mutex;

int main(void) {

    struct timespec start, end;
    clock_gettime(CLOCK_REALTIME, &start);

	srand(time(NULL));
	
	int num_thread;
	scanf("%d", &num_thread);
    pthread_t threads[num_thread];
    arg_for_t t_arg[num_thread];
	int c;	
	scanf ("%d", &c);
	pthread_mutex_init(&mutex, NULL);
    for (int i = 0; i < num_thread; ++i) {
		t_arg[i].radius = c;
		t_arg[i].to_do = 4000000 /num_thread;
		if ( i == 0) {
			t_arg[i].to_do += 4000000 % num_thread;
		}
		printf ("%d \n", t_arg[i].to_do);
        if (pthread_create(&(threads[i]), NULL, thread_body , &(t_arg[i]))) {
            perror("Create thread error");
            return -1;
        }
    }
	
    for (int i = 1; i <= num_thread; ++i) {
        if (pthread_join(threads[i - 1], NULL))
        {
            fprintf(stderr, "Error joining thread\n");
            return 2;
        }
    }

	double coef = (count_mutex/4000000.0);

	printf("res = %lf\n", coef*2*c*2*c );

    clock_gettime(CLOCK_REALTIME, &end);
    double time_spent = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1000000000.0;
    printf("The elapsed time is %f seconds\n", time_spent);

	pthread_mutex_destroy(&mutex);
}

void *thread_body(void* args) {
    arg_for_t *nw = args;
	double x, y;
	int local_sum_count = 0;
	int c = nw->radius;
	for (int i = 0; i < nw->to_do ; i++) {
		x = (rand()%(c*100000))/(double)100000;
		y = (rand()%(c*100000))/(double)100000;
		if ((x*x + y*y) <= (c*c)){
			(local_sum_count) ++;	
		}
	}

	pthread_mutex_lock(&mutex);
	count_mutex += local_sum_count;
	pthread_mutex_unlock(&mutex);
    return 0;
}
