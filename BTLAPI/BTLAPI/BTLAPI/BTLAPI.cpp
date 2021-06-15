// BTLAPI.cpp : Defines the entry point for the application.
//
#pragma once
#include "framework.h"
#include "BTLAPI.h"
#include <vector> // vẽ đường thẳng
#include <xstring>
#include <string>
#include "SaveFile.h" // lưu file
// chọn màu (choose color)
#include <commdlg.h>
#include <CommCtrl.h>
//
#include "minwinbase.h"
#include "ReadFile.h" // đọc file

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
HWND hwndHinh[20], hwndMauNen[20], hwndMauVien[20], hwndGroupBox[20], hwndSize[20],hwndStyleBrush[5]; // đa điều khiển  
HWND hwndChonVien, hwndChonNen, hwndCurrentSize, hwndPencil, hwndEraser, vsCroll, stColor, valueColor,comboBox; // đơn điều khiển
//bảng màu
static COLORREF color[10] = { RGB(255, 255, 255) ,RGB(195, 195, 195),RGB(185, 122, 87) ,RGB(255, 174, 201) ,RGB(255, 201, 14) ,
RGB(239, 228, 176) ,  RGB(181, 230, 29) , RGB(153, 217, 234) , RGB(112, 146, 190) , RGB(200, 191, 231) };
//điều khiển canvas (khung để vẽ)
static HWND hwndDrawArea;
//số lượng nút
// ?
//int numShape = 15;
//int numMauVien = 15;
//int numMauNen = 15;
//int num = 15;
static HWND hwndMain;
//biến toàn cục
static int currentShape = 0;
static COLORREF currentMauNen = RGB(255, 255, 255);
static COLORREF currentMauVien = RGB(0, 0, 0);
static COLORREF currentSize = 1;
static HDC hdc;
static int xLeft = 0, yTop = 0, xRight = 0, yBottom = 0;
int exist = 0;
//?
//int Shape[100][5];
//cờ kiểm tra
BOOLEAN isDraw = false;
BOOLEAN isClick = false;
BOOLEAN isEraser = false;
BOOLEAN ischoosecolor = false;
BOOLEAN ischoosebordercolor = false;
//BOOLEAN isBucket = false;
static int sizetext = 1; //chữ hiển thị size
int start = 0;
// chuyển chỉ số vào phần hiển thị màu
int colorIndex = 0;
int colorboderIndex = 0;

//
//HDC temp_hdc;
//HWND temp_hWnd;
//HPEN temp_hPen;
//HBRUSH temp_hBrush;
//bút vẽ
static HPEN hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
static HPEN hPen1 = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
#define ID_DRAW_AREA 200

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

//Hàm vẽ
void DrawDT(HDC hdc, int left, int top, int right, int bottom);
void DrawTGC(HDC hdc, int left, int top, int right, int bottom);
void DrawTGV(HDC hdc, int left, int top, int right, int bottom);
void DrawHT(HDC hdc, int left, int top, int right, int bottom);
void DrawNG(HDC hdc, int left, int top, int right, int bottom);
void DrawLG(HDC hdc, int left, int top, int right, int bottom);
void DrawMT_Right(HDC hdc, int left, int top, int right, int bottom);
void DrawMT_Left(HDC hdc, int left, int top, int right, int bottom);
void DrawMT_Down(HDC hdc, int left, int top, int right, int bottom);
void DrawMT_UP(HDC hdc, int left, int top, int right, int bottom);
void DrawNS_4(HDC hdc, int left, int top, int right, int bottom);
void DrawNS_5(HDC hdc, int left, int top, int right, int bottom);
void DrawNS_6(HDC hdc, int left, int top, int right, int bottom);
void DrawHCN(HDC hdc, int left, int top, int right, int bottom);
//hàm vẽ màn hình
void DrawInline(HBRUSH hbrush, HWND hWnd, COLORREF color[]);
void setToolBox(HBRUSH hbrush, HWND hWnd, COLORREF color[]);
// hàm lưu, mở ảnh
void ExportImage();
void OpenImage();
void OpenBitmapByFileName(wstring openFilename);
//hàm di chuột
void OnMouseMove(HWND hwnd, int x, int y, UINT keyFlags);


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: Place code here.

	// Initialize global strings
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_BTLAPI, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_BTLAPI));

	MSG msg;

	// Main message loop: (Vòng lặp thông điệp)
	while (GetMessage(&msg, nullptr, 0, 0)) // lấy ra 1 thông điệp từ hàng đợi
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) 
		{
			TranslateMessage(&msg); // chuyển thông điệp phím ảo sang thông điệp ký tự
			DispatchMessage(&msg); // truyền thông điệp vào thủ tục cửa sổ tương ứng để xử lý
		}
	}

	return (int)msg.wParam;
}

//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;
	//static TCHAR szAppname[] = TEXT("Bài tập lớn");

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW; //Kiểu cửa sổ
	wcex.lpfnWndProc = WndProc; //Thủ tục xử lý các thông điệp
	wcex.cbClsExtra = 0; //Không cần thông tin thêm cho cửa sổ
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_BTLAPI)); // Tải icon cho cửa sổ
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW); // Tải chuột
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1); // Màu nền của cửa sổ
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_BTLAPI); //menu
	wcex.lpszClassName = szWindowClass; // Tên lớp ứng dụng, szWindowClass có kiểu dữ liệu TCHAR được khai báo là static
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // Store instance handle in our global variable
	HWND hWnd1 = CreateWindow(szWindowClass, // Tên lớp cửa sổ
		szTitle, // Tiêu đề
		WS_OVERLAPPEDWINDOW // Kiểu cửa sổ
		| ES_AUTOHSCROLL | ES_AUTOVSCROLL,
		0, 0, // Tọa độ phía trên bên trái
		50, 50, // Kích thước cửa sổ
		nullptr, nullptr, hInstance, nullptr); // chỉ số cửa sổ cha, menu, cửa sổ hiện tại, con trỏ đến thông tin phụ khác
	// Main
	hwndMain = hWnd1;
	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//

