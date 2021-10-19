/***********************************************************
* Mount.cpp卷挂载点操作
************************************************************/

//预编译声明
#define _WIN32_WINNT 0x0501
#include <Windows.h>
#include <stdio.h>
#include <tchar.h>
#define BUFSIZE MAX_PATH
#define FILESYSNAMEBUFSIZE MAX_PATH

/// @brief 列举挂载点
/// @param hPt 
/// @param PtBuf 
/// @param dwPtBufSize 
/// @param Buf 
/// @return 
BOOL ProcessVolumeMountPoint(HANDLE hPt, TCHAR* PtBuf, DWORD dwPtBufSize, TCHAR* Buf)
{
	BOOL bFlag;					//结果
	TCHAR Path[BUFSIZE];		//全路径
	TCHAR Target[BUFSIZE];		//挂载点设备

	printf("\t查找到的卷挂载点:\"%s\"\n", PtBuf);
	lstrcpy(Path, Buf);
	lstrcat(Path, PtBuf);

	//根据指定的挂载点获取相应的卷设备名
	bFlag = GetVolumeNameForVolumeMountPoint(Path, Target, BUFSIZE);
	if (!bFlag)
	{
		printf("\t尝试获取卷名 %s 失败\n", Path);
	}
	else
	{
		printf("\t卷挂载点：%s \n", Target);
	}

	bFlag = FindNextVolumeMountPoint(hPt, PtBuf, dwPtBufSize);
	return (bFlag);
}

/// @brief 判断卷类型，列举挂载点
/// @param hVol 
/// @param Buf 
/// @param iBufSize 
/// @return 
BOOL ProcessVolume(HANDLE hVol, TCHAR* Buf, DWORD iBufSize)
{
	BOOL bFlag;	//返回标志
	HANDLE hPt;	//卷句柄
	TCHAR PtBuf[BUFSIZE];	//挂载点路径
	DWORD dwSysFlags;		//文件系统标记
	TCHAR FileSysNameBuf[FILESYSNAMEBUFSIZE];
	printf("查找卷：\"%s\"\n", Buf);

	//是否为NTFS
	GetVolumeInformation(Buf, NULL, 0, NULL, NULL, &dwSysFlags, FileSysNameBuf, FILESYSNAMEBUFSIZE);
	if (!(dwSysFlags & FILE_SUPPORTS_REPARSE_POINTS))
	{
		printf("\t此文件系统不支持卷挂载点\n");
	}
	else
	{
		//本卷中的挂载点
		hPt = FindFirstVolumeMountPoint(
			Buf,		//卷的路径
			PtBuf,		//挂载点路径
			BUFSIZE
		);
		if (hPt == INVALID_HANDLE_VALUE)
		{
			printf("\t没有找到挂载点\n");
		}
		else
		{
			//处理挂载点
			bFlag = ProcessVolumeMountPoint(hPt, PtBuf, BUFSIZE, Buf);

			//循环
			while (bFlag)
				bFlag = ProcessVolumeMountPoint(hPt, PtBuf, BUFSIZE, Buf);
			//结束
			FindVolumeMountPointClose(hPt);
		}
	}
	//下一个
	bFlag = FindNextVolume(hVol, Buf, iBufSize);
	return bFlag;
}

/// @brief 获取挂载点
/// @param  
/// @return 
int GetMountPoint(void)
{
	TCHAR buf[BUFSIZE];		//卷标识符
	HANDLE hVol;			//卷句柄
	BOOL bFlag;				//结果标志

	printf("此计算机的挂载点信息:\n\n");

	//打开卷
	hVol = FindFirstVolume(buf, BUFSIZE);
	if (hVol == INVALID_HANDLE_VALUE)
	{
		printf("找不到卷\n");
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

/// @brief 使用方法
/// @param argv 
void Usage(PCHAR argv)
{
	printf("\n\n\t%s,在挂载点上挂载一个卷\n", argv);
	printf("\t例: \"mount D:\\\\mnt\\\\drives\\\\ E:\\\\\" \n");
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
		argv[2], //输入挂载点或目录
		Buf,	//输入卷名
		BUFSIZE
	);

	if (bFlag != TRUE)
	{
		printf("检索 %s 卷名失败",argv[2]);
		return (-2);
	}

	printf("%s 的卷名为 %s\n", argv[2], Buf);

	bFlag = SetVolumeMountPoint(
		argv[1],		//挂载点
		Buf				//需要挂载的卷
	);
	if (!bFlag)
	{
		printf("尝试在 %s 挂在 %s 失败,错误码：%d\n",argv[1],argv[2],GetLastError());
	}

	return bFlag;
}