#include <stdio.h>       /* for fprintf() */
#include <stdlib.h>      /* for exit() */
#include <unistd.h>      /* for sleep() */
#include <pthread.h>     /* for pthreads functions */

int string_index = 0;
int alive=1;
pthread_mutex_t mut;
pthread_cond_t cond;
char string_to_print[] = "0123456789";

void *A(void *arg)
{
   sleep(1);   /* sleep 1 sec to allow all threads to start */
   
   while (alive) {
      pthread_mutex_lock(&mut);
      while (!((string_index==1)|(string_index==2)|(string_index==5)|(string_index==6)|(string_index==9))) pthread_cond_wait(&cond,&mut);
        
         printf("A%c ", string_to_print[string_index]);
         usleep(1);   /* sleep 1 usec */
         string_index = string_index + 1;
      
      
        
       
    
  if (string_index+1 == sizeof(string_to_print)) {
         printf("\n");
         string_index = 0;   /* wrap around */
       
      }

    
    pthread_mutex_unlock(&mut);
   }
}
void *B(void *arg)
{

   sleep(1);   /* sleep 1 sec to allow all threads to start */
   
   while (alive) {
      

      pthread_mutex_lock(&mut);
      
      if(!((string_index==1)|(string_index==2)|(string_index==5)|(string_index==6)|(string_index==9))) {
         printf("B%c ", string_to_print[string_index]);
         usleep(1);   /* sleep 1 usec */ 
         string_index = string_index + 1;  
      }
         if ((string_index==1)|(string_index==2)|(string_index==5)|(string_index==6)|(string_index==9)) pthread_cond_signal(&cond);
    pthread_mutex_unlock(&mut);
   }
}


int main(void)
{

   pthread_t threadA, threadB;

   pthread_create(&threadA, NULL, &A, NULL);
   pthread_create(&threadB, NULL, &B, NULL);
   

   sleep(20);   /* sleep 20 secs to allow time for the threads to run */
                /* before terminating them with pthread_cancel()      */
   alive=0;

   pthread_join(threadA, NULL);
   pthread_join(threadB, NULL);
   pthread_cancel(threadA);
   pthread_cancel(threadB);

   pthread_exit(NULL);
   pthread_mutex_destroy(&mut);
   pthread_cond_destroy(&cond);
}
