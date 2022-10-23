#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

long incircle = 0;
long radius = 0;
long ppt; /* points per thread*/
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
void *runner() {
    long incircle_thread = 0;
    
    unsigned int rand_state = rand();
    long i;
    for (i = 0; i < ppt; i++) {
        double x = rand_r(&rand_state) / ((double)RAND_MAX + 1) * 2* radius - (radius);
        double y = rand_r(&rand_state) / ((double)RAND_MAX + 1) * 2*radius - (radius);
        if (x * x + y * y <= (radius* radius)) {
            incircle_thread++;
        }
    }
    pthread_mutex_lock(&mutex);
    incircle += incircle_thread;
    pthread_mutex_unlock(&mutex);
	return NULL;
}

int main(int argc, const char *argv[])
{
    struct timespec start_t, end;
    clock_gettime(CLOCK_REALTIME, &start_t);

    if (argc != 4) {
        fprintf(stderr, "usage: ./pi <total points> <threads> <radius>\n");
        exit(1);
    }
    long totalpoints = atol(argv[1]);
    int thread_count = atoi(argv[2]);
	long nradius = atoi(argv[3]);
	radius = nradius;
    ppt = totalpoints / thread_count;

    time_t start = time(NULL);
    srand((unsigned)time(NULL));
    pthread_t *threads = malloc(thread_count * sizeof(pthread_t));
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    int i;
    for (i = 0; i < thread_count; i++) {
        pthread_create(&threads[i], &attr, runner, (void *) NULL);
    }
    for (i = 0; i < thread_count; i++) {
        pthread_join(threads[i], NULL);
    }
    pthread_mutex_destroy(&mutex);
    free(threads);

	clock_gettime(CLOCK_REALTIME, &end);
    double time_spent = (end.tv_sec - start_t.tv_sec) + (end.tv_nsec - start_t.tv_nsec) / 1000000000.0;
    printf("\n\nThe elapsed time is %f seconds\n", time_spent);

	double coef = (double)incircle / ((double)ppt * thread_count);
	
	printf ("%ld %ld %d\n", incircle, ppt,thread_count);
    printf("Plosh: %lf \n", coef*2*radius*2*radius);
    return 0;
}
