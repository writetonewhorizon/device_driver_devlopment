#include<iostream>
#include<cstdlib> 
using namespace std;
int main()
{
	int i=0;
	int *ptr= new (nothrow) int[10];
	if(ptr==0)
	cout << "error";
	for(i=0;i<10;i++)
	{	
		cout<< "enter the number" << endl;
		cin >> ptr[i];
		cout << "enterer no. is "<< *(ptr+i) << endl;
		cout << "address is "<< ptr+i << endl;
	}
	delete [] ptr;
	return 0;
}