//Thủ tục cửa sổ
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	//int N = 10;
	static int i;
	static TCHAR labelGroup[][20] = { TEXT("NỀN"),TEXT("VIỀN"),TEXT("MÀU"),TEXT("CỠ BÚT"),TEXT("NÉT BÚT"),TEXT("CÔNG CỤ") };
	//static TCHAR labelGroup[][20] = { TEXT("NET LIEN"),TEXT("NET DUT"),TEXT("NET CHAM"),TEXT("NET GACH"),TEXT("NÉT BÚT"),TEXT("CÔNG CỤ") };
	static TCHAR labelSize[][20] = { TEXT("1"),TEXT("2"),TEXT("3"),TEXT("4"),TEXT("5") };
	static TCHAR szBuffer[10],style[10];
	static TCHAR currentStyle;
	static HBRUSH hbrushMaunut;
	static HBRUSH hBrushHinh = CreateSolidBrush(RGB(255, 255, 255));
	static int Hinh = 0;

	CHOOSECOLOR  cc;
	COLORREF  acrCustClr[16];
	DWORD  rgbCurrent = RGB(0, 0, 0);
	HBRUSH  hbrush;
	int newColor = 0;

	int count = 0;
	int column = 0;
	int row = 0;

	switch (message)
	{
		//gửi tới cửa sổ sau khi kích thước của nó bị thay đổi
	case WM_SIZE: //khi kích thước cửa sổ chính của chương trình thay đổi mới chạy vào phần này, khi mới chạy chương trình cũng nhảy vào đây
	{
		DrawInline(hbrushMaunut, hWnd, color); //màu mặc định trắng đen
	/*	if (exist == 0) {

			int width = LOWORD(lParam);
			int height = HIWORD(lParam);

			
			exist = 1;
		}*/
		//kích cỡ window
		MoveWindow(hWnd, 200, 150, 1280, 720, TRUE);


		break;
	}

	case WM_CREATE: { // báo hiệu cửa sổ đang được tạo, trong quá trình thực hiện hàm CreateWindow
		hwndGroupBox[0] = CreateWindow(TEXT("BUTTON"), TEXT("HÌNH"), WS_CHILD | WS_VISIBLE | BS_GROUPBOX, 10, 20, 160, 130, hWnd, (HMENU)(16), NULL, NULL);

		//khai báo nút vẽ hình ID:0-14
		while (true) {
			hwndHinh[count] = CreateWindow(TEXT("BUTTON"), TEXT(""), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
				20 + column * 30, 50 + row * 30, 20, 20, hWnd, (HMENU)(count), NULL, NULL);
			// xuống dòng
			count++;
			if (count == 15)  break;
			column++;
			if (column >= 5) {
				column = 0;
				row++;
			}
		}
		//Thứ tự x, y, w, h
		//khai báo các groupbox ID:16-25
		//groupbox bao bên ngoài
		hwndGroupBox[1] = CreateWindow(TEXT("BUTTON"), TEXT(""), WS_CHILD | WS_VISIBLE | BS_GROUPBOX, 5, 5, 1245, 160, hWnd, (HMENU)(17), NULL, NULL);
		i = 2;
		// nền
		hwndGroupBox[i] = CreateWindow(TEXT("BUTTON"), labelGroup[i - 2], WS_CHILD | WS_VISIBLE | BS_GROUPBOX, 180 + (i - 2) * 230, 20, 225, 130, hWnd, (HMENU)(i + 16), NULL, NULL);
		i++;
		// viền
		hwndGroupBox[i] = CreateWindow(TEXT("BUTTON"), labelGroup[i - 2], WS_CHILD | WS_VISIBLE | BS_GROUPBOX, 180 + (i - 2) * 230, 20, 225, 130, hWnd, (HMENU)(i + 16), NULL, NULL);
		i++;
		// màu
		hwndGroupBox[i] = CreateWindow(TEXT("BUTTON"), labelGroup[i - 2], WS_CHILD | WS_VISIBLE | BS_GROUPBOX, 180 + (i - 2) * 230 + 5, 20, 70, 130, hWnd, (HMENU)(i + 16), NULL, NULL);
		i++;
		// cỡ bút
		hwndGroupBox[i] = CreateWindow(TEXT("BUTTON"), labelGroup[i - 2], WS_CHILD | WS_VISIBLE | BS_GROUPBOX, 180 + (i - 2) * 230 - 153, 20, 90, 130, hWnd, (HMENU)(i + 16), NULL, NULL);
		i++;
		 //nét bút
		hwndGroupBox[i] = CreateWindow(TEXT("BUTTON"), labelGroup[i - 2], WS_CHILD | WS_VISIBLE | BS_GROUPBOX, 180 + (i - 2) * 230 - 290, 20, 270, 130,hWnd, HMENU(i + 16), NULL, NULL);
		i++;
		// công cụ
		hwndGroupBox[i] = CreateWindow(TEXT("BUTTON"), labelGroup[i - 2], WS_CHILD | WS_VISIBLE | BS_GROUPBOX, 180 + (i - 2) * 230 - 245, 20, 150, 130, hWnd, (HMENU)(56), NULL, NULL);
		// khai báo canvas
		hwndDrawArea = CreateWindow(TEXT("static"), TEXT("DRAW"), WS_VISIBLE | WS_CHILD | SS_GRAYFRAME, 5, 165, 1245, 470, hWnd, (HMENU)ID_DRAW_AREA, NULL, NULL);
		column = 0;
		row = 0;
		//nét bút
		comboBox = CreateWindow(TEXT("COMBOBOX"),TEXT(""), CBS_DROPDOWN /*cuộn xuống*/ | WS_CHILD | WS_VISIBLE, 830,50,230,130,hWnd,HMENU(100),NULL,NULL);
		//thêm thành phần combobox
		SendMessage(comboBox, CB_INSERTSTRING, -1, (LPARAM)TEXT("NET LIEN"));
		SendMessage(comboBox, CB_INSERTSTRING, -1, (LPARAM)TEXT("NET DUT"));
		SendMessage(comboBox, CB_INSERTSTRING, -1, (LPARAM)TEXT("NET CHAM"));
		SendMessage(comboBox, CB_INSERTSTRING, -1, (LPARAM)TEXT("NET GACH"));
		//đặt thành phần default
		SendMessage(comboBox, CB_SETCURSEL, NULL, 0);
		//Các nút màu
		for (i = 0;i < 10;i++) {
			//20 color button
			hwndMauNen[i] = CreateWindow(TEXT("BUTTON"), TEXT(""), WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 185 + column * 40 + 8, 50 + 40 * (row + row * 0.125), 35, 35, hWnd, (HMENU)(i + 26), NULL, NULL);
			hwndMauVien[i] = CreateWindow(TEXT("BUTTON"), TEXT(""), WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 415 + column * 40 + 8, 50 + 40 * (row + row * 0.125), 35, 35, hWnd, (HMENU)(i + 37), NULL, NULL);
			column++;
			if (column >= 5) {
				column = 0;row++;
			}	
		}
		//nút chọn màu, công cụ, thanh cuộn chọn cỡ
		i = 0;
		hwndChonNen = CreateWindow(TEXT("BUTTON"), TEXT(""), WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 655, 45, 50, 50, hWnd, (HMENU)(i + 54), NULL, NULL);
		hwndChonVien = CreateWindow(TEXT("BUTTON"), TEXT(""), WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 655, 95, 50, 50, hWnd, (HMENU)(i + 55), NULL, NULL);
		hwndPencil = CreateWindow(TEXT("BUTTON"), TEXT("Pencil"), WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 1110, 45, 50, 50, hWnd, (HMENU)(i + 57), NULL, NULL);
		hwndEraser = CreateWindow(TEXT("BUTTON"), TEXT("Eraser"), WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 1165, 45, 50, 50, hWnd, (HMENU)(i + 58), NULL, NULL);
		vsCroll = CreateWindow(TEXT("scrollBar"), TEXT(""), WS_CHILD | WS_VISIBLE | WS_TABSTOP | SBS_VERT,
			730,40,30,105,  hWnd,
			(HMENU)2, NULL, NULL);
		SetScrollRange(vsCroll, SB_CTL, 1, 10, TRUE);
		SetScrollPos(vsCroll, SB_CTL, 1, FALSE);
		// hiển thị chỉ số cỡ bút
		valueColor = CreateWindow(TEXT("static"), TEXT("0"), WS_CHILD | WS_VISIBLE, 765,40,30,30, hWnd,
			(HMENU)3, NULL, NULL);
		break;
	}
	//lấy tọa độ chuột
	case WM_MOUSEMOVE:
		if (LOWORD(lParam) >= 6 && HIWORD(lParam) >= 170 && LOWORD(lParam) <= 1245 && HIWORD(lParam) <= 631) // nếu trong vùng vẽ
		{
			OnMouseMove(hWnd, LOWORD(lParam) - 6, HIWORD(lParam) - 166, TRUE);
		}
		else OnMouseMove(hWnd, 0, 0, TRUE);
		break;
	//lấy tọa độ + điều chỉnh scroll
	case WM_VSCROLL:

		switch (LOWORD(wParam))
		{
		// bấm vào khoảng trống phía dưới
		case SB_PAGEDOWN:
			if (sizetext <= 5)
				sizetext += 5;
			currentSize = sizetext;
			break;
		// bấm vào nút mũi tên xuống
		case SB_LINEDOWN:
			if (sizetext <= 9)
				sizetext += 1;
			currentSize = sizetext;
			break;

		case SB_PAGEUP:
			if (sizetext >= 6)
				sizetext -= 5;
			currentSize = sizetext;
			break;
		case SB_LINEUP:
			if (sizetext >= 2)
				sizetext -= 1;
			currentSize = sizetext;
			break;

		// kéo thanh trượt quá thì sẽ nhảy về giới hạn của nó
		case SB_TOP:
			sizetext = 0;
			currentSize = sizetext;
			break;

		case SB_BOTTOM:
			sizetext = 10;
			currentSize = sizetext;
			break;

		//case SB_THUMBPOSITION:

		// kéo thanh trượt theo
		case SB_THUMBTRACK:
			sizetext = HIWORD(wParam);
			currentSize = sizetext;
			break;

		default:
			break;
		}
		
		SetScrollPos(vsCroll, SB_CTL, sizetext, TRUE); // set vị trí thanh cuộn
		// hiện số bên cạnh
		wsprintf(szBuffer, L"%i", sizetext);
		SetWindowText(valueColor, szBuffer);
		// nếu đang bật cục tẩy
		if (isEraser == true) {
			hPen1 = CreatePen(PS_SOLID, currentSize * 5, RGB(255, 255, 255)); //chuyển sang màu trắng, size = 5
		}
		// nếu không thì lấy màu & cỡ & kiểu đang chọn
		else {
			if (currentStyle == 0) { //kiểu = 0 thì là solid
				hPen = CreatePen(PS_SOLID, currentSize, currentMauVien);
			}
			else if (currentStyle == 1) {
				if (currentSize != 1) { //nếu kiểu là 1 và size khác 1 thì thông báo
					MessageBox(0, L"Chỉ sử dụng với size là 1.Thay đổi size về 1.", //ĐỔI THÔNG ĐIỆP
						L"Warning", MB_ICONINFORMATION | MB_OK);
					currentSize = 1;
				}
				else hPen = CreatePen(PS_DOT, currentSize, currentMauVien); //nếu không thì chuyển nét thành chấm
			}
			else if (currentStyle == 2) {
				if (currentSize != 1) {
					MessageBox(0, L"Chỉ sử dụng với size là 1.Thay đổi size về 1.",
						L"Warning", MB_ICONINFORMATION | MB_OK);
					currentSize = 1;
				}
				else hPen = CreatePen(PS_DASHDOT, currentSize, currentMauVien);
			}
			hPen1 = CreatePen(PS_SOLID, currentSize, currentMauVien);
		}
	
		return 0;
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case 0:
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
		case 7:
		case 8:
		case 9:
		case 10:
		case 11:
		case 12:
		case 13:
		case 14:
			currentShape = wmId;
			Hinh = currentShape;
			isDraw = false;
			isEraser = false;
			InvalidateRect(hWnd, NULL, FALSE);
			break;
		case 26:
		case 27:
		case 28:
		case 29:
		case 30:
		case 31:
		case 32:
		case 33:
		case 34:
		case 35:
		case 36:
			currentMauNen = color[wmId - 26];
			hBrushHinh = CreateSolidBrush(currentMauNen);
			colorIndex = wmId - 26;
			InvalidateRect(hWnd, NULL, FALSE);
			break;
		case 37:
		case 38:
		case 39:
		case 40:
		case 41:
		case 42:
		case 43:
		case 44:
		case 45:
		case 46:
		case 47:
			currentMauVien = color[wmId - 37];
			colorboderIndex = wmId - 37;
			if (currentStyle == 0) {
				hPen = CreatePen(PS_SOLID, currentSize, currentMauVien);
			}
			else if (currentStyle == 1) {
				if (currentSize != 1) {
					MessageBox(0, L"Chỉ sử dụng với size là 1.Thay đổi size về 1.",
						L"Warning", MB_ICONINFORMATION | MB_OK);
					currentSize = 1;
				}
				else hPen = CreatePen(PS_DOT, currentSize, currentMauVien);
			}
			else if (currentStyle == 2) {
				if (currentSize != 1) {
					MessageBox(0, L"Chỉ sử dụng với size là 1.Thay đổi size về 1.",
						L"Warning", MB_ICONINFORMATION | MB_OK);
					currentSize = 1;
				}
			}
				else hPen = CreatePen(PS_DASHDOT, currentSize, currentMauVien);
			hPen1 = CreatePen(PS_SOLID, currentSize, currentMauVien);
			InvalidateRect(hWnd, NULL, FALSE);
			break;
		//chọn màu nền
		case 54:
		{
			ischoosecolor = true;
			ZeroMemory(&cc, sizeof(CHOOSECOLOR));
			cc.lStructSize = sizeof(CHOOSECOLOR);
			cc.hwndOwner = hWnd;
			cc.lpCustColors = (LPDWORD)acrCustClr;
			cc.Flags = CC_FULLOPEN | CC_RGBINIT;
			if (ChooseColor(&cc))
			{
				acrCustClr[newColor] = cc.rgbResult;
				newColor++;
				currentMauNen = cc.rgbResult;
				hBrushHinh = CreateSolidBrush(currentMauNen);
			}
			InvalidateRect(hWnd, NULL, FALSE);
			ReleaseDC(hWnd, hdc);
			break;
		}
		//chọn màu viền
		case 55:
		{
			ischoosebordercolor = true;
			ZeroMemory(&cc, sizeof(CHOOSECOLOR));
			cc.lStructSize = sizeof(CHOOSECOLOR);
			cc.hwndOwner = hWnd;
			cc.lpCustColors = acrCustClr;
			cc.Flags = CC_FULLOPEN | CC_RGBINIT;
			if (ChooseColor(&cc))
			{
				currentMauVien = cc.rgbResult;
				if (currentStyle == 0) {
					hPen = CreatePen(PS_SOLID, currentSize, currentMauVien);
				}
				else if (currentStyle == 1) {
					hPen = CreatePen(PS_DOT, currentSize, currentMauVien);
				}
				else if (currentStyle == 2) {
					hPen = CreatePen(PS_DASHDOT, currentSize, currentMauVien);
				}
				else if (currentStyle == 3) {
					hPen = CreatePen(PS_DASH, currentSize, currentMauVien);
				}
				hPen1 = CreatePen(PS_SOLID, currentSize, currentMauVien);
			}
			InvalidateRect(hWnd, NULL, FALSE);
			ReleaseDC(hWnd, hdc);
			break;
		}
		// bút chì
		case 57:
		{
				hPen1 = CreatePen(currentStyle, currentSize, currentMauVien);
				isEraser = false;
				isDraw = true;
				isClick = false;
			break;
		}
		// tẩy
		case 58:
		{
				hPen1 = CreatePen(currentStyle, currentSize*5, RGB(255, 255, 255));
				isEraser = true;
				isDraw = true;
				isClick = false;
			break;
		}
		//combo box nét bút
		case 100:
			if(HIWORD(wParam) == CBN_SELENDOK) {
				int selection = SendMessage(comboBox, CB_GETCURSEL, NULL, NULL);
				switch (selection) {
				case 0:
					currentStyle = 0;
					hPen = CreatePen(PS_SOLID, currentSize, currentMauVien);
					break;
				case 1:
					if (currentSize != 1) {
						MessageBox(0, L"Chỉ sử dụng với size là 1.Thay đổi size về 1 ",
							L"Warning", MB_ICONINFORMATION | MB_OK);
						currentSize = 1;
					}
					currentStyle = 1;
					hPen = CreatePen(PS_DOT, currentSize, currentMauVien);
					break;
				case 2:
					if (currentSize != 1) {
						MessageBox(0, L"Chỉ sử dụng với size là 1.Thay đổi size về 1 ",
							L"Warning", MB_ICONINFORMATION | MB_OK);
						currentSize = 1;
					}
					currentStyle = 2;
					hPen = CreatePen(PS_DASHDOT, currentSize, currentMauVien);
					break;
				case 3:
					if (currentSize != 1) {
						MessageBox(0, L"Chỉ sử dụng với size là 1.Thay đổi size về 1 ",
							L"Warning", MB_ICONINFORMATION | MB_OK);
						currentSize = 1;
					}
					currentStyle = 3;
					hPen = CreatePen(PS_DASH, currentSize, currentMauVien);
					break;
				}
				SendMessage(comboBox, CB_GETLBTEXT, selection, (LPARAM)style);
				MessageBox(hWnd, style,L"Warning", MB_ICONINFORMATION | MB_OK);
				break;
			}
			break;
		case ID_FILE_SAVE:
			ExportImage();
			break;
		case ID_FILE_OPEN32786:
		{
			OpenImage();
			break;
		}
		case IDM_FILE_NEW:
			hwndDrawArea = CreateWindow(TEXT("static"), TEXT("Draw"), WS_VISIBLE | WS_CHILD | SS_GRAYFRAME, 5, 165, 1245, 470, hWnd, (HMENU)ID_DRAW_AREA, NULL, NULL);
			break;
		case IDM_ABOUT: //sửa about
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			if (MessageBox(NULL, TEXT("Bạn có muốn thoát chương trình không"), TEXT("THÔNG BÁO"), MB_YESNO | MB_ICONQUESTION) == IDYES) {
				DestroyWindow(hWnd);
			}
			break;
		case ID_FILE_EXIT:
			if (MessageBox(NULL, TEXT("Bạn có muốn thoát chương trình không?"), TEXT("THÔNG BÁO"), MB_YESNO | MB_ICONQUESTION) == IDYES) {
				DestroyWindow(hWnd);
			}
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}

	}
	break;
	case WM_LBUTTONDOWN:
		//lấy vị trí chuột bấm xuống
		xLeft = LOWORD(lParam);
		yTop = HIWORD(lParam);
		isClick = true;
		break;
	case WM_LBUTTONUP:
	{
		//lấy vị trí chuột thả ra

		//khi dùng pencil
		if (isDraw == true) {
			isClick = false;
			xLeft = 0;
			yTop = 0;
			xRight = 0;
			yBottom = 0;
			start = 0;
			break;

		}
		// nếu k dùng bút chì thì lấy ra tọa độ để vẽ hình
		xRight = LOWORD(lParam);
		yBottom = HIWORD(lParam);
		if (yTop <= 160 || xLeft <= 5 || yBottom <= 20 || xRight <= 5 || yTop > 600 ) break; //nếu ở ngoài vùng vẽ thì break
		yTop -= 165;
		yBottom -= 165;
		int i = 0;
		hdc = GetDC(hwndDrawArea); //lấy ngữ cảnh thiết bị
		SelectObject(hdc, hPen); //lấy bút
		SelectObject(hdc, hBrushHinh); //lấy nền
		//select object áp dụng đến khi gặp 1 hàm select object khác
		if (Hinh == 0) {
			
			DrawDT(hdc, xLeft, yTop, xRight,	yBottom);
		}
		else if (Hinh == 1) {
			
			DrawTGC(hdc, xLeft, yTop, xRight, yBottom);
		}
		else if (Hinh == 2) {
			
			DrawTGV(hdc, xLeft, yTop, xRight, yBottom);
		}
		else if (Hinh == 3) {
		
			DrawHT(hdc, xLeft, yTop, xRight, yBottom);
		}
		else if (Hinh == 4) {
			
			DrawNG(hdc, xLeft, yTop, xRight, yBottom);
		}
		else if (Hinh == 5) {
			
			DrawLG(hdc, xLeft, yTop, xRight, yBottom);
		}
		else if (Hinh == 6) {
			
			DrawMT_Right(hdc, xLeft, yTop, xRight, yBottom);
		}
		else if (Hinh == 7) {
			
			DrawMT_Left(hdc, xLeft, yTop, xRight, yBottom);
		}
		else if (Hinh == 8) {
			
			DrawMT_Down(hdc, xLeft, yTop, xRight, yBottom);
		}
		else if (Hinh == 9) {
			
			DrawMT_UP(hdc, xLeft, yTop, xRight, yBottom);
		}
		else if (Hinh == 10) {
			
			DrawNS_4(hdc, xLeft, yTop, xRight, yBottom);
		}
		else if (Hinh == 11) {
			
			DrawNS_5(hdc, xLeft, yTop, xRight, yBottom);
		}
		else if (Hinh == 12) {
			
			DrawNS_6(hdc, xLeft, yTop, xRight, yBottom);
		}
		else if (Hinh == 13) {
			
			Rectangle(hdc, xLeft, yTop, xRight, yBottom);
		}
		else if (Hinh == 14) {
			
			DrawHCN(hdc, xLeft, yTop, xRight, yBottom);
		}
		//sau khi vẽ xong, reset về 0
		xLeft = 0;
		yTop = 0;
		xRight = 0;
		yBottom = 0;
		isClick = false;
		//có getdc thì phải releasedc
		ReleaseDC(hWnd, hdc);
		break;
	}

	// Lấy handle của DC
	case WM_PAINT: //gửi tới cửa sổ	khi 1 miền của cửa sổ cần được vẽ lại
		// xảy ra khi gọi hàm RedrawWindow hoặc UpdateWindow
	{
		PAINTSTRUCT ps; 
		// bắt đầu vẽ nội dung cửa sổ
		HDC hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code that uses hdc here...
		// các hàm GDI
		EndPaint(hWnd, &ps);// kết thúc vẽ
		// mỗi lần bấm nút lại settoolbox 1 lần
		setToolBox(hbrushMaunut, hWnd, color); //đặt màu & hình cho các nút
		// TODO: Add any drawing code that uses hdc here...
		break;
	}
	case WM_CLOSE: //báo hiệu 1 cửa sổ hoặc ứng dụng cần dc kết thúc
		//nếu người dùng chấp nhận hủy, gọi hàm DestroyWindow -> gửi thông điệp WM_DESTROY tới cửa sổ
		if (MessageBox(NULL, TEXT("Bạn có muốn thoát chương trình không"), TEXT("THÔNG BÁO"), MB_YESNO | MB_ICONQUESTION) == IDYES) {
			DestroyWindow(hWnd);
		}
		else {
			break;
		}
	case WM_DESTROY: //gửi tới cửa sổ sau khi dọn khỏi màn hình và trước khi bị tiêu hủy
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

