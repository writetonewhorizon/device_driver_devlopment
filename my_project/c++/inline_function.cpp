#include<iostream>
using namespace std;
inline int min(int nx, int ny)
{
	return nx > ny ? ny : nx;
}
int main()
{
	cout << min(5,6) << endl;
	cout << min(25,16) << endl;
	return 0;
}
