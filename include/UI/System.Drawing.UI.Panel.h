/*
* System.Drawing.UI.Panel.h
*
* Code Status: Drafts
*  Created on: Taiwan
*      Author: player
*/

#include "../stdafx.h"

#ifndef SYSTEM_DRAWING_UI_Panel_H_
#define SYSTEM_DRAWING_UI_Panel_H_

#if _MSC_VER > 1000
#pragma once
#endif

#include "../System.Collections.List.h"
#include "../System.String.h"
#include "System.Drawing.UI.Element.h"

namespace System {
	namespace Drawing {
		class Renderer;

		namespace UI {
			struct UIEvent;

			class Panel : public Element
			{
			private:
				List<Element*> _all;

			public:
				Panel(String& id);
				virtual ~Panel();

				void UpdateZindex();
				void AddElement(Element* pElem);
				void RemoveElement(Element* pElem);
				void RemoveElement(String ID);
				void RemoveAllElement();
				Element* FindElement(String ID);
				
				//顯示
				void Draw(Renderer* pRenderer);

				//事件處理
				void OnEvent(UIEvent& e);

			};
		} /* namespace UI */
	} /* namespace Drawing */
} /* namespace System */

#endif /* SYSTEM_DRAWING_UI_Label_H_ */