//ͷ�ļ�
#include <Windows.h>

/// @brief WindowsӦ�ó������
/// @param hInstance ��������HINSTANCE���˲�����ʾӦ�ó��򱾴�����ʵ���ľ��
/// @param hPrevInstance ��������HINSTANCE����ʾӦ�ó���֮ǰ����ʵ���ľ��������ʵ��Ӧ���У��˲���ʼ��ΪNULL
/// @param lpCmdLine ����ʱ������������cmd������������"start.exe command argumeng",��ô�˲�����ָ���ַ���"command argumeng",���� LPSTR ��Windows API�г��õ��ַ������� 
/// @param nCmdShow ��ʾӦ�ó��򴰿ڣ�����У�����ʾ״̬��
/// @return 
int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//����LPWSTR���͵Ŀ��ַ���
	LPWSTR szUnicode = L"This is a Unicode String";

	//����LPSTR���͵�խ�ַ���
	LPSTR szMutliByte = "This is a Unicode String";

	//����LPTSTR���͵���ʹ���ַ���
	LPTSTR szString = TEXT("This string is Unicode or not depends on the option");

	//ʹ��W�汾��API�������Կ��ַ���Ϊ����
	MessageBoxW(NULL, szUnicode, L"<�ַ�����1>", MB_OK);

	//ʹ��A�汾��API��������խ�ַ���Ϊ����
	MessageBoxA(NULL, szMutliByte, "<�ַ�����2>", MB_OK);

	//���ݱ��������Զ�ѡ��A�汾��W�汾��API��������������Ӧ���ַ�������Ϊ����
	MessageBox(NULL, szString, TEXT("<�ַ�����3>"), MB_OK);

	return 0;

}