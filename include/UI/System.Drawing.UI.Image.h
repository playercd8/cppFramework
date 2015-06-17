﻿/*
* System.Drawing.UI.Image.h
*
* Code Status: Drafts
*  Created on: Taiwan
*      Author: player
*/

#include "../stdafx.h"

#ifndef SYSTEM_DRAWING_UI_IMAGE_H_
#define SYSTEM_DRAWING_UI_IMAGE_H_

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

			class Image : public Element
			{
			public:
				Image(String& id);
				virtual ~Image();

				//顯示
				void Draw(Renderer* pRenderer);

				//事件處理
				void OnEvent(UIEvent& e);

			};
		} /* namespace UI */
	} /* namespace Drawing */
} /* namespace System */

#endif /* SYSTEM_DRAWING_UI_IMAGE_H_ */