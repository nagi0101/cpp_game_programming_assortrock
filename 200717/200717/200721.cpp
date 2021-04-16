#include <iostream>

using namespace std;

int main()
{
	int iNumber = 100;
	int* pNum = &iNumber;

	cout << sizeof(int*) << endl;
	cout << sizeof(char*) << endl;
	cout << sizeof(double*) << endl;

	cout << "iNumber address : " << &iNumber << endl;
	cout << "pNum value : " << pNum << endl;
	cout << "pNum address : " << &pNum << endl;

	char str[8] = "abcdefg";
	str[0] = 'b';

	cout << str << endl;



	return 0;
}