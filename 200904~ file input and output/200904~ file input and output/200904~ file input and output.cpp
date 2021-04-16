#include <iostream>

using namespace std;

int main()
{
	FILE* pFile = NULL;
	/*
	fopen_s(&pFile, "hot.txt", "wt");

	if (pFile != NULL)
	{
		const char* pText = "abcd";
		fwrite(pText, 1, 4, pFile);

		fclose(pFile);

		cout << "파일 만들기 성공!" << endl;
	}
	*/

	fopen_s(&pFile, "hot.txt", "rt");

	if (pFile)
	{
		char strText[5] = {};

		fread(strText, 1, 4, pFile);

		cout << strText << endl;

		fclose(pFile);
	}

	return 0;
}