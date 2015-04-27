unsigned char indx(unsigned char x,int fm,int mcount)
{
	lseek(fm,SEEK_SET,0);
	int j;
	unsigned char marray[mcount],a;
	read(fm,marray,mcount);
	for(j = 0;j < mcount;j++)
	{
		if(x == marray[j])
		{
			a = j;
			break;
		}
		else
			continue;
	}
	return a;
}
