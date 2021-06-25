#include<stdio.h>
#include<semaphore.h>
#include<pthread.h>
#include<stdlib.h>

sem_t empty;
sem_t full;
pthread_mutex_t mylock;

int g_buffer[10];
int p_count =0;
int c_count = 0;
int count =0;

void *producer(void *arg)
{
	char *c = (char *)arg;
	printf("you are in %s\n",c);
	while(1) {
		sem_wait(&empty);
		pthread_mutex_lock(&mylock);
		g_buffer[p_count] = random();
		printf("[%s - %d] p_count = %d g_buffer[%d] = %d\n",__func__,__LINE__,p_count,p_count,g_buffer[p_count]);
		//p_count = (p_count+1)%10;
		p_count = p_count+1;
		pthread_mutex_unlock(&mylock);
		sem_post(&full);
	}
		g_buffer[count] = count ;
		count++;
		pthread_mutex_unlock(&mylock);
		sem_post(&full);
}

void *consumer(void *arg)
{

	char *c = (char *)arg;
	int t;
	printf("you are in %s\n",c);
	while(1) {
		sem_wait(&full);
		pthread_mutex_lock(&mylock);
		//t = g_buffer[c_count];
		t = g_buffer[--p_count];
		printf("[%s - %d] p_count = %d t = %d\n",__func__,__LINE__,p_count,t);
	//	c_count = (c_count +1)%10;
		pthread_mutex_unlock(&mylock);
		sem_post(&empty);
	}
		t = g_buffer[count];
		count --;
		printf("t = %d\n",t);
		pthread_mutex_unlock(&mylock);
		sem_post(&empty);
}

int main()
{
	pthread_t t1,t2;
	pthread_mutex_init(&mylock,0);
	sem_init(&empty,0,10);
	sem_init(&full,0,0);
	pthread_create(&t1,NULL,producer,"Producer");
	pthread_create(&t2,NULL,consumer,"Consumer");

	printf("You are in main\n");
	pthread_join(t1,NULL);
	pthread_join(t2,NULL);
	pthread_create(&t1,NULL,consumer,"Consumer");

	printf("You are in main\n");
	pthread_join(t1,NULL);
	pthread_join(t1,NULL);

	pthread_mutex_destroy(&mylock);
	sem_destroy(&empty);
	sem_destroy(&full);
	return 0;
}
