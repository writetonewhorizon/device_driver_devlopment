
int compress4()
//void comp(char m_arr[10])
{
	int fw,fc,fs,i,j,g = 0,l,count = 0,rc;
	char k,s_e,s_o,store;
	fw = open("/home/avtar/project1/mdcproject/masterarrayg.txt",O_RDONLY);
	fs = open("/home/avtar/project1/mdcproject/origionalg.txt",O_RDONLY);
	fc = open("/home/avtar/project1/mdcproject/compressed_codeg.txt",O_WRONLY);
	rc = read(fw,&k,1);
	while(rc != 0)
	{
		count++;
		rc = read(fw,&k,1);
	}
	lseek(fw,SEEK_SET,0);
	char key[count];
//	printf("%d\n",count);
	read(fw,&key,count);
//	printf("%c\n",key[9]);
	rc = read(fs,&k,1);
//	for(m = 0;m < 2;m++)
//	
//	{
		while(rc != 0)
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
			rc = read(fs,&k,1);
			g++;

		}
	store = '\0';
	write(fc,&store,1);	
//	}
	return(1);
}
