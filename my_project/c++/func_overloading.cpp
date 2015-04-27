#include<iostream>
using namespace std;
double add(double dx,double dy)
{
	cout << dx << endl;
	cout << dy << endl;
	return dx + dy;
}
int add(int nx,char ny)
{
	cout << nx << endl;
	cout << ny << endl;
	return nx ;
}
int add(int cx,int cy, int cz)	//default value concept ie actual value will be given to formal argumenyt
{
	cout << cx << endl;
	cout << cy << endl;
	cout << cz << endl;
	return cx - cy - cz;
}

int main()
{
	cout << add(4,'d') << endl;
	cout << add(3.8,6.2) << endl;
	cout << add(67,1,2) << endl;
return 0;
}
