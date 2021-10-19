/********************************************************************************
* diskspace.cpp 获取磁盘空间信息
* *******************************************************************************/

/*头文件*/
#include <Windows.h>
#include <stdio.h>

/// @brief 根据输入的驱动器，获取磁盘总容量、空闲空间、簇数量等磁盘信息
/// @param pszDrive 驱动器根路径，比如"D:\"
/// @return 
BOOL GetDiskSpaceInfo(LPCSTR pszDrive)
{
	DWORD64 qwFreeBytesToCaller;//可获得的空闲空间
	DWORD64 qwTotalBytes;		//总容量
	DWORD64 qwFreeBytes;		//空闲空间

	DWORD dwSectPerClust;	//空闲的簇数量
	DWORD dwBytesPerSect;	//总簇数量
	DWORD dwFreeClusters;	//每簇的扇区数
	DWORD dwTotalClusters;	//没扇区的容量(字节)

	BOOL bResult;//执行结果

	//使用GetDiskFreeSpaceEx获取磁盘信息并打印

	/*
	* BOOL GetDiskFreeSpaceEx(
    * LPCTSTR lpDirectoryName,//输入参数，指向所要获取磁盘空间信息的磁盘分区根路径字符串
    * PULARGE_INTEGER lpFreeBytesAvailableToCaller,//输出参数，指针，指向用于存储可获得的总字节数量的变量
    * PULARGE_INTEGER lpTotalNumberOfBytes,//输出参数，指针，指向存储磁盘空间总字节数据的变量
    * PULARGE_INTEGER lpTotalNumberOfFreeBytes//输出参数，指针，指向存储磁盘空闲空间总字节的变量
    * );
	*/
	bResult = GetDiskFreeSpaceEx(pszDrive,
		(PULARGE_INTEGER)&qwFreeBytesToCaller,
		(PULARGE_INTEGER)&qwTotalBytes,
		(PULARGE_INTEGER)&qwFreeBytes
		);
	if (bResult)
	{
		printf("使用GetDiskFreeSpaceEx 获取磁盘空间信息\n");
		printf("可获得的空闲空间(字节):\t\t%I64d\n", qwFreeBytesToCaller);
		printf("空闲空间(字节): \t\t%I64d\n", qwFreeBytes);
		printf("磁盘总容量(字节):\t\t%I64d\n", qwTotalBytes);
	}

	//使用GetDiskFreeSpace获取磁盘信息并打印结果
	bResult = GetDiskFreeSpace(
		pszDrive,
		&dwSectPerClust,
		&dwBytesPerSect,
		&dwFreeClusters,
		&dwTotalClusters
	);
	if (bResult)
	{
		printf("\n使用GetDiskFreeSpace获取磁盘空间信息\n");
		printf("空闲的簇数量:\t\t%d\n", dwFreeClusters);
		printf("总簇数量:\t\t%d\n", dwTotalClusters);
		printf("每簇的扇区数量:\t\t%d\n", dwSectPerClust);
		printf("每扇区的容量(字节):\t\t%d\n", dwBytesPerSect);
		printf("空闲空间(字节):\t\t%I64d\n",(DWORD64)dwFreeClusters * (DWORD64)dwSectPerClust * (DWORD64)dwBytesPerSect);
		printf("磁盘总容量(字节):\t\t%I64d\n", (DWORD64)dwTotalClusters * (DWORD64)dwSectPerClust * (DWORD64)dwBytesPerSect);
	}
	return bResult;
}

// 应用主程序，根据输入的参数调用GetDiskSpaceInfo 函数获取磁盘空间信息
// 参数：驱动器根路径,比如 "D:\"
int main(int argc, char** argv)
{
	GetDiskSpaceInfo(argv[1]);
}