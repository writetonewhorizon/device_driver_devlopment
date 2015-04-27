#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>


int main()
//void comp(char m_arr[10])
{
	int fw,fc,fs,i,j,g = 0,l,count = 0;
	char k,s_e,s_o,store;
	fw = open("encryptionkey.c",O_RDONLY);
	fs = open("singh.c",O_RDONLY);
	fc = open("compressed_code.c",O_WRONLY);
	read(fw,&k,1);
	while(k != '\0')
	{
		count++;
		read(fw,&k,1);
	}
	lseek(fw,SEEK_SET,0);
	char key[count];
//	printf("%d\n",count);
	read(fw,&key,count);
//	printf("%c\n",key[9]);
	read(fs,&k,1);
//	for(m = 0;m < 2;m++)
//	
//	{
		while(k != '\0')
		{
			for(j = 0;j < count;j++)
			{
				if(k == key[j])
				{
					i = j;
					break;
				}
				else
					continue;
			}
			{
			if(g%2 == 0)
			{
				l = i;
				l = l << 4;
				s_e = l;
			}
			else
			{
				s_o = i;
				store = s_o | s_e;
				write(fc,&store,1);
//				printf("%d\n",store);
			}
			}
			read(fs,&k,1);
			g++;

		}
	store = '\0';
	write(fc,&store,1);	
//	}
	return 0;
}