// CÁC HÀM VẼ HÌNH
void DrawDT(HDC hdc, int left, int top, int right, int bottom) {
	POINT p[2];
	p[0].x = left;
	p[0].y = top;
	p[1].x = right;
	p[1].y = bottom;
	Polyline(hdc, p, 2);
}
void DrawTGC(HDC hdc, int left, int top, int right, int bottom) {
	POINT p[4];
	p[3].x = p[0].x = left + (right - left) / 2;
	p[3].y = p[0].y = top;
	p[1].x = left;
	p[1].y = p[2].y = bottom;
	p[2].x = right;
	Polygon(hdc, p, 4);
}
void DrawTGV(HDC hdc, int left, int top, int right, int bottom) {
	POINT p[4];
	p[3].x = p[0].x = left;
	p[3].y = p[0].y = top;
	p[1].x = left;
	p[1].y = p[2].y = bottom;
	p[2].x = right;
	Polygon(hdc, p, 4);
}
void DrawHT(HDC hdc, int left, int top, int right, int bottom) {
	POINT p[5];
	p[4].x = p[0].x = left + (right - left) / 2;
	p[4].y = p[0].y = top;

	p[1].y = p[3].y = top + (bottom - top) / 2;
	p[1].x = right;

	p[2].x = left + (right - left) / 2;
	p[2].y = bottom;

	p[3].x = left;
	Polygon(hdc, p, 5);
}
void DrawNG(HDC hdc, int left, int top, int right, int bottom) {
	POINT p[6];
	p[5].x = p[0].x = left + (right - left) / 2;
	p[5].y = p[0].y = top;

	p[1].x = left;
	p[1].y = p[4].y = top + 2 * (bottom - top) / 5;

	p[2].x = left + (right - left) / 5;
	p[2].y = p[3].y = bottom;

	p[3].x = left + 4 * (right - left) / 5;

	p[4].x = right;
	Polygon(hdc, p, 6);
}
void DrawLG(HDC hdc, int left, int top, int right, int bottom) {
	POINT p[7];
	p[6].x = p[0].x = p[3].x = left + (right - left) / 2;
	p[6].y = p[0].y = top;

	p[2].x = p[1].x = left;
	p[1].y = p[5].y = top + (bottom - top) / 4;
	p[4].x = p[5].x = right;

	p[2].y = p[4].y = top + 3 * (bottom - top) / 4;

	p[3].y = bottom;
	Polygon(hdc, p, 7);
}
void DrawMT_Right(HDC hdc, int left, int top, int right, int bottom) {
	if (right < left) {
		int t = left;
		left = right;
		right = t;
	}
	POINT p[8];
	p[7].x = p[0].x = p[1].x = p[4].x = p[5].x = left + (right - left) / 2;
	p[7].y = p[0].y = top;

	p[1].y = p[2].y = top + (bottom - top) / 4;
	p[2].x = p[3].x = left;

	p[3].y = p[4].y = top + 3 * (bottom - top) / 4;
	p[5].y = bottom;

	p[6].x = right;
	p[6].y = top + (bottom - top) / 2;
	Polygon(hdc, p, 8);
}
void DrawMT_Left(HDC hdc, int left, int top, int right, int bottom) {
	if (right < left) {
		int t = left;
		left = right;
		right = t;
	}
	POINT p[8];
	p[7].x = p[0].x = p[1].x = p[4].x = p[5].x = left + (right - left) / 2;
	p[7].y = p[0].y = top;

	p[1].y = p[2].y = top + (bottom - top) / 4;
	p[2].x = p[3].x = right;

	p[3].y = p[4].y = top + 3 * (bottom - top) / 4;
	p[5].y = bottom;

	p[6].x = left;
	p[6].y = top + (bottom - top) / 2;
	Polygon(hdc, p, 8);
}
void DrawMT_Down(HDC hdc, int left, int top, int right, int bottom) {
	if (bottom < top) {
		int t = top;
		top = bottom;
		bottom = t;
	}
	POINT p[8];
	p[0].x = p[7].x = p[1].x = left + (right - left) / 4;
	p[0].y = p[7].y = p[6].y = top;
	p[1].y = p[2].y = p[4].y = p[5].y = top + (bottom - top) / 2;
	p[2].x = left;

	p[3].x = left + (right - left) / 2;
	p[3].y = bottom;

	p[4].x = right;
	p[5].x = p[6].x = left + 3 * (right - left) / 4;
	Polygon(hdc, p, 8);
}
void DrawMT_UP(HDC hdc, int left, int top, int right, int bottom) {
	if (bottom < top) {
		int t = top;
		top = bottom;
		bottom = t;
	}
	POINT p[8];
	p[0].x = p[7].x = p[1].x = left + (right - left) / 4;
	p[0].y = p[7].y = p[6].y = bottom;
	p[1].y = p[2].y = p[4].y = p[5].y = top + (bottom - top) / 2;
	p[2].x = left;

	p[3].x = left + (right - left) / 2;
	p[3].y = top;

	p[4].x = right;
	p[5].x = p[6].x = left + 3 * (right - left) / 4;
	Polygon(hdc, p, 8);
}
void DrawNS_4(HDC hdc, int left, int top, int right, int bottom) {
	POINT p[9];
	p[4].x = p[8].x = p[0].x = left + (right - left) / 2;
	p[8].y = p[0].y = top;

	p[1].x = p[3].x = left + 2 * (right - left) / 5;
	p[1].y = p[7].y = top + 2 * (bottom - top) / 5;

	p[2].x = left;
	p[2].y = p[6].y = top + (bottom - top) / 2;

	p[3].y = p[5].y = top + 3 * (bottom - top) / 5;
	p[4].y = bottom;

	p[5].x = p[7].x = left + 3 * (right - left) / 5;
	p[6].x = right;
	Polygon(hdc, p, 9);
}
void DrawNS_5(HDC hdc, int left, int top, int right, int bottom) {
	POINT p[11];
	p[10].x = p[0].x = left + (right - left) / 2;
	p[10].y = p[0].y = top;
	p[1].x = left + 10 * (right - left) / 16;
	p[1].y = top + 3 * (bottom - top) / 8;

	p[2].x = right;
	p[2].y = top + 3 * (bottom - top) / 8; //=p1

	p[3].x = left + 5 * (right - left) / 7;
	p[3].y = top + 5 * (bottom - top) / 8;

	p[4].x = left + 5 * (right - left) / 6;
	p[4].y = bottom;

	p[5].x = left + (right - left) / 2;
	p[5].y = top + 3 * (bottom - top) / 4;

	p[6].x = left + (right - left) / 6;
	p[6].y = bottom;

	p[7].x = left + 2 * (right - left) / 7;
	p[7].y = top + 5 * (bottom - top) / 8;

	p[8].x = left;
	p[8].y = top + 3 * (bottom - top) / 8;

	p[9].x = left + 6 * (right - left) / 16;
	p[9].y = top + 3 * (bottom - top) / 8;
	Polygon(hdc, p, 11);
}
void DrawNS_6(HDC hdc, int left, int top, int right, int bottom) {
	POINT p[13];
	p[6].x = p[12].x = p[0].x = left + (right - left) / 2;
	p[12].y = p[0].y = top;

	p[5].x = p[1].x = left + (right - left) / 3;
	p[10].y = p[11].y = p[2].y = p[1].y = top + (bottom - top) / 4;

	p[4].x = p[2].x = left;
	p[3].x = left + (right - left) / 6;
	p[9].y = p[3].y = top + (bottom - top) / 2;

	p[8].y = p[7].y = p[5].y = p[4].y = top + 3 * (bottom - top) / 4;
	p[6].y = bottom;

	p[11].x = p[7].x = left + 2 * (right - left) / 3;
	p[10].x = p[8].x = right;
	p[9].x = left + 5 * (right - left) / 6;

	Polygon(hdc, p, 13);
}

