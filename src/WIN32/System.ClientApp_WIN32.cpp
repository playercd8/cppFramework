/*
* System.ClientApp_WIN32.cpp
*
*  Created on: Taiwan
*      Author: player
*/

#include "../../include/stdafx.h"

#if defined(_WINDOWS) && (_APP_MODE == _APP_MODE_CLIENT)

#include "../../include/System.Drawing.Graphics.h"
#include "../../include/System.Drawing.Renderer.h"
#include "../../include/System.Drawing.Scene.h"
#include "../../include/System.ScriptEngine.h"
#include "../../include/UI/System.Drawing.UI.UIManager.h"
#include "../../include/UI/System.Drawing.UI.Element.h"
#include "../../include/WIN32/System.ClientApp.h"
#include <time.h>

using namespace System;

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPTSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	ClientApp_Desc desc;
	desc.argc = __argc;
	desc.argv = __argv;
	desc.width = 800;
	desc.height = 600;
	desc.isFullScreen = false;
	desc.vsync = false;

	desc.hInstance = hInstance;
	desc.cmdShow = nCmdShow;
	desc.strClassName = _T("OurGameClass");
	desc.strWindowTitle = _T("OurGame");

	//全域變數
	pApp = new ClientApp(desc);
	pApp->Run();

	int exitCode = pApp->GetExitCode();
	SafeDelete(pApp);

	return exitCode;
}

namespace System {
	//宣告class ClientApp的static成員變數
	ResourceManager* ClientApp::pResourceManager = NULL;
	Graphics* ClientApp::pGraphics = NULL;
	Renderer* ClientApp::pRenderer = NULL;
	ScriptEngine* ClientApp::pScriptEngine = NULL;
	UIManager* ClientApp::pUIManager = NULL;
	Scene* ClientApp::pScene = NULL;

	CallBackWndFunc  ClientApp::_WndFunc[WM_USER];
	Map<UINT, CallBackWndFunc>  ClientApp::_UserWndFunc;

	namespace Drawing {
		Renderer* GetDefaultRendererPtr() {
			return ClientApp::pRenderer;
		}
	}

	ClientApp::ClientApp(ClientApp_Desc& desc) :
		_desc(desc),
		_hWnd(NULL),
		_hAccelTable(NULL),
		_idIcon(0),
		_idAccelerators(0)
	{
		//初始化COM
		HRESULT hr = ::CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);

		//初始化鍵盤的按鍵狀態
		ZeroMemory(_KeyStatus, sizeof(_KeyStatus)*sizeof(bool));
		//for (int i = 0; i < 256; i++)
		//	_KeyStatus[i] = false;


		//初始化視窗訊息處理函式(預設都先接到DefWindowProc)
		ZeroMemory(_WndFunc, sizeof(_WndFunc)*sizeof(CallBackWndFunc));
		//for (int id = 0; id < WM_USER; id++)
		//	_WndFunc[id] = DefWindowProc;

		SetCallBack(WM_DESTROY, OnDestroy);
		SetCallBack(WM_PAINT, OnPaint);
		SetCallBack(WM_SYSCOMMAND, OnSysCommand);

		//Keyboard Input Notifications
		SetCallBack(WM_CHAR, OnChar);
		SetCallBack(WM_KEYDOWN, OnKeyDown);
		SetCallBack(WM_KEYUP, OnKeyUp);

		//Mouse Input Notifications
		SetCallBack(WM_MOUSEMOVE, OnMouseMove);
		SetCallBack(WM_MOUSEWHEEL, OnMouseWheel);
		SetCallBack(WM_LBUTTONDBLCLK, OnButtonDblClk);
		SetCallBack(WM_LBUTTONDOWN, OnButtonDown);
		SetCallBack(WM_LBUTTONUP, OnButtonUp);
		SetCallBack(WM_RBUTTONDBLCLK, OnButtonDblClk);
		SetCallBack(WM_RBUTTONDOWN, OnButtonDown);
		SetCallBack(WM_RBUTTONUP, OnButtonUp);
		SetCallBack(WM_MBUTTONDBLCLK, OnButtonDblClk);
		SetCallBack(WM_MBUTTONDOWN, OnButtonDown);
		SetCallBack(WM_MBUTTONUP, OnButtonUp);

