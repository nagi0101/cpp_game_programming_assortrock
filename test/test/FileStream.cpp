#include "FileStream.h"

CFileStream::CFileStream() :m_pFile(NULL), m_iFileSize(0), m_bOpen(false)
{
}

CFileStream::~CFileStream()
{
	Close();
}

bool CFileStream::Open(const char* pFileName, const char* pMode)
{
	//������ �̹� ������ ����ϰ� �ִٸ� �ٽ� ���� ���ϰ� �Ѵ�.
	if (m_bOpen)
		return false;

	fopen_s(&m_pFile, pFileName, pMode);

	if (!m_pFile)
		return false;

	//���� Ŀ���� ���� �ڷ� �̵���Ų��
	//fseek �Լ��� ���� Ŀ���� ���ϴ� ��ġ�� �̵���ų �� �ִ� �Լ��̴�.
	//3��° ���ڴ� 3 ������ �ִ�.
	//SEEK_SET : ������ ���� ó���� �ǹ��Ѵ�.
	//SEEK_CUR : ���� ����Ű�� �ִ� ���� Ŀ���� ��ġ�� �ǹ��Ѵ�.
	//SEEK_END : ������ ���� �������� �ǹ��Ѵ�.
	//2��° ������ offset ���� ����Ʈ �� ��ŭ 3��° ���ڿ��� ������
	//��ġ�κ��� �̵��ϰ� �ȴ�.
	fseek(m_pFile, 0, SEEK_END);

	//ftell : ���� Ŀ���� ��ġ�� ������ �Լ��̴�. ������ ���� Ŀ����
	//���� ���������� �̵����ױ� ������ ftell�� �̿��ؼ� ���� Ŀ���� ��ġ��
	//������ �� ���� ũ��� �ȴ�.
	m_iFileSize = ftell(m_pFile);

	fseek(m_pFile, 0, SEEK_SET);

	m_bOpen = true;

	return true;
}

bool CFileStream::Close()
{
	if (!m_bOpen)
		return false;

	m_bOpen = false;

	//SAFE_DELETE(m_pFile);
	fclose(m_pFile); //���⼭ ����
	m_pFile = NULL;
	m_iFileSize = 0;

	return false;
}

void CFileStream::Read(void* pData, int iSize)
{
	//������ �������� ���� �����̸� �а��� �Ұ���
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
	iSize = 0;;

	//feof�� ���� Ŀ���� ������ ���� �����ߴ��� üũ�Ѵ�.
	//������ ���� �������� �ʾ��� ��� 0�� �����ϰ�
	//���� ��� 0�� �ƴ� ���� �����Ѵ�.
	while (feof(m_pFile) == 0)
	{
		fread(&cData, 1, 1, m_pFile);
		if (cData == '\n')
			return;

		pChangeData[iSize] = cData;
		++iSize;
	}
}

void CFileStream::Write(void* pData, int iSize)
{
	if (!m_bOpen)
		return;

	fwrite(pData, iSize, 1, m_pFile);
}