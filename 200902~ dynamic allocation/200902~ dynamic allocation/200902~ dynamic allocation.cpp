#include <iostream>

using namespace std;

int main()
{
	int* pNumber = new int;

	*pNumber = 100;
	
	delete pNumber;
	
	int* pArray = new int[2];

	pArray[1] = 300;

	delete[] pArray;
	
	return 0;
}