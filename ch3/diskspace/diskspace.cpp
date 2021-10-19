/********************************************************************************
* diskspace.cpp ��ȡ���̿ռ���Ϣ
* *******************************************************************************/

/*ͷ�ļ�*/
#include <Windows.h>
#include <stdio.h>

/// @brief �������������������ȡ���������������пռ䡢�������ȴ�����Ϣ
/// @param pszDrive ��������·��������"D:\"
/// @return 
BOOL GetDiskSpaceInfo(LPCSTR pszDrive)
{
	DWORD64 qwFreeBytesToCaller;//�ɻ�õĿ��пռ�
	DWORD64 qwTotalBytes;		//������
	DWORD64 qwFreeBytes;		//���пռ�

	DWORD dwSectPerClust;	//���еĴ�����
	DWORD dwBytesPerSect;	//�ܴ�����
	DWORD dwFreeClusters;	//ÿ�ص�������
	DWORD dwTotalClusters;	//û����������(�ֽ�)

	BOOL bResult;//ִ�н��

	//ʹ��GetDiskFreeSpaceEx��ȡ������Ϣ����ӡ

	/*
	* BOOL GetDiskFreeSpaceEx(
    * LPCTSTR lpDirectoryName,//���������ָ����Ҫ��ȡ���̿ռ���Ϣ�Ĵ��̷�����·���ַ���
    * PULARGE_INTEGER lpFreeBytesAvailableToCaller,//���������ָ�룬ָ�����ڴ洢�ɻ�õ����ֽ������ı���
    * PULARGE_INTEGER lpTotalNumberOfBytes,//���������ָ�룬ָ��洢���̿ռ����ֽ����ݵı���
    * PULARGE_INTEGER lpTotalNumberOfFreeBytes//���������ָ�룬ָ��洢���̿��пռ����ֽڵı���
    * );
	*/
	bResult = GetDiskFreeSpaceEx(pszDrive,
		(PULARGE_INTEGER)&qwFreeBytesToCaller,
		(PULARGE_INTEGER)&qwTotalBytes,
		(PULARGE_INTEGER)&qwFreeBytes
		);
	if (bResult)
	{
		printf("ʹ��GetDiskFreeSpaceEx ��ȡ���̿ռ���Ϣ\n");
		printf("�ɻ�õĿ��пռ�(�ֽ�):\t\t%I64d\n", qwFreeBytesToCaller);
		printf("���пռ�(�ֽ�): \t\t%I64d\n", qwFreeBytes);
		printf("����������(�ֽ�):\t\t%I64d\n", qwTotalBytes);
	}

	//ʹ��GetDiskFreeSpace��ȡ������Ϣ����ӡ���
	bResult = GetDiskFreeSpace(
		pszDrive,
		&dwSectPerClust,
		&dwBytesPerSect,
		&dwFreeClusters,
		&dwTotalClusters
	);
	if (bResult)
	{
		printf("\nʹ��GetDiskFreeSpace��ȡ���̿ռ���Ϣ\n");
		printf("���еĴ�����:\t\t%d\n", dwFreeClusters);
		printf("�ܴ�����:\t\t%d\n", dwTotalClusters);
		printf("ÿ�ص���������:\t\t%d\n", dwSectPerClust);
		printf("ÿ����������(�ֽ�):\t\t%d\n", dwBytesPerSect);
		printf("���пռ�(�ֽ�):\t\t%I64d\n",(DWORD64)dwFreeClusters * (DWORD64)dwSectPerClust * (DWORD64)dwBytesPerSect);
		printf("����������(�ֽ�):\t\t%I64d\n", (DWORD64)dwTotalClusters * (DWORD64)dwSectPerClust * (DWORD64)dwBytesPerSect);
	}
	return bResult;
}

// Ӧ�������򣬸�������Ĳ�������GetDiskSpaceInfo ������ȡ���̿ռ���Ϣ
// ��������������·��,���� "D:\"
int main(int argc, char** argv)
{
	GetDiskSpaceInfo(argv[1]);
}