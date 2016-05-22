/* declaration */
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#define NUM_THREADS 8
/* print */
void *PrintHello(void *thread_id)
{
   long tid = (long)thread_id;;
   printf("Hello World! It's thread #%ld!\n", 
	  tid);
   pthread_exit(NULL);
}
/* main */
int main (int argc, char *argv[])
{
   pthread_t threads[NUM_THREADS];
   int rc;
   long t;
   for(t = 0; t < NUM_THREADS; t++){
      printf("In main: creating thread %ld\n", t);
      rc = pthread_create(&threads[t], NULL, 
			  PrintHello, (void *)t);
      if (rc) {
         printf("ERROR; return code %d\n", rc);
         exit(-1);
      }
   }
   pthread_exit(NULL);
}
/* end */
