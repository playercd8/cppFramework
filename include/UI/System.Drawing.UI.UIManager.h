/*
* System.Drawing.UI.UIManager.h
*
* Code Status: Drafts
*  Created on: Taiwan
*      Author: player
*/

#include "../stdafx.h"

#ifndef SYSTEM_DRAWING_UI_UIMANAGER_H_
#define SYSTEM_DRAWING_UI_UIMANAGER_H_

#if _MSC_VER > 1000
#pragma once
#endif

#include "../System.Collections.List.h"
#include "../System.Drawing.Math.h"
#include "../System.OOP.h"
#include "../System.String.h"

using namespace System::Collections;

namespace System {
	namespace Drawing {
		class Renderer;

		namespace UI {
			class Element;
			struct UIEvent;

			class UIManager : public Singleton<UIManager>
			{
			private:
				List<Element*> _all;
				Element* _pFocus;
				Element* _pGameController;

				//protected:
			public:
				UIManager();
				virtual ~UIManager();

				void UpdateZindex();
				
				void SetFocus(Element* pFocus);
				Element* GetFocus() {
					return _pFocus;
				}

				void SetGameController(Element* pGameController) {
					_pGameController = pGameController;
				}
				Element* GetGameController() {
					return _pGameController;
				}

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

#endif /* SYSTEM_DRAWING_UI_UIMANAGER_H_ */