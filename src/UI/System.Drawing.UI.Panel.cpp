/*
* System.Drawing.UI.Panel.cpp
*
* Code Status: Drafts
*  Created on: Taiwan
*      Author: player
*/

#include "../../include/UI/System.Drawing.UI.Panel.h"
#include "../../include/UI/System.Drawing.UI.UIManager.h"

namespace System {
	namespace Drawing {
		namespace UI {
			Panel::Panel(String& id)
			{
				Enable = true;				//啟用
				Visibility = true;			//可視
				AllowFocus = true;			//允許焦點
				AllowKeyEvent = true;		//允許鍵盤事件
				AllowMouseEvent = true;		//允許滑鼠事件	

				IsMouseOver = false;

				ID = id;
			}

			Panel::~Panel()
			{
			}

			void Panel::UpdateZindex()
			{
				_all.Sort();
			}

			void Panel::AddElement(Element* pElem) {
				_all.AddTail(pElem);
			}

			void Panel::RemoveElement(Element* pElem)
			{
				//是否為焦點物件
				UIManager* pUIManager = UIManager::GetInstance();
				if (pUIManager->GetFocus() == pElem) {
					pUIManager->SetFocus(NULL);
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

			void Panel::RemoveElement(String ID)
			{
				Element* pElem;
				List<Element*>::Iterator iter = _all.GetHeadPosition();
				while (_all.iteratorValid(iter)) {
					pElem = _all.GetAt(iter);
					if (pElem->ID.Compare(ID) == 0) {
						//是否為焦點物件
						UIManager* pUIManager = UIManager::GetInstance();
						if (pUIManager->GetFocus() == pElem) {
							pUIManager->SetFocus(NULL);
						}

						_all.RemoveAt(iter);
						return;
					}
				}
			}

			void Panel::RemoveAllElement()
			{
				_all.RemoveAll();
			}

			Element* Panel::FindElement(String ID)
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
			void Panel::Draw(Renderer* pRenderer)
			{
				//先畫Panel (底圖與標框)

				//再畫Element
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
			void Panel::OnEvent(UIEvent& e)
			{
				UIManager* pUIManager = UIManager::GetInstance();

				switch (e.EventType) {
				case KeyDown:
				case KeyUp:
				case Char:
					break;
				case MouseMove:
				{
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
					{
						bool isRunEvent = false;
						Element* pElem;
						List<Element*>::Iterator iter = _all.GetHeadPosition();
						while (_all.iteratorValid(iter)) {
							pElem = _all.GetAt(iter);
							if ((pElem->Enable) &&
								pElem->PtInRect(pt)) {
								if ((e.EventType == MouseButtonDown) &&
									(pElem->AllowFocus)) {
									pUIManager->SetFocus(pElem);
								}
								pElem->OnEvent(e);
								isRunEvent = true;
								break;
							}
						}

						if ((isRunEvent == false) &&
							(pUIManager->GetGameController())) {
							pUIManager->GetGameController()->OnEvent(e);
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