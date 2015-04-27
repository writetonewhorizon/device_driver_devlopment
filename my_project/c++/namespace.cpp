#include<iostream>
using namespace std;
namespace foo
{
	int my_name(int nx,int ny)
	{
		return nx + ny;
	}
}
namespace go
{
	int my_name(int nx,int ny)
	{
		return nx - ny;
	}
}
int main()
{
	using namespace foo;
	cout << my_name(20,20) << endl;
	//or
	//cout << foo:: my_name(20,20) << endl;   
	// scope resolution operator is used in this case ie :: so
	cout << go:: my_name(20,20) << endl;
return 0;
}
