// GetVolumeInfo.cpp 编译驱动器并获取驱动器属性

//头文件
#include <Windows.h>
#include <stdlib.h>
#include <stdio.h>

//预定义
#define BUFSIZE 1024

//函数声明
BOOL GetDirverInfo(LPSTR szDrive);

//遍历驱动器并调用GetDriverInfo，获取驱动器属性
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

/// @brief 获取驱动器得属性
/// @param szDrive 指明要获取属性的驱动器的根路径 如 C:\
/// @return 是否成功
BOOL GetDirverInfo(LPSTR szDrive)
{
	UINT uDriveType;
	DWORD dwVolumeSerialNumber;
	DWORD dwMaximaximumComponentLength;
	DWORD dwFileStyleFlags;
	TCHAR szFileSystemNameBuffer[BUFSIZE];
	printf("\n%s\n", szDrive);
	//获取驱动器类型
	uDriveType = GetDriveType(szDrive);

	//判断类型
	switch (uDriveType)
	{
	case DRIVE_UNKNOWN:
		printf("无法确定驱动器类型。");
		break;
	case DRIVE_NO_ROOT_DIR:
		printf("根路径无效，例如，路径上未装入卷。 ");
		break;
	case DRIVE_REMOVABLE:
		printf("驱动器是一种具有可移动介质的类型，例如软盘驱动器或可移动硬盘。");
		break;
	case DRIVE_FIXED:
		printf("该驱动器属于无法删除的类型，例如，固定硬盘驱动器。");
		break;
	case DRIVE_REMOTE:
		printf("该驱动器是远程（网络）驱动器。");
		break;
	case DRIVE_CDROM:
		printf("该驱动器为CD-ROM驱动器。");
		break;
	case DRIVE_RAMDISK:
		printf("该驱动器是一个RAM磁盘。");
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
	printf("\n卷序列号为:%u", dwVolumeSerialNumber);
	printf("\n最大组件长度为:%u", dwMaximaximumComponentLength);
	printf("\n系统类型:^s\n", szFileSystemNameBuffer);

	if (dwFileStyleFlags & FILE_SUPPORTS_REPARSE_POINTS)
	{
		printf("文件系统不支持卷装入点。\n");
	}
	if (dwFileStyleFlags & FILE_VOLUME_QUOTAS)
	{
		printf("文件系统支持磁盘配额。\n");
	}
	if (dwFileStyleFlags & FILE_CASE_SENSITIVE_SEARCH)
	{
		printf("文件系统支持区分大小写的文件名。\n");
	}

	//可以使用这些值来获取更多信息
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