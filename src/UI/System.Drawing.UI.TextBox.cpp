/*
* System.Drawing.UI.TextBox.cpp
*
* Code Status: Drafts
*  Created on: Taiwan
*      Author: player
*/

#include "../../include/UI/System.Drawing.UI.TextBox.h"
#include "../../include/System.ScriptEngine.h"
#include "../../include/Win32/System.ComSafeArray.h"

namespace System {
	namespace Drawing {
		namespace UI {
			TextBox::TextBox(String& id)
			{
				Enable = true;				//啟用
				Visibility = true;			//可視
				AllowFocus = true;			//允許焦點
				AllowKeyEvent = true;		//允許鍵盤事件
				AllowMouseEvent = true;		//允許滑鼠事件

				IsMouseOver = false;		//滑鼠游標是否在控制項上?
				_IsInsertMode = false;		//是否為插入模式
				_CursorPostion - 0;			//游標位置

				ID = id;
				Text = "";
			}

			TextBox::~TextBox()
			{
			}

			//Style更新
			void TextBox::UpdateStyle() 
			{
				//1.套用CSS
				String css;
				css = Attributes.Get(_css, String::EmptyString);
				if (!css.IsEmpty()) {
					//分割css (可能有多個css)
				}

				//2.套用Style
				if (!Style.IsEmpty()) {
				}
			}

			//顯示
			void TextBox::Draw(Renderer* pRenderer)
			{
				if (Visibility) {
					//1.Draw底圖
					//2.Draw文字
					//3.Draw游標
				}
			}

			//事件處理
			void TextBox::OnEvent(UIEvent& e)
			{
				try {
					String func;
					switch (e.EventType) {
					case KeyDown:
						func = Attributes.Get(_onkeydown, String::EmptyString);
						if (!func.IsEmpty()) {
							ComSafeArray SafeArray;

							_variant_t var;
							var = e.KeyCode;
							SafeArray.Create(VT_VARIANT, 1, 0, 1);		// 1 parameter
							SafeArray.PutElement(0, (void*)&var);		// parameter1 -> index 0
							LPSAFEARRAY saParameters = SafeArray.GetArray();

							_variant_t varRet;
							if (FAILED(ScriptEngine::GetInstance()->RunProcedure(func, &saParameters, &varRet)))
								throw;
						}
						break;
					case KeyUp:
						func = Attributes.Get(_onkeyup, String::EmptyString);
						if (!func.IsEmpty()) {
							ComSafeArray SafeArray;

							_variant_t var;
							var = e.KeyCode;
							SafeArray.Create(VT_VARIANT, 1, 0, 1);		// 1 parameter
							SafeArray.PutElement(0, (void*)&var);		// parameter1 -> index 0
							LPSAFEARRAY saParameters = SafeArray.GetArray();

							_variant_t varRet;
							if (FAILED(ScriptEngine::GetInstance()->RunProcedure(func, &saParameters, &varRet)))
								throw;
						}
						break;
					case Char:
						if (_IsInsertMode) {
						}
						else {
							Text += e.Character;
						}						

						func = Attributes.Get(_onchange, String::EmptyString);
						if (!func.IsEmpty()) {
							ComSafeArray SafeArray;

							_variant_t var;
							var = "";
							SafeArray.Create(VT_VARIANT, 1, 0, 1);		// 1 parameter
							SafeArray.PutElement(0, (void*)&var);		// parameter1 -> index 0
							LPSAFEARRAY saParameters = SafeArray.GetArray();

							_variant_t varRet;
							if (FAILED(ScriptEngine::GetInstance()->RunProcedure(func, &saParameters, &varRet)))
								throw;
						}
						break;
					}
				}
				catch (...) {
					//String err = ScriptEngine::GetInstance()->GetErrorString();
				}
			}
		} /* namespace UI */
	} /* namespace Drawing */
} /* namespace System */