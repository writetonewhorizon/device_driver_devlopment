#include"header1.h"
#define REQ_FIFO "reqfifo"
#define RESULT_FIFO "result%dfifo"

struct data
{
	int cl_pid;
	int op1;
	int op2;
	unsigned char op;
}rcv_data;

int main(int argc,char *argv[])
{
	char *ch = "0123456789";
	int fdr;
	int fdw;
	int rfd;
	int rc,wc;
	int i=0;
	int wt;
	int result;
	char *buff;
	char *wd;
	char *rd;
	char *wd1;
	char *rd1;
	int pp[2],pp1[2];
	pid_t pid;
	pipe(pp);
	pipe(pp1);

	buff = (char *)malloc(sizeof(char)*30);
	wd = (char *)malloc(sizeof(char)*5);
	rd = (char *)malloc(sizeof(char)*5);
	wd1 = (char *)malloc(sizeof(char)*5);
	rd1 = (char *)malloc(sizeof(char)*5);

	sprintf(wd,"%d",pp[1]);
	sprintf(rd,"%d",pp[0]);
	sprintf(wd1,"%d",pp1[1]);
	sprintf(rd1,"%d",pp1[0]);

	if(access(REQ_FIFO,F_OK) == -1)
		mkfifo(REQ_FIFO,0777);

	printf("NO CLIENT YET\n");

	fdr = open(REQ_FIFO,O_RDONLY);

	while(1)
	{
		
		printf("Waiting for Client request\n");

again:		rc = read(fdr,&rcv_data,sizeof(struct data));
		
		if (rc != 0)
		{
			printf("Request is %d%c%d\n",rcv_data.op1,rcv_data.op,rcv_data.op2);

			write(pp1[1],&rcv_data,sizeof(struct data));

			pid = fork();
	
			if(!pid)
			{
				if(rcv_data.op == '+')
					execl("add_process","add_process",rd,wd,rd1,wd1,NULL);
				else if(rcv_data.op == '-')
					execl("sub_process","sub_process",rd,wd,rd1,wd1,NULL);
				else if(rcv_data.op == '*')
					execl("multi_process","multi_process",rd,wd,rd1,wd1,NULL);

				else
				{
				printf("No Processing client for Requested opretion i.e %d\n",rcv_data.op);
					return 0;
				}
			}	
			
			wait(&wt);
		
			rc = read(pp[0],&result,sizeof(int));
			
			printf("Result of Req is %d\n",result);

			sprintf(buff,RESULT_FIFO,rcv_data.cl_pid);
			rfd = open(buff,O_WRONLY);

			wc = write(rfd,&result,sizeof(int));

			close(rfd);

			memset(buff,'\0',strlen(buff));	
			printf("i = %d\n\n",i++);
		}
		else 
			goto again;
	}
		
	return 0;
}
