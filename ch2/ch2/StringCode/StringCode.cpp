//头文件
#include <Windows.h>

/// @brief Windows应用程序入口
/// @param hInstance 数据类型HINSTANCE，此参数表示应用程序本次运行实例的句柄
/// @param hPrevInstance 数据类型HINSTANCE，表示应用程序之前运行实例的句柄，但在实际应用中，此参数始终为NULL
/// @param lpCmdLine 运行时参数，例如在cmd命令行中运行"start.exe command argumeng",那么此参数将指向字符串"command argumeng",类型 LPSTR 是Windows API中常用的字符串类型 
/// @param nCmdShow 表示应用程序窗口（如果有）的显示状态。
/// @return 
int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//定义LPWSTR类型的宽字符串
	LPWSTR szUnicode = L"This is a Unicode String";

	//定义LPSTR类型的窄字符串
	LPSTR szMutliByte = "This is a Unicode String";

	//定义LPTSTR类型的自使用字符串
	LPTSTR szString = TEXT("This string is Unicode or not depends on the option");

	//使用W版本的API函数，以宽字符串为参数
	MessageBoxW(NULL, szUnicode, L"<字符编码1>", MB_OK);

	//使用A版本的API函数，以窄字符串为参数
	MessageBoxA(NULL, szMutliByte, "<字符编码2>", MB_OK);

	//根据编译条件自动选择A版本或W版本的API函数，采用相适应的字符串类型为参数
	MessageBox(NULL, szString, TEXT("<字符编码3>"), MB_OK);

	return 0;

}