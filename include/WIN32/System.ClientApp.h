/*
* System.ClientApp.h
*
* Code Status: Drafts
*  Created on: Taiwan
*      Author: player
*/

#include "../stdafx.h"

#if defined(_WINDOWS) && ( _APP_MODE == _APP_MODE_CLIENT)

#ifndef SYSTEM_APPLICATION_H_
#define SYSTEM_APPLICATION_H_

#if _MSC_VER > 1000
#pragma once
#endif

#include <windows.h>
#include "../System.AutoPtr.h"
#include "../System.String.h"
#include "../System.Drawing.Math.h"
#include "../System.Collections.Map.h"
#include "../System.ResourceManager.h"

typedef struct ClientApp_Desc {
	int argc;
	char **argv;
	unsigned int width;
	unsigned int height;
	bool isFullScreen;
	bool vsync;

	HINSTANCE hInstance;
	int cmdShow;
	LPTSTR strClassName;
	LPTSTR strWindowTitle;
}  ClientApp_Desc;

typedef LRESULT(CALLBACK* CallBackWndFunc)(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

namespace System {
	namespace Drawing {
		class Graphics;
		class Renderer;
		class Scene;

		namespace UI {
			class UIManager;
		} /* namespace UI */
	} /* namespace Drawing */
	class ScriptEngine;
} /* namespace System */

using namespace System::Collections;
using namespace System::Drawing;
using namespace System::Drawing::UI;

namespace System {
	class ClientApp {
		//private:
	protected:
		HWND _hWnd;
		MSG _msg;
		HACCEL _hAccelTable;
		int _idIcon;
		int _idAccelerators;

		ClientApp_Desc& _desc;
		bool _enableRender;
		bool _KeyStatus[256];

		static CallBackWndFunc _WndFunc[WM_USER];
		static Map<UINT, CallBackWndFunc> _UserWndFunc;

		static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	public:
		ClientApp(ClientApp_Desc& desc);
		virtual ~ClientApp();

		/*
		<summary>傳回Pentium以上的開機到現在的時間(以CPU的時脈週期為單位)</summary>
		<returns>這個數值隨著電腦開機到現在的時間, 以及CPU的時脈數而遞增</returns>
		*/
		__int64 GetMachineCycleCount(void)
		{
			__int64 qwCycles;

			__asm {
				// won't work on 486 or below - only pentium or above
				rdtsc

					lea		ebx, qwCycles
					mov[ebx], eax
					mov[ebx + 4], edx
			};

			return qwCycles;
		}

		void SetKeyStatus(UINT key, bool isKeyDown) {
			_KeyStatus[key & 0xff] = isKeyDown;
		}

		bool GetKeyStatus(UINT key) {
			return _KeyStatus[key & 0xff];
		}

		void SetEnableRender(bool isEnable) {
			_enableRender = isEnable;
		}

		bool SGtEnableRender() {
			return _enableRender;
		}

		inline void SetCallBack(UINT id, CallBackWndFunc func) {
			if (id < WM_USER)
				_WndFunc[id] = func;
			else
				_UserWndFunc.SetAt(id, func);
		}

		inline CallBackWndFunc GetCallBack(UINT id) {
			CallBackWndFunc func;
			if (id < WM_USER) 
				func = _WndFunc[id];
			else if (!_UserWndFunc.Lookup(id, func))
				func = DefWindowProc;
			return func;
		}

		virtual ATOM RegisterClass();
		virtual bool InitInstance();

		virtual void Run();

		inline int GetExitCode() {
			return (int)_msg.wParam;
		}

		inline bool GetKeyState(int VirtKey) {
			return _KeyStatus[VirtKey & 0xff];
		}

		//----------------
		//static LRESULT CALLBACK OnCommand(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		static LRESULT CALLBACK OnDestroy(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		static LRESULT CALLBACK OnPaint(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		static LRESULT CALLBACK OnSetCursor(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		static LRESULT CALLBACK OnSysCommand(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

		//Keyboard Input Notifications
		static LRESULT CALLBACK OnChar(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		static LRESULT CALLBACK OnKeyDown(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		static LRESULT CALLBACK OnKeyUp(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

		//Mouse Input Notifications
		static LRESULT CALLBACK OnMouseMove(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		static LRESULT CALLBACK OnMouseWheel(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		static LRESULT CALLBACK OnButtonDblClk(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		static LRESULT CALLBACK OnButtonDown(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		static LRESULT CALLBACK OnButtonUp(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

		static ResourceManager* pResourceManager;
		static Graphics* pGraphics;
		static Renderer* pRenderer;
		static ScriptEngine* pScriptEngine;
		static UIManager* pUIManager;
		static Scene* pScene;
	};

	static ClientApp* pApp = NULL;
} /* namespace System */

#endif /* SYSTEM_APPLICATION_H_ */

#endif