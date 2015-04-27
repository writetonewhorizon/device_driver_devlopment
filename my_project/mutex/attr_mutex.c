#include<stdio.h>
#include<pthread.h>
#include<signal.h>


pthread_t tid1,tid2;
pthread_mutexattr_t attr;
pthread_mutex_t mlock;
int a = 0;
void *ret;
void * thread1(void *);
void * thread2(void *);


void handler1(int signum)
{
	printf("Executing %s\n",__func__);
	pthread_join(tid1,&ret);
	printf("ret1 = %s\n",(char *)ret);
	printf("Finishing %s\n",__func__);
//	a++;
}

void handler2(int signum)
{
	printf("Executing %s\n",__func__);
	pthread_join(tid2,&ret);
	printf("ret2 = %s\n",(char *)ret);
	printf("Finishing %s\n",__func__);
//	a++;
}
int main()
{
	printf("Executing %s\n",__func__);
	signal(SIGUSR1,handler1);
	signal(SIGUSR2,handler2);
	pthread_create(&tid1,NULL,&thread1,NULL);
	pthread_create(&tid2,NULL,&thread2,NULL);
	pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
	pthread_mutex_init(&mlock,&attr);
	printf("mlock = %d\n",mlock);
	while(a < 2)
	{
		printf("%s\tPID = %d PPID = %d\ta = %d\n",__func__,getpid(),getppid(),a);
		sleep(1);
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
//	pthread_mutex_lock(&mlock);
	printf("Executing %s\n",__func__);
	int type = 0;
//	a++;
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
	kill(getpid(),SIGUSR1);
	a++;
//	pthread_mutex_unlock(&mlock);
	pthread_exit("thread1");
}

void * thread2(void * ptr)
{
	int ret;
//	ret = pthread_mutex_unlock(&mlock);
/*
	if(WIFEXIT(ret))
	{
		printf("%s\n",IFEXITSTATUS(ret));
	}
*/
	pthread_mutex_lock(&mlock);
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
	kill(getpid(),SIGUSR2);
	a++;
	pthread_exit("thread2");
}
