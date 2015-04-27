#include<iostream>
using namespace std;
int main()
{
	struct something
	{
		int value;
		float fly;
	};
	something some;
	something &rsomething = some;
	rsomething.value=10;
	cout << rsomething.value << endl;
	cout << some.value << endl;
	some.value=20;
	cout << some.value << endl;
	cout << rsomething.value << endl;
	

	int nvalue =5;
	int &rnref=nvalue;
	cout << nvalue << endl;
	nvalue++;
	cout << nvalue << endl;
	cout << rnref << endl;
	cout << &nvalue << endl;
	cout << &rnref << endl;


	return 0;
}
