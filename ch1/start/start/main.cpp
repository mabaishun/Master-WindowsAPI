//头文件
#include <Windows.h>

//链接时使用User32.lib
#pragma comment(lib,"User32.lib")

/// @brief Windows应用程序入口
/// @param hInstance 数据类型HINSTANCE，此参数表示应用程序本次运行实例的句柄
/// @param hPrevInstance 数据类型HINSTANCE，表示应用程序之前运行实例的句柄，但在实际应用中，此参数始终为NULL
/// @param lpCmdLine 运行时参数，例如在cmd命令行中运行"start.exe command argumeng",那么此参数将指向字符串"command argumeng",类型 LPSTR 是Windows API中常用的字符串类型 
/// @param nCmdShow 表示应用程序窗口（如果有）的显示状态。
/// @return 
int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//调用API函数 MessageBox
	MessageBox(NULL, TEXT("开始学习Windows编程，并做学习笔记"), TEXT("消息对话框"), MB_OK);
	return 0;
}