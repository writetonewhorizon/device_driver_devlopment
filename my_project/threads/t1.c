#include<stdio.h>
#include<pthread.h>
void *func(void *);
void *fun(void *);
void *func1(void *);
int main()
{
	printf("BEGIN: %s\n",__func__);
	pthread_t th,th1;
	void * ret;
	pthread_create(&th,0,&func,(void *)"hello\n");
	pthread_join(th,&ret);
	//pthread_create(&th1,0,&func1,(void *)"......hello\n");
	int i;
	for(i = 0; i < 5; i++ )
	{
		printf("in main\n");
		sleep(1);
	}
	printf("data in main is : %s",(void **)ret);
//	pthread_join(th1,&ret);
//	printf(".....data in main is : %s",(void **)ret);
	printf("END: %s\n",__func__);
	return 0;
}
void *func(void *p)
{
	int i;
	printf("data is : %s",(char *)p);
	pthread_t th;
	void * ret;
	pthread_create(&th,0,&fun,(void *)"\t\thello\n");
	for(i = 0; i < 10; i++ )
	{
		printf("in func\n");
		sleep(1);
	}
	pthread_join(th,&ret);
	pthread_exit((void *)"bye\n");
}
void *func1(void *p)
{
	int i;
	printf("__________data is : %s",(char *)p);
	for(i = 0; i < 10; i++ )
	{
		printf(".....in func\n");
		sleep(1);
	}
	pthread_exit((void *)".....bye\n");
}
void *fun(void *p)
{
	int i;
	printf("\t\t__________data is : %s",(char *)p);
	for(i = 0; i < 10; i++ )
	{
		printf("\t\t.....in fun\n");
		sleep(1);
	}
	pthread_exit((void *)"\t\t.....bye\n");
}
