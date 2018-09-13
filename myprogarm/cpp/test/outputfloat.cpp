//test the format the float data.
#define UNIT_ONE (1)

#include<iostream.h>
#include<iomanip.h>

int main()
{
	float a = 3;
	float b = 33.444;
	int c = 7;
	int d = 1, scale;
	
	cout << "a = " << a << endl;
	cout << "b = " << b << endl;
	cout << "c = " << c << endl;
	cout.precision(4);
	scale = UNIT_ONE << 0;
	cout << "a = " << a << endl;
	cout << "b = " << b << "%" << endl;
	cout << "c = " << c << endl;
	cout << "scale = " << scale << endl;
	cout.precision(6);
	scale = UNIT_ONE << 8;
	cout << "a = " << a << endl;
	cout << "b = " << b << "%" << endl;
	cout << "c = " << c << endl;
	cout << "scale = " << scale << endl;
	return 0;
	
}
