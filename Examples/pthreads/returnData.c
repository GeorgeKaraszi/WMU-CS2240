
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#define NUM_THREADS 10



/* create thread argument struct for thr_func() */
typedef struct _thread_data_t {
  int tid;

} thread_data_t;

void *thr_func(void *arg) {

    thread_data_t* data = malloc(sizeof(thread_data_t));
    

    data->tid = *((int *)arg);
    

    //pthread_exit(data);
    return data;

   }

int main(int argc, char **argv) {

    pthread_t thr[NUM_THREADS];
    pthread_attr_t attr;
    int nums[NUM_THREADS];
    int i, rc;

    /* create a thread_data_t array of pointers*/
    thread_data_t *thr_data[NUM_THREADS];

    /* for portability since all threads are not created equa... I mean join-able */
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    

    /* create threads */
    for (i = 0; i < NUM_THREADS; ++i) {
    	
    	//can't I just pass it &i?
    	nums[i] = i;

    	printf("creating thread %d\n",i );
        

        if ((rc = pthread_create(&thr[i], &attr, thr_func, &nums[i]))) {
      
            fprintf(stderr, "error: pthread_create, rc: %d\n", rc);
      
            return EXIT_FAILURE;
        }
    }

    /* DESTROY the attribute */
    pthread_attr_destroy(&attr);


    /* block until all threads complete */
    for (i = 0; i < NUM_THREADS; ++i) {


        pthread_join(thr[i], (void**) &thr_data[i] );


        printf("Thread %d has joined with thr_data->tid:%d \n",i,thr_data[i]->tid );
        free(thr_data[i]);
    }

    /*
     *There is a definite problem if main() finishes before the threads it spawned if you don't call pthread_exit() explicitly.
     *All of the threads it created will terminate because main() is done and no longer exists to support the threads.
     *
     *we dont have this issue since we called thread join
     */

    return EXIT_SUCCESS;
}
