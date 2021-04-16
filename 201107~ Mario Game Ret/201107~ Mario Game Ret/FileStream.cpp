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
	//������ �̹� ������ ������̶�� �ٽ� ���� ���ϰ� �Ѵ�.
	if (m_bOpen)
		return false;

	fopen_s(&m_pFile, pFileName, pMode);

	if (!m_pFile)
		return false;

	//���� Ŀ���� ���� �ڷ� �̵���Ų��
	fseek(m_pFile, 0, SEEK_END);

	//���� ũ�⸦ ���´�
	m_iFileSize = ftell(m_pFile);

	//Ŀ���� ���� ������ �ٽ� �̵������ش�.
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
	//������ �������� ������ �а� ���⸦ �� �� ����.
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

	//feof�� ����Ŀ���� ������ ���� �����ߴ����� üũ�Ѵ�.
	//���� �������� ������ ��� 0, �ƴϸ� 1 ����.
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
	//������ �������� ������ �а� ���⸦ �� �� ����.
	if (!m_bOpen)
		return;

	fwrite(pData, iSize, 1, m_pFile);
}

void CFileStream::WriteLine(void* pData, int iSize)
{
	//������ �������� ������ �а� ���⸦ �� �� ����.
	if (!m_bOpen)
		return;

	char* pBuffer = new char[iSize + 1];

	*(pBuffer + iSize) = '\n';

	fwrite(pBuffer, iSize + 1, 1, m_pFile);

	delete[] pBuffer;
}