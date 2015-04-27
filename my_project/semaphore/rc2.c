#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<stdio.h>
#include<sys/sem.h>
#include<sys/ipc.h>
struct data{
		char arry;
		int arr[2];
		}datavar;
struct data1{
		int result;
		char operator;
		}datavar1;
/*struct sembuf{
		short sem_num;
		short sem_ops;
		short sem_flg;
		}sem;*/
union semun{
		int val;
		struct semid_ds *buf;
		unsigned short *array;
		}sem;
static void del_semvalue(void);
static int semaphore_p(void);
static int semaphore_v(void);
int sem_id;
int main()
{
	int fd1,fd2,file1,recived;
	datavar.arry='-';
	datavar.arr[0]=30;
	datavar.arr[1]=20;
	semaphore_p();
//	recived=semop(sem_id,struct sembuf *sem,SEM_UNDO);
//	printf("semid is %d\n",sem_id);
//	sem.sem_num=0;
//	sem.sem_ops=-1;
	fd1=open("fifo_server",O_WRONLY);
//	printf("process pid is %d\n",getpid());
	recived=write(fd1,&datavar,sizeof(datavar));
	close(fd1);
//	printf("number of written by are %d\n",recived);
//	printf("writen data is %c %d %d\n",datavar.arry,datavar.arr[0],datavar.arr[1]);
	if(access("fifo_client1",F_OK) == -1)
	file1=mkfifo("fifo_client1",0777);
	if(file1<0)
	{
		printf("file not created successfuly\n");
	}
	else
	{
		printf("file created successfully and pid is %d\n",getpid());
	}
	fd2=open("fifo_client1",O_RDONLY);
	printf("file discriptor is %d\n",fd2);
	recived=read(fd2,&datavar1,sizeof(datavar));
	close(fd2);
//	printf("number of bytes read are %d\n",recived);
	printf("result of differance (30-20)= %d\n",datavar1.result);
	semaphore_v();
	//printf("end of program\n");
	//sem.sem_ops=1;
//semop(sem_id,struct sembuf *sem_ops,SEM_UNDO);
}
static int semaphore_p(void)
{
	struct sembuf sem_b;
	sem_b.sem_num = 0;
	sem_b.sem_op = -1;
	sem_b.sem_flg=SEM_UNDO;
	if(semop(sem_id,&sem_b,1)==-1)
	{
		fprintf(stderr,"semaphore_p failed\n");
		return(0);
	}
	return(1);
}
static int semaphore_v(void)
{
	struct sembuf sem_b;
	sem_b.sem_num = 0;
	sem_b.sem_op=1;
	sem_b.sem_flg=SEM_UNDO;
	if(semop(sem_id,&sem_b,1)==-1)
	{
		fprintf(stderr,"semaphore_v failed\n");
		return(0);
	}
	return(1);
}
static void del_semvalue(void)
{
	union semun sem;
	if(semctl(sem_id,0,IPC_RMID,sem)==-1)
	fprintf(stderr,"failed to dellete semaphore\n");
}
