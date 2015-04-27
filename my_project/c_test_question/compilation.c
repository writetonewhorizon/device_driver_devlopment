/* gcc flags(-E,-S,-C,-save-temps) sourcefilename -o outputfilename*/
#include<stdio.h> 
int main()
{
	printf("preprocessing(-E)->compilation(-C)->assambly(-S)->linking\n");
	printf("use -> readelf (objdump),nm,size,command to fetch the information of a executable file\n"); 
	return 0;
}
