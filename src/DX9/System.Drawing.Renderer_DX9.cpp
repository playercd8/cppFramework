/*
* System.Drawing.Renderer_DX9.cpp
*
*  Created on: Taiwan
*      Author: player
*/

#include "../../include/stdafx.h"

#if (_DRAWING_MODE == _DRAWING_MODE_DX9)
#include "../../include/DX9/System.Drawing.Renderer.h"
#include "../../include/DX9/System.Drawing.Font.h"
#include "../../include/System.ComPtr.h"

namespace System {
	namespace Drawing {
		//Renderer*	Renderer::DefaultPtr = NULL;

		Renderer::Renderer(Renderer_Desc& desc)
		{
			memcpy(this, &desc, sizeof(Renderer_Desc));
		}

		Renderer::~Renderer()
		{
			SafeRelease(_pSwapChain);
			SafeRelease(_pDevice);
		}

		void Renderer::Clear()
		{
			_pDevice->Clear(
				0,
				NULL,
				D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL,
				_BkColor,
				1.0f,
				0);
		}

		void Renderer::Present()
		{
			HWND hDestWindowOverride;

			if (isFullScreen || (hWnd == NULL))
				hDestWindowOverride = NULL;
			else
				hDestWindowOverride = hWnd;

			_pSwapChain->Present(
				NULL,					//[in]  const RECT *pSourceRect,
				NULL,					//[in]  const RECT *pDestRect,
				hDestWindowOverride,	//[in]  HWND hDestWindowOverride,
				NULL,					//[in]  const RGNDATA *pDirtyRegion,
				NULL					//[in]  DWORD dwFlags
				);
		}

		//頂點格式
		struct D3DTLVERTEX {
			float x, y, z;
			float rhw;
			DWORD color;
			float tu0, tv0;

			enum { FVF = D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1 };
		};

		void Renderer::DrawTexture2D(Texture2D& texture, Vector2& dest1, Vector2& dest2, Vector2& src1, Vector2& src2, DWORD color)
		{
			float _invW = texture._invW;
			float _invH = texture._invH;

			D3DTLVERTEX v[] = {
					{ dest1.x, dest1.y, 0, 1, color, src1.x * _invW, src1.y * _invH },
					{ dest2.x, dest1.y, 0, 1, color, src2.x * _invW, src1.y * _invH },
					{ dest1.x, dest2.y, 0, 1, color, src1.x * _invW, src2.y * _invH },
					{ dest2.x, dest2.y, 0, 1, color, src2.x * _invW, src2.y * _invH },
			};

			_pDevice->SetTexture(0, texture);
			_pDevice->SetFVF(D3DTLVERTEX::FVF);
			_pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, v, sizeof(D3DTLVERTEX));
		}

		void Renderer::DrawTexture2D(Texture2D& texture, float x1, float y1, float x2, float y2,
			float sx1, float sy1, float sx2, float sy2, DWORD color)
		{
			float _invW = texture._invW;
			float _invH = texture._invH;

			D3DTLVERTEX v[] = {
					{ x1, y1, 0, 1, color, sx1 * _invW, sy1 * _invH },
					{ x2, y1, 0, 1, color, sx2 * _invW, sy1 * _invH },
					{ x1, y2, 0, 1, color, sx1 * _invW, sy2 * _invH },
					{ x2, y2, 0, 1, color, sx2 * _invW, sy2 * _invH },
			};

			_pDevice->SetTexture(0, texture);
			_pDevice->SetFVF(D3DTLVERTEX::FVF);
			_pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, v, sizeof(D3DTLVERTEX));
		}

		void Renderer::DrawText(Font& font, LPCTSTR pString, int count, LPRECT pRect, DWORD format, DWORD color) {
			LPD3DXSPRITE pSprite = NULL;

#if defined(_UNICODE)
			font.GetPtr()->DrawTextW(
				pSprite,			//[in]  LPD3DXSPRITE pSprite,
				pString,			//[in]  LPCWSTR pString,
				count,				//[in]  INT Count,
				pRect,				//[in]  LPRECT pRect,
				format,				//[in]  DWORD Format,
				color				//[in]  D3DCOLOR Color
				);
#else
			font.GetPtr()->DrawTextA(
				pSprite,			//[in]  LPD3DXSPRITE pSprite,
				pString,			//[in]  LPCSTR pString,
				count,				//[in]  INT Count,
				pRect,				//[in]  LPRECT pRect,
				format,				//[in]  DWORD Format,
				color				//[in]  D3DCOLOR Color
				);
#endif
		}

		void Renderer::RenderScene(Scene& scene)
		{
		}
	} /* namespace Drawing */
} /* namespace System */

#endif