//ͷ�ļ�
#include <Windows.h>

//����ʱʹ��User32.lib
#pragma comment(lib,"User32.lib")

/// @brief WindowsӦ�ó������
/// @param hInstance ��������HINSTANCE���˲�����ʾӦ�ó��򱾴�����ʵ���ľ��
/// @param hPrevInstance ��������HINSTANCE����ʾӦ�ó���֮ǰ����ʵ���ľ��������ʵ��Ӧ���У��˲���ʼ��ΪNULL
/// @param lpCmdLine ����ʱ������������cmd������������"start.exe command argumeng",��ô�˲�����ָ���ַ���"command argumeng",���� LPSTR ��Windows API�г��õ��ַ������� 
/// @param nCmdShow ��ʾӦ�ó��򴰿ڣ�����У�����ʾ״̬��
/// @return 
int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//����API���� MessageBox
	MessageBox(NULL, TEXT("��ʼѧϰWindows��̣�����ѧϰ�ʼ�"), TEXT("��Ϣ�Ի���"), MB_OK);
	return 0;
}