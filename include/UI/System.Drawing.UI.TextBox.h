/*
* System.Drawing.UI.TexeBox.h
*
* Code Status: Drafts
*  Created on: Taiwan
*      Author: player
*/

#include "../stdafx.h"

#ifndef SYSTEM_DRAWING_UI_TEXTBOX_H_
#define SYSTEM_DRAWING_UI_TEXTBOX_H_

#if _MSC_VER > 1000
#pragma once
#endif

#include "../System.String.h"
#include "System.Drawing.UI.Element.h"

namespace System {
	namespace Drawing {
		class Renderer;

		namespace UI {
			struct UIEvent;

			class TextBox : public Element
			{
			//private:
			protected:
				bool _IsInsertMode;	//是否為插入模式
				int _CursorPostion;	//游標位置

			public:
				TextBox(String& id);
				virtual ~TextBox();

				String Text;

				//Style更新
				void UpdateStyle();

				//顯示
				void Draw(Renderer* pRenderer);

				//事件處理
				void OnEvent(UIEvent& e);
			};
		} /* namespace UI */
	} /* namespace Drawing */
} /* namespace System */

#endif /* SYSTEM_DRAWING_UI_TEXTBOX_H_ */