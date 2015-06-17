/*
* System.Drawing.UI.Image.h
*
* Code Status: Drafts
*  Created on: Taiwan
*      Author: player
*/

#include "../../include/UI/System.Drawing.UI.Image.h"

namespace System {
	namespace Drawing {
		namespace UI {
			Image::Image(String& id)
			{
				Enable  = true;				//啟用
				Visibility  = true;			//可視
				AllowFocus = false;			//允許焦點
				AllowKeyEvent = false;		//允許鍵盤事件
				AllowMouseEvent = false;	//允許滑鼠事件

				IsMouseOver = false;

				ID = id;
			}

			Image::~Image()
			{
			}

			//顯示
			void Image::Draw(Renderer* pRenderer)
			{
			}

			//事件處理
			void Image::OnEvent(UIEvent& e)
			{
			}
		} /* namespace UI */
	} /* namespace Drawing */
} /* namespace System */

