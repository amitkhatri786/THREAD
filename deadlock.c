#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include <unistd.h>

volatile int balance1 = 1;
volatile int balance2 = 1;

pthread_mutex_t mymutex1;
pthread_mutex_t mymutex2;

void *function(void *args)
{
	int i;
	char *p = (char *)args;
	printf("Thread name %s\n",p);
	printf("Calling lock mutex1 %s\n",p);
	pthread_mutex_lock(&mymutex1);
	sleep(2);
	printf("Calling lock mutex2 %s\n",p);
	pthread_mutex_lock(&mymutex2);
	printf("%s accure mymutex2\n",p);
	pthread_mutex_unlock(&mymutex2);

	pthread_mutex_unlock(&mymutex1);
	printf("%s Done\n",p);
	//return 1;
}

void *function1(void *args)
{
	int i;
	char *p = (char *)args;
	printf("Thread name %s\n",p);
	printf("Calling lock mutex2 %s\n",p);
	pthread_mutex_lock(&mymutex2);
	sleep(2);
	printf("Calling lock mutex1 %s\n",p);
	pthread_mutex_lock(&mymutex1);
	printf("%s accure mymutex1\n",p);
	pthread_mutex_unlock(&mymutex1);
	pthread_mutex_unlock(&mymutex2);
	printf("%s Done\n",p);
}

int main()
{
	pthread_t t1,t2;
	pthread_mutex_init(&mymutex1,0);
	pthread_mutex_init(&mymutex2,0);
	pthread_create(&t1,NULL,function,"Thread1");
	pthread_create(&t2,NULL,function1,"Thread2");

	printf("Going to join thread1\n");
	pthread_join(t1,NULL);
	printf("Going to join thread2\n");
	pthread_join(t2,NULL);
	pthread_mutex_destroy(&mymutex1);
	pthread_mutex_destroy(&mymutex2);
	printf("MAin thread balance1 = %d balance2 = %d \n",balance1,balance2);
	return 0;
}

