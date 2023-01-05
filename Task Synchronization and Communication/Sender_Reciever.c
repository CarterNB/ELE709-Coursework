#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>
#include <mqueue.h>
#include <errno.h>

sem_t sem;
struct Msg {char str[40]; unsigned int priority; };
int errno;

const char *queue = "/myque";  // Define the name of the MQ, use your
                               // last name as part of the name to create
                               // a unique name.

void *Receiver(void *arg)  // This thread receives msgs from the MQ
{
   mqd_t rx;
   struct mq_attr my_attrs;
   ssize_t n;
   int nMsgs;
   char inBuf[50];
   unsigned int priority;

   sleep(2);

   rx = mq_open(queue, O_RDONLY);  // Open the MQ for reading only (O_RDONLY)

   if (rx < 0 ) perror("Receiver mq_open:");  // Error checking

   mq_getattr(rx, &my_attrs);     // Determine no. of msgs currently in the MQ
   nMsgs = my_attrs.mq_curmsgs;
   // Receive all messages in the MQ by calling mq_receive

   while (nMsgs>> 0){
      n = mq_receive(rx, inBuf, sizeof(inBuf), &priority);
      inBuf[n] = '\0';
      if (n < 0) perror("Receiver mq_receive:");  // Error checking
      printf("Message recieved = %s. Priority %d\n", inBuf, priority);
      sem_post(&sem);
   }
   
   mq_close(rx);   // Close the MQ
   pthread_exit(NULL);
}
   
void *Sender(void *arg)  // This thread sends msgs to the MQ
{
   int retcode, i;
   mqd_t tx;
   struct Msg myMsg;

   sleep(1);

   tx = mq_open(queue, O_WRONLY);  // Open the MQ for writing only (O_WRONLY)

   if (tx < 0) perror("Sender mq_open:");  // Error checking
   
    for(i=1;i<=10;i++){
      sem_wait(&sem);
      sprintf(myMsg.str, "This is message %d", i);  // Set up message to be sent
      myMsg.priority = i;    // Set up priority of this message
      printf("Message sent = %s. Priority = %d\n",myMsg.str,myMsg.priority);
      retcode = mq_send(tx, myMsg.str, (size_t)strlen(myMsg.str), myMsg.priority);
      if (retcode < 0) perror("Sender mq_send:");  // Error checking 
    }
   mq_close(tx);
   pthread_exit(NULL);
}

int main(void *arg)
{
   sem_init(&sem, 0, 1);
   mqd_t trx;
   mode_t mode;
   int oflags;
   struct mq_attr my_attrs;
   pthread_t Sender_thread, Receiver_thread;

   my_attrs.mq_maxmsg = 1;      // Set max no of msg in queue to 10 msgs
   my_attrs.mq_msgsize = 50;     // Set the max msg size to 50 bytes

   oflags = O_CREAT | O_RDWR ;   // Set oflags to create queue (O_CREAT)
                                 //  and for read & write (O_RDWR)
   
   mode = S_IRUSR | S_IWUSR;     // Set mode to allow other threads
                                 //  (created by same user) to use the queue

   trx = mq_open(queue, oflags, mode, &my_attrs);  // Create the MQ

   if (trx < 0) perror("Main mq_open:");  // Error checking

   // Create a thread to send messages to the MQ

   printf("Creating Sender thread\n");
   if (pthread_create(&Sender_thread, NULL, &Sender, NULL) != 0) {
       printf("Error creating Sender thread.\n");
       exit(-1);
   }

   // Create a thread to receive the messages from the MQ

   printf("Creating Receiver thread\n");
   if (pthread_create(&Receiver_thread, NULL, &Receiver, NULL) != 0) {
       printf("Error creating Receiver thread.\n");
       exit(-1);
   }
   
   pthread_join(Sender_thread, NULL);
   pthread_join(Receiver_thread, NULL);
   mq_unlink(queue);     // Destroy the MQ
   sem_destroy(&sem);
   exit(0);
   
}
