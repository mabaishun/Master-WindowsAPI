/*头文件*/
#include <Windows.h>
#include <stdio.h>

/// @brief Windows应用程序入口
/// @param hInstance 数据类型HINSTANCE，此参数表示应用程序本次运行实例的句柄
/// @param hPrevInstance 数据类型HINSTANCE，表示应用程序之前运行实例的句柄，但在实际应用中，此参数始终为NULL
/// @param lpCmdLine 运行时参数，例如在cmd命令行中运行"start.exe command argumeng",那么此参数将指向字符串"command argumeng",类型 LPSTR 是Windows API中常用的字符串类型 
/// @param nCmdShow 表示应用程序窗口（如果有）的显示状态。
/// @return 
int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//定义字符串
	LPSTR szString = "Windows data type ,string";

	//定义字符数组
	CHAR lpString[120];	//要大于szString的长度

	//定义 DWORD 类型的数据
	DWORD dwMax = 0XFFFFFFFF;
	DWORD dwOne = 0X00000001;

	//定义 INT 类型的数据
	INT iMax = 0XFFFFFFFF;
	INT iOne = 0X00000001;

	//显示字符串
	MessageBox(NULL, szString, "LPSTR", MB_OK);

	//复制内容，将字符串复制到数组中(包括NULL结束符)
	CopyMemory(lpString, szString, lstrlen(szString) + 1);

	//显示复制的字符串
	MessageBox(NULL, lpString, "CHAR[]", MB_OK);

	//比较DWORD并显示结果
	if (dwMax > dwOne)
	{
		MessageBox(NULL, "DWORD 类型的数据 0XFFFFFFFF > 0X00000001", "DWORD", MB_OK);
	}

	//比较INT并显示结果
	if (iMax < iOne)
	{
		MessageBox(NULL, "INT 类型的数据 0XFFFFFFFF > 0X00000001", "INT", MB_OK);
	}

	return 0;
}