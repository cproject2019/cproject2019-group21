#include"标头.h"

/*Windows data type naming rules
Unsigned types: usually start with "U", such as "UINT" for "INT".
Pointer type: add "LP" or "P" before the data type it points to. For example, the pointer type to DWORD is "LPDWORD" and "PDWORD".
Handle type: starts with "H".For example, HWND is window (short for WND), that is, window handle, MENU type corresponding to the handle type of "HMENU" and so on.
*/
/*
/*Call the API function MessageBox
Int nSelect = MessageBox(NULL, TEXT)), TEXT (" Welcome "), MB_OKCANCEL);
Prototype is a MessageBox ()
Int WINAPI MessageBox(HWND HWND, LPCTSTR lpText, LPCTSTR lpCaption, UINT uType);
HWnd: handle to the parent window of the message box. If this parameter is NULL, the message box does not have a parent window.
LpText: the contents of the message box.LPCTSTR is a custom data type, equivalent to const char *.
Caption: the title of the message box.
UType: button styles and ICONS for dialog boxes.
*/
/*	if (nSelect == IDOK) {
MessageBox(NULL, TEXT("你点击了“确定”按钮"), TEXT("提示"), MB_OK);
}
else {
MessageBox(NULL, TEXT("你点击了“取消”按钮"), TEXT("提示"), MB_OK);
}
return 0;
*/


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
//HINSTANCE hInstance:Handle of the current window, HINSTANCE hPrevInstance:Previous window handle，and in the Win32 it is NULL, PSTR szCmdLine:command the parameter of lines, int iCmdShow: the mode of the window display。
//类似控制台程序中的main函数，windows程序中的主函数是winmain函数
{
	static TCHAR szClassName[] = TEXT("HelloWin");  //the name of window structure
	HWND     hwnd;  //window's handle
	MSG      msg;  //message

				   /*****create window*****/
	{
		/****Define the window structure class****/
		WNDCLASS wndclass;
		wndclass.style = CS_HREDRAW | CS_VREDRAW;  //Window style, the variables mean that the window size changes will redraw the window, so that the text in the middle
		wndclass.lpfnWndProc = WndProc;  //window process
		wndclass.cbClsExtra = 0;
		wndclass.cbWndExtra = 0;
		wndclass.hInstance = hInstance;  //current window handle
		wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);  //window icon
		wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);  //mouse style
		wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);  //the paint brush of window's background, which is the window background color
		wndclass.lpszMenuName = NULL;  //window menu
		wndclass.lpszClassName = szClassName;  //the window class name

											   /****register a window****/
		RegisterClass(&wndclass);//A window class is simply a struct, and if it defines only struct variables, then it can't be used. Okay?The value of the lpszClassName field finds the structure.So you also need to call RegisterClass() to register

								 /****create a window****/
		hwnd = CreateWindow
			(
				szClassName,  // The name of the window class
				TEXT("计算器"),  //The title of the window
				WS_OVERLAPPEDWINDOW,  //The style of the window
				CW_USEDEFAULT,  //initialize x coordinate
				CW_USEDEFAULT,  //initialaize y coordinate
				600,  //Width
				660,  //Highth
				NULL,  //Parent window handle. There is no parent window, so it is NULL
				NULL,  //Window menu handle. The current window has no menu, so it is NULL
				hInstance,  //Handle of the current window, being passed in through the WinMain function.
				NULL
				);

		/****show the window****/
		ShowWindow(hwnd, iCmdShow);//When creating a window through the CreateWindows() function, we just allocate memory for the window and get a handle, but the window doesn't show up, so we need to call?The ShowWindow() function to display the window.

								   /*****Update the window and draw the control*****/
		UpdateWindow(hwnd);//Update the window and draw the control. The ShowWindow() function displays the window but does not draw the client area, so we also need to call the UpdateWindow() function to generate the VM_PAINT message to draw the various controls in the client area.
	}

	/*****message loop*****/
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);  //Translate messages
		DispatchMessage(&msg);  //Dispatch messages
	}

	return msg.wParam;
}


