#include <windows.h>
#include <windowsx.h>
#include <stdio.h>
#include <locale.h>
#include"resource.h"
//#pragma comment(linker, "/subsystem:\"console\" /entry:\"WinMainCRTStartup\"")

#define WM_AAA WM_USER + 1

//typedef long LRESULT
//���ھ�� ��ϢID 
LRESULT CALLBACK wndproc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	char windowname[] = "����";
	char title[] = "���Դ���";

	WNDCLASS wndclass;
	wndclass.style = CS_HREDRAW;
	wndclass.lpfnWndProc = wndproc;//���崰�ڴ�����
	wndclass.cbClsExtra = 0;//����������չ
	wndclass.cbWndExtra = 0;//����ʵ������չ
	wndclass.hInstance = hInstance; //��ǰʵ�����
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);//���ڵ���С��ͼ��Ϊȱʡͼ��
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);//���ڲ��ü�ͷ���
	wndclass.hbrBackground = (HBRUSH)(GetStockObject(LTGRAY_BRUSH));//���ڱ���Ϊ��ɫ
	wndclass.lpszMenuName = NULL;//�����޲˵�
	wndclass.lpszClassName = windowname;

	ATOM ret = RegisterClass(&wndclass);
	if (ret == 0) return ret; //���ע��ʧ�� ��������

	//����ǰ����WM_CREATE
	HWND hwnd = CreateWindow(windowname,//������������������ʱһ��Ҫ���������Ѿ�ע����Ĵ�����������"����"��
		title,//���ڱ�����
		WS_OVERLAPPEDWINDOW,
		100,//�������Ͻ�����ֵ
		100,
		300,//���ڵĸߺͿ�
		300,
		NULL,//�˴����޸�����
		NULL,//�˴������Ӳ˵�
		hInstance,//�����˴��ڵ�Ӧ�ó���ĵ�ǰ���
		NULL);

	//��ʾ����
	ShowWindow(hwnd, nShowCmd);

	//�����û���(����WM_PAINT)
	UpdateWindow(hwnd);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))//GetMessage()�����Ǵӵ����̵߳���Ϣ������ȡ��һ����Ϣ������ÿһ��Ӧ�ó��򴰿��̣߳�����ϵͳ����Ϊ�佨��һ����Ϣ���У������ǵĴ�������Ϣʱ������������������߳���ص���Ϣ��������ϵͳ��������Ϣ�ŵ����̵߳���Ϣ���е��У����ǵĴ��ڳ����ͨ�����GetMessage()�������Լ�����Ϣ������ȡ��һ��һ���������Ϣ��������Ӧ������
	{
		TranslateMessage(&msg);//��"��Ϣ��"��ת������Լ��̵�WM_KEYDOWN��WM_KEYUP��Ϣ��ת��ΪWM_CHAR��Ϣ�����ҽ�ת���������ϢͶ�ݵ����ǵ���Ϣ������ȥ�����ת����������Ӱ��ԭ������Ϣ��ֻ�����һ���µ���Ϣ��
		DispatchMessage(&msg);//DispatchMessage()�����ǽ�����ȡ������Ϣ�������ڵĻص�����ȥ�����������Ϊ�ú�����ȡ������Ϣ·�ɸ�����ϵͳ��Ȼ�����ϵͳȥ�������ǵĴ��ڻص������������Ϣ���д���
	}

	return msg.wParam;
}

LRESULT CALLBACK wndproc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
{
	switch (message)
	{
	case WM_NOTIFY:
	{
		
	}
	break;
	case WM_COMMAND:
	{
		WORD id = LOWORD(wparam);
		WORD code = HIWORD(wparam);
		HWND hctrl = (HWND)lparam;


	}
	break;
	case WM_CREATE:
	{
		LPCREATESTRUCT pcs = (LPCREATESTRUCT)lparam;

	
	}
	break;
	case WM_DESTROY:
	{
		//SendMessage(hwnd, WM_AAA, 0, 0); //ͬ�����ͣ�ֱ�ӷ��͸����ڴ�����
		//PostMessage(hwnd, WM_AAA, 0, 0); //�첽���ͣ����͸�������Ϣ����
		//PostThreadMessage(GetCurrentThreadId(), WM_QUIT, 0, 0); //��ͬ��PostQuitMessage(0);
		PostQuitMessage(0);
	}
	break;
	default:
		return DefWindowProc(hwnd, message, wparam, lparam);
	}

	return 0;
}