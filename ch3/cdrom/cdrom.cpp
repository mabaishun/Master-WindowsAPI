/**************************************************
* cdrom.cpp 判断光驱中是否有光盘
* **************************************************/

//头文件
#include <Windows.h>
#include <stdio.h>
#include <tchar.h>

//预定义
#define BUFSIZE	512

//功能：应用程序主函数，根据输入的驱动器根路径参数判断是否为光驱，是否放入光盘
//参数：驱动器根路径,比如 "D:\"
int main(int argc, char** argv)
{
	//存储文件系统类别名
	CHAR szFileSystemNameBuffer[BUFSIZE];
	DWORD dwLastError;
	DWORD dwFileSystemFlags;

	//判断是否输入运行时参数
	if (argc != 2)
	{
		printf("请输入驱动器的根路径，比如: \"D:\\\"\n");
		return (-1);
	}

	//判断输入的驱动器是否为CD\DVD ROM
	if (GetDriveType(argv[1]) != DRIVE_CDROM)
	{
		printf("驱动器 %s 不是 CD/DVD ROM。\n", argv[1]);
		return (-1);
	}

	//获取卷信息
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
			printf("设备未就绪，请放入光盘!\n");
			return 0;
		}
		else
		{
			printf("GetVolumeInformation 错误 %d\n", dwLastError);
			return 0;
		}
		printf("光盘已经放入，文件系统类别 %s\n", szFileSystemNameBuffer);

	}
	return 0;
}