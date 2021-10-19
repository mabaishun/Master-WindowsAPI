/***********************************************************
* Mount.cpp����ص����
************************************************************/

//Ԥ��������
#define _WIN32_WINNT 0x0501
#include <Windows.h>
#include <stdio.h>
#include <tchar.h>
#define BUFSIZE MAX_PATH
#define FILESYSNAMEBUFSIZE MAX_PATH

/// @brief �оٹ��ص�
/// @param hPt 
/// @param PtBuf 
/// @param dwPtBufSize 
/// @param Buf 
/// @return 
BOOL ProcessVolumeMountPoint(HANDLE hPt, TCHAR* PtBuf, DWORD dwPtBufSize, TCHAR* Buf)
{
	BOOL bFlag;					//���
	TCHAR Path[BUFSIZE];		//ȫ·��
	TCHAR Target[BUFSIZE];		//���ص��豸

	printf("\t���ҵ��ľ���ص�:\"%s\"\n", PtBuf);
	lstrcpy(Path, Buf);
	lstrcat(Path, PtBuf);

	//����ָ���Ĺ��ص��ȡ��Ӧ�ľ��豸��
	bFlag = GetVolumeNameForVolumeMountPoint(Path, Target, BUFSIZE);
	if (!bFlag)
	{
		printf("\t���Ի�ȡ���� %s ʧ��\n", Path);
	}
	else
	{
		printf("\t����ص㣺%s \n", Target);
	}

	bFlag = FindNextVolumeMountPoint(hPt, PtBuf, dwPtBufSize);
	return (bFlag);
}

/// @brief �жϾ����ͣ��оٹ��ص�
/// @param hVol 
/// @param Buf 
/// @param iBufSize 
/// @return 
BOOL ProcessVolume(HANDLE hVol, TCHAR* Buf, DWORD iBufSize)
{
	BOOL bFlag;	//���ر�־
	HANDLE hPt;	//����
	TCHAR PtBuf[BUFSIZE];	//���ص�·��
	DWORD dwSysFlags;		//�ļ�ϵͳ���
	TCHAR FileSysNameBuf[FILESYSNAMEBUFSIZE];
	printf("���Ҿ�\"%s\"\n", Buf);

	//�Ƿ�ΪNTFS
	GetVolumeInformation(Buf, NULL, 0, NULL, NULL, &dwSysFlags, FileSysNameBuf, FILESYSNAMEBUFSIZE);
	if (!(dwSysFlags & FILE_SUPPORTS_REPARSE_POINTS))
	{
		printf("\t���ļ�ϵͳ��֧�־���ص�\n");
	}
	else
	{
		//�����еĹ��ص�
		hPt = FindFirstVolumeMountPoint(
			Buf,		//���·��
			PtBuf,		//���ص�·��
			BUFSIZE
		);
		if (hPt == INVALID_HANDLE_VALUE)
		{
			printf("\tû���ҵ����ص�\n");
		}
		else
		{
			//������ص�
			bFlag = ProcessVolumeMountPoint(hPt, PtBuf, BUFSIZE, Buf);

			//ѭ��
			while (bFlag)
				bFlag = ProcessVolumeMountPoint(hPt, PtBuf, BUFSIZE, Buf);
			//����
			FindVolumeMountPointClose(hPt);
		}
	}
	//��һ��
	bFlag = FindNextVolume(hVol, Buf, iBufSize);
	return bFlag;
}

/// @brief ��ȡ���ص�
/// @param  
/// @return 
int GetMountPoint(void)
{
	TCHAR buf[BUFSIZE];		//���ʶ��
	HANDLE hVol;			//����
	BOOL bFlag;				//�����־

	printf("�˼�����Ĺ��ص���Ϣ:\n\n");

	//�򿪾�
	hVol = FindFirstVolume(buf, BUFSIZE);
	if (hVol == INVALID_HANDLE_VALUE)
	{
		printf("�Ҳ�����\n");
		return (-1);
	}
	
	bFlag = ProcessVolume(hVol, buf, BUFSIZE);
	while (bFlag)
	{
		bFlag = ProcessVolume(hVol, buf, BUFSIZE);
	}
	bFlag = FindVolumeClose(hVol);
	return (bFlag);
}

/// @brief ʹ�÷���
/// @param argv 
void Usage(PCHAR argv)
{
	printf("\n\n\t%s,�ڹ��ص��Ϲ���һ����\n", argv);
	printf("\t��: \"mount D:\\\\mnt\\\\drives\\\\ E:\\\\\" \n");
}


int main(int argc,char **argv)
{
	BOOL bFlag;
	CHAR Buf[BUFSIZE];
	if (argc != 3)
	{
		GetMountPoint();
		Usage(argv[0]);
		return (-1);
	}

	bFlag = GetVolumeNameForVolumeMountPoint(
		argv[2], //������ص��Ŀ¼
		Buf,	//�������
		BUFSIZE
	);

	if (bFlag != TRUE)
	{
		printf("���� %s ����ʧ��",argv[2]);
		return (-2);
	}

	printf("%s �ľ���Ϊ %s\n", argv[2], Buf);

	bFlag = SetVolumeMountPoint(
		argv[1],		//���ص�
		Buf				//��Ҫ���صľ�
	);
	if (!bFlag)
	{
		printf("������ %s ���� %s ʧ��,�����룺%d\n",argv[1],argv[2],GetLastError());
	}

	return bFlag;
}