char *gxxx()
{
	static char xxx[1024];
	return xxx;
}
int main()
{
	char *g="string";
	strcpy(gxxx(),g);
	g = gxxx();
	strcpy(g,"oldstring");
	printf("The string is : %s",gxxx());
	getchar();
return 0;
}
