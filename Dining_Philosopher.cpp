#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
using namespace std;
#define N 5
sem_t forks[N], room;
pthread_mutex_t printLock = PTHREAD_MUTEX_INITIALIZER;

void* philosopher(void* arg) {
    int id = *(int*)arg;
    int left = id, right = (id + 1) % N;
    for(int i = 0; i < 2; i++) {
        pthread_mutex_lock(&printLock);
        cout << "Philosopher " << id << " is thinking" << endl;
        pthread_mutex_unlock(&printLock);
        usleep(100000);
        sem_wait(&room);
        sem_wait(&forks[left]);
        sem_wait(&forks[right]);
        pthread_mutex_lock(&printLock);
        cout << "Philosopher " << id << " is eating (fork "
             << left << " and fork " << right << ")" << endl;
        pthread_mutex_unlock(&printLock);
        usleep(150000);
        sem_post(&forks[right]);
        sem_post(&forks[left]);
        sem_post(&room);
        pthread_mutex_lock(&printLock);
        cout << "Philosopher " << id
             << " finished eating and put down forks" << endl;
        pthread_mutex_unlock(&printLock);
    }
    return NULL;
}

int main() {
    pthread_t philo[N];
    int ids[N];
    for (int i = 0; i < N; i++)
        sem_init(&forks[i], 0, 1);
    sem_init(&room, 0, N - 1);
    for (int i = 0; i < N; i++) {
        ids[i] = i;
        pthread_create(&philo[i], NULL, philosopher, &ids[i]);
    }
    for (int i = 0; i < N; i++)
        pthread_join(philo[i], NULL);
    for (int i = 0; i < N; i++)
        sem_destroy(&forks[i]);
    sem_destroy(&room);
    pthread_mutex_destroy(&printLock);
    return 0;
}
