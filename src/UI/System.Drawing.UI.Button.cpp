/*
* System.Drawing.UI.Button.cpp
*
* Code Status: Drafts
*  Created on: Taiwan
*      Author: player
*/

#include "../../include/UI/System.Drawing.UI.Button.h"

namespace System {
	namespace Drawing {
		namespace UI {
			Button::Button(String& id)
			{
				Enable = true;				//啟用
				Visibility = true;			//可視
				AllowFocus = true;			//允許焦點
				AllowKeyEvent = true;		//允許鍵盤事件
				AllowMouseEvent = true;		//允許滑鼠事件	

				IsMouseOver = false;

				ID = id;
			}

			Button::~Button()
			{
			}

			//顯示
			void Button::Draw(Renderer* pRenderer) {
			}

			//事件處理
			void Button::OnEvent(UIEvent& e)
			{
			}
		} /* namespace UI */
	} /* namespace Drawing */
} /* namespace System */