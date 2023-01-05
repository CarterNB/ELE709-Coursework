#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define M 18
#define N 16
#define O 18
struct thread_info {
   int i;
   int j;
};

   int A[M][N];
   int B[N][O];
   int C[M][O];

typedef struct thread_info thread_info_t;

void *compute_C_ij(void *arg)
{
    thread_info_t *info;
    int n, sum=0;
    info = (thread_info_t *)arg; 

    for (n=0;n<N;n++){
        sum += A[info->i][n] *B[n][info->j];
    }
    C[info->i][info->j]=sum;
    
    pthread_exit(NULL);

   pthread_exit(NULL);
}

int main(void)
{
   int i, j;
   pthread_t thread;
   thread_info_t info;

   int width =0;
   for (i=0;i<M;i++)   {
        for (j=0;j<N; j++) {
            A[i][j]=(i+1)+(j+1);
        }
   }
   for (i=0;i<N;i++)   {
        for (j=0;j<O; j++) {
            B[i][j]=(i+1)+2*(j+1);
        }
   }
   for (size_t i=0;i<M;i++){
       for (size_t j=0;j<N;j++){
            int w= snprintf(NULL, 0, "%d", A[i][j]);
            if (width <w){
                width=w;
            }
       }
   }
   printf("MATRIX A\n");
   for (size_t i=0;i<M;i++){
       for (size_t j=0;j<N;j++){
            printf("%*d    ",width,A[i][j]);
            if (j==(N-1)){            
                printf("\n");
            }
       }
   }  
   printf("\n");
   for (size_t i=0;i<N;i++){
       for (size_t j=0;j<O;j++){
            int w= snprintf(NULL, 0, "%d", B[i][j]);
            if (width <w){
                width=w;
            }
       }
   }
   printf("MATRIX B\n");
   for (size_t i=0;i<N;i++){
       for (size_t j=0;j<O;j++){
            printf("%*d    ",width,B[i][j]);
            if (j==(O-1)){            
                printf("\n");
            }
       }
   }
   printf("\n");
   for (i=0;i<M;i++){
        for (j=0;j<O;j++){
            info.i=(int)i;
            info.j=(int)j;
            pthread_t thread;
            pthread_create(&thread,NULL,&compute_C_ij, &info);
            pthread_join(thread, NULL);
        }
   }
   for (size_t i=0;i<M;i++){
       for (size_t j=0;j<O;j++){
            int w= snprintf(NULL, 0, "%d", C[i][j]);
            if (width <w){
                width=w;
            }
       }
   }
   printf("MATRIX C\n");
   for (size_t i=0;i<M;i++){
       for (size_t j=0;j<O;j++){
            printf("%*d    ",width,C[i][j]);
            if (j==(O-1)){            
                printf("\n");
            }
       }
   }

}