		RegisterClass();
		if (InitInstance() == false) {
			::MessageBox(NULL, _T("無法初始化應用程式"), _desc.strWindowTitle, MB_OK | MB_ICONWARNING);
		}
	}

	ClientApp::~ClientApp() {
		if (_hAccelTable != NULL)
			::DestroyAcceleratorTable(_hAccelTable);

		SafeDelete(pScene);
		SafeDelete(pRenderer);

		::CoUninitialize();
	}

	/*
	<summary>註冊視窗類別</summary>
	*/
	ATOM ClientApp::RegisterClass()
	{
		WNDCLASSEX wcex;

		::ZeroMemory(&wcex, sizeof(wcex));
		wcex.cbSize = sizeof(WNDCLASSEX);

		wcex.style = CS_HREDRAW | CS_VREDRAW;
		wcex.lpfnWndProc = WndProc;
		wcex.cbClsExtra = 0;
		wcex.cbWndExtra = 0;
		wcex.hInstance = _desc.hInstance;
		if (_idIcon != 0)
			wcex.hIcon = LoadIcon(_desc.hInstance, MAKEINTRESOURCE(_idIcon));
		wcex.hCursor = ::LoadCursor(NULL, IDC_ARROW);
		wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
		//wcex.lpszMenuName = MAKEINTRESOURCE(IDC_OURGAME);
		if (_desc.strClassName != NULL)
			wcex.lpszClassName = _desc.strClassName;
		//wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

		return RegisterClassEx(&wcex);
	}

	/*
	<summary>儲存執行個體控制代碼並且建立主視窗</summary>
	<param name='nCmdShow'></param>
	<remarks>
	在這個函式中，我們會將執行個體控制代碼儲存在全域變數中，
	並且建立和顯示主程式視窗。
	</remarks>
	*/
	bool ClientApp::InitInstance() {
		//初始化Graphics
		pGraphics = Graphics::GetInstance();
		if (!pGraphics->Initialize())
			return false;

		//建立視窗
		_hWnd = ::CreateWindow(_desc.strClassName,
			_desc.strWindowTitle,
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT,
			0,
			CW_USEDEFAULT,
			0,
			NULL,
			NULL,
			_desc.hInstance,
			NULL);

		if (!_hWnd)
			return false;

		::ShowWindow(_hWnd, _desc.cmdShow);
		::UpdateWindow(_hWnd);

		if (_idAccelerators != 0)
			_hAccelTable = ::LoadAccelerators(_desc.hInstance, MAKEINTRESOURCE(_idAccelerators));

		//初始化Renderer
		Renderer_Desc desc;
		ZeroMemory(&desc, sizeof(Renderer_Desc));
		desc.width = _desc.width;
		desc.height = _desc.height;
		desc.vsync = _desc.vsync;
		desc.isFullScreen = _desc.isFullScreen;
		desc.hWnd = _hWnd;

		//初始化ResourceManager
		pResourceManager = ResourceManager::GetInstance();

		//初始化Renderer
		pRenderer = pGraphics->GetRenderer(desc);

		//初始化Script引擎
		pScriptEngine = ScriptEngine::GetInstance();

		//初始化UIManager
		pUIManager = UIManager::GetInstance();

		//初始化Scene
		pScene = new Scene();

		//WM_PAINT
		InvalidateRect(desc.hWnd, NULL, true);

		return true;
	}

	/*
	<summary>主視窗的訊息迴圈。</summary>
	*/
	void ClientApp::Run() {
		_enableRender = false;
		clock_t lastRender = clock(), now;
		float diff;

		// Initialize the message structure.
		::ZeroMemory(&_msg, sizeof(MSG));

		do {
			try {
				_msg.message = WM_NULL;

				// Handle the windows messages.
				if (::PeekMessage(&_msg, NULL, 0, 0, PM_REMOVE))	{
					if (_hAccelTable != NULL)
						::TranslateAccelerator(_msg.hwnd, _hAccelTable, &_msg);

					if (WM_PAINT != _msg.message) {
						::TranslateMessage(&_msg);
						::DispatchMessage(&_msg);
					}
					else {
						_enableRender = true;
					}
				}

				if (_enableRender) {
					now = clock();
					diff = (float)now - (float)lastRender;

					if (diff >= 33.0f) { //每33ms刷新畫面
						pApp->GetCallBack(WM_PAINT)(_msg.hwnd, _msg.message, _msg.wParam, _msg.lParam);
						lastRender = clock();
					}
				}

				//防止應用程式鎖死系統
				if ((WM_NULL == _msg.message) || (WM_ENTERIDLE == _msg.message))
					::Sleep(1);
			}
			catch (...) {
			}
		} while (WM_QUIT != _msg.message);
	}

	/*
	<summary>處理主視窗的訊息。</summary>
	<param name='hWnd'></param>
	<param name='uMsg'></param>
	<param name='wParam'></param>
	<param name='lParam'></param>
	<returns></returns>
	*/
	LRESULT CALLBACK ClientApp::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
		try {
			CallBackWndFunc func = pApp->GetCallBack(uMsg);
			if (func)
				return func(hWnd, uMsg, wParam, lParam);
			else
				return DefWindowProc(hWnd, uMsg, wParam, lParam);
		}
		catch (...) {
			return S_OK;
		}
	}

	//LRESULT CALLBACK ClientApp::OnCommand(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	//	int wmId = LOWORD(wParam);
	//	int wmEvent = HIWORD(wParam);
	//
	//	// 剖析功能表選取項目:
	//	switch (wmId) {
	//	case IDM_EXIT:
	//		::DestroyWindow(hWnd);
	//		break;
	//	default:
	//		return ::DefWindowProc(hWnd, uMsg, wParam, lParam);
	//	}
	//}

	LRESULT CALLBACK ClientApp::OnDestroy(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
		::PostQuitMessage(0);
		return S_OK;
	}

	LRESULT CALLBACK ClientApp::OnPaint(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
		Renderer* pRender = ClientApp::pRenderer;
		if (pRender != NULL) {
			pRender->Clear();

			//設定Camera到pRender

			//場景描繪(含SkyBox, 地板, 與其他動態的3D物件)
			//pRender->RenderScene(ClientApp::pScene);

			//UI描繪
			if (pUIManager)
				pUIManager->Draw(pRender);

			//翻頁
			pRender->Present();
		}
		else {			
			PAINTSTRUCT Ps;
			HDC hDC = BeginPaint(hWnd, &Ps);
			//....

			EndPaint(hWnd, &Ps);
		}

		return S_OK;
	}

