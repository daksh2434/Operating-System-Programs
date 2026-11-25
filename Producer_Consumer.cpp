#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
using namespace std;
#define SIZE 5
#define ITEMS 10
int buffer[SIZE], in = 0, out = 0;
sem_t emptySlots, full, mutex;
void* producer(void*) {
    for (int i = 1; i <= ITEMS; i++) {
        sem_wait(&emptySlots);
        sem_wait(&mutex);
        buffer[in] = i;
        cout << "Producer produced item " << i
             << " at slot " << in << endl;
        in = (in + 1) % SIZE;
        sem_post(&mutex);
        sem_post(&full);
        usleep(100000);
    }
    return NULL;
}
void* consumer(void*) {
    for (int i = 1; i <= ITEMS; i++) {
        sem_wait(&full);
        sem_wait(&mutex);
        int item = buffer[out];
        cout << "\tConsumer consumed item " << item
             << " from slot " << out << endl;
        out = (out + 1) % SIZE;
        sem_post(&mutex);
        sem_post(&emptySlots);
        usleep(150000);
    }
    return NULL;
}
int main() {
    pthread_t prod, cons;
    sem_init(&emptySlots, 0, SIZE);
    sem_init(&full, 0, 0);
    sem_init(&mutex, 0, 1);
    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);
    pthread_join(prod, NULL);
    pthread_join(cons, NULL);
    sem_destroy(&emptySlots);
    sem_destroy(&full);
    sem_destroy(&mutex);
    cout << "All items produced and consumed." << endl;
    return 0;
}
