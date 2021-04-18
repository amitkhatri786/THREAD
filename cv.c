#include<stdio.h>
#include<pthread.h>

pthread_mutex_t lock;
pthread_cond_t cv1;
pthread_cond_t cv2;
int firstprint = 0;
int secondprint = 0;

void *fun1(void *arg)
{
	pthread_mutex_lock(&lock);
	printf("[%s - %d]\n",__func__,__LINE__);
	firstprint = 1;
	pthread_cond_signal(&cv1);
	pthread_mutex_unlock(&lock);
	printf("EXIT [%s - %d]\n",__func__,__LINE__);
}

void *fun2(void *arg)
{
	
	pthread_mutex_lock(&lock);
	printf("[%s - %d]\n",__func__,__LINE__);
	while(firstprint == 0) {
		printf("waiting [%s - %d]\n",__func__,__LINE__);
		pthread_cond_wait(&cv1,&lock);
	}
	secondprint = 1;
	pthread_cond_signal(&cv2);
	pthread_mutex_unlock(&lock);
	printf("EXIT [%s - %d]\n",__func__,__LINE__);
}

void *fun3(void *arg)
{
	pthread_mutex_lock(&lock);
	printf("[%s - %d]\n",__func__,__LINE__);
	while(secondprint==0) {
		printf("waiting [%s - %d]\n",__func__,__LINE__);
		pthread_cond_wait(&cv2,&lock);
	}
	pthread_mutex_unlock(&lock);
	printf("EXIT [%s - %d]\n",__func__,__LINE__);
}

int main()
{
	pthread_t t1,t2,t3;
	pthread_mutex_init(&lock,NULL);
	pthread_cond_init(&cv1,NULL);
	pthread_cond_init(&cv2,NULL);
	pthread_create(&t1,NULL,fun1,NULL);
	pthread_create(&t2,NULL,fun2,NULL);
	pthread_create(&t3,NULL,fun3,NULL);
	printf("This is main thread\n");
	pthread_join(t1,NULL);
	pthread_join(t2,NULL);
	pthread_join(t3,NULL);
	pthread_mutex_destroy(&lock);
	pthread_cond_destroy(&cv1);
	pthread_cond_destroy(&cv2);
	return 0;

}

