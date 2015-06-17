/*
 * System.Drawing.RenderTargetView_DX9.cpp
 *
 *  Created on: Taiwan
 *      Author: player
 */

#include "../../include/stdafx.h"
#if (_DRAWING_MODE == _DRAWING_MODE_DX10)

#include "../../include/DX10/System.Drawing.Renderer.h"
#include "../../include/DX10/System.Drawing.RenderTargetView.h"
#include "../../include/DX10/System.Drawing.Texture.h"

namespace System {
	namespace Drawing {
		//---------------------------------------------------------------------------------------------------------
		// class RenderTargetView

		RenderTargetView::RenderTargetView(RenderTargetView_Desc& desc, Renderer* pRender)
		{
			HRESULT hr = pRender->GetDevice()->CreateRenderTargetView(
				NULL,	//[in]   ID3D10Resource *pResource,
				&desc,	//[in]   const D3D10_RENDER_TARGET_VIEW_DESC *pDesc,
				&_ptr	//[out]  ID3D10RenderTargetView **ppRTView
				);
		}

		RenderTargetView::RenderTargetView(ID3D10RenderTargetView* pRenderTargetView)
		{
			_ptr = pRenderTargetView;
		}

		/*
		Texture2D* RenderTargetView::GetTexture2D()
		{
		if (_ptr == NULL)
		return (Texture2D*)NULL;

		ID3D10Resource* pResource = NULL;

		//__try {
		void *pContainer = NULL;
		_ptr->GetResource(&pResource);
		HRESULT hr = pResource->QueryInterface(IID_ID3D10Texture2D, &pContainer);
		SafeRelease(pResource);

		if (SUCCEEDED(hr) && pContainer)
		return new Texture2D((ID3D10Texture2D*)pContainer);
		//}
		//_/_finally {
		//SafeRelease(pResource);
		//}

		return (Texture2D*)NULL;
		}
		*/
		/*
		void RenderTargetView::SetRenderTargetView(Graphics& g, DWORD RenderTargetIndex) {
		if (_ptr)
		g.GetDevice()->OMSetRenderTargets(
		RenderTargetIndex,	//[in]  UINT NumViews,
		&_ptr,				//[in]  ID3D10RenderTargetView* const *ppRenderTargetViews,
		NULL				//[in]  ID3D10DepthStencilView *pDepthStencilView
		);
		}

		void RenderTargetView::Clear() {
		g.GetDevice()->ClearRenderTargetView(_ptr, D3DXCOLOR(0, 0, 0, 0));
		}
		*/
	} /* namespace Drawing */
} /* namespace System */

#endif