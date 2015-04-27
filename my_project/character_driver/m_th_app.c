#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>
#include<fcntl.h>
#include<unistd.h>

void *wr_open_th(void *);
void *rd_open_th(void *);
void *read_th(void *);
void *write_th(void *);
void *close_th(void *);

int rfd,wfd;

int main(int argc, char *argv[])
{
	pthread_t th[4];
	int ret;
	void **rptr = (void **)malloc(sizeof(void *));

	printf("Begin>>>>>> %s in app PID is %d\n",__func__,getpid());

	ret = pthread_create(&th[0],NULL,wr_open_th,(void *)argv[1]);
	if(ret)
	{
		printf("thread creation failed\n");
	}

	ret = pthread_create(&th[1],NULL,rd_open_th,(void *)argv[1]);
	if(ret)
	{
		printf("thread creation failed\n");
	}


	ret = pthread_create(&th[3],NULL,read_th,(void *)argv[1]);
	if(ret)
	{
		printf("thread creation failed\n");
	}
	

	ret = pthread_create(&th[2],NULL,write_th,(void *)argv[1]);
	if(ret)
	{
		printf("thread creation failed\n");
	}

	while(!rfd && !wfd);
	printf("Write File Discriptor is %d\n",wfd);
	printf("Read File Discriptor is %d\n",rfd);

	pthread_join(th[0],rptr);
	pthread_join(th[1],rptr);
	pthread_join(th[2],rptr);
	pthread_join(th[3],rptr);

	printf("End<<<<<<<<< %s in app\n",__func__);
	return 0;
}

void *wr_open_th(void *arg)
{
	char *file;
	printf("Begin>>>>>> %s\n",__func__);
	file = (char *)arg;
	printf("In %s PID = %d\n",__func__,getpid());

	wfd = open(file,O_WRONLY);
	if(wfd < 0)
		printf("Open in Write mode Failed\n");

	printf("End<<<<<<<<< %s\n",__func__);
	while(1);

	pthread_exit(NULL);
}

void *rd_open_th(void *arg)
{
	char *file;
	printf("Begin>>>>>> %s\n",__func__);
	file = (char *)arg;
	printf("In %s PID = %d\n",__func__,getpid());

	rfd = open(file,O_RDONLY);
	if(rfd < 0)
		printf("Open in Read mode Failed\n");

	printf("End<<<<<<<<< %s\n",__func__);
	while(1);
	pthread_exit(NULL);
}

void *write_th(void *arg)
{
	int wc;
	char *ch = "........................Vikram Sharma Attri.......................";
	while(!wfd);
	printf("Begin>>>>>> %s\n",__func__);
	printf("In %s PID = %d\n",__func__,getpid());

	wc = write(wfd,ch,strlen(ch));
	printf("%d bytes written over Device\n",wc);

	sleep(300);

	printf("End<<<<<<<<< %s\n",__func__);
	while(1);
	pthread_exit(NULL);
}

void *read_th(void *arg)
{
	int rc;
	char *ch = (char *)malloc(sizeof(char) * 3000);
	while(!rfd);
	printf("Begin>>>>>> %s\n",__func__);
	printf("In %s PID = %d\n",__func__,getpid());

	rc = read(rfd,ch,3000);
	printf("%d bytes read from Device\n",rc);

	printf("Read from Device %s\n",ch);
	while(1);
	sleep(300);

	printf("End<<<<<<<<< %s\n",__func__);
	pthread_exit(NULL);
}
