#include<pthread.h>
#include<stdio.h>

volatile int balance = 1;

pthread_mutex_t mymutex;

void *function(void *args)
{
	int i;
	char *p = (char *)args;
	printf("Thread name %s\n",p);
	for(i=0;i<1000000;i++) {
		pthread_mutex_lock(&mymutex);
		balance = balance + 1;
		pthread_mutex_unlock(&mymutex);
	}
	printf("%s Done\n",p);

	//return 1;
}


int main()
{
	pthread_t t1,t2;
	pthread_mutex_init(&mymutex,0);
	pthread_create(&t1,NULL,function,"Thread1");
	pthread_create(&t2,NULL,function,"Thread2");

	printf("Going to join thread1\n");
	pthread_join(t1,NULL);
	printf("Going to join thread2\n");
	pthread_join(t2,NULL);
	pthread_mutex_destroy(&mymutex);
	printf("MAin thread balance = %d\n",balance);
	return 0;
}