void DrawHCN(HDC hdc, int left, int top, int right, int bottom) {
	if (right < left) {
		int t = left;
		left = right;
		right = t;
	}

	if (bottom < top) {
		int t = top;
		top = bottom;
		bottom = t;
	}

	int width = (right - left) * 20 / 100;
	int height = (bottom - top) * 20 / 100;
	RoundRect(hdc, left, top, right, bottom, width, height);
}

// ?
void DrawInline(HBRUSH hbrushMaunut, HWND hWnd, COLORREF color[]) {
	PAINTSTRUCT ps;

	hdc = BeginPaint(hwndHinh[0], &ps);
	DrawDT(hdc, 5, 5, 15, 15);
	EndPaint(hwndHinh[0], &ps);

	hdc = BeginPaint(hwndHinh[1], &ps);
	DrawTGC(hdc, 5, 5, 15, 15);
	EndPaint(hwndHinh[1], &ps);

	hdc = BeginPaint(hwndHinh[2], &ps);
	DrawTGV(hdc, 5, 5, 15, 15);
	EndPaint(hwndHinh[2], &ps);

	hdc = BeginPaint(hwndHinh[3], &ps);
	DrawHT(hdc, 5, 5, 15, 15);
	EndPaint(hwndHinh[3], &ps);

	hdc = BeginPaint(hwndHinh[4], &ps);
	DrawNG(hdc, 5, 5, 15, 15);
	EndPaint(hwndHinh[4], &ps);

	hdc = BeginPaint(hwndHinh[5], &ps);
	DrawLG(hdc, 5, 5, 15, 15);
	EndPaint(hwndHinh[5], &ps);

	hdc = BeginPaint(hwndHinh[6], &ps);
	DrawMT_Right(hdc, 5, 5, 15, 15);
	EndPaint(hwndHinh[6], &ps);

	hdc = BeginPaint(hwndHinh[7], &ps);
	DrawMT_Left(hdc, 5, 5, 15, 15);
	EndPaint(hwndHinh[7], &ps);

	hdc = BeginPaint(hwndHinh[8], &ps);
	DrawMT_Down(hdc, 5, 5, 15, 15);
	EndPaint(hwndHinh[8], &ps);

	hdc = BeginPaint(hwndHinh[9], &ps);
	DrawMT_UP(hdc, 5, 5, 15, 15);
	EndPaint(hwndHinh[9], &ps);

	hdc = BeginPaint(hwndHinh[10], &ps);
	DrawNS_4(hdc, 5, 5, 15, 15);
	EndPaint(hwndHinh[10], &ps);

	hdc = BeginPaint(hwndHinh[11], &ps);
	DrawNS_5(hdc, 5, 5, 15, 15);
	EndPaint(hwndHinh[11], &ps);

	hdc = BeginPaint(hwndHinh[12], &ps);
	DrawNS_6(hdc, 5, 5, 15, 15);
	EndPaint(hwndHinh[12], &ps);

	hdc = BeginPaint(hwndHinh[13], &ps);
	Rectangle(hdc, 5, 5, 15, 15);
	EndPaint(hwndHinh[13], &ps);

	hdc = BeginPaint(hwndHinh[14], &ps);
	DrawHCN(hdc, 5, 5, 15, 15);
	EndPaint(hwndHinh[14], &ps);

	//for (int i = 0;i < 10;i++) {
	//	hbrushMaunut = CreateSolidBrush(color[i]); //tạo 1 màu nút

	//	hdc = BeginPaint(hwndMauNen[i], &ps); //vẽ các nút hiển thị màu nền
	//	SelectObject(hdc, hbrushMaunut); //chọn màu nút
	//	Rectangle(hdc, 2, 2, 33, 33); //vẽ hình chữ nhật
	//	EndPaint(hwndMauNen[i], &ps);

	//	hdc = BeginPaint(hwndMauVien[i], &ps); //vẽ các nút hiển thị màu viền
	//	SelectObject(hdc, hbrushMaunut); //chọn màu nút
	//	Rectangle(hdc, 2, 2, 33, 33); //vẽ hình chữ nhật
	//	DeleteObject(hbrushMaunut);
	//	EndPaint(hwndMauVien[i], &ps);
	//}
	hdc = GetDC(hWnd);

	//HPEN hp;
	//hp = CreatePen(PS_SOLID, currentSize, RGB(0, 0, 0));
	//SelectObject(hdc, hp);

	//POINT point[2];
	//point[0].x = 850;
	//point[0].y = 50;
	//point[1].x = 1050;
	//point[1].y = 50;
	//Polyline(hdc, point, 2);

	//hp = CreatePen(PS_DOT, currentSize, RGB(0, 0, 0));
	//SelectObject(hdc, hp);
	//point[0].x = 850;
	//point[0].y = 80;
	//point[1].x = 1050;
	//point[1].y = 80;
	//Polyline(hdc, point, 2);

	//hp = CreatePen(PS_DASHDOT, currentSize, RGB(0, 0, 0));
	//SelectObject(hdc, hp);
	//point[0].x = 850;
	//point[0].y = 110;
	//point[1].x = 1050;
	//point[1].y = 110;
	//Polyline(hdc, point, 2);

	//hp = CreatePen(PS_DASH, currentSize, RGB(0, 0, 0));
	//SelectObject(hdc, hp);
	//point[0].x = 850;
	//point[0].y = 140;
	//point[1].x = 1050;
	//point[1].y = 140;
	//Polyline(hdc, point, 2);

	/*ReleaseDC(hWnd, hdc);
	hbrushMaunut = CreateSolidBrush(RGB(255, 255, 255));
	hdc = BeginPaint(hwndChonNen, &ps);
	SelectObject(hdc, hbrushMaunut);
	Rectangle(hdc, 2, 2, 45, 45);
	EndPaint(hwndChonNen, &ps);
	hbrushMaunut = CreateSolidBrush(RGB(0, 0, 0));
	hdc = BeginPaint(hwndChonVien, &ps);
	SelectObject(hdc, hbrushMaunut);
	Rectangle(hdc, 2, 2, 45, 45);
	DeleteObject(hbrushMaunut);
	EndPaint(hwndChonNen, &ps);*/

	ReleaseDC(hWnd, hdc);
}

