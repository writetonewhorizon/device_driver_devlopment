char function(unsigned char x,int fm,int mcount)
{
	char marray[mcount],ch;
	int j;
	lseek(fm,SEEK_SET,0);
	read(fm,marray,mcount);
	for(j = 0;j < mcount ;j++)
	{
		if(x == j)
		{
			ch = marray[j];
			break;
		}
		else
			continue;
	}
	return ch;
}
