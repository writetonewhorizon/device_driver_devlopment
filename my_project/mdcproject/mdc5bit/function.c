unsigned char fun(unsigned char x,int fm ,int mcount)
{
	int j ;
	unsigned char a;
	char marray[mcount];
	lseek(fm,SEEK_SET,0);
	read(fm,marray,mcount);
	for(j = 0; j < mcount;j++)
	{
		if(x == marray[j])
		{
			a = j;
			break;
		}
		else
			continue;
	}
	printf("return a is %d\n",a);
	return a;

}
