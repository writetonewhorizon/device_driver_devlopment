#include<stdio.h>
#include<pthread.h>
#include<signal.h>


pthread_t tid1,tid2;
int a = 0;
void *ret;
void * thread1(void *);
void * thread2(void *);

pthread_mutex_t mlock;

void handler1(int signum)
{
	printf("Executing %s\n",__func__);
	pthread_join(tid1,&ret);
	a++;
	printf("ret1 = %s\n",(char *)ret);
	printf("Finishing %s\n",__func__);
}

void handler2(int signum)
{
	printf("Executing %s\n",__func__);
	pthread_join(tid2,&ret);
	a++;
	printf("ret2 = %s\n",(char *)ret);
	printf("Finishing %s\n",__func__);
}

int main()
{
	printf("Executing %s\n",__func__);
	signal(SIGUSR1,handler1);
	signal(SIGUSR2,handler2);
	pthread_create(&tid1,NULL,&thread1,NULL);
	pthread_create(&tid2,NULL,&thread2,NULL);
	pthread_mutex_init(&mlock,NULL);
	printf("mlock = %d\n",mlock);
	while(a != 4)
	{
		printf("%s\tPID = %d PPID = %d\ta = %d\n",__func__,getpid(),getppid(),a);
		sleep(1);
	}
	pthread_mutex_destroy(&mlock);
	printf("Finishing %s\n",__func__);
	return 0;
}

void * thread1(void * ptr)
{
	printf("Executing %s\n",__func__);
	pthread_mutex_lock(&mlock);
	a++;
//	pthread_mutex_lock(&mlock);
//	sleep(5);
	printf("%s\tPID = %d PPID = %d\n",__func__,getpid(),getppid());
	kill(getpid(),SIGUSR1);
	printf("Finishing %s\n",__func__);
	pthread_mutex_unlock(&mlock);
	pthread_exit("thread1");
}

void * thread2(void * ptr)
{
	printf("Executing %s\n",__func__);
//	sleep(1);
//	pthread_mutex_unlock(&mlock);
	pthread_mutex_lock(&mlock);
	a++;
	printf("%s\tPID = %d PPID = %d\n",__func__,getpid(),getppid());
	kill(getpid(),SIGUSR2);
	printf("Finishing %s\n",__func__);
	pthread_mutex_unlock(&mlock);
	pthread_exit("thread2");
}

