/*
 * System.Drawing.RenderTargetView.h
 *
 *  Created on: Taiwan
 *      Author: player
 */

#include "../stdafx.h"
#if (_DRAWING_MODE == _DRAWING_MODE_DX10)

#ifndef SYSTEM_DRAWING_RENDERTARGENTVIEW_H_
#define SYSTEM_DRAWING_RENDERTARGENTVIEW_H_

#if _MSC_VER > 1000
#pragma once
#endif

#include "DX10.h"
#include "System.Drawing.Texture.h"
#include "../System.ComPtr.h"

namespace System {
	namespace Drawing {
		class Renderer;
		Renderer* GetDefaultRendererPtr();

		typedef D3D10_RENDER_TARGET_VIEW_DESC RenderTargetView_Desc;

		class RenderTargetView : public ComPtr < ID3D10RenderTargetView > {
			//private:
			//protected:
		public:
			RenderTargetView(RenderTargetView_Desc& desc, Renderer* pRender = DefaultRendererPtr);
			RenderTargetView(ID3D10RenderTargetView* pRenderTargetView);

			//Texture2D* GetTexture2D();

			//	void SetRenderTargetView(Graphics& g, DWORD RenderTargetIndex);
			//	void Clear();

			//protected:
		};
	} /* namespace Drawing */
} /* namespace System */

#endif /* SYSTEM_DRAWING_RENDERTARGENTVIEW_H_ */
#endif
