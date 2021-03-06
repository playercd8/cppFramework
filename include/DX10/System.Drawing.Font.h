﻿/*
 * System.Drawing.Font.h
 *
 *  Created on: Taiwan
 *      Author: player
 */

#include "../stdafx.h"
#if (_DRAWING_MODE == _DRAWING_MODE_DX10)

#ifndef SYSTEM_DRAWING_FONT_H_
#define SYSTEM_DRAWING_FONT_H_

#if _MSC_VER > 1000
#pragma once
#endif

#include "DX10.h"
#include "../System.ComPtr.h"

namespace System {
	namespace Drawing {
		class Renderer;
		Renderer* GetDefaultRendererPtr();

		typedef D3DX10_FONT_DESC Font_Desc;

		class Font : public ComPtr < ID3DX10Font > {
			//private:
			//protected:
		public:
			Font(Font_Desc& desc, Renderer* pRender = DefaultRendererPtr);
			Font(ID3DX10Font* pFont = NULL);

			//int DrawText(LPCTSTR pString, int Count, LPRECT pRect, DWORD format, DWORD color);
		};
	} /* namespace Drawing */
} /* namespace System */

#endif /* SYSTEM_DRAWING_FONT_H_ */
#endif
