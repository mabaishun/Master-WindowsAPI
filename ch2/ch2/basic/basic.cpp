/*
* 获取系统目录信息，并存储到文件中
*/

#include <Windows.h>

int main(int argc, char** argv)
{
	//文件句柄
	HANDLE hFile;
	DWORD dwWritten;

	//字符数组，用于存储系统目录给
	TCHAR szSystemDir[MAX_PATH];

	//获取系统目录
	GetSystemDirectory(szSystemDir, MAX_PATH);

	//创建文件systemroot.txt
	hFile = CreateFile("systemroot.txt", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	//判断文件是否创建成功
	if (hFile != INVALID_HANDLE_VALUE)
	{
		//将系统目录中系统信息写入文件
		if (!WriteFile(hFile, szSystemDir, lstrlen(szSystemDir), &dwWritten, NULL))
		{
			return GetLastError();
		}
	}

	//关闭文件，返回
	CloseHandle(hFile);
	return 0;
}


//程序输出文件，内容：
//C:\WINDOWS\system32