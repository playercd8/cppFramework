/*
 * System.Drawing.Font_DX9.cpp
 *
 * Code Status: Drafts
 *  Created on: Taiwan
 *      Author: player
 */

#include "../../include/stdafx.h"
#if (_DRAWING_MODE == _DRAWING_MODE_DX9)

#include "../../include/DX9/System.Drawing.Font.h"
#include "../../include/DX9/System.Drawing.Renderer.h"
#include "../../include/DX9/System.Drawing.Sprite.h"

namespace System {
	namespace Drawing {
		//---------------------------------------------------------------------------------------------------------
		// class Font

		Font::Font(Font_Desc& desc, Renderer* pRender) 
		{
			HRESULT hr;
			V(D3DXCreateFontIndirect(
				pRender->GetDevice(),	//[in]	LPDIRECT3DDEVICE9 pDevice,
				&desc,					//[in]   const D3DXFONT_DESC *pDesc,
				&_ptr					//[out]  LPD3DXFONT *ppFont
				));

			if FAILED(hr) 
				_ptr = NULL;
		}

		Font::Font(ID3DXFont* pFont) {
			_ptr = pFont;
		}
	} /* namespace Drawing */
} /* namespace System */

#endif