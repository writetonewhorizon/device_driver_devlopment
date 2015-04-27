#include<stdio.h>
#include<pthread.h>
#include<signal.h>
#include<string.h>
#include<errno.h>

pthread_t tid[2];
pthread_mutexattr_t attr;
pthread_mutex_t mlock;
int a = 0;
void *ret;
void * thread1(void *);
void * thread2(void *);

int main()
{
	printf("Executing %s\n",__func__);
	int i = 0;
	pthread_create(&tid[0],NULL,&thread1,NULL);
	pthread_create(&tid[1],NULL,&thread2,NULL);
	pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_NORMAL);
	pthread_mutex_init(&mlock,&attr);
	printf("mlock = %d\n",mlock);
/*
	while(a < 2)
	{
		printf("%s\tPID = %d PPID = %d\ta = %d\n",__func__,getpid(),getppid(),a);
		sleep(1);
	}
*/
	for(i = 0;i < 2;i++)
	{
		pthread_join(tid[i],&ret);
		printf("RET = %s\n",ret);
	}
	sleep(1);
	pthread_mutexattr_destroy(&attr);
	pthread_mutex_destroy(&mlock);
	printf("Finishing %s\n",__func__);
	return 0;
}

void * thread1(void * ptr)
{
	pthread_mutex_lock(&mlock);
	printf("Executing %s\n",__func__);
	sleep(5);
	int type = 0;
	pthread_mutexattr_gettype(&attr,&type);
	switch(type)
	{
		case PTHREAD_MUTEX_NORMAL:
			printf("Case 1\n");
			break;
		case PTHREAD_MUTEX_RECURSIVE:
			printf("Case 2\n");
			break;
		case PTHREAD_MUTEX_ERRORCHECK:
			printf("Case 3\n");
			break;
	}
	printf("%s\tPID = %d PPID = %d\n",__func__,getpid(),getppid());
	printf("Finishing %s\n",__func__);
	pthread_mutex_unlock(&mlock);
//	a++;
	pthread_exit("thread1");
}

void * thread2(void * ptr)
{
	int ret;
	char errbuff[10];
	ret = pthread_mutex_unlock(&mlock);
	strerror_r(ret,errbuff,5);
	printf("Error = %d %s\n",ret,errbuff);
//	ret = errno;
	if(ret == 0)
		printf("Unlocked Successfully\n");
//	else

	ret = errno;
	strerror_r(ret,errbuff,5);
	printf("Error = %d %s\n",ret,errbuff);
//	pthread_mutex_lock(&mlock);
	printf("Executing %s\n",__func__);
	int type = 0;
	sleep(5);
	pthread_mutexattr_gettype(&attr,&type);
	switch(type)
	{
		case PTHREAD_MUTEX_NORMAL:
			printf("Case 1\n");
			break;
		case PTHREAD_MUTEX_RECURSIVE:
			printf("Case 2\n");
			break;
		case PTHREAD_MUTEX_ERRORCHECK:
			printf("Case 3\n");
			break;
	}
	printf("%s\tPID = %d PPID = %d\n",__func__,getpid(),getppid());
	printf("Finishing %s\n",__func__);
	pthread_mutex_unlock(&mlock);
//	a++;
	pthread_exit("thread2");
}
