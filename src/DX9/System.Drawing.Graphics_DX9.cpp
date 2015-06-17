/*
* System.Drawing.Graphics_DX9.cpp
*
*  Created on: Taiwan
*      Author: player
*/

#include "../../include/stdafx.h"

#if (_DRAWING_MODE == _DRAWING_MODE_DX9)

#include "../../include/System.ComPtr.h"
#include "../../include/DX9/System.Drawing.Graphics.h"
#include "../../include/DX9/System.Drawing.Renderer.h"
#include "../../include/System.Drawing.Math.h"

namespace System {
	namespace Drawing {
		Graphics::Graphics() :
			_pD3D9(NULL)
		{
		}

		Graphics::~Graphics()
		{
			SafeRelease(_pD3D9);
		}

		bool Graphics::Initialize()
		{
			_pD3D9 = Direct3DCreate9(D3D_SDK_VERSION);
			if (_pD3D9 == NULL)
				return false;
			return true;
		}

		Renderer* Graphics::GetRenderer(Renderer_Desc& desc)
		{
			HRESULT hr;
			D3DPRESENT_PARAMETERS d3dpp;
			ZeroMemory(&d3dpp, sizeof(D3DPRESENT_PARAMETERS));

			d3dpp.BackBufferWidth = desc.width;
			d3dpp.BackBufferHeight = desc.height;

			if (desc.isFullScreen) {
				// Full Screen mode
				d3dpp.Windowed = false;
				d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
				d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
				d3dpp.BackBufferCount = D3DPRESENT_BACK_BUFFERS_MAX;
				d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
				d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;
				d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
				d3dpp.SwapEffect = D3DSWAPEFFECT_FLIP;
			}
			else {
				// Window mode
				D3DDISPLAYMODE d3ddm;
				V(_pD3D9->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm));
				d3dpp.Windowed = true;
				d3dpp.BackBufferFormat = d3ddm.Format;
				d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
				d3dpp.BackBufferCount = D3DPRESENT_BACK_BUFFERS_MAX;
				d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
				d3dpp.SwapEffect = D3DSWAPEFFECT_COPY;
			}

			d3dpp.EnableAutoDepthStencil = TRUE;
			d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

			DWORD Flags = D3DCREATE_MIXED_VERTEXPROCESSING | D3DCREATE_MULTITHREADED;
			V(_pD3D9->CreateDevice(
				D3DADAPTER_DEFAULT,		//[in]           UINT Adapter,
				D3DDEVTYPE_HAL,			//[in]           D3DDEVTYPE DeviceType,
				desc.hWnd,				//[in]           HWND hFocusWindow,
				Flags,					//[in]           DWORD BehaviorFlags,
				&d3dpp,					//[in, out]      D3DPRESENT_PARAMETERS *pPresentationParameters,
				&desc._pDevice			//[out, retval]  IDirect3DDevice9 **ppReturnedDeviceInterface
				));

			if (FAILED(hr) || (desc._pDevice == NULL))
				return NULL;

			d3dpp.BackBufferCount = 1;
			V(desc._pDevice->CreateAdditionalSwapChain(
				&d3dpp,						//[in, out]      D3DPRESENT_PARAMETERS *pPresentationParameters,
				&desc._pSwapChain			//[out, retval]  IDirect3DSwapChain9 **ppSwapChain
				));

			//Enabling Depth Buffering
			desc._pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);

			//Set ViewPort
			desc._viewport.SetViewPort(0, 0, desc.width, desc.height);
			desc._pDevice->SetViewport(desc._viewport);

			Renderer* pRenderer = new Renderer(desc);
			return pRenderer;
		}
	} /* namespace Drawing */
} /* namespace System */

#endif