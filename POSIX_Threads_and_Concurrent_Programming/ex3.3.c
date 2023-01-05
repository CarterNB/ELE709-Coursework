#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <pthread.h>

struct thread_info {
   int maxitr;
   double exec_time;
   char op;
   double a,b;
   double c;
};

typedef struct thread_info thread_info_t;

void *func(void *arg)
{
   struct timespec time_1, time_2;
   double exec_time;
   thread_info_t *info;
   int i, maxitr,num;
   volatile double a, b, c;
   char op;

   info = (thread_info_t *)arg;
   maxitr = info->maxitr;
   a = info->a;
   b = info->b;
   op = info->op;
   exec_time = 0.0;

   if (op == '+') {
   clock_gettime(CLOCK_REALTIME, &time_1);
   
   for (i = 0; i < maxitr ; i++) {
         c = a + b;
   }
         
   clock_gettime(CLOCK_REALTIME, &time_2);  
   printf("Thread 1 Done\n");
   }

   else if (op =='-') {   
   clock_gettime(CLOCK_REALTIME, &time_1);
   
   for (i = 0; i < maxitr ; i++) {
         c = a - b;
   }
   clock_gettime(CLOCK_REALTIME, &time_2);
   printf("Thread 2 Done\n");
   }
   
   else if (op =='*') {   
   clock_gettime(CLOCK_REALTIME, &time_1);
   
   for (i = 0; i < maxitr ; i++) {
         c = a * b;
   }
   clock_gettime(CLOCK_REALTIME, &time_2);
   printf("Thread 3 Done\n");
   }

   else if (op =='/') {   
   clock_gettime(CLOCK_REALTIME, &time_1);
   
   for (i = 0; i < maxitr ; i++) {
         c = a / b;
   }
   clock_gettime(CLOCK_REALTIME, &time_2);
   printf("Thread 4 Done\n");
   }

   exec_time = (time_2.tv_sec - time_1.tv_sec);
   exec_time = exec_time + (time_2.tv_nsec - time_1.tv_nsec)/1.0e9;

   info->exec_time = exec_time;
   info->c=c;

   pthread_exit(NULL);
}

int main(void)
{
   pthread_t thread1, thread2, thread3, thread4;
   thread_info_t info1, info2, info3, info4;
   double maxitr;
   double a,b;

   maxitr = 5.0e8;
   a=2.3; b=4.5;
    
   info1.maxitr = (int)maxitr;
   info1.op = '+';
   info1.a=(double)a;
   info1.b=(double)b;
   if (pthread_create(&thread1, NULL, &func, &info1) != 0) {
           printf("Error in creating thread 1\n");
           exit(1);
   }

   info2.maxitr = (int)maxitr;
   info2.op = '-';
   info2.a=(double)a;
   info2.b=(double)b;
   if (pthread_create(&thread2, NULL, &func, &info2) != 0) {
           printf("Error in creating thread 1\n");
           exit(1);
   }

   info3.maxitr = (int)maxitr;
   info3.op = '*';
   info3.a=(double)a;
   info3.b=(double)b;
   if (pthread_create(&thread3, NULL, &func, &info3) != 0) {
           printf("Error in creating thread 1\n");
           exit(1);
   }

   info4.maxitr = (int)maxitr;
   info4.op = '/';
   info4.a=(double)a;
   info4.b=(double)b;
   if (pthread_create(&thread4, NULL, &func, &info4) != 0) {
           printf("Error in creating thread 1\n");
           exit(1);
   }
   
   pthread_join(thread1, NULL);
   printf("Exec time for thread1 = %lf sec and result is %lf\n", info1.exec_time,info1.c);

   pthread_join(thread2, NULL);
   printf("Exec time for thread2 = %lf sec and result is %lf\n", info2.exec_time, info2.c);
  
   pthread_join(thread3, NULL);
   printf("Exec time for thread3 = %lf sec and result is %lf\n", info3.exec_time, info3.c);

   pthread_join(thread4, NULL);
   printf("Exec time for thread4 = %lf sec and result is %lf\n", info4.exec_time, info4.c);

   pthread_exit(NULL);
}
