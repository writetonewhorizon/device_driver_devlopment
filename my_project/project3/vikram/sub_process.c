#include"header1.h"
struct data
{
	int cl_pid;
	int op1;
	int op2;
	unsigned char op;
}rcv_data;

int main(int argc,char * argv[])
{
	int i = 0;
	int j = 0;
	int rd,wr;
	char *op;
	int result;
	char ch=1;
	op = (char *)malloc(sizeof(char));

	rd = atoi(argv[3]);
	wr = atoi(argv[2]);

	read(rd,&rcv_data,sizeof(struct data));
	
	result = rcv_data.op1 - rcv_data.op2;
	printf("result %d\n",result);

	write(wr,&result,4);
	
	exit(4);
}	