#pragma region Keyboard Input Notifications

	LRESULT CALLBACK ClientApp::OnChar(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		int keyCode = wParam & 0xff;

		UIEvent e;
		e.EventType = UIEventType::Char;
		e.Character = keyCode;
		e.RepCnt = (UINT)LOWORD(lParam);

		pUIManager->OnEvent(e);
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}

	LRESULT CALLBACK ClientApp::OnKeyDown(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		int keyCode = wParam & 0xff;
		pApp->SetKeyStatus(keyCode, true);

		UIEvent e;
		e.EventType = UIEventType::KeyDown;
		e.KeyCode = keyCode;

		e.KeyState.SHIFT = (0 != (GetAsyncKeyState(VK_SHIFT) & 0x8000));
		e.KeyState.LSHIFT = (0 != (GetAsyncKeyState(VK_LSHIFT) & 0x8000));
		e.KeyState.RSHIFT = (0 != (GetAsyncKeyState(VK_RSHIFT) & 0x8000));
		e.KeyState.CONTROL = (0 != (GetAsyncKeyState(VK_CONTROL) & 0x8000));
		e.KeyState.LCONTROL = (0 != (GetAsyncKeyState(VK_LCONTROL) & 0x8000));
		e.KeyState.RCONTROL = (0 != (GetAsyncKeyState(VK_RCONTROL) & 0x8000));
		e.KeyState.MENU = (0 != (GetAsyncKeyState(VK_MENU) & 0x8000));
		e.KeyState.LMENU = (0 != (GetAsyncKeyState(VK_LMENU) & 0x8000));
		e.KeyState.RMENU = (0 != (GetAsyncKeyState(VK_RMENU) & 0x8000));

		pUIManager->OnEvent(e);
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}

	LRESULT CALLBACK ClientApp::OnKeyUp(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		int keyCode = wParam & 0xff;
		pApp->SetKeyStatus(keyCode, false);

		UIEvent e;
		e.EventType = UIEventType::KeyUp;
		e.KeyCode = keyCode;

		e.KeyState.SHIFT = (0 != (GetAsyncKeyState(VK_SHIFT) & 0x8000));
		e.KeyState.LSHIFT = (0 != (GetAsyncKeyState(VK_LSHIFT) & 0x8000));
		e.KeyState.RSHIFT = (0 != (GetAsyncKeyState(VK_RSHIFT) & 0x8000));
		e.KeyState.CONTROL = (0 != (GetAsyncKeyState(VK_CONTROL) & 0x8000));
		e.KeyState.LCONTROL = (0 != (GetAsyncKeyState(VK_LCONTROL) & 0x8000));
		e.KeyState.RCONTROL = (0 != (GetAsyncKeyState(VK_RCONTROL) & 0x8000));
		e.KeyState.MENU = (0 != (GetAsyncKeyState(VK_MENU) & 0x8000));
		e.KeyState.LMENU = (0 != (GetAsyncKeyState(VK_LMENU) & 0x8000));
		e.KeyState.RMENU = (0 != (GetAsyncKeyState(VK_RMENU) & 0x8000));

		pUIManager->OnEvent(e);
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}