void setToolBox(HBRUSH hbrushMaunut, HWND hWnd, COLORREF color[]) {
	PAINTSTRUCT ps;

	hdc = BeginPaint(hwndHinh[0], &ps);
	DrawDT(hdc, 5, 5, 15, 15);
	EndPaint(hwndHinh[0], &ps);

	hdc = BeginPaint(hwndHinh[1], &ps);
	DrawTGC(hdc, 5, 5, 15, 15);
	EndPaint(hwndHinh[1], &ps);

	hdc = BeginPaint(hwndHinh[2], &ps);
	DrawTGV(hdc, 5, 5, 15, 15);
	EndPaint(hwndHinh[2], &ps);

	hdc = BeginPaint(hwndHinh[3], &ps);
	DrawHT(hdc, 5, 5, 15, 15);
	EndPaint(hwndHinh[3], &ps);

	hdc = BeginPaint(hwndHinh[4], &ps);
	DrawNG(hdc, 5, 5, 15, 15);
	EndPaint(hwndHinh[4], &ps);

	hdc = BeginPaint(hwndHinh[5], &ps);
	DrawLG(hdc, 5, 5, 15, 15);
	EndPaint(hwndHinh[5], &ps);

	hdc = BeginPaint(hwndHinh[6], &ps);
	DrawMT_Right(hdc, 5, 5, 15, 15);
	EndPaint(hwndHinh[6], &ps);

	hdc = BeginPaint(hwndHinh[7], &ps);
	DrawMT_Left(hdc, 5, 5, 15, 15);
	EndPaint(hwndHinh[7], &ps);

	hdc = BeginPaint(hwndHinh[8], &ps);
	DrawMT_Down(hdc, 5, 5, 15, 15);
	EndPaint(hwndHinh[8], &ps);

	hdc = BeginPaint(hwndHinh[9], &ps);
	DrawMT_UP(hdc, 5, 5, 15, 15);
	EndPaint(hwndHinh[9], &ps);

	hdc = BeginPaint(hwndHinh[10], &ps);
	DrawNS_4(hdc, 5, 5, 15, 15);
	EndPaint(hwndHinh[10], &ps);

	hdc = BeginPaint(hwndHinh[11], &ps);
	DrawNS_5(hdc, 5, 5, 15, 15);
	EndPaint(hwndHinh[11], &ps);

	hdc = BeginPaint(hwndHinh[12], &ps);
	DrawNS_6(hdc, 5, 5, 15, 15);
	EndPaint(hwndHinh[12], &ps);

	hdc = BeginPaint(hwndHinh[13], &ps);
	Rectangle(hdc, 5, 5, 15, 15);
	EndPaint(hwndHinh[13], &ps);

	hdc = BeginPaint(hwndHinh[14], &ps);
	DrawHCN(hdc, 5, 5, 15, 15);
	EndPaint(hwndHinh[14], &ps);

	for (int i = 0;i < 10;i++) {
		hbrushMaunut = CreateSolidBrush(color[i]);

		hdc = BeginPaint(hwndMauNen[i], &ps);
		SelectObject(hdc, hbrushMaunut);
		Rectangle(hdc, 2, 2, 33, 33);
		EndPaint(hwndMauNen[i], &ps);

		hdc = BeginPaint(hwndMauVien[i], &ps);
		SelectObject(hdc, hbrushMaunut);
		Rectangle(hdc, 2, 2, 33, 33);
		DeleteObject(hbrushMaunut);
		EndPaint(hwndMauVien[i], &ps);
	}

	// hiển thị màu trong ô màu nền đang chọn
	if (ischoosecolor == true) { //nếu màu đang được chọn
		hbrushMaunut = CreateSolidBrush(currentMauNen); //gán màu nền hiện tại cho màu nút
		hdc = BeginPaint(hwndChonNen, &ps);
		SelectObject(hdc, hbrushMaunut);
		Rectangle(hdc, 2, 2, 45, 45);
		EndPaint(hwndChonNen, &ps);
	}
	else { //nếu không thì lấy có sẵn
		hbrushMaunut = CreateSolidBrush(color[colorIndex]);
		hdc = BeginPaint(hwndChonNen, &ps);
		SelectObject(hdc, hbrushMaunut);
		Rectangle(hdc, 2, 2, 45, 45);
		EndPaint(hwndChonNen, &ps);
	}

	//hiển thị màu viền trong ô màu viền đang chọn
	if (ischoosebordercolor == true)
	{
		hbrushMaunut = CreateSolidBrush(currentMauVien);
		hdc = BeginPaint(hwndChonVien, &ps);
		SelectObject(hdc, hbrushMaunut);
		Rectangle(hdc, 2, 2, 45, 45);
		EndPaint(hwndChonNen, &ps);
		ReleaseDC(hWnd, hdc);
	}
	else {
	hbrushMaunut = CreateSolidBrush(color[colorboderIndex]);
	hdc = BeginPaint(hwndChonVien, &ps);
	SelectObject(hdc, hbrushMaunut);
	Rectangle(hdc, 2, 2, 45, 45);
	EndPaint(hwndChonNen, &ps);
	ReleaseDC(hWnd, hdc);
	}

}

