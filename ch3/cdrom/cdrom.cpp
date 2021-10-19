/**************************************************
* cdrom.cpp �жϹ������Ƿ��й���
* **************************************************/

//ͷ�ļ�
#include <Windows.h>
#include <stdio.h>
#include <tchar.h>

//Ԥ����
#define BUFSIZE	512

//���ܣ�Ӧ�ó����������������������������·�������ж��Ƿ�Ϊ�������Ƿ�������
//��������������·��,���� "D:\"
int main(int argc, char** argv)
{
	//�洢�ļ�ϵͳ�����
	CHAR szFileSystemNameBuffer[BUFSIZE];
	DWORD dwLastError;
	DWORD dwFileSystemFlags;

	//�ж��Ƿ���������ʱ����
	if (argc != 2)
	{
		printf("�������������ĸ�·��������: \"D:\\\"\n");
		return (-1);
	}

	//�ж�������������Ƿ�ΪCD\DVD ROM
	if (GetDriveType(argv[1]) != DRIVE_CDROM)
	{
		printf("������ %s ���� CD/DVD ROM��\n", argv[1]);
		return (-1);
	}

	//��ȡ����Ϣ
	if (!GetVolumeInformation(
		argv[1], NULL, 0,
		NULL, NULL,
		&dwFileSystemFlags,
		szFileSystemNameBuffer,
		BUFSIZE
	))
	{
		dwLastError = GetLastError();
		if (dwLastError == 21)
		{
			printf("�豸δ��������������!\n");
			return 0;
		}
		else
		{
			printf("GetVolumeInformation ���� %d\n", dwLastError);
			return 0;
		}
		printf("�����Ѿ����룬�ļ�ϵͳ��� %s\n", szFileSystemNameBuffer);

	}
	return 0;
}