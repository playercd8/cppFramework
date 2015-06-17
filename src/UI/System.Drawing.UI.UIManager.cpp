/*
* System.Drawing.UI.UIManager.cpp
*
* Code Status: Drafts
*  Created on: Taiwan
*      Author: player
*/

#include "../../include/UI/System.Drawing.UI.UIManager.h"
#include "../../include/UI/System.Drawing.UI.Element.h"

namespace System {
	namespace Drawing {
		namespace UI {
			UIManager::UIManager() :
				_pFocus(NULL),
				_pGameController(NULL)
			{
			}

			UIManager::~UIManager() {
			}

			void UIManager::SetFocus(Element* pFocus)
			{
				UIEvent e;
				//失去Focus
				if (_pFocus) {
					e.EventType = Blur;
					_pFocus->OnEvent(e);
				}

				//得到Focus
				_pFocus = pFocus;
				if (_pFocus) {
					e.EventType = Focus;
					_pFocus->OnEvent(e);
				}
			}

			void UIManager::UpdateZindex()
			{
				_all.Sort();
			}

			void UIManager::AddElement(Element* pElem) {
				_all.AddTail(pElem);
			}

			void UIManager::RemoveElement(Element* pElem)
			{
				//是否為焦點物件
				if (_pFocus == pElem) {
					SetFocus(NULL);
				}

				Element* pElem2;
				List<Element*>::Iterator iter = _all.GetHeadPosition();
				while (_all.iteratorValid(iter)) {
					pElem2 = _all.GetAt(iter);
					if (pElem2 == pElem) {
						_all.RemoveAt(iter);
						return;
					}
				}
			}

			void UIManager::RemoveElement(String ID)
			{
				Element* pElem;
				List<Element*>::Iterator iter = _all.GetHeadPosition();
				while (_all.iteratorValid(iter)) {
					pElem = _all.GetAt(iter);
					if (pElem->ID.Compare(ID) == 0) {
						//是否為焦點物件
						if (_pFocus == pElem) {
							SetFocus(NULL);
						}

						_all.RemoveAt(iter);
						return;
					}
				}
			}

			void UIManager::RemoveAllElement()
			{
				_pFocus = NULL;
				_all.RemoveAll();
			}

			Element* UIManager::FindElement(String ID)
			{
				Element* pElem;
				List<Element*>::Iterator iter = _all.GetHeadPosition();
				while (_all.iteratorValid(iter)) {
					pElem = _all.GetAt(iter);
					if (pElem->ID.Compare(ID) == 0) {
						return pElem;
					}
				}
				return NULL;
			}

			//顯示
			void UIManager::Draw(Renderer* pRenderer)
			{
				Element* pElem;
				List<Element*>::Iterator iter = _all.GetHeadPosition();
				while (_all.iteratorValid(iter)) {
					pElem = _all.GetAt(iter);
					if (pElem->Visibility) {
						pElem->Draw(pRenderer);
					}
				}
			}

			//事件處理
			void UIManager::OnEvent(UIEvent& e)
			{
				switch (e.EventType) {
				case KeyDown:
				case KeyUp:
				case Char:
					if (_pFocus) {
						_pFocus->OnEvent(e);
					}
					else if (_pGameController) {
						_pGameController->OnEvent(e);
					}
					break;
				case MouseMove:
				{
					//MouseMove
					if (_pFocus) {
						_pFocus->OnEvent(e);
					}
					else if (_pGameController) {
						_pGameController->OnEvent(e);
					}

					//MouseOut, MouseOver,
					Point pt(e.Position);
					Element* pElem;
					List<Element*>::Iterator iter = _all.GetHeadPosition();
					while (_all.iteratorValid(iter)) {
						pElem = _all.GetAt(iter);
						if (pElem->Enable) {
							if (pElem->PtInRect(pt)) {
								e.EventType = MouseOver;
								pElem->OnEvent(e);
								pElem->IsMouseOver = true;
							}
							else if (pElem->IsMouseOver) {
								e.EventType = MouseOut;
								pElem->OnEvent(e);
								pElem->IsMouseOver = false;
							}
						}
					}
				}
					break;
				case MouseButtonDown:
				case MouseButtonDblClk:
				case MouseButtonUp:
				case MouseWheel:
				{
					Point pt(e.Position);
					if ((_pFocus) && _pFocus->PtInRect(pt)) {
						_pFocus->OnEvent(e);
					}
					else {
						bool isRunEvent = false;
						Element* pElem;
						List<Element*>::Iterator iter = _all.GetHeadPosition();
						while (_all.iteratorValid(iter)) {
							pElem = _all.GetAt(iter);
							if ((pElem->Enable) &&
								pElem->PtInRect(pt)) {
								if ((e.EventType == MouseButtonDown) &&
									(pElem->AllowFocus)) {
									SetFocus(pElem);
								}
								pElem->OnEvent(e);
								isRunEvent = true;
								break;
							}
						}

						if ((isRunEvent == false) &&
							(_pGameController)) {
							_pGameController->OnEvent(e);
						}
					}
				}
					break;

				case Other:
				default:
					break;
				}
			}
		} /* namespace UI */
	} /* namespace Drawing */
} /* namespace System */