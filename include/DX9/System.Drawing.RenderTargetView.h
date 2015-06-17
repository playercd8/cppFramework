/*
 * System.Drawing.RenderTargetView.h
 *
 * Code Status: Drafts
 *  Created on: Taiwan
 *      Author: player
 */

#include "../stdafx.h"
#if (_DRAWING_MODE == _DRAWING_MODE_DX9)

#ifndef SYSTEM_DRAWING_RENDERTARGENTVIEW_H_
#define SYSTEM_DRAWING_RENDERTARGENTVIEW_H_

#if _MSC_VER > 1000
#pragma once
#endif

#include "DX9.h"
#include "../System.ComPtr.h"
#include "System.Drawing.Texture.h"

namespace System {
	namespace Drawing {
		class Renderer;
		Renderer* GetDefaultRendererPtr();

		typedef struct RenderTargetView_Desc {
			UINT Width;
			UINT Height;
			D3DFORMAT Format;
			D3DMULTISAMPLE_TYPE MultiSample;
			DWORD MultisampleQuality;
			BOOL Lockable;
			HANDLE *pSharedHandle;
		} RenderTargetView_Desc;

		class RenderTargetView : public ComPtr < IDirect3DSurface9 > {
			//private:
			//protected:

		public:
			RenderTargetView(RenderTargetView_Desc& desc, Renderer* pRender = DefaultRendererPtr);
			RenderTargetView(IDirect3DSurface9* pSurface);

			Texture2D* GetTexture2D();
		};
	} /* namespace Drawing */
} /* namespace System */

#endif /* SYSTEM_DRAWING_RENDERTARGENTVIEW_H_ */
#endif