void OpenImage() {
	OPENFILENAME ofn;
	WCHAR szFilePath[MAX_PATH] = L""; //đường dẫn
	WCHAR szFileTitle[MAX_PATH] = L"";

	ZeroMemory(&ofn, sizeof(ofn));

	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = hwndMain;
	ofn.lpstrFilter = L"JPEG (*.jpg)\0*.jpg\0PNG (*.png)\0*.png\0Bitmap Files (*.bmp)\0*.bin";
	ofn.lpstrFile = szFilePath;
	ofn.lpstrFileTitle = szFileTitle;
	ofn.nMaxFile = MAX_PATH;
	ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
	ofn.lpstrDefExt = L"bmp";
	static wstring openFilename;
	static bool isOpenFile = false;
	static int orderOpen = 0;
	if (GetOpenFileName(&ofn))
	{
		wstring ws(szFilePath);
		//string fileName(ws.begin(), ws.end());
		openFilename = ws;
		isOpenFile = true;
		OpenBitmapByFileName(openFilename);
	}
}
void OpenBitmapByFileName(wstring openFilename) {
	HBITMAP       hBitmap, hOldBitmap;
	HPALETTE      hPalette, hOldPalette;
	HDC           hMemDC;
	BITMAP        bm;
	HDC hDC = GetDC(hwndDrawArea);

	if (LoadBitmapFromBMPFile(openFilename.c_str(), &hBitmap, &hPalette))
	{
		GetObject(hBitmap, sizeof(BITMAP), &bm);
		hMemDC = CreateCompatibleDC(hDC);
		hOldBitmap = (HBITMAP)SelectObject(hMemDC, hBitmap);
		hOldPalette = SelectPalette(hDC, hPalette, FALSE);
		RealizePalette(hDC); //nhan dang mau

							 // copy hMemDC to hdc
		BitBlt(hDC, 0, 0, bm.bmWidth, bm.bmHeight,
			hMemDC, 0, 0, SRCCOPY);

		SelectObject(hMemDC, hOldBitmap);
		DeleteObject(hBitmap);
		SelectPalette(hDC, hOldPalette, FALSE);
		DeleteObject(hPalette);
	}
}
void ExportImage() {
	OPENFILENAME ofn;
	WCHAR szFileName[MAX_PATH] = L"";

	ZeroMemory(&ofn, sizeof(ofn));

	ofn.lStructSize = sizeof(ofn); // SEE NOTE BELOW
	ofn.hwndOwner = hwndMain;

	ofn.lpstrFilter = L"JPEG (*.jpg)\0*.jpg\0PNG (*.png)\0*.png\0Bitmap Files (*.bmp)\0*.bin";
	ofn.lpstrFile = szFileName;
	ofn.nMaxFile = MAX_PATH;
	ofn.Flags = OFN_EXPLORER | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT;
	ofn.lpstrDefExt = L"bmp";

	if (GetSaveFileName(&ofn))
	{
		wstring ws(szFileName);
		HDC hDC = GetDC(hwndDrawArea); //tạo ngữ cảnh vùng vẽ
		HDC hTargetDC = CreateCompatibleDC(hDC);
		RECT rect = { 0 }; //tạo 1 hcn
		GetWindowRect(hwndDrawArea, &rect); //sau khi dùng api này ta sẽ có mảng rect bao gồm tọa bộ xLeft,yTop,xRight,yBottom
		//tạo 1 bitmap 
		HBITMAP hBitmap = CreateCompatibleBitmap(hDC, rect.right - rect.left,
			rect.bottom - rect.top); //tạo bitmap có cỡ bằng cỡ khung
		SelectObject(hTargetDC, hBitmap);
		//PrintWindow(hwndDrawArea, hTargetDC, PW_CLIENTONLY);
		BitBlt(hTargetDC, 0, 0, rect.right, rect.bottom, hDC, 0, 0, SRCCOPY);
		PBITMAPINFO pbmi = CreateBitmapInfoStruct(hwndDrawArea, hBitmap);
		//tạo ra 1 file ảnh đuôi bmp
		CreateBMPFile(hwndDrawArea, ws.c_str(), pbmi, hBitmap, hDC);
		DeleteObject(hBitmap);
		ReleaseDC(hwndDrawArea, hDC);
		DeleteDC(hTargetDC);
	}
}
// vẽ bút chì
void OnMouseMove(HWND hwnd, int x, int y, UINT keyFlags)
{
	
	HDC hdc1 = GetDC(hwndDrawArea);

	if (isDraw == true && isClick == true && xLeft != 0 && yTop != 0 && x != 0 && y != 0) {

		if (start == 0) {
			start++;
			xLeft = x;
			yTop = y;
		}
		else {
			SelectObject(hdc1, hPen1);
			DrawDT(hdc1, xLeft, yTop, x, y);
			xLeft = x;
			yTop = y;
		}

	}
	ReleaseDC(hwndDrawArea, hdc1);
}