/*****window process*****/
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
// HWND hwnd: window's handle, UINT message:window's type, WPARAM wParam:extra message1, LPARAM lParam:extra message2
{
	int wmId, wmEvent;
	int szText = a;
	PAINTSTRUCT ps;//Store information about the drawing environment
	HDC hdc;//Set the environment handle
	HDC hdcStatic;
	static HFONT hFont;
	static HBRUSH hBrush;  //画刷

	//单选项标签
	static HWND htype;
	static HWND hAri;//arithmetic operation
	static HWND hFun; //Function operations
		static HWND hCF;// calculateFunction
		static HWND hIF;//integrateFunction
	static HWND hSta;//Statistics
		static HWND hS1;//statisticsVariable1
		static HWND hS2;//statisticsVariable2
	static HWND hCon;// Conversion of numbers*
		static HWND hT2;//translate2
		static HWND hT8;//translate8
		static HWND hT16;//translate16
	static HWND hLin;//Linear equations

	//输入
	static HWND hInputBoxA;
	static HWND hInputBoxCF1;
	static HWND hInputBoxCF2;
	static HWND hInputBoxIF1;
	static HWND hInputBoxIF2;
	static HWND hInputBoxIF3;
	static HWND hInputBoxS1;
	static HWND hInputBoxS2;
	static HWND hInputBoxC;
	static HWND hInputBoxL1;
	static HWND hInputBoxL2;
	static HWND hInputBoxL3;
	static HWND hInputBoxL4;

	static HWND hOutputBoxA;
	static HWND hOutputBoxCF;
	static HWND hOutputBoxIF;
	static HWND hOutputBoxS1;
	static HWND hOutputBoxS2;
	static HWND hOutputBoxC;
	static HWND hOutputBoxL;

	static HWND hButtonA;
	static HWND hButtonCF;
	static HWND hButtonIF;
	static HWND hButtonS1;
	static HWND hButtonS2;
	static HWND hButtonT2;
	static HWND hButtonT8;
	static HWND hButtonT16;
	static HWND hButtonL;


	switch (message)
	{
	case  WM_CREATE://The window is created
					//Create logical fonts
		hFont = CreateFont
			(
				-15/*Highth*/, -7.5/*Width*/, 0, 0, 400,
				FALSE/*Not italic*/, FALSE/*No underlines*/, FALSE/*No strikethrough*/,
				DEFAULT_CHARSET,  //Use default character set
				OUT_CHARACTER_PRECIS, CLIP_CHARACTER_PRECIS,
				DEFAULT_QUALITY,  //Default output quality
				FF_DONTCARE,  //No font family is specified
				L"微软雅黑"  //No fontname
				);

		//创建画刷
		hBrush = CreateSolidBrush(RGB(0x50, 0xB7, 0xC1));

		//Create a static text control
		hOutputBoxA = CreateWindow
			(
				TEXT("static"),  //The class name of the static text box
				TEXT("欢迎使用"),  //The conttol text
				WS_CHILD /*Child window*/ | WS_VISIBLE | SS_CENTER |WS_BORDER /*Frames*/,
				20/*x coordinate*/, 195/*y coordinate*/, 545/*Width*/, 220/*Highth*/, hWnd/*The handle of father window*/,
				(HMENU)00,  //Specifie a unique identifier for the control
				hInst,  //Handle of the current instance
				NULL
				);

		hOutputBoxCF = CreateWindow
			(
				TEXT("static"),  //The class name of the static text box
				TEXT("欢迎使用"),  //The conttol text
				WS_CHILD /*Child window*/ | SS_CENTER | WS_BORDER /*Frames*/,
				20/*x coordinate*/, 255/*y coordinate*/, 545/*Width*/, 220/*Highth*/, hWnd/*The handle of father window*/,
				(HMENU)01,  //Specifie a unique identifier for the control
				hInst,  //Handle of the current instance
				NULL
				);

		hOutputBoxIF = CreateWindow
			(
				TEXT("static"),  //The class name of the static text box
				TEXT("欢迎使用"),  //The conttol text
				WS_CHILD /*Child window*/ | SS_CENTER | WS_BORDER /*Frames*/,
				20/*x coordinate*/, 315/*y coordinate*/, 545/*Width*/, 220/*Highth*/, hWnd/*The handle of father window*/,
				(HMENU)02,  //Specifie a unique identifier for the control
				hInst,  //Handle of the current instance
				NULL
				);

		hOutputBoxS1 = CreateWindow
			(
				TEXT("static"),  //The class name of the static text box
				TEXT("欢迎使用"),  //The conttol text
				WS_CHILD /*Child window*/ | SS_CENTER | WS_BORDER /*Frames*/,
				20/*x coordinate*/, 195/*y coordinate*/, 545/*Width*/, 220/*Highth*/, hWnd/*The handle of father window*/,
				(HMENU)03,  //Specifie a unique identifier for the control
				hInst,  //Handle of the current instance
				NULL
				);

		hOutputBoxS2 = CreateWindow
			(
				TEXT("static"),  //The class name of the static text box
				TEXT("欢迎使用"),  //The conttol text
				WS_CHILD /*Child window*/ | SS_CENTER | WS_BORDER /*Frames*/,
				20/*x coordinate*/, 255/*y coordinate*/, 545/*Width*/, 220/*Highth*/, hWnd/*The handle of father window*/,
				(HMENU)04,  //Specifie a unique identifier for the control
				hInst,  //Handle of the current instance
				NULL
				);

		hOutputBoxC = CreateWindow
			(
				TEXT("static"),  //The class name of the static text box
				TEXT("欢迎使用"),  //The conttol text
				WS_CHILD /*Child window*/ | SS_CENTER | WS_BORDER /*Frames*/,
				20/*x coordinate*/, 195/*y coordinate*/, 545/*Width*/, 220/*Highth*/, hWnd/*The handle of father window*/,
				(HMENU)05,  //Specifie a unique identifier for the control
				hInst,  //Handle of the current instance
				NULL
				);

		hOutputBoxL = CreateWindow
			(
				TEXT("static"),  //The class name of the static text box
				TEXT("欢迎使用"),  //The conttol text
				WS_CHILD /*Child window*/ | SS_CENTER | WS_BORDER /*Frames*/,
				20/*x coordinate*/, 375/*y coordinate*/, 545/*Width*/, 220/*Highth*/, hWnd/*The handle of father window*/,
				(HMENU)06,  //Specifie a unique identifier for the control
				hInst,  //Handle of the current instance
				NULL
				);


		hInputBoxA = CreateWindow
			(
				TEXT("edit"), TEXT("请在此输入"),
				WS_CHILD | WS_BORDER | BS_FLAT/*Flat style*/,
				20 /*x coordnite*/, 100 /*y coordnite*/, 545 /*Width*/, 50/*Highth*/,
				hWnd, (HMENU)10 /*The unique identifier of control*/, hInst, NULL
				);

		hInputBoxCF1 = CreateWindow
			(
				TEXT("edit"), TEXT("请在此输入"),
				WS_CHILD | WS_BORDER | BS_FLAT/*Flat style*/,
				20 /*x coordnite*/, 100 /*y coordnite*/, 545 /*Width*/, 50/*Highth*/,
				hWnd, (HMENU)11 /*The unique identifier of control*/, hInst, NULL
				);

		hInputBoxCF2 = CreateWindow
			(
				TEXT("edit"), TEXT("请在此输入"),
				WS_CHILD | WS_BORDER | BS_FLAT/*Flat style*/,
				20 /*x coordnite*/, 160 /*y coordnite*/, 545 /*Width*/, 50/*Highth*/,
				hWnd, (HMENU)12 /*The unique identifier of control*/, hInst, NULL
				);

		hInputBoxIF1 = CreateWindow
			(
				TEXT("edit"), TEXT(""),
				WS_CHILD | WS_BORDER | BS_FLAT,
				20, 100, 545, 50,
				hWnd, (HMENU)13, hInst, NULL
				);

		hInputBoxIF2 = CreateWindow
			(
				TEXT("edit"), TEXT(""),
				WS_CHILD | WS_BORDER | BS_FLAT,
				20, 160, 545, 50,
				hWnd, (HMENU)14, hInst, NULL
				);
		hInputBoxIF3 = CreateWindow
			(
				TEXT("edit"), TEXT(""),
				WS_CHILD | WS_BORDER | BS_FLAT,
				20, 220, 545, 50,
				hWnd, (HMENU)15, hInst, NULL
				);

		hInputBoxS1 = CreateWindow
			(
				TEXT("edit"), TEXT(""),
				WS_CHILD| WS_BORDER | BS_FLAT,
				20, 100, 545, 50,
				hWnd, (HMENU)16, hInst, NULL
				);

		hInputBoxS2 = CreateWindow
			(
				TEXT("edit"), TEXT(""),
				WS_CHILD | WS_BORDER | BS_FLAT,
				20, 160, 545, 50,
				hWnd, (HMENU)17, hInst, NULL
				);
		hInputBoxC =  CreateWindow
			(
				TEXT("edit"), TEXT("请在此输入"),
				WS_CHILD | WS_BORDER | BS_FLAT/*Flat style*/,
				20 /*x coordnite*/, 100 /*y coordnite*/, 545 /*Width*/, 50/*Highth*/,
				hWnd, (HMENU)18 /*The unique identifier of control*/, hInst, NULL
				);

		hInputBoxL1 = CreateWindow
			(
				TEXT("edit"), TEXT("请在此输入"),
				WS_CHILD | WS_BORDER | BS_FLAT/*Flat style*/,
				20 /*x coordnite*/, 100 /*y coordnite*/, 545 /*Width*/, 50/*Highth*/,
				hWnd, (HMENU)190 /*The unique identifier of control*/, hInst, NULL
				);

		hInputBoxL2 = CreateWindow
			(
				TEXT("edit"), TEXT("请在此输入"),
				WS_CHILD | WS_BORDER | BS_FLAT/*Flat style*/,
				20 /*x coordnite*/, 160 /*y coordnite*/, 545 /*Width*/, 50/*Highth*/,
				hWnd, (HMENU)191 /*The unique identifier of control*/, hInst, NULL
				);

		hInputBoxL3 = CreateWindow
			(
				TEXT("edit"), TEXT("请在此输入"),
				WS_CHILD | WS_BORDER | BS_FLAT/*Flat style*/,
				20 /*x coordnite*/, 220 /*y coordnite*/, 545 /*Width*/, 50/*Highth*/,
				hWnd, (HMENU)192 /*The unique identifier of control*/, hInst, NULL
				);

		hInputBoxL4 = CreateWindow
			(
				TEXT("edit"), TEXT("请在此输入"),
				WS_CHILD | WS_BORDER | BS_FLAT/*Flat style*/,
				20 /*x coordnite*/, 280 /*y coordnite*/, 545 /*Width*/, 50/*Highth*/,
				hWnd, (HMENU)193 /*The unique identifier of control*/, hInst, NULL

				);



		hButtonA = CreateWindow(TEXT("button"), TEXT("求解"), WS_CHILD | WS_BORDER | BS_FLAT, 470, 160, 70, 25, hWnd, (HMENU)20, hInst, NULL);
		hButtonCF = CreateWindow(TEXT("button"), TEXT("求解"), WS_CHILD | WS_BORDER | BS_FLAT, 470, 220, 70, 25, hWnd, (HMENU)21, hInst, NULL);
		hButtonIF = CreateWindow(TEXT("button"), TEXT("求解"), WS_CHILD | WS_BORDER | BS_FLAT, 470, 280, 70, 25, hWnd, (HMENU)22, hInst, NULL);
		hButtonS1 = CreateWindow(TEXT("button"), TEXT("求解"), WS_CHILD | WS_BORDER | BS_FLAT, 470, 160, 70, 25, hWnd, (HMENU)23, hInst, NULL);
		hButtonS2 = CreateWindow(TEXT("button"), TEXT("求解"), WS_CHILD | WS_BORDER | BS_FLAT, 470, 220, 70, 25, hWnd, (HMENU)24, hInst, NULL);
		hButtonT2 = CreateWindow(TEXT("button"), TEXT("求解"), WS_CHILD | WS_BORDER | BS_FLAT, 470, 160, 70, 25, hWnd, (HMENU)25, hInst, NULL);
		hButtonT8 = CreateWindow(TEXT("button"), TEXT("求解"), WS_CHILD | WS_BORDER | BS_FLAT, 470, 160, 70, 25, hWnd, (HMENU)26, hInst, NULL);
		hButtonT16 = CreateWindow(TEXT("button"), TEXT("求解"), WS_CHILD | WS_BORDER | BS_FLAT, 470, 160, 70, 25, hWnd, (HMENU)27, hInst, NULL);
		hButtonL = CreateWindow(TEXT("button"), TEXT("求解"), WS_CHILD | WS_BORDER | BS_FLAT, 470, 340, 70, 25, hWnd, (HMENU)28, hInst, NULL);
		
						 
		//创建分组框控件
		htype = CreateWindow
			(TEXT("static"), TEXT("请选择运算类型"), WS_CHILD | WS_VISIBLE | WS_BORDER | SS_CENTER, 20, 10, 550, 60, hWnd, (HMENU)30,  hInst, NULL );

		//添加单选按钮

		hAri = CreateWindow(
			TEXT("button"), TEXT("算术运算"),
			WS_CHILD | WS_VISIBLE | BS_LEFT | BS_AUTORADIOBUTTON /*单选按钮*/,
			55, 40, 100, 26,
			hWnd/*父窗口为type控件*/, (HMENU)31, hInst, NULL
			);
		hFun = CreateWindow(
			TEXT("button"), TEXT("函数运算"),
			WS_CHILD | WS_VISIBLE | BS_LEFT | BS_AUTORADIOBUTTON,
			155, 40, 100, 26,
			hWnd, (HMENU)32, hInst, NULL
			);
		hCF = CreateWindow(
			TEXT("button"), TEXT("函数求值"),
			WS_CHILD | BS_LEFT | BS_AUTORADIOBUTTON,
			155, 70, 100, 26,
			hWnd, (HMENU)321, hInst, NULL
			);
		hIF = CreateWindow(
			TEXT("button"), TEXT("求积分"),
			WS_CHILD | BS_LEFT | BS_AUTORADIOBUTTON,
			255, 70, 100, 26,
			hWnd, (HMENU)322, hInst, NULL
			);
		hSta = CreateWindow(
			TEXT("button"), TEXT("统计运算"),
			WS_CHILD | WS_VISIBLE | BS_LEFT | BS_AUTORADIOBUTTON,
			255, 40, 100, 26,
			hWnd, (HMENU)33, hInst, NULL
			);
		hS1 = CreateWindow(
			TEXT("button"), TEXT("单变量统计"),
			WS_CHILD | BS_LEFT | BS_AUTORADIOBUTTON,
			255, 70, 100, 26,
			hWnd, (HMENU)331, hInst, NULL
			);
		hS2 = CreateWindow(
			TEXT("button"), TEXT("双变量统计"),
			WS_CHILD| BS_LEFT | BS_AUTORADIOBUTTON,
			355, 70, 100, 26,
			hWnd, (HMENU)332, hInst, NULL
			);
		hCon = CreateWindow(
			TEXT("button"), TEXT("进制转换"),
			WS_CHILD | WS_VISIBLE | BS_LEFT | BS_AUTORADIOBUTTON,
			355, 40, 100, 26,
			hWnd, (HMENU)34, hInst, NULL
			);
		hT2 = CreateWindow(
			TEXT("button"), TEXT("转2进制"),
			WS_CHILD | BS_LEFT | BS_AUTORADIOBUTTON,
			255, 70, 100, 26,
			hWnd, (HMENU)341, hInst, NULL
			);
		hT8 = CreateWindow(
			TEXT("button"), TEXT("转8进制"),
			WS_CHILD | BS_LEFT | BS_AUTORADIOBUTTON,
			355, 70, 100, 26,
			hWnd, (HMENU)342, hInst, NULL
			);
		hT16 = CreateWindow(
			TEXT("button"), TEXT("转16进制"),
			WS_CHILD | BS_LEFT | BS_AUTORADIOBUTTON,
			455, 70, 100, 26,
			hWnd, (HMENU)343, hInst, NULL
			);
		hLin = CreateWindow(
			TEXT("button"), TEXT("线性方程"),
			WS_CHILD | WS_VISIBLE | BS_LEFT | BS_AUTORADIOBUTTON,
			455, 40, 100, 26,
			hWnd, (HMENU)35, hInst, NULL
			);

		SendMessage(hInputBoxA, WM_SETFONT, (WPARAM)hFont, NULL);//Set the text box font
		SendMessage(hInputBoxCF1, WM_SETFONT, (WPARAM)hFont, NULL);
		SendMessage(hInputBoxCF2, WM_SETFONT, (WPARAM)hFont, NULL);
		SendMessage(hInputBoxIF1, WM_SETFONT, (WPARAM)hFont, NULL);
		SendMessage(hInputBoxIF2, WM_SETFONT, (WPARAM)hFont, NULL);
		SendMessage(hInputBoxIF3, WM_SETFONT, (WPARAM)hFont, NULL);
		SendMessage(hInputBoxS1, WM_SETFONT, (WPARAM)hFont, NULL);
		SendMessage(hInputBoxS2, WM_SETFONT, (WPARAM)hFont, NULL);
		SendMessage(hInputBoxC, WM_SETFONT, (WPARAM)hFont, NULL);
		SendMessage(hInputBoxL1, WM_SETFONT, (WPARAM)hFont, NULL);
		SendMessage(hInputBoxL2, WM_SETFONT, (WPARAM)hFont, NULL);
		SendMessage(hInputBoxL3, WM_SETFONT, (WPARAM)hFont, NULL);
		SendMessage(hInputBoxL4, WM_SETFONT, (WPARAM)hFont, NULL);
		SendMessage(hOutputBoxA, WM_SETFONT, (WPARAM)hFont, NULL);
		SendMessage(hOutputBoxCF, WM_SETFONT, (WPARAM)hFont, NULL);
		SendMessage(hOutputBoxIF, WM_SETFONT, (WPARAM)hFont, NULL);
		SendMessage(hOutputBoxS1, WM_SETFONT, (WPARAM)hFont, NULL);
		SendMessage(hOutputBoxS2, WM_SETFONT, (WPARAM)hFont, NULL);
		SendMessage(hOutputBoxC, WM_SETFONT, (WPARAM)hFont, NULL);
		SendMessage(hOutputBoxL, WM_SETFONT, (WPARAM)hFont, NULL);
		SendMessage(hButtonA, WM_SETFONT, (WPARAM)hFont, NULL);
		SendMessage(hButtonCF, WM_SETFONT, (WPARAM)hFont, NULL);
		SendMessage(hButtonIF, WM_SETFONT, (WPARAM)hFont, NULL);
		SendMessage(hButtonS1, WM_SETFONT, (WPARAM)hFont, NULL);
		SendMessage(hButtonS2, WM_SETFONT, (WPARAM)hFont, NULL);
		SendMessage(hButtonT2, WM_SETFONT, (WPARAM)hFont, NULL);
		SendMessage(hButtonT8, WM_SETFONT, (WPARAM)hFont, NULL);
		SendMessage(hButtonT16, WM_SETFONT, (WPARAM)hFont, NULL);
		SendMessage(hButtonL, WM_SETFONT, (WPARAM)hFont, NULL);
		SendMessage(htype, WM_SETFONT, (WPARAM)hFont, NULL);
		SendMessage(hAri, WM_SETFONT, (WPARAM)hFont, NULL);
		SendMessage(hFun, WM_SETFONT, (WPARAM)hFont, NULL);
		SendMessage(hCF, WM_SETFONT, (WPARAM)hFont, NULL);
		SendMessage(hIF, WM_SETFONT, (WPARAM)hFont, NULL);
		SendMessage(hSta, WM_SETFONT, (WPARAM)hFont, NULL);
		SendMessage(hS1, WM_SETFONT, (WPARAM)hFont, NULL);
		SendMessage(hS2, WM_SETFONT, (WPARAM)hFont, NULL);
		SendMessage(hCon, WM_SETFONT, (WPARAM)hFont, NULL);		
		SendMessage(hT2, WM_SETFONT, (WPARAM)hFont, NULL);
		SendMessage(hT8, WM_SETFONT, (WPARAM)hFont, NULL);
		SendMessage(hT16, WM_SETFONT, (WPARAM)hFont, NULL);
		SendMessage(hLin, WM_SETFONT, (WPARAM)hFont, NULL);

		break;

		//更改颜色
    case WM_CTLCOLORSTATIC:
			hdcStatic = (HDC)wParam;
			SetTextColor(hdcStatic, RGB(255, 255, 255));  //白色

			
			SetBkColor(hdcStatic, RGB(0x50, 0xB7, 0xC1));  //橙色
			return (INT_PTR)hBrush;

	case WM_COMMAND://
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		switch (wmId)
		{
		case 31://Ari
		{
			if (SendMessage(hAri, BM_GETCHECK, 0, 0) == BST_CHECKED) 
			{
				ShowWindow(hButtonA, SW_HIDE);
				ShowWindow(hButtonCF, SW_HIDE);
				ShowWindow(hButtonIF, SW_HIDE);
				ShowWindow(hButtonS1, SW_HIDE);
				ShowWindow(hButtonS2, SW_HIDE);
				ShowWindow(hButtonT2, SW_HIDE);
				ShowWindow(hButtonT8, SW_HIDE);
				ShowWindow(hButtonT16, SW_HIDE);
				ShowWindow(hButtonL, SW_HIDE);
				ShowWindow(hInputBoxA, SW_HIDE);
				ShowWindow(hInputBoxCF1, SW_HIDE);
				ShowWindow(hInputBoxCF2, SW_HIDE);
				ShowWindow(hInputBoxIF1, SW_HIDE);
				ShowWindow(hInputBoxIF2, SW_HIDE);
				ShowWindow(hInputBoxIF3, SW_HIDE);
				ShowWindow(hInputBoxS1, SW_HIDE);
				ShowWindow(hInputBoxS2, SW_HIDE);
				ShowWindow(hInputBoxC, SW_HIDE);
				ShowWindow(hInputBoxL1, SW_HIDE);
				ShowWindow(hInputBoxL2, SW_HIDE);
				ShowWindow(hInputBoxL3, SW_HIDE);
				ShowWindow(hInputBoxL4, SW_HIDE);
				ShowWindow(hOutputBoxA, SW_HIDE);
				ShowWindow(hOutputBoxCF, SW_HIDE);
				ShowWindow(hOutputBoxIF, SW_HIDE);
				ShowWindow(hOutputBoxS1, SW_HIDE);
				ShowWindow(hOutputBoxS2, SW_HIDE);
				ShowWindow(hOutputBoxC, SW_HIDE);
				ShowWindow(hOutputBoxL, SW_HIDE);
				ShowWindow(hCF, SW_HIDE);
				ShowWindow(hIF, SW_HIDE);
				ShowWindow(hS1, SW_HIDE);
				ShowWindow(hS2, SW_HIDE);
				ShowWindow(hT2, SW_HIDE);
				ShowWindow(hT8, SW_HIDE);
				ShowWindow(hT16, SW_HIDE);

				ShowWindow(hButtonA, SW_SHOW);
				ShowWindow(hInputBoxA, SW_SHOW);
				ShowWindow(hOutputBoxA, SW_SHOW);
				SetWindowText(hInputBoxA, TEXT("请在此输入"));
			}
			break;
		}

		case 32://Fun
		{
			if (SendMessage(hFun, BM_GETCHECK, 0, 0) == BST_CHECKED)
			{
				ShowWindow(hCF, SW_SHOW);
				ShowWindow(hIF, SW_SHOW);
				ShowWindow(hS1, SW_HIDE);
				ShowWindow(hS2, SW_HIDE);
				ShowWindow(hT2, SW_HIDE);
				ShowWindow(hT8, SW_HIDE);
				ShowWindow(hT16, SW_HIDE);
			}
			break;
		}
		
		case 321://S1
		{
			if (SendMessage(hCF, BM_GETCHECK, 0, 0) == BST_CHECKED)
			{
				ShowWindow(hButtonA, SW_HIDE);
				ShowWindow(hButtonCF, SW_HIDE);
				ShowWindow(hButtonIF, SW_HIDE);
				ShowWindow(hButtonS1, SW_HIDE);
				ShowWindow(hButtonS2, SW_HIDE);
				ShowWindow(hButtonT2, SW_HIDE);
				ShowWindow(hButtonT8, SW_HIDE);
				ShowWindow(hButtonT16, SW_HIDE);
				ShowWindow(hButtonL, SW_HIDE);
				ShowWindow(hInputBoxA, SW_HIDE);
				ShowWindow(hInputBoxCF1, SW_HIDE);
				ShowWindow(hInputBoxCF2, SW_HIDE);
				ShowWindow(hInputBoxIF1, SW_HIDE);
				ShowWindow(hInputBoxIF2, SW_HIDE);
				ShowWindow(hInputBoxIF3, SW_HIDE);
				ShowWindow(hInputBoxS1, SW_HIDE);
				ShowWindow(hInputBoxS2, SW_HIDE);
				ShowWindow(hInputBoxC, SW_HIDE);
				ShowWindow(hInputBoxL1, SW_HIDE);
				ShowWindow(hInputBoxL2, SW_HIDE);
				ShowWindow(hInputBoxL3, SW_HIDE);
				ShowWindow(hInputBoxL4, SW_HIDE);
				ShowWindow(hOutputBoxA, SW_HIDE);
				ShowWindow(hOutputBoxCF, SW_HIDE);
				ShowWindow(hOutputBoxIF, SW_HIDE);
				ShowWindow(hOutputBoxS1, SW_HIDE);
				ShowWindow(hOutputBoxS2, SW_HIDE);
				ShowWindow(hOutputBoxC, SW_HIDE);
				ShowWindow(hOutputBoxL, SW_HIDE);
				ShowWindow(hCF, SW_HIDE);
				ShowWindow(hIF, SW_HIDE);
				ShowWindow(hS1, SW_HIDE);
				ShowWindow(hS2, SW_HIDE);
				ShowWindow(hT2, SW_HIDE);
				ShowWindow(hT8, SW_HIDE);
				ShowWindow(hT16, SW_HIDE);

				ShowWindow(hButtonCF, SW_SHOW);
				ShowWindow(hInputBoxCF1, SW_SHOW);
				ShowWindow(hInputBoxCF2, SW_SHOW);
				ShowWindow(hOutputBoxCF, SW_SHOW);
				SetWindowText(hInputBoxCF1, TEXT("请在此输入函数，自变量请用小写x"));
				SetWindowText(hInputBoxCF2, TEXT("请在此输入自变量x的值"));
			}
			break;
		}
		
		case 322://IF
		{
			if (SendMessage(hIF, BM_GETCHECK, 0, 0) == BST_CHECKED)
			{
				ShowWindow(hButtonA, SW_HIDE);
				ShowWindow(hButtonCF, SW_HIDE);
				ShowWindow(hButtonIF, SW_HIDE);
				ShowWindow(hButtonS1, SW_HIDE);
				ShowWindow(hButtonS2, SW_HIDE);
				ShowWindow(hButtonT2, SW_HIDE);
				ShowWindow(hButtonT8, SW_HIDE);
				ShowWindow(hButtonT16, SW_HIDE);
				ShowWindow(hButtonL, SW_HIDE);
				ShowWindow(hInputBoxA, SW_HIDE);
				ShowWindow(hInputBoxCF1, SW_HIDE);
				ShowWindow(hInputBoxCF2, SW_HIDE);
				ShowWindow(hInputBoxIF1, SW_HIDE);
				ShowWindow(hInputBoxIF2, SW_HIDE);
				ShowWindow(hInputBoxIF3, SW_HIDE);
				ShowWindow(hInputBoxS1, SW_HIDE);
				ShowWindow(hInputBoxS2, SW_HIDE);
				ShowWindow(hInputBoxC, SW_HIDE);
				ShowWindow(hInputBoxL1, SW_HIDE);
				ShowWindow(hInputBoxL2, SW_HIDE);
				ShowWindow(hInputBoxL3, SW_HIDE);
				ShowWindow(hInputBoxL4, SW_HIDE);
				ShowWindow(hOutputBoxA, SW_HIDE);
				ShowWindow(hOutputBoxCF, SW_HIDE);
				ShowWindow(hOutputBoxIF, SW_HIDE);
				ShowWindow(hOutputBoxS1, SW_HIDE);
				ShowWindow(hOutputBoxS2, SW_HIDE);
				ShowWindow(hOutputBoxC, SW_HIDE);
				ShowWindow(hOutputBoxL, SW_HIDE);
				ShowWindow(hCF, SW_HIDE);
				ShowWindow(hIF, SW_HIDE);
				ShowWindow(hS1, SW_HIDE);
				ShowWindow(hS2, SW_HIDE);
				ShowWindow(hT2, SW_HIDE);
				ShowWindow(hT8, SW_HIDE);
				ShowWindow(hT16, SW_HIDE); 
				
				ShowWindow(hButtonIF, SW_SHOW);
				ShowWindow(hInputBoxIF1, SW_SHOW);
				ShowWindow(hInputBoxIF2, SW_SHOW);
				ShowWindow(hInputBoxIF3, SW_SHOW);
				ShowWindow(hOutputBoxIF, SW_SHOW);
				SetWindowText(hInputBoxIF1, TEXT("请在此输入函数，自变量请用小写x"));
				SetWindowText(hInputBoxIF2, TEXT("请在此输入积分上限"));
				SetWindowText(hInputBoxIF3, TEXT("请在此输入积分下限"));
			}
			break;
		} 
		case 33://Sta
		{
			if (SendMessage(hSta, BM_GETCHECK, 0, 0) == BST_CHECKED)
			{
				ShowWindow(hS1, SW_SHOW);
				ShowWindow(hS2, SW_SHOW);
				//ShowWindow(hsSta, SW_SHOW);
				ShowWindow(hCF, SW_HIDE);
				ShowWindow(hIF, SW_HIDE);
				ShowWindow(hT2, SW_HIDE);
				ShowWindow(hT8, SW_HIDE);
				ShowWindow(hT16, SW_HIDE);
				//ShowWindow(hsFun, SW_HIDE);
				//ShowWindow(hsCon, SW_HIDE);
			}
			break;
		}
		
		case 331://S1
		{
			if (SendMessage(hS1, BM_GETCHECK, 0, 0) == BST_CHECKED)
			{
				ShowWindow(hButtonA, SW_HIDE);
				ShowWindow(hButtonCF, SW_HIDE);
				ShowWindow(hButtonIF, SW_HIDE);
				ShowWindow(hButtonS1, SW_HIDE);
				ShowWindow(hButtonS2, SW_HIDE);
				ShowWindow(hButtonT2, SW_HIDE);
				ShowWindow(hButtonT8, SW_HIDE);
				ShowWindow(hButtonT16, SW_HIDE);
				ShowWindow(hButtonL, SW_HIDE);
				ShowWindow(hInputBoxA, SW_HIDE);
				ShowWindow(hInputBoxCF1, SW_HIDE);
				ShowWindow(hInputBoxCF2, SW_HIDE);
				ShowWindow(hInputBoxIF1, SW_HIDE);
				ShowWindow(hInputBoxIF2, SW_HIDE);
				ShowWindow(hInputBoxIF3, SW_HIDE);
				ShowWindow(hInputBoxS1, SW_HIDE);
				ShowWindow(hInputBoxS2, SW_HIDE);
				ShowWindow(hInputBoxC, SW_HIDE);
				ShowWindow(hInputBoxL1, SW_HIDE);
				ShowWindow(hInputBoxL2, SW_HIDE);
				ShowWindow(hInputBoxL3, SW_HIDE);
				ShowWindow(hInputBoxL4, SW_HIDE);
				ShowWindow(hOutputBoxA, SW_HIDE);
				ShowWindow(hOutputBoxCF, SW_HIDE);
				ShowWindow(hOutputBoxIF, SW_HIDE);
				ShowWindow(hOutputBoxS1, SW_HIDE);
				ShowWindow(hOutputBoxS2, SW_HIDE);
				ShowWindow(hOutputBoxC, SW_HIDE);
				ShowWindow(hOutputBoxL, SW_HIDE);
				ShowWindow(hCF, SW_HIDE);
				ShowWindow(hIF, SW_HIDE);
				ShowWindow(hS1, SW_HIDE);
				ShowWindow(hS2, SW_HIDE);
				ShowWindow(hT2, SW_HIDE);
				ShowWindow(hT8, SW_HIDE);
				ShowWindow(hT16, SW_HIDE);

				ShowWindow(hButtonS1, SW_SHOW);
				ShowWindow(hInputBoxS1, SW_SHOW);
				ShowWindow(hOutputBoxS1, SW_SHOW);
				SetWindowText(hInputBoxS1, TEXT("请在此输入变量,变量之间由逗号隔开"));
			}
			break;
		}
	

		case 332://S2
		{
			if (SendMessage(hS2, BM_GETCHECK, 0, 0) == BST_CHECKED)
			{
				ShowWindow(hButtonA, SW_HIDE);
				ShowWindow(hButtonCF, SW_HIDE);
				ShowWindow(hButtonIF, SW_HIDE);
				ShowWindow(hButtonS1, SW_HIDE);
				ShowWindow(hButtonS2, SW_HIDE);
				ShowWindow(hButtonT2, SW_HIDE);
				ShowWindow(hButtonT8, SW_HIDE);
				ShowWindow(hButtonT16, SW_HIDE);
				ShowWindow(hButtonL, SW_HIDE);
				ShowWindow(hInputBoxA, SW_HIDE);
				ShowWindow(hInputBoxCF1, SW_HIDE);
				ShowWindow(hInputBoxCF2, SW_HIDE);
				ShowWindow(hInputBoxIF1, SW_HIDE);
				ShowWindow(hInputBoxIF2, SW_HIDE);
				ShowWindow(hInputBoxIF3, SW_HIDE);
				ShowWindow(hInputBoxS1, SW_HIDE);
				ShowWindow(hInputBoxS2, SW_HIDE);
				ShowWindow(hInputBoxC, SW_HIDE);
				ShowWindow(hInputBoxL1, SW_HIDE);
				ShowWindow(hInputBoxL2, SW_HIDE);
				ShowWindow(hInputBoxL3, SW_HIDE);
				ShowWindow(hInputBoxL4, SW_HIDE);
				ShowWindow(hOutputBoxA, SW_HIDE);
				ShowWindow(hOutputBoxCF, SW_HIDE);
				ShowWindow(hOutputBoxIF, SW_HIDE);
				ShowWindow(hOutputBoxS1, SW_HIDE);
				ShowWindow(hOutputBoxS2, SW_HIDE);
				ShowWindow(hOutputBoxC, SW_HIDE);
				ShowWindow(hOutputBoxL, SW_HIDE);
				ShowWindow(hCF, SW_HIDE);
				ShowWindow(hIF, SW_HIDE);
				ShowWindow(hS1, SW_HIDE);
				ShowWindow(hS2, SW_HIDE);
				ShowWindow(hT2, SW_HIDE);
				ShowWindow(hT8, SW_HIDE);
				ShowWindow(hT16, SW_HIDE); 
				
				ShowWindow(hButtonS2, SW_SHOW);
				ShowWindow(hInputBoxS1, SW_SHOW);
				ShowWindow(hInputBoxS2, SW_SHOW);
				ShowWindow(hOutputBoxS2, SW_SHOW);
				SetWindowText(hInputBoxS1, TEXT("请在此输入第一组变量,变量之间由逗号隔开"));
				SetWindowText(hInputBoxS2, TEXT("请在此输入第二组变量,变量之间由逗号隔开"));
			}
			break;
		} 

		case 34://Con
		{
			if (SendMessage(hCon, BM_GETCHECK, 0, 0) == BST_CHECKED)
			{
				ShowWindow(hCF, SW_HIDE);
				ShowWindow(hIF, SW_HIDE);
				ShowWindow(hS1, SW_HIDE);
				ShowWindow(hS2, SW_HIDE);
				ShowWindow(hT2, SW_SHOW);
				ShowWindow(hT8, SW_SHOW);
				ShowWindow(hT16, SW_SHOW);
			}
			break;
		}

		case 341://T2
		{
			if (SendMessage(hT2, BM_GETCHECK, 0, 0) == BST_CHECKED)
			{
				ShowWindow(hButtonA, SW_HIDE);
				ShowWindow(hButtonCF, SW_HIDE);
				ShowWindow(hButtonIF, SW_HIDE);
				ShowWindow(hButtonS1, SW_HIDE);
				ShowWindow(hButtonS2, SW_HIDE);
				ShowWindow(hButtonT2, SW_HIDE);
				ShowWindow(hButtonT8, SW_HIDE);
				ShowWindow(hButtonT16, SW_HIDE);
				ShowWindow(hButtonL, SW_HIDE);
				ShowWindow(hInputBoxA, SW_HIDE);
				ShowWindow(hInputBoxCF1, SW_HIDE);
				ShowWindow(hInputBoxCF2, SW_HIDE);
				ShowWindow(hInputBoxIF1, SW_HIDE);
				ShowWindow(hInputBoxIF2, SW_HIDE);
				ShowWindow(hInputBoxIF3, SW_HIDE);
				ShowWindow(hInputBoxS1, SW_HIDE);
				ShowWindow(hInputBoxS2, SW_HIDE);
				ShowWindow(hInputBoxC, SW_HIDE);
				ShowWindow(hInputBoxL1, SW_HIDE);
				ShowWindow(hInputBoxL2, SW_HIDE);
				ShowWindow(hInputBoxL3, SW_HIDE);
				ShowWindow(hInputBoxL4, SW_HIDE);
				ShowWindow(hOutputBoxA, SW_HIDE);
				ShowWindow(hOutputBoxCF, SW_HIDE);
				ShowWindow(hOutputBoxIF, SW_HIDE);
				ShowWindow(hOutputBoxS1, SW_HIDE);
				ShowWindow(hOutputBoxS2, SW_HIDE);
				ShowWindow(hOutputBoxC, SW_HIDE);
				ShowWindow(hOutputBoxL, SW_HIDE);
				ShowWindow(hCF, SW_HIDE);
				ShowWindow(hIF, SW_HIDE);
				ShowWindow(hS1, SW_HIDE);
				ShowWindow(hS2, SW_HIDE);
				ShowWindow(hT2, SW_HIDE);
				ShowWindow(hT8, SW_HIDE);
				ShowWindow(hT16, SW_HIDE); 
				
				ShowWindow(hButtonT2, SW_SHOW);
				ShowWindow(hInputBoxC, SW_SHOW);
				ShowWindow(hOutputBoxC, SW_SHOW);
				SetWindowText(hInputBoxC, TEXT("请在此输入"));
			}
			break;
		}
		case 342://T8
		{
			if (SendMessage(hT8, BM_GETCHECK, 0, 0) == BST_CHECKED)
			{
				ShowWindow(hButtonA, SW_HIDE);
				ShowWindow(hButtonCF, SW_HIDE);
				ShowWindow(hButtonIF, SW_HIDE);
				ShowWindow(hButtonS1, SW_HIDE);
				ShowWindow(hButtonS2, SW_HIDE);
				ShowWindow(hButtonT2, SW_HIDE);
				ShowWindow(hButtonT8, SW_HIDE);
				ShowWindow(hButtonT16, SW_HIDE);
				ShowWindow(hButtonL, SW_HIDE);
				ShowWindow(hInputBoxA, SW_HIDE);
				ShowWindow(hInputBoxCF1, SW_HIDE);
				ShowWindow(hInputBoxCF2, SW_HIDE);
				ShowWindow(hInputBoxIF1, SW_HIDE);
				ShowWindow(hInputBoxIF2, SW_HIDE);
				ShowWindow(hInputBoxIF3, SW_HIDE);
				ShowWindow(hInputBoxS1, SW_HIDE);
				ShowWindow(hInputBoxS2, SW_HIDE);
				ShowWindow(hInputBoxC, SW_HIDE);
				ShowWindow(hInputBoxL1, SW_HIDE);
				ShowWindow(hInputBoxL2, SW_HIDE);
				ShowWindow(hInputBoxL3, SW_HIDE);
				ShowWindow(hInputBoxL4, SW_HIDE);
				ShowWindow(hOutputBoxA, SW_HIDE);
				ShowWindow(hOutputBoxCF, SW_HIDE);
				ShowWindow(hOutputBoxIF, SW_HIDE);
				ShowWindow(hOutputBoxS1, SW_HIDE);
				ShowWindow(hOutputBoxS2, SW_HIDE);
				ShowWindow(hOutputBoxC, SW_HIDE);
				ShowWindow(hOutputBoxL, SW_HIDE);
				ShowWindow(hCF, SW_HIDE);
				ShowWindow(hIF, SW_HIDE);
				ShowWindow(hS1, SW_HIDE);
				ShowWindow(hS2, SW_HIDE);
				ShowWindow(hT2, SW_HIDE);
				ShowWindow(hT8, SW_HIDE);
				ShowWindow(hT16, SW_HIDE); 
				
				ShowWindow(hButtonT8, SW_SHOW);
				ShowWindow(hInputBoxC, SW_SHOW);
				ShowWindow(hOutputBoxC, SW_SHOW);
				SetWindowText(hInputBoxC, TEXT("请在此输入"));
			}
			break;
		}

		case 343://T16
		{
			if (SendMessage(hT16, BM_GETCHECK, 0, 0) == BST_CHECKED)
			{
				ShowWindow(hButtonA, SW_HIDE);
				ShowWindow(hButtonCF, SW_HIDE);
				ShowWindow(hButtonIF, SW_HIDE);
				ShowWindow(hButtonS1, SW_HIDE);
				ShowWindow(hButtonS2, SW_HIDE);
				ShowWindow(hButtonT2, SW_HIDE);
				ShowWindow(hButtonT8, SW_HIDE);
				ShowWindow(hButtonT16, SW_HIDE);
				ShowWindow(hButtonL, SW_HIDE);
				ShowWindow(hInputBoxA, SW_HIDE);
				ShowWindow(hInputBoxCF1, SW_HIDE);
				ShowWindow(hInputBoxCF2, SW_HIDE);
				ShowWindow(hInputBoxIF1, SW_HIDE);
				ShowWindow(hInputBoxIF2, SW_HIDE);
				ShowWindow(hInputBoxIF3, SW_HIDE);
				ShowWindow(hInputBoxS1, SW_HIDE);
				ShowWindow(hInputBoxS2, SW_HIDE);
				ShowWindow(hInputBoxC, SW_HIDE);
				ShowWindow(hInputBoxL1, SW_HIDE);
				ShowWindow(hInputBoxL2, SW_HIDE);
				ShowWindow(hInputBoxL3, SW_HIDE);
				ShowWindow(hInputBoxL4, SW_HIDE);
				ShowWindow(hOutputBoxA, SW_HIDE);
				ShowWindow(hOutputBoxCF, SW_HIDE);
				ShowWindow(hOutputBoxIF, SW_HIDE);
				ShowWindow(hOutputBoxS1, SW_HIDE);
				ShowWindow(hOutputBoxS2, SW_HIDE);
				ShowWindow(hOutputBoxC, SW_HIDE);
				ShowWindow(hOutputBoxL, SW_HIDE);
				ShowWindow(hCF, SW_HIDE);
				ShowWindow(hIF, SW_HIDE);
				ShowWindow(hS1, SW_HIDE);
				ShowWindow(hS2, SW_HIDE);
				ShowWindow(hT2, SW_HIDE);
				ShowWindow(hT8, SW_HIDE);
				ShowWindow(hT16, SW_HIDE); 
				
				ShowWindow(hButtonT16, SW_SHOW);
				ShowWindow(hInputBoxC, SW_SHOW);
				ShowWindow(hOutputBoxC, SW_SHOW);
				SetWindowText(hInputBoxC, TEXT("请在此输入"));
			}
			break;
		}

		case 35://Lin
		{
			if (SendMessage(hLin, BM_GETCHECK, 0, 0) == BST_CHECKED)
			{
				ShowWindow(hButtonA, SW_HIDE);
				ShowWindow(hButtonCF, SW_HIDE);
				ShowWindow(hButtonIF, SW_HIDE);
				ShowWindow(hButtonS1, SW_HIDE);
				ShowWindow(hButtonS2, SW_HIDE);
				ShowWindow(hButtonT2, SW_HIDE);
				ShowWindow(hButtonT8, SW_HIDE);
				ShowWindow(hButtonT16, SW_HIDE);
				ShowWindow(hButtonL, SW_HIDE);
				ShowWindow(hInputBoxA, SW_HIDE);
				ShowWindow(hInputBoxCF1, SW_HIDE);
				ShowWindow(hInputBoxCF2, SW_HIDE);
				ShowWindow(hInputBoxIF1, SW_HIDE);
				ShowWindow(hInputBoxIF2, SW_HIDE);
				ShowWindow(hInputBoxIF3, SW_HIDE);
				ShowWindow(hInputBoxS1, SW_HIDE);
				ShowWindow(hInputBoxS2, SW_HIDE);
				ShowWindow(hInputBoxC, SW_HIDE);
				ShowWindow(hInputBoxL1, SW_HIDE);
				ShowWindow(hInputBoxL2, SW_HIDE);
				ShowWindow(hInputBoxL3, SW_HIDE);
				ShowWindow(hInputBoxL4, SW_HIDE);
				ShowWindow(hOutputBoxA, SW_HIDE);
				ShowWindow(hOutputBoxCF, SW_HIDE);
				ShowWindow(hOutputBoxIF, SW_HIDE);
				ShowWindow(hOutputBoxS1, SW_HIDE);
				ShowWindow(hOutputBoxS2, SW_HIDE);
				ShowWindow(hOutputBoxC, SW_HIDE);
				ShowWindow(hOutputBoxL, SW_HIDE);
				ShowWindow(hCF, SW_HIDE);
				ShowWindow(hIF, SW_HIDE);
				ShowWindow(hS1, SW_HIDE);
				ShowWindow(hS2, SW_HIDE);
				ShowWindow(hT2, SW_HIDE);
				ShowWindow(hT8, SW_HIDE);
				ShowWindow(hT16, SW_HIDE); 

				ShowWindow(hButtonL, SW_SHOW);
				ShowWindow(hInputBoxL1, SW_SHOW);
				ShowWindow(hInputBoxL2, SW_SHOW);
				ShowWindow(hInputBoxL3, SW_SHOW);
				ShowWindow(hInputBoxL4, SW_SHOW);
				ShowWindow(hOutputBoxL, SW_SHOW);
				SetWindowText(hInputBoxL1, TEXT("请在此输入系数矩阵阶数"));
				SetWindowText(hInputBoxL2, TEXT("请在此输如系数矩阵元素,元素之间由逗号隔开"));
				SetWindowText(hInputBoxL3, TEXT("请在此输入等号右边的矩阵元素，元素之间由逗号隔开."));
				SetWindowText(hInputBoxL4, TEXT("x[n]中n的值"));
			}
			break;
		}

		case 20://普通计算
		{
			GetWindowText(hInputBoxA, szInputBox1, 300);//After clicking, save the contents of the InputBox to the array szInputBox[300].
			char a[200];
			TCHARTochar(szInputBox1, a, 100);
			function = a;
			if (findFalse1(function) && findFalse2(function))
			{
				res = Calculate(function);
				swprintf(szInputBox1, L"%f", res);
				SetWindowText(hOutputBoxA, szInputBox1);
				break;
			}
			else
			{
				MessageBox(hWnd, TEXT("错误"), TEXT("Warning"), MB_ICONINFORMATION);
				break;
			}
			break;
		}

		case 21://函数
		{
			GetWindowText(hInputBoxCF1, szInputBox1, 300);
			GetWindowText(hInputBoxCF2, szInputBox2, 300);
			char a[200];
			TCHARTochar(szInputBox1, a, 100);
			char a1[200];
			TCHARTochar(szInputBox2, a1, 100);
			function = a;
			value = a1;
			res = calculateFunction(function, value);
			swprintf(szInputBox1, L"%f", res);
			SetWindowText(hOutputBoxCF, szInputBox1);
			break;
		}

		case 22://积分
		{
			GetWindowText(hInputBoxIF1, szInputBox1, 300);
			GetWindowText(hInputBoxIF2, szInputBox2, 300);
			GetWindowText(hInputBoxIF3, szInputBox3, 300);
			char a[200];
			TCHARTochar(szInputBox1, a, 100);
			char a1[200];
			TCHARTochar(szInputBox2, a1, 100);
			char a2[200];
			TCHARTochar(szInputBox3, a2, 100);
			function = a;
			down = a1;
			up = a2;
			res = integrateFunction(function, down, up);
			swprintf(szInputBox1, L"%f", res);
			SetWindowText(hOutputBoxIF, szInputBox1);
			break;
		}

		case 23://单变量统计
		{
			GetWindowText(hInputBoxS1, szInputBox1, 300);

			char a[200];

			TCHARTochar(szInputBox1, a, 100);
			function1 = a;

			statisticsVariable1(function1, &avg, &s2, &sigma, &barsigma);
			swprintf(szInputBox1, L"平均数为 % 4lf\n方差为 %4lf\n标准差为 %2lf\n算术平均值的标准差为 %2lf\n", avg, s2, sigma, barsigma);
			SetWindowText(hOutputBoxS1, szInputBox1);
			break;
		}

		case 24://双变量统计
		{
			GetWindowText(hInputBoxS1, szInputBox1, 300);
			GetWindowText(hInputBoxS2, szInputBox2, 300);

			char a[200];
			char b[200];

			TCHARTochar(szInputBox1, a, 100);
			function1 = a;
			TCHARTochar(szInputBox2, b, 100);
			function2 = b;
			statisticsVariable2(function1, function2, &avgx, &avgy, &s2x, &s2y, &sigmax, &sigmay, &barsigmax, &barsigmay, &sigmaA, &sigmaB, &r, &a1, &b1);
			swprintf(szInputBox1, L"x的平均数为 % 4lf\nx的方差为 %4lf\nx的标准差为 %2lf\nx的算术平均值的标准差为 %2lf\ny的平均数为 % 4lf\ny的方差为 %4lf\ny的标准差为 %2lf\ny的算术平均值的标准差为 %2lf\n回归方程为 y = %2lfx + (%2lf) r为 %2lf\na,b的不确定度为 %2lf %2lf", avgx, s2x, sigmax, barsigmax, avgy, s2y, sigmay, barsigmay, b1, a1, r, sigmaA, sigmaB);
			SetWindowText(hOutputBoxS2, szInputBox1);
			break;
		}

		case 25://转2
		{
			GetWindowText(hInputBoxC, szInputBox1, 300);
			char a[200];
			TCHARTochar(szInputBox1, a, 100);
			function = a;
			res = translate2(function);
			swprintf(szInputBox1, L"%f", res);
			SetWindowText(hOutputBoxC, szInputBox1);
			break;
		}

		case 26://转8
		{
			GetWindowText(hInputBoxC, szInputBox1, 300);
			char a[200];
			TCHARTochar(szInputBox1, a, 100);
			function = a;
			res = translate8(function);
			swprintf(szInputBox1, L"%f", res);
			SetWindowText(hOutputBoxC, szInputBox1);
			break;
		}

		case 27://转16
		{
			GetWindowText(hInputBoxC, szInputBox1, 300);
			char a[200];
			TCHARTochar(szInputBox1, a, 100);
			function = a;
			function = translate16(function);
			for (int j = 0; j < function.size(); j++)
			{
				a[j] = function[j];
			}
			TCHARTochar(szInputBox1, a, 100);
			SetWindowText(hOutputBoxC, szInputBox1);
			break;
		}

		case 28://线性方程
		{
			GetWindowText(hInputBoxL1, szInputBox1, 300);
			GetWindowText(hInputBoxL2, szInputBox2, 300);
			GetWindowText(hInputBoxL3, szInputBox3, 300);
			GetWindowText(hInputBoxL4, szInputBox4, 300);
			char a[200];
			TCHARTochar(szInputBox1, a, 100);
			function1 = a;
			char b[200];
			TCHARTochar(szInputBox2, b, 100);
			function2 = b;
			char c[200];
			TCHARTochar(szInputBox3, c, 100);
			function3 = c;
			char e[200];
			TCHARTochar(szInputBox4, e, 100);
			function = e;
			double d[200];
			k = (int)changeStringtofloat(function1);
			linearalgebra(k, function2, function3, d);
			int n = 0;
			n = (int)changeStringtofloat(function) - 1;
			swprintf(szInputBox1, L"%f", d[n]);
			SetWindowText(hOutputBoxL, szInputBox1);
		}



		/***********The stored results are analyzed, calculated and stored in szOutputBox[300]*************/

		//wsprintf(Data, TEXT("计算结果：%s \r\n "), szOutputBox);
		//MessageBox(hWnd, Data, TEXT("信息提示"), MB_ICONINFORMATION);

		default:
			//Messages that are not processed must be handled by DefWindowProc。
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT://The window is redrawn
		hdc = BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		return 0;
		
		
		break;

	case WM_DESTROY://The window is detroyed
		DeleteObject(hBrush); 
		DeleteObject(hFont);
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}



void TCHARTochar(const wchar_t *wchar, char *chr, int length)
{
	WideCharToMultiByte(CP_ACP, 0, wchar, -1,
		chr, length, NULL, NULL);
}

int Priority(char x)
{
	switch (x)
	{
	case '+':
		return 1;
		break;
	case'-':
		return 1;
		break;
	case'*':
		return 2;
		break;
	case'/':
		return 2;
		break;
	case'^':
		return 3;
		break;
	case's':
		return 0;
		break;
	case'c':
		return 0;
		break;
	case't':
		return 0;
		break;
	}
}//Determine operator priority, it will be used in Polish algorithm
float changeStringtofloat(string m)
{
	float res = 0;
	string s1, s2;//If the string has a dot, divide it into two strings according to the dot's place
	int x;
	for (int i = 0; m[i] != '.' && i < m.size(); i++)
	{
		s1 = s1 + m[i];
	}
	for (int i = s1.size() + 1; i < m.size(); i++)
	{
		s2 = s2 + m[i];
	}
	for (int i = 0; i < s1.size(); i++)
	{
		res = res + ((float)s1[i] - 48) * pow(10, s1.size() - i - 1);
		/*Fetch every lement of s1 which is a char and change it to a float and multply it by the power of 10.
		for example, 23 = 2*10^1 + 3*10^0 */
	}
	for (int i = 1; i <= s2.size(); i++)
	{
		res = res + ((float)s2[i - 1] - 48) * pow(10, -i);
		/*0.23 = 3*10^(-2) + 2*10^(-1)*/
	}
	return res;
}
//Convert a string variable to a float variable
string changeFloattostring(float exp)
{
	/*It is the reverse process of changeFloattostring function*/
	string res;
	char x;
	int y;
	for (float i = 100; i / 0.000001 >= 1; i = i / 10)
	{
		y = (int)(exp / i);
		exp = exp - y * i;
		x = (char)(y + 48);
		if (i == 1)
			res = res + x + '.';
		else
			res = res + x;
	}
	return res;
}//convert a float to string, making it easy to be pushed into stacks
char changeStringtochar(string m)
{
	char x;
	x = m[0];
	return x;
}

string connectNumber(string str, int i)
{
	int j = i;
	string m;
	for (j; str[j] == '0' || str[j] == '1' || str[j] == '2' || str[j] == '3' || str[j] == '4' || str[j] == '5' || str[j] == '6' || str[j] == '7' || str[j] == '8' || str[j] == '9' || str[j] == '.'; j++)
	{
		m = m + str[j];
		if (j == str.size() - 1)
			break;
	}
	return m;
}
/*Determines operator priority to join Numbers.When traversing an operational expression,
only 2 and 4 are read for 24, which this function can link to 24*/
int lengthofNumber(string str)
{
	/*Change 'sin' to 's' in order to compare the Priority*/
	int len = str.size();
	return len;
}
string connectSymbol(string str, int i)
{
	int j = i;
	string m;
	for (j; str[j] != '0' && str[j] != '1' && str[j] != '2' && str[j] != '3' && str[j] != '4' && str[j] != '5' && str[j] != '6' && str[j] != '7' && str[j] != '8' && str[j] != '9' && str[j] != '(' && str[j] != ')'; j++)
	{
		m = m + str[j];
		if (j == str.size() - 1)
			break;
	}
	return m;
}//connect operators, such as connecting 's' 'i' 'n' to 'sin'

void Polish(stack<string> &number, stack<string> &symbol, string str)
{
	for (int i = 0; i < str.size(); i++)
	{
		/*This circulation is to nifix expression to postfix expression*/
		if (str[i] == '0' || str[i] == '1' || str[i] == '2' || str[i] == '3' || str[i] == '4' || str[i] == '5' || str[i] == '6' || str[i] == '7' || str[i] == '8' || str[i] == '9')
		{
			/*Numbers are pushed into Number stack directly*/
			string s1;
			s1 = connectNumber(str, i);                                                                                                                                                                                                                                number
				; number.push(s1);
			i = i + lengthofNumber(s1) - 1;
			continue;
		}
		if (str[i] == '(')
		{
			/*'(' is pushed into Symbol stack directly*/
			string s2;
			s2 = s2 + str[i];//Change char(str[i]) to string(s2) and then it can be pushed into the stack
			symbol.push(s2);
			continue;
		}
		if (str[i] == ')')
		{
			/*When a close parenthesis is entered, pop all operators in the symbol stack onto the number stack until an open parenthesis is encountered*/
			for (int i = 0; changeStringtochar(symbol.top()) != '('; i++)
			{
				number.push(symbol.top());
				symbol.pop();
			}
			continue;
		}
		else
		{
			/*Operatoers are pushed in Symbol stack*/
			if (symbol.empty())
			{
				str[i] = changeStringtochar(connectSymbol(str, i));//We don't push 'sin' but 's' so that it can be operated next easily
				string s3;
				s3 = s3 + str[i];
				i = i + connectSymbol(str, i).size() - 1;
				symbol.push(s3);
				continue;
			}
			else
			{
				if (changeStringtochar(symbol.top()) == '(')
				{
					/*Push all elements in Symbol stack between '(' and ')' into Number stack */
					str[i] = changeStringtochar(connectSymbol(str, i));
					string s4;
					s4 = s4 + str[i];
					i = i + connectSymbol(str, i).size() - 1;
					symbol.push(s4);
					continue;
				}

				if (Priority(str[i]) > Priority(changeStringtochar(symbol.top())))
				{
					str[i] = changeStringtochar(connectSymbol(str, i));
					string s5;
					s5 = s5 + str[i];
					i = i + connectSymbol(str, i).size() - 1;
					symbol.push(s5);
					continue;
				}
				else
				{
					/*If it is a common operator, and the top element of Symbol stack is an operator as well
					and the top operator has priority over it, then push all elements in Symbol stack into
					Number stack in order until Symbol stack is empty or the top element is ‘(’ or the it
					has priority over the top operator.*/
					for (int j = 0; Priority(str[i]) <= Priority(changeStringtochar(symbol.top())); j++)
					{
						number.push(symbol.top());
						symbol.pop();
						if (symbol.empty())
							break;
					}
					str[i] = changeStringtochar(connectSymbol(str, i));
					string s6;
					s6 = s6 + str[i];
					i = i + connectSymbol(str, i).size() - 1;
					symbol.push(s6);
				}
			}
		}
	}
	/*The rest elements are also pushed into Number stack */
	for (int j = 0; !symbol.empty(); j++)
	{
		number.push(symbol.top());
		symbol.pop();;
	}

}//Convert an infix expression to a postfix expression, which is stored in Number stack in the end
void Function(stack<float> &calculator, stack<string> &temporary)
{
	float cal;
	float m, n;
	string s;
	for (int i = 0; !temporary.empty(); i++)
	{
		switch (changeStringtochar(temporary.top()))
		{
		case'+':
		{
			/*Fetch the top two elemnets in Calculator stack and operate it according to the operator*/
			m = calculator.top();
			calculator.pop();
			n = calculator.top();
			calculator.pop();
			cal = m + n;
			calculator.push(cal);
			break;
		}
		case'-':
		{
			m = calculator.top();
			calculator.pop();
			n = calculator.top();
			calculator.pop();
			cal = n - m;
			calculator.push(cal);
			break;
		}
		case'*':
		{
			m = calculator.top();
			calculator.pop();
			n = calculator.top();
			calculator.pop();
			cal = m * n;
			calculator.push(cal);
			break;
		}
		case'/':
		{
			m = calculator.top();
			calculator.pop();
			n = calculator.top();
			calculator.pop();
			cal = n / m;
			calculator.push(cal);
			break;
		}
		case's':
		{
			m = calculator.top();
			calculator.pop();
			cal = sin(m);
			calculator.push(cal);
			break;
		}
		case'c':
		{
			m = calculator.top();
			calculator.pop();
			cal = cos(m);
			calculator.push(cal);
			break;
		}
		case't':
		{
			m = calculator.top();
			calculator.pop();
			cal = tan(m);
			calculator.push(cal);
			break;
		}
		case'^':
		{
			m = calculator.top();
			calculator.pop();
			n = calculator.top();
			calculator.pop();
			cal = pow(n, m);
			calculator.push(cal);
			break;
		}
		break;
		}
		break;
	}

}
float Calculate(string str)
{
	stack<float> calculator;
	stack<string> number;
	stack<string> symbol;
	stack<string> temporary;

	string x;

	Polish(number, symbol, str);

	/*Calculate the postfix expression in Number stack*/
	for (int i = 0; !number.empty(); i++)
	{
		temporary.push(number.top());
		number.pop();
	}
	for (int i = 0; !temporary.empty(); i++)
	{
		if (changeStringtochar(temporary.top()) == '0' || changeStringtochar(temporary.top()) == '1' || changeStringtochar(temporary.top()) == '2' || changeStringtochar(temporary.top()) == '3' || changeStringtochar(temporary.top()) == '4' || changeStringtochar(temporary.top()) == '5' || changeStringtochar(temporary.top()) == '6' || changeStringtochar(temporary.top()) == '7' || changeStringtochar(temporary.top()) == '8' || changeStringtochar(temporary.top()) == '9')
		{
			calculator.push(changeStringtofloat(temporary.top()));
			temporary.pop();
		}
		else
		{
			Function(calculator, temporary);
			temporary.pop();
		}
	}
	float res;
	res = calculator.top();
	return res;
}

/*Function operations*/
float calculateFunction(string function, string value)
{
	/*Value is what we want to substitute into*/
	string equation;
	float res;

	stack<string> s1;
	stack<string> s2;

	for (int i = 0; i < function.size(); i++)
	{
		/*Change all the 'x' in the function to value*/
		string m;
		m = m + function[i];
		s1.push(m);
	}
	for (int i = 0; !s1.empty(); i++)
	{
		s2.push(s1.top());
		s1.pop();
	}
	for (int i = 0; !s2.empty(); i++)
	{
		if (changeStringtochar(s2.top()) != 'x')//Change all the 'x' in the function to the value
		{
			equation = equation + s2.top();
			s2.pop();
		}
		else
		{
			equation = equation + value;
			s2.pop();
		}
	}//equation is a string, and it is an arithmetic operation
	res = Calculate(equation);
	return res;
}
float integrateFunction(string function, string down, string up)
{
	float res = 0;
	float fx;
	float dx = 0.001;//Like a infinitesimal
	for (float x = changeStringtofloat(down); x <= changeStringtofloat(up); x = x + dx)
	{
		/*Take advantage of the definition of definite integral*/
		string m = changeFloattostring(x);
		fx = calculateFunction(function, m);
		res = res + fx * dx;
	}
	return res;
}

/*Conversion of numbers*/
float translate2(string s)
{
	int m = 0;
	int equ;
	string str;
	stack<int> translator;
	equ = (int)(changeStringtofloat(s));

	int i = equ;
	int j = equ;

	while (1)
	{
		i = i / 2;
		j = j % 2;
		translator.push(j);
		j = i;
		m++;
		if (i == 0)
			break;
	}
	for (int k = 0; !translator.empty(); k++)
	{
		str = str + (char)(translator.top() + 48);
		translator.pop();
	}
	float res = changeStringtofloat(str);
	return res;

}
float translate8(string s)
{
	int m = 0;
	int equ;
	string str;
	stack<int> translator;

	equ = (int)(changeStringtofloat(s));
	int i = equ;
	int j = equ;

	while (1)
	{
		i = i / 8;
		j = j % 8;
		translator.push(j);
		j = i;
		m++;
		if (i == 0)
			break;
	}
	for (int k = 0; !translator.empty(); k++)
	{
		str = str + (char)(translator.top() + 48);
		translator.pop();
	}
	float res = changeStringtofloat(str);
	return res;
}
string translate16(string s)
{
	int m = 0;
	int equ;
	char tem;
	string res;
	stack<char> translator;

	equ = (int)(changeStringtofloat(s));
	int i = equ;
	int j = equ;

	while (1)
	{
		i = i / 16;
		j = j % 16;
		m++;
		if (j < 10)
		{
			tem = (char)(j + 48);
			translator.push(tem);
		}
		else
		{
			j = j % 10;
			tem = (char)(j + 48);
			switch (tem)
			{
			case'0':
				translator.push('A');
			case'1':
				translator.push('B');
			case'2':
				translator.push('C');
			case'3':
				translator.push('D');
			case'4':
				translator.push('E');
			case'5':
				translator.push('F');
			}
		}
		j = i;
		if (i == 0)
			break;
	}
	for (int k = 0; !translator.empty(); k++)
	{
		res = res + translator.top();
		translator.pop();
	}
	return res;
}

/*Statistics*/
void statisticsVariable1(string str, double* avg, double* s2, double* sigma, double* barsigma)
{
	Node* p;
	Node* head = NULL;
	int i = 0;
	for (i; i < str.size(); i++)
	{
		string s;
		s = s + connectNumber(str, i);
		i = i + s.size();
		double num = (double)changeStringtofloat(s);
		p = (Node*)malloc(sizeof(Node));
		p->value = num;
		p->pNext = NULL;
		// find the last

		Node* last = head;
		if (last)
		{
			while (last->pNext)
			{
				last = last->pNext;
			}
			last->pNext = p;
		}
		else
		{
			head = p;
		}
	}
	// Delete one of the list 
	// In this programme You must choose one item to delete, I suggest add a button to choose whether you want to delete one.
	double wrongvalue;
	// calculate average		
	double sum = 0;
	int cnt = 0;
	for (p = head; p; p = p->pNext)
	{
		sum = sum + p->value;
		cnt++;
	}
	*avg = sum / cnt;
	// calculate variance
	for (p = head; p; p = p->pNext)
	{
		(*s2) = (*s2) + (p->value - (*avg)) * (p->value - (*avg)) / cnt;
	}
	//calculate \sigma and \bar{sigma}
	*sigma = sqrt(cnt * (*s2) / (cnt - 1));
	*barsigma = sqrt((*s2) / (cnt - 1));
	//output the result	
}
void statisticsVariable2(string str1, string str2, double* avgx, double* avgy, double* s2x, double* s2y, double* sigmax, double* sigmay, double* barsigmax, double* barsigmay, double* sigmaA, double* sigmaB, double* r, double* a, double* b)
{
	// createlist
	Node2* head = NULL;
	Node2* p;

	for (int i = 0; i < str1.size(); i++)
	{
		double numx;
		string sx;
		sx = sx + connectNumber(str1, i);
		i = i + sx.size();
		p = (Node2*)malloc(sizeof(Node2));
		numx = (double)changeStringtofloat(sx);
		p->x = numx;
		p->next = NULL;
		//find the last
		Node2* last = head;
		if (last)
		{
			while (last->next)
			{
				last = last->next;
			}
			last->next = p;
		}
		else
		{
			head = p;
		}
	}
	int i = 0;
	for (p = head; p; p = p->next)
	{
		double numy;
		for (i; i < str2.size(); i++)
		{
			string sy;
			sy = sy + connectNumber(str2, i);
			i = i + sy.size() + 1;
			numy = (double)changeStringtofloat(sy);
			p->y = numy;
			break;
		}
	}
	//delete one list, the problem is the same as it for one variable.
	Node2* q;

	// calculate average
	double sumx = 0, sumy = 0;
	int cnt = 0;
	for (p = head; p; p = p->next)
	{
		sumx = sumx + p->x;
		sumy = sumy + p->y;
		cnt++;
	}
	(*avgx) = sumx / cnt;
	(*avgy) = sumy / cnt;
	double x = (*avgy);
	// claculate variance
	for (p = head; p; p = p->next)
	{
		(*s2x) = (*s2x) + (p->x - (*avgx))*(p->x - (*avgx)) / cnt;
		(*s2y) = (*s2y) + (p->y - (*avgy))*(p->y - (*avgy)) / cnt;
	}
	//calculate \sigma and \bar{sigma}
	(*sigmax) = sqrt(cnt*(*s2x) / (cnt - 1));
	(*barsigmax) = sqrt((*s2x) / (cnt - 1));
	(*sigmay) = sqrt(cnt*(*s2y) / (cnt - 1));
	(*barsigmay) = sqrt((*s2y) / (cnt - 1));
	// linear regression 
	double fenzi = 0, fenmu = 0, s = 0, u = 0;
	for (p = head; p; p = p->next)
	{
		fenzi = fenzi + (p->x - (*avgx)) * (p->y - (*avgy));
		fenmu = fenmu + (p->x - (*avgx)) * (p->x - (*avgx));
	}
	(*b) = fenzi / fenmu;
	(*a) = (*avgy) - (*b) * (*avgx);
	(*r) = fenzi / sqrt(((*s2x) * (*s2y) * cnt * cnt));
	for (p = head; p; p = p->next)
	{
		s = s + (p->y - (*a) - (*b) * (p->x))*(p->y - (*a) - (*b) * (p->x)) / (cnt - 2);
	}
	for (p = head; p; p = p->next)
	{
		u = u + 1 / cnt - (*avgx) * (p->x - (*avgx)) / ((*s2x) * cnt);
	}
	(*sigmaA) = s * sqrt(u);
	(*sigmaB) = (*b) * sqrt((1 / (*r) / (*r) - 1) / (cnt - 2));;
}

/*Linear equations*/
double det(double** a, int k) {
	double **b;
	int i, x, y;
	b = (double**)malloc((k - 1) * sizeof(double));
	for (i = 0; i < k - 1; ++i)
	{
		b[i] = (double*)malloc(sizeof(double)*(k - 1));
	}
	double sum = 0;
	if (k == 1) {
		for (i = 0; i < k - 1; ++i) {
			free(b[i]);
		}
		free(b);
		return a[0][0];
	}
	else if (k > 1)
	{
		for (i = 0; i < k; i++)
		{
			for (x = 0; x < k - 1; x++)
			{
				for (y = 0; y < k - 1; y++)
				{
					if (y < i)
						b[x][y] = a[x + 1][y];
					else
						b[x][y] = a[x + 1][y + 1];
				}
			}
			sum = sum + det(b, k - 1)*a[0][i] * pow(-1, i);
		}
		for (i = 0; i < k - 1; ++i) {
			free(b[i]);
		}
		free(b);
		return sum;
	}
	else {
		printf("Illegal input!");
		for (i = 0; i < k - 1; ++i) {
			free(b[i]);
		}
		free(b);
		return 0;
	}

}
void linearalgebra(int k, string str2, string str3, double* c)
{
	int i, x, y;
	int j = 0;
	int l = 0;
	double **a;
	a = (double**)malloc(k * sizeof(double*));
	for (i = 0; i < k; i++)
	{
		a[i] = (double*)malloc(sizeof(double)*k);
	}
	for (x = 0; x < k; x++)
	{
		for (y = 0; y < k; y++)
		{
			a[x][y] = (double)changeStringtofloat(connectNumber(str2, j));
			j = j + connectNumber(str2, j).size() + 1;
		}
	}
	double* b;

	b = (double*)malloc(sizeof(double)*k);
	for (i = 0; i < k; i++)
	{
		b[i] = (double)changeStringtofloat(connectNumber(str3, l));
		l = l + connectNumber(str3, l).size() + 1;
	}
	double **D;
	D = (double**)malloc(k * sizeof(double*));
	for (i = 0; i < k; i++)
	{
		D[i] = (double*)malloc(sizeof(double)*k);
	}
	if (det(a, k) != 0)
	{
		for (i = 0; i < k; i++)
		{
			for (x = 0; x < k; x++)
			{
				for (y = 0; y < k; y++)
				{
					if (y == i)
						D[x][y] = b[x];
					else
						D[x][y] = a[x][y];
				}
			}

			c[i] = det(D, k) / det(a, k);
			double tem = c[i];
		}
	}
	// free variables
}

/*Find false*/
bool findFalse1(string str)
{
	int right = 0;
	int left = 0;
	for (int i = 0; i < str.size(); i++)
	{
		if (str[i] == '(')
			right++;
		if (str[i] == ')')
			left++;
	}
	if (left != right)
		return false;
	else
		return true;
}
bool findFalse2(string str)
{
	int j = 0;
	for (j; j < str.size(); j++)
	{
		if (str[j] != '0' && str[j] != '1' && str[j] != '2' && str[j] != '3' && str[j] != '4' && str[j] != '5' && str[j] != '6' && str[j] != '7' && str[j] != '8' && str[j] != '9' && str[j] != '(' && str[j] != ')' && str[j] != 's' && str[j] != 'i' && str[j] != 'n' && str[j] != 'c' && str[j] != 'o' && str[j] != 't' && str[j] != 'a' && str[j + 1] != '0' && str[j + 1] != '1' && str[j + 1] != '2' && str[j + 1] != '3' && str[j + 1] != '4' && str[j + 1] != '5' && str[j + 1] != '6' && str[j + 1] != '7' && str[j + 1] != '8' && str[j + 1] != '9' && str[j + 1] != '(' && str[j + 1] != ')')
		{
			return false;
			continue;
		}
	}
	if (j == str.size() - 1)//If traverse is over and there are no false then return true
	{
		return true;
	}

}

