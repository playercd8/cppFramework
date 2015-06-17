/*
 * System.Drawing.Font_DX10.cpp
 *
 *  Created on: Taiwan
 *      Author: player
 */

#include "../../include/stdafx.h"
#if (_DRAWING_MODE == _DRAWING_MODE_DX10)

#include "../../include/DX10/System.Drawing.Font.h"
#include "../../include/DX10/System.Drawing.Renderer.h"

namespace System {
	namespace Drawing {
		//---------------------------------------------------------------------------------------------------------
		// class Font

		Font::Font(Font_Desc& desc, Renderer* pRender)
		{
			HRESULT hr;
			V(D3DX10CreateFontIndirect(
				pRender->GetDevice(),	//[in]  ID3D10Device *pDevice,
				&desc,					//[in]   const D3DX10_FONT_DESC *pDesc,
				&_ptr					//[out]  LPD3DX10FONT *ppFont
				));

			if FAILED(hr)
				_ptr = NULL;
		}

		Font::Font(ID3DX10Font* pFont) {
			_ptr = pFont;
		}

		/*
		int Font::DrawText(LPCTSTR pString, int count, LPRECT pRect, DWORD format, DWORD color) {
		#if defined(_UNICODE)
		return _ptr->DrawTextW(
		_pSprite,			//[in]  LPD3DXSPRITE pSprite,
		pString,			//[in]  LPCWSTR pString,
		count,				//[in]  INT Count,
		pRect,				//[in]  LPRECT pRect,
		format,				//[in]  DWORD Format,
		color				//[in]  D3DCOLOR Color
		);
		#else
		return  _ptr->DrawTextA(
		_pSprite,			//[in]  LPD3DXSPRITE pSprite,
		pString,			//[in]  LPCSTR pString,
		count,				//[in]  INT Count,
		pRect,				//[in]  LPRECT pRect,
		format,				//[in]  DWORD Format,
		color				//[in]  D3DCOLOR Color
		);
		#endif
		}
		*/
	} /* namespace Drawing */
} /* namespace System */

#endif