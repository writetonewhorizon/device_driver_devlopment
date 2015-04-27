#include<iostream>
const int size=7;
int array[size]={1,2,3,4,5};
using namespace std;
int main()
{
	int i=0;
	char arr[size]="dharam";
	char *ptr=arr;
	cout << "derefrance value of array is " << *array << endl;
	cout << *(array+1)<<endl;
	cout << *(array+2)<<endl;
	cout << *(array+3)<<endl;
	cout << *(array+4)<<endl;
	cout << array[0] << endl;
	cout << array[1] << endl;
	cout << array[2] << endl;
	cout << array[3] << endl;
	cout << array[4] << endl;
		cout << array << endl;
		cout << &array << endl;
		cout << *array << endl;
		cout << *&array << endl;
	cout << "sizeof(array) is " << sizeof(array) << endl;
	cout << "sizeof(arr) is " << sizeof(arr) << endl;
	cout << "sizeof(ptr) is " << sizeof(ptr) << endl;
	for(i=0;i<size;i++)
	{
		int total=0;
		total=array[0]+array[1]+array[2]+array[3]+array[4];
		cout << "tatal sum of elements of arrays is " << total << endl;
		cout << *ptr << endl;
		cout << &ptr << endl;
		cout << ptr << endl;
		ptr++;
	}
	/*cout << *ptr++ << endl;
	cout << *++ptr << endl;
	cout << *(ptr++) << endl;
	cout << (*ptr)++ << endl;*/
	return 0;
}
