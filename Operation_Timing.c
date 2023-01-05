#include <stdio.h>
#include <time.h>

int main()
{
   int i, maxitr;
   double a,b,c;
   struct timespec TIME1, TIME2, sleep_time, res;
   double ELAPSED_TIME, TIME_PERITR;
   char op;

   maxitr = 500000000;
   while(op!='b') {
   printf("Input First Number: ");
   scanf("%lf",&a);
   
   printf("Input Second Number: ");
   scanf("%lf",&b);

   printf("Input Operation to be Timed or 'b' to end program: ");
   scanf(" %c",&op);

   /* If Addition */
   if(op=='+') {
   clock_gettime(CLOCK_REALTIME, &TIME1);
   for(i = 0; i < maxitr; i++) c = a + b;
   clock_gettime(CLOCK_REALTIME, &TIME2);
   ELAPSED_TIME = (TIME2.tv_sec - TIME1.tv_sec)*1e9;
   ELAPSED_TIME  += (TIME2.tv_nsec - TIME1.tv_nsec);
   TIME_PERITR=ELAPSED_TIME/maxitr;
   printf("Addition yeilds %lf and takes %lf nanoseconds per iteration.\n",c, TIME_PERITR);
   }

   /* If Subtraction */
   if(op=='-') {
   clock_gettime(CLOCK_REALTIME, &TIME1);
   for(i = 0; i < maxitr; i++) c = a - b;
   clock_gettime(CLOCK_REALTIME, &TIME2);
   ELAPSED_TIME = (TIME2.tv_sec - TIME1.tv_sec)*1e9;
   ELAPSED_TIME  += (TIME2.tv_nsec - TIME1.tv_nsec);
   TIME_PERITR=ELAPSED_TIME/maxitr;
     printf("Subtraction yeilds %lf and takes %lf nanoseconds per iteration.\n",c, TIME_PERITR);
   }

   /* If Multiplication */
   if(op=='*') {
   clock_gettime(CLOCK_REALTIME, &TIME1);
   for(i = 0; i < maxitr; i++) c = a * b;
   clock_gettime(CLOCK_REALTIME, &TIME2);
   ELAPSED_TIME = (TIME2.tv_sec - TIME1.tv_sec)*1e9;
   ELAPSED_TIME  += (TIME2.tv_nsec - TIME1.tv_nsec);
   TIME_PERITR=ELAPSED_TIME/maxitr;;
   printf("Multiplication yeilds %lf and takes %lf nanoseconds per iteration.\n",c, TIME_PERITR);
   }

   /* If Division */
   if(op=='/') {
   clock_gettime(CLOCK_REALTIME, &TIME1);
   for(i = 0; i < maxitr; i++) c = a / b;
   clock_gettime(CLOCK_REALTIME, &TIME2);
   ELAPSED_TIME = (TIME2.tv_sec - TIME1.tv_sec)*1e9;
   ELAPSED_TIME  += (TIME2.tv_nsec - TIME1.tv_nsec);
   TIME_PERITR=ELAPSED_TIME/maxitr;
   printf("Division yeilds %lf and takes %lf nanoseconds per iteration.\n",c, TIME_PERITR);
   }
}
}
