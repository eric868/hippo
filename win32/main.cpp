#include <windows.h>
#include <stdio.h>
#pragma comment(linker, "/subsystem:\"console\" /entry:\"WinMainCRTStartup\"")

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	printf("%p %p\n", hInstance, GetModuleHandle(NULL));

	MessageBox(NULL, L"��һ��Win32����", L"hello world", MB_OK);
	return 0;
}