/*
* ��ȡϵͳĿ¼��Ϣ�����洢���ļ���
*/

#include <Windows.h>

int main(int argc, char** argv)
{
	//�ļ����
	HANDLE hFile;
	DWORD dwWritten;

	//�ַ����飬���ڴ洢ϵͳĿ¼��
	TCHAR szSystemDir[MAX_PATH];

	//��ȡϵͳĿ¼
	GetSystemDirectory(szSystemDir, MAX_PATH);

	//�����ļ�systemroot.txt
	hFile = CreateFile("systemroot.txt", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	//�ж��ļ��Ƿ񴴽��ɹ�
	if (hFile != INVALID_HANDLE_VALUE)
	{
		//��ϵͳĿ¼��ϵͳ��Ϣд���ļ�
		if (!WriteFile(hFile, szSystemDir, lstrlen(szSystemDir), &dwWritten, NULL))
		{
			return GetLastError();
		}
	}

	//�ر��ļ�������
	CloseHandle(hFile);
	return 0;
}


//��������ļ������ݣ�
//C:\WINDOWS\system32