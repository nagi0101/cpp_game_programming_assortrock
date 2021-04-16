#include "FileStream.h"

CFileStream::CFileStream() :
	m_pFile(NULL),
	m_iFileSize(0),
	m_bOpen(false)
{
}

CFileStream::~CFileStream()
{
	Close();
}

bool CFileStream::Open(const char* pFileName, const char* pMode)
{
	//파일이 이미 열려서 사용중이라면 다시 열지 못하게 한다.
	if (m_bOpen)
		return false;

	fopen_s(&m_pFile, pFileName, pMode);

	if (!m_pFile)
		return false;

	//파일 커서를 가장 뒤로 이동시킨다
	fseek(m_pFile, 0, SEEK_END);

	//파일 크기를 얻어온다
	m_iFileSize = ftell(m_pFile);

	//커서를 가장 앞으로 다시 이동시켜준다.
	fseek(m_pFile, 0, SEEK_SET);

	m_bOpen = true;

	return true;
}

bool CFileStream::Close()
{
	if (!m_bOpen)
		return false;

	m_bOpen = false;

	fclose(m_pFile);
	m_pFile = NULL;
	m_iFileSize = 0;

	return true;
}

void CFileStream::Read(void* pData, int iSize)
{
	//파일이 열려있지 않으면 읽고 쓰기를 할 수 없다.
	if (!m_bOpen)
		return;

	fread(pData, iSize, 1, m_pFile);
}

void CFileStream::ReadLine(void* pData, int& iSize)
{
	if (!m_bOpen)
		return;

	char cData;
	char* pChangeData = (char*)pData;
	iSize = 0;

	//feof는 파일커서가 파일의 끝에 도달했는지를 체크한다.
	//끝에 도달하지 못했을 경우 0, 아니면 1 리턴.
	while (feof(m_pFile) == 0)
	{
		fread(&cData, 1, 1, m_pFile);

		if (cData == '\n')
			break;

		pChangeData[iSize] = cData;
		++iSize;
	}
}

void CFileStream::Write(void* pData, int iSize)
{
	//파일이 열려있지 않으면 읽고 쓰기를 할 수 없다.
	if (!m_bOpen)
		return;

	fwrite(pData, iSize, 1, m_pFile);
}

void CFileStream::WriteLine(void* pData, int iSize)
{
	//파일이 열려있지 않으면 읽고 쓰기를 할 수 없다.
	if (!m_bOpen)
		return;

	char* pBuffer = new char[iSize + 1];

	*(pBuffer + iSize) = '\n';

	fwrite(pBuffer, iSize + 1, 1, m_pFile);

	delete[] pBuffer;
}