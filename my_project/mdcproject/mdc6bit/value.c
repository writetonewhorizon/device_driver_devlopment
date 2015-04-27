char value(unsigned char x,int fm,int mcount)
{
	char marray[mcount],ret;
	int j;
	lseek(fm,SEEK_SET,0);
	read(fm,marray,mcount);
	marray[mcount] = 0;
	for(j = 0;j < mcount;j++)
	{
		if(x == j)
		{
			ret = marray[j];
			break;
		}
		else
			continue;
	}
	return ret;

}
