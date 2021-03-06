﻿/*
* System.Drawing.Graphics_DX11.cpp
*
*  Created on: Taiwan
*      Author: player
*/

#include "../../include/stdafx.h"

#if (_DRAWING_MODE == _DRAWING_MODE_DX11)

#include "../../include/DX11/System.Drawing.Graphics.h"
#include "../../include/DX11/System.Drawing.Renderer.h"
#include "../../include/System.ComPtr.h"
#include "../../include/System.Drawing.Math.h"

namespace System {
	namespace Drawing {
		Graphics::Graphics() {
		}

		Graphics::~Graphics() {
		}

		bool Graphics::Initialize()
		{
			return true;
		}

		Renderer* Graphics::GetRenderer(Renderer_Desc& desc) {
			try {
				HRESULT hr;
				DXGI_SWAP_CHAIN_DESC scd;
				ZeroMemory(&scd, sizeof(scd));

				scd.BufferCount = 1;									// one back buffer
				scd.BufferDesc.Width = desc.width;
				scd.BufferDesc.Height = desc.height;
				scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;		// use 32-bit color
				if (desc.vsync)	{
					scd.BufferDesc.RefreshRate.Numerator = 60;
					scd.BufferDesc.RefreshRate.Denominator = 1;
				}
				else {
					scd.BufferDesc.RefreshRate.Numerator = 0;
					scd.BufferDesc.RefreshRate.Denominator = 1;
				}
				scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;		// how swap chain is to be used
				scd.OutputWindow = desc.hWnd;
				scd.SampleDesc.Count = 4;
				scd.SampleDesc.Quality = 0;

				UINT SDKVersion = D3D11_SDK_VERSION;
				D3D_FEATURE_LEVEL FeatureLevels =  D3D_FEATURE_LEVEL_10_1;
				D3D_FEATURE_LEVEL FeatureLevel;

				unsigned int creationFlags = 0;

#if defined(_DEBUG)
				scd.Windowed = TRUE;
				//creationFlags |= D3D11_CREATE_DEVICE_DEBUG;
#else
				scd.Windowed = (desc.isFullScreen) ? FALSE : TRUE;
#endif
				D3D_DRIVER_TYPE DriverType = D3D_DRIVER_TYPE_HARDWARE;

				V(D3D11CreateDeviceAndSwapChain(
					NULL,					//[in]	IDXGIAdapter *pAdapter
					DriverType,				//[in]	D3D_DRIVER_TYPE DriverType
					NULL,					//[in]	HMODULE Software
					creationFlags,			//[in]	UINT Flags
					&FeatureLevels,			//[in]	D3D_FEATURE_LEVEL *pFeatureLevels
					1,						//[in]	UINT FeatureLevels
					SDKVersion,				//[in]	UINT SDKVersion
					&scd,					//[in]	DXGI_SWAP_CHAIN_DESC *pSwapChainDesc
					&desc._pSwapChain,		//[out]	IDXGISwapChain **ppSwapChain
					&desc._pDevice,			//[out]	ID3D11Device **ppDevice
					&FeatureLevel,			//[out]	D3D_FEATURE_LEVEL *pFeatureLevel
					&desc._pDeviceContext	//[out]	ID3D11DeviceContext **ppDeviceContext
					));

				if FAILED(hr)
					return NULL;

				// Get the pointer to the back buffer.
				ID3D11Texture2D* backBufferPtr = NULL;
				V(desc._pSwapChain->GetBuffer(0, IID_ID3D11Texture2D, (LPVOID*)&backBufferPtr));
				if FAILED(hr)
					throw _T("Failed at pSwapChain->GetBuffer");

				// Create the render target view with the back buffer pointer.
				V(desc._pDevice->CreateRenderTargetView(backBufferPtr, NULL, &desc._pRenderTargetView));
				if FAILED(hr)
					throw _T("Failed at pDevice->CreateRenderTargetView");

				// Release pointer to the back buffer as we no longer need it.
				SafeRelease(backBufferPtr);

				// Initialize the description of the depth buffer.
				D3D11_TEXTURE2D_DESC depthBufferDesc;
				ZeroMemory(&depthBufferDesc, sizeof(depthBufferDesc));

				// Set up the description of the depth buffer.
				depthBufferDesc.Width = desc.width;
				depthBufferDesc.Height = desc.height;
				depthBufferDesc.MipLevels = 1;
				depthBufferDesc.ArraySize = 1;
				depthBufferDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
				depthBufferDesc.SampleDesc.Count = 1;
				depthBufferDesc.SampleDesc.Quality = 0;
				depthBufferDesc.Usage = D3D11_USAGE_DEFAULT;
				depthBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
				depthBufferDesc.CPUAccessFlags = 0;
				depthBufferDesc.MiscFlags = 0;

				// Create the texture for the depth buffer using the filled out description.
				V(desc._pDevice->CreateTexture2D(&depthBufferDesc, NULL, &desc._pDepthStencilBuffer));
				if FAILED(hr)
					throw _T("Failed at pDevice->CreateTexture2D");

				// Initialize the description of the stencil state.
				D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
				ZeroMemory(&depthStencilDesc, sizeof(depthStencilDesc));

				// Set up the description of the stencil state.
				depthStencilDesc.DepthEnable = true;
				depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
				depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;

				depthStencilDesc.StencilEnable = true;
				depthStencilDesc.StencilReadMask = 0xFF;
				depthStencilDesc.StencilWriteMask = 0xFF;

				// Stencil operations if pixel is front-facing.
				depthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
				depthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
				depthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
				depthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

				// Stencil operations if pixel is back-facing.
				depthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
				depthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
				depthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
				depthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

				// Create the depth stencil state.
				V(desc._pDevice->CreateDepthStencilState(&depthStencilDesc, &desc._pDepthStencilState));
				if FAILED(hr)
					throw _T("Failed at pDevice->CreateDepthStencilState");

				// Set the depth stencil state.
				desc._pDeviceContext->OMSetDepthStencilState(desc._pDepthStencilState, 1);

				// Initialize the depth stencil view.
				D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
				ZeroMemory(&depthStencilViewDesc, sizeof(depthStencilViewDesc));

				// Set up the depth stencil view description.
				depthStencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
				depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
				depthStencilViewDesc.Texture2D.MipSlice = 0;

				// Create the depth stencil view.
				V(desc._pDevice->CreateDepthStencilView(desc._pDepthStencilBuffer, &depthStencilViewDesc, &desc._pDepthStencilView));
				if FAILED(hr)
					throw _T("Failed at pDevice->CreateDepthStencilView");

				// Bind the render target view and depth stencil buffer to the output render pipeline.
				desc._pDeviceContext->OMSetRenderTargets(1, &desc._pRenderTargetView, desc._pDepthStencilView);

				// Setup the raster description which will determine how and what polygons will be drawn.
				D3D11_RASTERIZER_DESC rasterDesc;
				rasterDesc.AntialiasedLineEnable = false;
				rasterDesc.CullMode = D3D11_CULL_BACK;
				rasterDesc.DepthBias = 0;
				rasterDesc.DepthBiasClamp = 0.0f;
				rasterDesc.DepthClipEnable = true;
				rasterDesc.FillMode = D3D11_FILL_SOLID;
				rasterDesc.FrontCounterClockwise = false;
				rasterDesc.MultisampleEnable = false;
				rasterDesc.ScissorEnable = false;
				rasterDesc.SlopeScaledDepthBias = 0.0f;

				// Create the rasterizer state from the description we just filled out.
				V(desc._pDevice->CreateRasterizerState(&rasterDesc, &desc._pRasterState));
				if FAILED(hr)
					throw _T("Failed at pDevice->CreateRasterizerState");

				// Now set the rasterizer state.
				desc._pDeviceContext->RSSetState(desc._pRasterState);
				
				//Set ViewPort
				desc._viewport.SetViewPort(0, 0, desc.width, desc.height);
				desc._pDeviceContext->RSSetViewports(1, desc._viewport);

				Renderer* pRenderer = new Renderer(desc);
				return pRenderer;
			}
			catch (LPCTSTR pErrorMessage) {
				UNREFERENCED_PARAMETER(pErrorMessage);

				if (desc._pSwapChain)
					desc._pSwapChain->SetFullscreenState(false, NULL);
				SafeRelease(desc._pRasterState);
				SafeRelease(desc._pDepthStencilView);
				SafeRelease(desc._pDepthStencilState);
				SafeRelease(desc._pDepthStencilBuffer);
				SafeRelease(desc._pRenderTargetView);
				SafeRelease(desc._pDeviceContext);
				SafeRelease(desc._pSwapChain);
				SafeRelease(desc._pDevice);

				return NULL;
			}
		}
	} /* namespace Drawing */
} /* namespace System */

#endif