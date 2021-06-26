#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<string.h>

pthread_mutex_t my_lock;
int global = 0;

void *thread_func(void *arg)
{
	int i;
	int ret;
	int x = (int *)arg;
	printf("You are in [%s] x = %d\n",__func__,x);
	while(ret = pthread_mutex_trylock(&my_lock))
		printf("error pthread_mutex_trylock %s\n",strerror(ret));
//	pthread_mutex_lock(&my_lock);
	for(i=0;i<1000000;i++)
		global++;
	pthread_mutex_unlock(&my_lock);
	printf("Final global = %d\n",global);
}

int main()
{
	pthread_t t1,t2;
	int x ;
	pthread_mutex_init(&my_lock,0);
	pthread_create(&t1,NULL,thread_func,(int *)1);
	//sleep(1); // Global value will reach as expected 200000
	pthread_create(&t2,NULL,thread_func,(int *)2);

	printf("You are in main\n");

	pthread_join(t1,NULL);
	pthread_join(t2,NULL);

	pthread_mutex_destroy(&my_lock);
	return(0);
}
