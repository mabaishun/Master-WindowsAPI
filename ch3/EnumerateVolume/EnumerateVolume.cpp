//EnumerateVolume.cpp ��������������ȡ����������

#define _WIN32_WINNT 0x0501

//ͷ�ļ�
#include <Windows.h>
#include <stdio.h>

//Ԥ����
#define BUFSIZE MAX_PATH

//��������
BOOL GetDriverInfo(LPSTR szDrive);

//����������������GetDriverInfo��ȡ����������
int main(void)
{
	TCHAR buf[BUFSIZE];
	HANDLE hVol;	//��������
	BOOL bFlag;

	hVol = FindFirstVolume(buf, BUFSIZE);
	if (hVol == INVALID_HANDLE_VALUE)
	{
		printf(TEXT("û���ҵ���!\n"));
		return (-1);
	}

	GetDriverInfo(buf);

	while (FindNextVolume(hVol, buf, BUFSIZE))
	{
		GetDriverInfo(buf);
	}

	bFlag = FindVolumeClose(hVol);

	return bFlag;
}


BOOL GetDriverInfo(LPSTR szDrive)
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