#pragma endregion Keyboard Input Notifications

#pragma region Mouse Input Notifications
	LRESULT CALLBACK ClientApp::OnMouseMove(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		UIEvent e;
		e.EventType = UIEventType::MouseMove;
		e.MouseStatus = GET_KEYSTATE_WPARAM(wParam);
		e.WheelDelta = 0;	// GET_WHEEL_DELTA_WPARAM(wParam);
		e.Position.x = LOWORD(lParam);
		e.Position.y = HIWORD(lParam);

		pUIManager->OnEvent(e);
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}

	LRESULT CALLBACK ClientApp::OnMouseWheel(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		UIEvent e;
		e.EventType = UIEventType::MouseWheel;
		e.MouseStatus = GET_KEYSTATE_WPARAM(wParam);
		e.WheelDelta = GET_WHEEL_DELTA_WPARAM(wParam);
		e.Position.x = LOWORD(lParam);
		e.Position.y = HIWORD(lParam);

		pUIManager->OnEvent(e);
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}

	LRESULT CALLBACK ClientApp::OnButtonDblClk(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		UIEvent e;
		e.EventType = UIEventType::MouseButtonDblClk;
		e.MouseStatus = GET_KEYSTATE_WPARAM(wParam);
		e.WheelDelta = 0;	// GET_WHEEL_DELTA_WPARAM(wParam);
		e.Position.x = LOWORD(lParam);
		e.Position.y = HIWORD(lParam);

		pUIManager->OnEvent(e);
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
	LRESULT CALLBACK ClientApp::OnButtonDown(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		UIEvent e;
		e.EventType = UIEventType::MouseButtonDown;
		e.MouseStatus = GET_KEYSTATE_WPARAM(wParam);
		e.WheelDelta = 0;	// GET_WHEEL_DELTA_WPARAM(wParam);
		e.Position.x = LOWORD(lParam);
		e.Position.y = HIWORD(lParam);

		pUIManager->OnEvent(e);
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
	LRESULT CALLBACK ClientApp::OnButtonUp(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		UIEvent e;
		e.EventType = UIEventType::MouseButtonUp;
		e.MouseStatus = GET_KEYSTATE_WPARAM(wParam);
		e.WheelDelta = 0;	// GET_WHEEL_DELTA_WPARAM(wParam);
		e.Position.x = LOWORD(lParam);
		e.Position.y = HIWORD(lParam);

		pUIManager->OnEvent(e);
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
#pragma endregion Mouse Input Notifications

	LRESULT CALLBACK ClientApp::OnSetCursor(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		SetCursor(NULL);  //hidden the cursor
		return S_OK;
	}

	LRESULT CALLBACK ClientApp::OnSysCommand(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		switch (wParam) {
		case SC_MINIMIZE:
			pApp->SetEnableRender(false);
			break;
		case SC_RESTORE:
			pApp->SetEnableRender(true);
			ValidateRect(hWnd, NULL);
			break;
		case SC_CLOSE:
			//Alt+F4觸發(關閉程式)
			::PostQuitMessage(0);
			break;
		}
		return ::DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
} /* namespace System */

#endif