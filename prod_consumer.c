/**
 * gcc -pthread prod_consumer.c -o prod_consumer
 **/

#include <stdio.h>
#include <pthread.h>

int b; /* buffer size = 1; */
int turn=0;

int main() {
    pthread_t producer_thread1;
    pthread_t producer_thread2;
    pthread_t producer_thread3;

    pthread_t consumer_thread1;
    pthread_t consumer_thread2;
    pthread_t consumer_thread3;

    void *producer();
    void *consumer();

    pthread_create(&consumer_thread1,NULL,consumer,NULL);
    pthread_create(&consumer_thread2,NULL,consumer,NULL);
    pthread_create(&consumer_thread3,NULL,consumer,NULL);

    pthread_create(&producer_thread1,NULL,producer,NULL);
    pthread_create(&producer_thread2,NULL,producer,NULL);
    pthread_create(&producer_thread3,NULL,producer,NULL);


    pthread_join(consumer_thread1,NULL);
    pthread_join(consumer_thread2,NULL);
    pthread_join(consumer_thread3,NULL);

    return 0;
}

void put(int i){
    b = i;
}

int get(){
    return b ;
}

void *producer() {
    int i = 0;
    //
    while (1) {
        printf("Produtor\n");
        while (turn == 1) ;
        printf("turn P %d \n", turn);
        put(i);
        turn = 1;
        i = i + 1;
    }
    pthread_exit(NULL);
}

void *consumer() {
    int i,v;
    //printf("Consumidor\n");
    for (i=0;i<2;i++) {
        printf("Consumidor \n");
        while (turn == 0) ;
        printf("turn C %d \n", turn);
        v = get();
        turn = 0;
        printf("Peguei %d \n",v);
    }
    pthread_exit(NULL);
}
