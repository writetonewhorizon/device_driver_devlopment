#include"header1.h"
#define REQ_FIFO "reqfifo"
#define RESULT_FIFO "result%dfifo"

struct data
{
	int pid;
	int op1;
	int op2;
	unsigned char op;
}req_data;

int main(int argc,char *argv[])
{
	int fdw;
	int fdr;
	int wc;
	int rc;
	int op1,op2;
	char op;
	int result;
	int pid;
	char *buff;
	char ch;

	ch = '\0';
	
	buff = (char *)malloc(sizeof(char)*20);

	sprintf(buff,RESULT_FIFO,getpid());

	if(access(buff,F_OK) == -1)
		mkfifo(buff,0777);	
	
	fdw = open(REQ_FIFO,O_WRONLY);	

	req_data.op1 = 12;
	req_data.op2 = 3;
	req_data.op = '*';

	req_data.pid = getpid();

	wc = write(fdw,&req_data,sizeof(struct data));

	close(fdw);

	fdr = open(buff,O_RDONLY);

	rc = read(fdr,&result,4);

	printf("Client2 Got Result %d for Req %d%c%d\n\n",result,req_data.op1,req_data.op,req_data.op2);

	close(fdr);

	unlink(buff);
	
	return 0;
}
