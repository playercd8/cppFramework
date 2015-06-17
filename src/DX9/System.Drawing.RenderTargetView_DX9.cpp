/*
 * System.Drawing.RenderTargetView_DX9.cpp
 *
 *  Created on: Taiwan
 *      Author: player
 */

#include "../../include/stdafx.h"
#if (_DRAWING_MODE == _DRAWING_MODE_DX9)

#include "../../include/DX9/System.Drawing.RenderTargetView.h"
#include "../../include/DX9/System.Drawing.Renderer.h"
#include "../../include/DX9/System.Drawing.Texture.h"

namespace System {
	namespace Drawing {
		//---------------------------------------------------------------------------------------------------------
		// class RenderTargetView

		RenderTargetView::RenderTargetView(RenderTargetView_Desc& desc, Renderer* pRender)
		{
			HRESULT hr;
			V(pRender->GetDevice()->CreateRenderTarget(
				desc.Width,					//[in]	UINT Width,
				desc.Height,				//[in]	UINT Height,
				desc.Format,				//[in]	D3DFORMAT Format,
				desc.MultiSample,			//[in]	D3DMULTISAMPLE_TYPE MultiSample,
				desc.MultisampleQuality,	//[in]	DWORD MultisampleQuality,
				desc.Lockable,				//[in]	BOOL Lockable,
				&_ptr,						//[out]	IDirect3DSurface9 **ppSurface,
				desc.pSharedHandle			//[in]	HANDLE *pSharedHandle
				));

			if FAILED(hr)
				_ptr = NULL;
		}

		RenderTargetView::RenderTargetView(IDirect3DSurface9* pSurface)
		{
			_ptr = NULL;

			if (pSurface) {
				HRESULT hr;
				D3DSURFACE_DESC desc;
				V(pSurface->GetDesc(&desc));
				if (SUCCEEDED(hr) && (desc.Usage & D3DUSAGE_RENDERTARGET)) {
					_ptr = pSurface;
				}
			}
		}

		Texture2D* RenderTargetView::GetTexture2D() {
			if (_ptr == NULL)
				return (Texture2D*)NULL;

			HRESULT hr;
			void *pContainer = NULL;
			V(_ptr->GetContainer(IID_IDirect3DTexture9, &pContainer));
			if (SUCCEEDED(hr) && pContainer)
				return new Texture2D((IDirect3DTexture9*)pContainer);

			return (Texture2D*)NULL;
		}
	} /* namespace Drawing */
} /* namespace System */

#endif