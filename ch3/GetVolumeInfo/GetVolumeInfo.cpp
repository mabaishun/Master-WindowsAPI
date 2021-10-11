// GetVolumeInfo.cpp ��������������ȡ����������

//ͷ�ļ�
#include <Windows.h>
#include <stdlib.h>
#include <stdio.h>

//Ԥ����
#define BUFSIZE 1024

//��������
BOOL GetDirverInfo(LPSTR szDrive);

//����������������GetDriverInfo����ȡ����������
int main(void)
{
	CHAR szLogicalDriveStrings[BUFSIZE];
	PCHAR szDrive;
	ZeroMemory(szLogicalDriveStrings, BUFSIZE);
	GetLogicalDriveStrings(BUFSIZE - 1, szLogicalDriveStrings);
	
	szDrive = (PCHAR)szLogicalDriveStrings;
	do
	{
		if (!GetDirverInfo(szDrive))
		{
			printf("\nGet Volume Infomation Error:%d\n", GetLastError());
		}
		szDrive += (lstrlen(szDrive) + 1);
	} while (*szDrive != '\x00');

	return 0;
}

/// @brief ��ȡ������������
/// @param szDrive ָ��Ҫ��ȡ���Ե��������ĸ�·�� �� C:\
/// @return �Ƿ�ɹ�
BOOL GetDirverInfo(LPSTR szDrive)
{
	UINT uDriveType;
	DWORD dwVolumeSerialNumber;
	DWORD dwMaximaximumComponentLength;
	DWORD dwFileStyleFlags;
	TCHAR szFileSystemNameBuffer[BUFSIZE];
	printf("\n%s\n", szDrive);
	//��ȡ����������
	uDriveType = GetDriveType(szDrive);

	//�ж�����
	switch (uDriveType)
	{
	case DRIVE_UNKNOWN:
		printf("�޷�ȷ�����������͡�");
		break;
	case DRIVE_NO_ROOT_DIR:
		printf("��·����Ч�����磬·����δװ��� ");
		break;
	case DRIVE_REMOVABLE:
		printf("��������һ�־��п��ƶ����ʵ����ͣ�������������������ƶ�Ӳ�̡�");
		break;
	case DRIVE_FIXED:
		printf("�������������޷�ɾ�������ͣ����磬�̶�Ӳ����������");
		break;
	case DRIVE_REMOTE:
		printf("����������Զ�̣����磩��������");
		break;
	case DRIVE_CDROM:
		printf("��������ΪCD-ROM��������");
		break;
	case DRIVE_RAMDISK:
		printf("����������һ��RAM���̡�");
		break;
	default:
		break;
	}

	if (!GetVolumeInformation(
		szDrive, NULL, 0,
		&dwVolumeSerialNumber,
		&dwMaximaximumComponentLength,
		&dwFileStyleFlags,
		szFileSystemNameBuffer,
		BUFSIZE
	))
	{
		return false;
	}
	printf("\n�����к�Ϊ:%u", dwVolumeSerialNumber);
	printf("\n����������Ϊ:%u", dwMaximaximumComponentLength);
	printf("\nϵͳ����:^s\n", szFileSystemNameBuffer);

	if (dwFileStyleFlags & FILE_SUPPORTS_REPARSE_POINTS)
	{
		printf("�ļ�ϵͳ��֧�־�װ��㡣\n");
	}
	if (dwFileStyleFlags & FILE_VOLUME_QUOTAS)
	{
		printf("�ļ�ϵͳ֧�ִ�����\n");
	}
	if (dwFileStyleFlags & FILE_CASE_SENSITIVE_SEARCH)
	{
		printf("�ļ�ϵͳ֧�����ִ�Сд���ļ�����\n");
	}

	//����ʹ����Щֵ����ȡ������Ϣ
	//
	//FILE_CASE_PRESERVED_NAMES
	//FILE_CASE_SENSITIVE_SEARCH
	//FILE_FILE_COMPRESSION
	//FILE_NAMED_STREAMS
	//FILE_PERSISTENT_ACLS
	//FILE_READ_ONLY_VOLUME
	//FILE_SUPPORTS_ENCRYPTION
	//FILE_SUPPORTS_OBJECT_IDS
	//FILE_SUPPORTS_REPARSE_POINTS
	//FILE_SUPPORTS_SPARSE_FILES
	//FILE_UNICODE_ON_DISK
	//FILE_VOLUME_IS_COMPRESSED
	//FILE_VOLUME_QUOTAS

	printf("...\n");
	return TRUE;
}