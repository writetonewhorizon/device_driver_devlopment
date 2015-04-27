int master(int s)
{
	char *marray;
	char c,r[s],k = 0;
	int i,j,x;
	int count = 0;
//	marray = (char *)malloc(sizeof(char));
//	printf("%d\n",sizeof(*marray));
/*	FILE *fp;
	fp = open("singh.c","r");
	c = getc(fp);
	*marray = c;
	c = getc(fp);
	printf("%c %c\n",c,*marray);
	fputc(marray,fp);*/
	int fq,fz;
	fq = open("singh.c",O_RDONLY);
	x = read(fq,&r,s);
//	printf("%s\n",r);
	for(i = 0;i < s;i++)
	{
		count++;
		c = r[i];
		if(i == 0)
		{
			marray = malloc(sizeof(char));
			*marray = c;
			continue;
		
		}
		else if(c != '\0')
		{
			for(j = 0;j < count-1;j++)
			{
				if(c != r[j] && j == count - 2)
				{
					k++;
					marray = realloc(marray,(k + 1));
					*(marray+(k)) = c;
//					printf("%c",*(marray+(k)));
				}
				else if(c != r[j])
					continue;
				else
					break;

			}
		}
		else if(c == '\0')
		{
				k++;
				marray = realloc(marray,(k + 1));
				*(marray+(k)) = '\0';
				break;
		}
//		else
//			break;
	}
//	printf("\nsize of master array is :%d\n",k);
//	printf("Master array is\n");
	fz = open("encryptionkey.c",O_WRONLY);
	i = 0;
	while(*(marray + i) != '\0')
	{
	k = write(fz,(marray + i),1);
//	printf("%c",*(marray + i));
	i++;
	}
	if(*(marray + i) == '\0')
	write(fz,(marray + i),1);
	close(fz);
	close(fq);
//	printf("%d\n",*(marray + 10));
//	comp(a);
	return(1);
}
