/*
* System.Drawing.UI.Element.h
*
* Code Status: Drafts
*  Created on: Taiwan
*      Author: player
*		http://www.w3.org/TR/html5/dom.htm
*/

#include "../stdafx.h"

#ifndef SYSTEM_DRAWING_UI_ELEMENT_H_
#define SYSTEM_DRAWING_UI_ELEMENT_H_

#if _MSC_VER > 1000
#pragma once
#endif

#include "../System.Collections.Map.h"
#include "../System.Drawing.Math.h"
#include "../System.String.h"
#include "../System.OOP.h"
#include "../System.Variant.h"

using namespace System::Collections;

namespace System {
	namespace Drawing {
		class Renderer;

		namespace UI {
			enum UIEventType {
				KeyDown, KeyUp,
				Char,
				MouseMove, MouseButtonDblClk, MouseButtonDown, MouseButtonUp, MouseWheel,
				MouseOut, MouseOver,
				Blur, Focus,
				Other
			};

			typedef struct UIEvent {
				UIEventType EventType;
				union {
					//KeyDown, 			KeyUp,
					struct {
						//unsigned char KeyState;
						struct {
							unsigned int SHIFT : 1;
							unsigned int LSHIFT : 1;
							unsigned int RSHIFT : 1;
							unsigned int CONTROL : 1;
							unsigned int LCONTROL : 1;
							unsigned int RCONTROL : 1;
							unsigned int MENU : 1;
							unsigned int LMENU : 1;
							unsigned int RMENU : 1;
						} KeyState;
						unsigned char KeyCode;
					};
					//Char
					struct {
						TCHAR Character;	//字元
						UINT RepCnt;		//重複次數
					};
					//MouseMove, MouseButtonDblClk, MouseButtonDown, MouseButtonUp,
					struct {
						WORD MouseStatus;	// GET_KEYSTATE_WPARAM(wParam);
						WORD WheelDelta;	// GET_WHEEL_DELTA_WPARAM(wParam);
						_Point Position;	// x = LOWORD(lParam); y = HIWORD(lParam);
					};
					//Other
					struct {
						UINT uMsg;
						WPARAM wParam;
						LPARAM lParam;
					};
				};
			} UIEvent;


			typedef struct _Element {
				//基礎
				String ID;

				//顯示必須
				Point Position;
				Size Size;
				DWORD Zindex;		//z-index 數字越大的在越上面，反之則在越下

				union {
					DWORD Flags;
					struct {
						unsigned int Enable : 1;			//啟用
						unsigned int Visibility : 1;		//可視
						unsigned int AllowFocus : 1;		//允許焦點
						unsigned int AllowKeyEvent : 1;		//允許鍵盤事件
						unsigned int AllowMouseEvent : 1;	//允許滑鼠事件
						unsigned int Reserve1 : 1;			//保留
						unsigned int Reserve2 : 1;
						unsigned int IsMouseOver : 1;
					};
				};

				IAttributes<String, Variant>	Attributes;
				IAttributes<String, Variant>	Style;
			} _Element;

			class Element :public _Element
			{
			public:
				inline bool PtInRect(Point& pt)
				{
					return (pt.x >= Position.x) &&
						(pt.y >= Position.y) &&
						(pt.x <= (Position.x + Size.cx)) &&
						(pt.y <= (Position.y + Size.cy));
				}

				//顯示
				virtual void Draw(Renderer* pRenderer) = 0;

				//事件處理
				virtual void OnEvent(UIEvent& e) = 0;

				//private:
			protected:
				static String _css;
				static String _onkeydown;
				static String _onkeyup;
				static String _onchange;
			};

			inline bool operator < (const Element& a, const Element& b) {
				return (a.Zindex < b.Zindex);
			}
		} /* namespace UI */
	} /* namespace Drawing */
} /* namespace System */

using namespace System::Drawing::UI;

#endif /* SYSTEM_DRAWING_UI_ELEMENT_H_ */