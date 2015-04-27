#include<iostream>
/*struct datestruct
{
	int nmonth;
	int nday;
	int nyear;
};*/
//defination of class
using namespace std;
class date
{
	int a;	//by default all are private
	int b;
	public:
		int m_nmonth;	//you can accessed its variable since these are publicaly available
		int m_nday;
		int m_nyear;
		void setdate(int nmonth, int nday, int nyear)
		{
			m_nmonth = nmonth;
			m_nday = nday;
			m_nyear = nyear;
		}
	protected:
		int c;
		int d;
	private:
		int f;
};
int main()
{
	date ctoday;    //declaration of class
	ctoday.m_nmonth=11;
	ctoday.m_nday=20;
	ctoday.m_nyear=1990;
	ctoday.setdate(11,20,2013);
//	ctoday.c=90; //private and protected class cannot be accessed
//	ctoday.b=19;
	cout << ctoday.m_nmonth << endl;
	cout << ctoday.m_nday << endl;
	cout << ctoday.m_nyear << endl;
	return 0;
}
