#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 4
#define ARRAY_SIZE 10000

//global arrs
int *array_ints;
long *sum;

//thread arg struct for thread_fcn (Example)
typedef struct _thread_data_t{
    int tid;
    double stuff;
} thread_data_t;

void *thread_fcn (void *arg){
    thread_data_t *data = (thread_data_t *) arg;
    printf("Hello from thread_fcn, thread id: %d\n", data->tid);
    sum[data->tid]=0;
    int thread_part = ARRAY_SIZE/NUM_THREADS;
    for (int i=data->tid*thread_part, j=0; j < thread_part; i++, j++){
        sum[data->tid] += array_ints[i];
    }
    printf("Sum calc'd by thread: %d\n was %ld\n", data->tid, sum[data->tid]);
    pthread_exit(NULL);
}

int main(int argc, char**argv){
    pthread_t threads[NUM_THREADS];
    int rc;

    //create thread_data_t arg array
    thread_data_t threads_data[NUM_THREADS];

    //create array of ints
    array_ints = malloc(ARRAY_SIZE * sizeof(int));
    for(int i=0; i < ARRAY_SIZE; i++){
        array_ints[i] = rand()%100;
    }
    //sum calc'd for each thread
    sum=malloc(NUM_THREADS * sizeof(long));

    //create threads
    for (int i = 0; i < NUM_THREADS; i++){
        threads_data[i].tid = i;
        if ((rc = pthread_create(&threads[i], NULL, thread_fcn, &threads_data[i]))){
            fprintf(stderr, "error: pthread create, rc=%d\n", rc);
            exit(1);
        }
    }
    //blocks until all threads complete.
    for (int i = 0; i < NUM_THREADS; i++){
        pthread_join(threads[i], NULL);
    }
    int total_sum;
    for (int i = 0; i < NUM_THREADS; i++){
        total_sum += sum[i];
    }
    printf("\nTotal sum: %d\n", total_sum);


    return 0;
}