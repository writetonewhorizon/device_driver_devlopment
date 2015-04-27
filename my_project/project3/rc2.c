#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
int main(int argc,char *argv[])
{
	int i,file_discriptor[2];
        int recived,sum;
        char sum1[2],sum2[2];
	struct data{
			char arry;
			int aar[2];
		}datavar;
	struct data1{
			char operator;
			int result;
			}datavar1;
        printf("minu\n");
        sscanf(argv[1],"%d",&file_discriptor[0]);
	printf("fd = %d\n",file_discriptor[0]);
        sscanf(argv[2],"%d",&file_discriptor[1]);
	printf("fd = %d\n",file_discriptor[1]);
                recived=read(file_discriptor[0],&datavar,sizeof(datavar));
		printf("%c %d %d \n",datavar.arry,datavar.aar[0],datavar.aar[1]);
                datavar1.result=datavar.aar[0]-datavar.aar[1];
                printf("differance is= %d\n",datavar1.result);
		datavar1.operator=datavar.arry;
                //sprintf(datavar.sum1,"%d",sum);
                recived = write(file_discriptor[1],&datavar1,sizeof(datavar));
		//write(file_discriptor[1],&datavar.arry,4);
		printf("number of bytes write are =%d\n",recived);
		printf("operator write is %c\n",datavar1.operator);
        exit(1);

}
