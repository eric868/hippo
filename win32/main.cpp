#include <windows.h>
#include <stdio.h>
#include <locale.h>
//#pragma comment(linker, "/subsystem:\"console\" /entry:\"WinMainCRTStartup\"")

#define WM_AAA WM_USER + 1

//typedef long LRESULT
//窗口句柄 消息ID 
LRESULT CALLBACK wndproc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	char windowname[] = "窗口";
	char title[] = "测试窗口";

	WNDCLASS wndclass;
	wndclass.style = CS_HREDRAW;
	wndclass.lpfnWndProc = wndproc;//定义窗口处理函数
	wndclass.cbClsExtra = 0;//窗口类无扩展
	wndclass.cbWndExtra = 0;//窗口实列无扩展
	wndclass.hInstance = hInstance; //当前实例句柄
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);//窗口的最小化图标为缺省图标
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);//窗口采用箭头光标
	wndclass.hbrBackground = (HBRUSH)(GetStockObject(LTGRAY_BRUSH));//窗口背景为白色
	wndclass.lpszMenuName = NULL;//窗口无菜单
	wndclass.lpszClassName = windowname;

	ATOM ret = RegisterClass(&wndclass);
	if (ret == 0)//如果注册失败 发出警告
	{
		return 0;
	}

	//返回前发送WM_CREATE
	HWND hwnd = CreateWindow(windowname,//窗口类名，创建窗口时一定要基于我们已经注册过的窗口类名，即"窗口"。
		title,//窗口标题名
		WS_OVERLAPPEDWINDOW,
		100,//窗口左上角坐标值为缺省值 CW_  Create Wndow
		100,
		300, //窗口的高和宽为缺省值
		300,
		NULL,//此窗口无父窗口
		NULL,//此窗口无子菜单
		hInstance,//创建此窗口的应用程序的当前句柄
		NULL);

	//显示窗口
	ShowWindow(hwnd, nCmdShow);

	//绘制用户区(发送WM_PAINT)
	UpdateWindow(hwnd);

	HWND hwnd2 = CreateWindow(windowname,//窗口类名，创建窗口时一定要基于我们已经注册过的窗口类名，即"窗口"。
		title,//窗口标题名
		WS_OVERLAPPEDWINDOW,
		100,//窗口左上角坐标值为缺省值 CW_  Create Wndow
		500,
		300, //窗口的高和宽为缺省值
		300,
		NULL,//此窗口无父窗口
		NULL,//此窗口无子菜单
		hInstance,//创建此窗口的应用程序的当前句柄
		NULL);

	//显示窗口
	ShowWindow(hwnd2, nCmdShow);

	//绘制用户区(发送WM_PAINT)
	UpdateWindow(hwnd2);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))//GetMessage()函数是从调用线程的消息队列中取出一条消息；对于每一个应用程序窗口线程，操作系统都会为其建立一个消息队列，当我们的窗口有消息时（即所有与这个窗口线程相关的消息），操纵系统会把这个消息放到该线程的消息队列当中，我们的窗口程序就通过这个GetMessage()函数从自己的消息队列中取出一条一条具体的消息并进行响应操作。
	{
		if (msg.message == WM_LBUTTONDOWN)
		{
			//char str[64];
			//sprintf(str, "窗口句柄:%p", msg.hwnd);
			//MessageBox(NULL, str, "测试", MB_OK);
			//SendMessage直接发给窗口过程，阻塞，处理完成返回
			//SendMessage(hwnd, WM_AAA, 0, 0);
			//PostMessage发送到消息队列中，异步
			//PostMessage(hwnd, WM_AAA, 0, 0);
			PostThreadMessage(GetCurrentThreadId(), WM_QUIT, 0, 0); // 等价于PostQuitMessage(0);
			int a = 100;
		}

		if (msg.message == WM_AAA)
		{
			MessageBox(NULL, "消息循环AAA", "测试", MB_OK);
		}

		TranslateMessage(&msg);//对"消息对"的转化，如对键盘的WM_KEYDOWN和WM_KEYUP消息对转化为WM_CHAR消息，并且将转换后的新消息投递到我们的消息队列中去，这个转化操作不会影响原来的消息，只会产生一个新的消息。
		DispatchMessage(&msg);//DispatchMessage()函数是将我们取出的消息传到窗口的回调函数去处理；可以理解为该函数将取出的消息路由给操作系统，然后操作系统去调用我们的窗口回调函数对这个消息进行处理。
	}

	return msg.wParam;
}

LRESULT CALLBACK wndproc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
{
	switch (message)
	{
	case WM_AAA:
		MessageBox(NULL, "窗口处理程序AAA", "测试", MB_OK);

	case WM_CREATE:
		//init the window
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	default:
		return DefWindowProc(hwnd, message, wparam, lparam);
	}

	return 0;
}