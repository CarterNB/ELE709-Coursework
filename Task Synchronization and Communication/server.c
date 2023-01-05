#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <pthread.h>
#include <mqueue.h>
#include <errno.h>
#define name  "/burwash-queue"
int stop_printing;

void *Cprompt(void *arg)
{
    mqd_t CRQ;

if ((CRQ = mq_open ("/client-qname", O_RDWR)) == -1) {
        perror ("Server: mq_open (client)");
        exit (1);
    }
    stop_printing = 0;
    int n;
    char buf[10];

while (1) {
printf("Enter the nth prime number you wish to know: ");
scanf("%d", &n);
sprintf(buf,"%d",n);
if (mq_send (CRQ, buf, sizeof(buf), 0) == -1) {
            perror ("Client: Not able to send message to server");
            continue;
        }
    if (n == 0) {
        stop_printing = 1;
        mq_close(CRQ);
        pthread_exit(NULL);
    }
}   
}

void *Cprint(void *arg)
{
    mqd_t SRQ;
    mode_t mode = 0666; 
    int prime;
    struct mq_attr my_attr;
    my_attr.mq_maxmsg = 10;      // Set max no of msg in queue to 10 msgs
    my_attr.mq_msgsize = 10;     // Set the max msg size to 10 bytes
    char inBuf[10];
if ((SRQ = mq_open ("/server-qname", O_RDWR)) == -1) {
        perror ("Server: mq_open (server)");
        exit (1);
    }
while (1) {
    mq_getattr(SRQ, &my_attr);
    int nMsgs = my_attr.mq_curmsgs;
while (nMsgs!=0) {
mq_receive(SRQ, inBuf, sizeof(inBuf), NULL);
prime=atoi(inBuf);
printf("\nThe Prime in that Position is %d\n", prime);

}
if (stop_printing == 1) {
    mq_close(SRQ);
    pthread_exit(NULL);
}
}
}

int main ()
{
    pthread_t Cprompt_t, Cprint_t;
    pthread_create(&Cprint_t, NULL, &Cprint, NULL);
    pthread_create(&Cprompt_t, NULL, &Cprompt, NULL);
    pthread_join(Cprint_t, NULL);
    pthread_join(Cprompt_t, NULL);
    pthread_exit(NULL);
}

