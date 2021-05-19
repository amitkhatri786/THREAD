#include<stdio.h>
#include<semaphore.h>
#include<pthread.h>


sem_t empty;
sem_t full;
pthread_mutex_t mylock;

int g_buffer[10];
int count =0;

void *producer(void *arg)
{
	char *c = (char *)arg;
	printf("you are in %s\n",c);
	while(1) {
		sem_wait(&empty);
		pthread_mutex_lock(&mylock);
		g_buffer[count] = count ;
		count++;
		pthread_mutex_unlock(&mylock);
		sem_post(&full);
	}

}

void *consumer(void *arg)
{

	char *c = (char *)arg;
	int t;
	printf("you are in %s\n",c);
	while(1) {
		sem_wait(&full);
		pthread_mutex_lock(&mylock);
		t = g_buffer[count];
		count --;
		printf("t = %d\n",t);
		pthread_mutex_unlock(&mylock);
		sem_post(&empty);
	}

}

int main()
{
	pthread_t t1,t2;
	pthread_mutex_init(&mylock,0);
	sem_init(&empty,0,10);
	sem_init(&full,0,0);
	pthread_create(&t1,NULL,producer,"Producer");
	pthread_create(&t1,NULL,consumer,"Consumer");

	printf("You are in main\n");
	pthread_join(t1,NULL);
	pthread_join(t1,NULL);

	pthread_mutex_destroy(&mylock);
	sem_destroy(&empty);
	sem_destroy(&full);
	return 0;
}
