/*
 * System.Drawing.RenderTargetView.h
 *
 *  Created on: Taiwan
 *      Author: player
 */

#include "../stdafx.h"
#if (_DRAWING_MODE == _DRAWING_MODE_OpenGL)

#ifndef SYSTEM_DRAWING_RENDERTARGENTVIEW_H_
#define SYSTEM_DRAWING_RENDERTARGENTVIEW_H_

#if _MSC_VER > 1000
	#pragma once
#endif

#include "OpenGL.h"
#include "System.Drawing.Graphics.h"
#include "../System.ComPtr.h"

namespace System {
namespace Drawing {


class Renderer;
Renderer* GetDefaultRendererPtr();

typedef D3D11_RENDER_TARGET_VIEW_DESC RenderTargetView_Desc;


class RenderTargetView : public ComPtr<ID3D11RenderTargetView> {
//protected:
public:
	RenderTargetView(RenderTargetView_Desc& desc, Renderer* pRender = DefaultRendererPtr);
	RenderTargetView(ID3D11RenderTargetView* pRenderTargetView);

	//void SetRenderTargetView(DWORD RenderTargetIndex);
};
	


} /* namespace Drawing */
} /* namespace System */

#endif /* SYSTEM_DRAWING_RENDERTARGENTVIEW_H_ */
#endif
