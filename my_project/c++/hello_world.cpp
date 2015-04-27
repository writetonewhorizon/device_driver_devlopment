#include<iostream>
#include<string>
#include<cmath> 
using namespace std;
int main()
{
	int sum=0;
	int a;
	char b;
	float c;
	short int d;
	double e;
	long double f;
	bool g;
	wchar_t h;
	string my_name="dharmender sharma";
	cout << " my_ name is " << my_name << endl;
	cout << " enter the first number " << endl;
	cin >> a;
	cout << "enter the 2nd number  " << endl;
	cin >> d;
	sum=a+d;
	cout << "sum is " << sum << endl;
	cout << "do you want to calculate size of data type(y or n)" << endl;
	char name=0;
	cin >> name;
	switch(name)
	{
		case'y':
			cout << " \nsizeof(int) " <<sizeof(a);
			cout << " \nsizeof(char) " << sizeof(b);
			cout << " \nsizeof(float) " << sizeof(c);
			cout << " \nsizeof(short int) " << sizeof(d);
			cout << " \nsizeof(double) " << sizeof(e);
			cout << " \nsizeof(long double) " << sizeof(f);
			cout << " \nsizeof(bool) " << sizeof(g);
			cout << " \nsizeof(wchar_t) " << sizeof(h) << endl;
			break;
		case'n':
			cout << "\nok good bye";
			break;
	}
	sum = sqrt(a);
	cout << sum ;
	cout << "squre of " << a << " is " << sum << endl;
	return 0;
}

