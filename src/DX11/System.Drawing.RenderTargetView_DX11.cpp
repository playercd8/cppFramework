/*
 * System.Drawing.RenderTargetView_DX11.cpp
 *
 *  Created on: Taiwan
 *      Author: player
 */

#include "../../include/stdafx.h"
#if (_DRAWING_MODE == _DRAWING_MODE_DX11)

#include "../../include/DX11/System.Drawing.RenderTargetView.h"
#include "../../include/DX11/System.Drawing.Renderer.h"


namespace System {
namespace Drawing {

//---------------------------------------------------------------------------------------------------------
// class RenderTargetView

RenderTargetView::RenderTargetView(RenderTargetView_Desc& desc, Renderer* pRender) 
{
	HRESULT hr = pRender->GetDevice()->CreateRenderTargetView(
		NULL,	//[in]   ID3D11Resource *pResource,
		&desc,	//[in]   const D3D11_RENDER_TARGET_VIEW_DESC *pDesc,
		&_ptr	//[out]  ID3D11RenderTargetView **ppRTView
		);

	if FAILED(hr) {
		_ptr = NULL;
	}
}

RenderTargetView::RenderTargetView(ID3D11RenderTargetView* pRenderTargetView) {
	_ptr = pRenderTargetView;
}

//void RenderTargetView::SetRenderTargetView(DWORD RenderTargetIndex) {
//	_pDeviceContext->OMSetRenderTargets(
//		RenderTargetIndex,	//[in]  UINT NumViews,
//		&_ptr,				//[in]  ID3D11RenderTargetView *const **ppRenderTargetViews,
//		NULL				//[in]  ID3D11DepthStencilView *pDepthStencilView
//		);
//}

} /* namespace Drawing */
} /* namespace System */

#endif
