/*
 * System.Drawing.Texture_DX10.cpp
 *
 *  Created on: Taiwan
 *      Author: player
 */

#include "../../include/stdafx.h"
#if (_DRAWING_MODE == _DRAWING_MODE_DX10)

#include "../../include/DX10/System.Drawing.Texture.h"
#include "../../include/DX10/System.Drawing.Renderer.h"

namespace System {
	namespace Drawing {
		//---------------------------------------------------------------------------------------------------------
		// class Texture1D
#pragma region class Texture1D
		Texture1D::Texture1D(Texture1D_Desc& desc, Renderer* pRender)
		{
			HRESULT hr;
			ID3D10Device* pDevice = pRender->GetDevice();

			V(pDevice->CreateTexture1D(
				&desc,		//[in]   const D3D10_TEXTURE1D_DESC *pDesc,
				NULL,		//[in]   const D3D10_SUBRESOURCE_DATA *pInitialData,
				&_ptr		//[out]  ID3D10Texture1D **ppTexture1D
				));

			if (SUCCEEDED(hr)) {
				_width = (float)desc.Width;
				_invW = 1.0f / _width;

				D3D10_SHADER_RESOURCE_VIEW_DESC resourceViewDesc;
				resourceViewDesc.Format = desc.Format;
				resourceViewDesc.ViewDimension = D3D10_SRV_DIMENSION_TEXTURE1D;
				resourceViewDesc.Texture1D.MostDetailedMip = 0;
				resourceViewDesc.Texture1D.MipLevels = desc.MipLevels;

				ID3D10ShaderResourceView* pResourceView;
				V(pDevice->CreateShaderResourceView(
					(ID3D10Resource *)_ptr,		//[in]   ID3D10Resource *pResource,
					&resourceViewDesc,			//[in]   const D3D10_SHADER_RESOURCE_VIEW_DESC *pDesc,
					&pResourceView				//[out]  ID3D10ShaderResourceView **ppSRView
					));
				if (SUCCEEDED(hr)) {
					_ResourceView = pResourceView;
				}
			}
			else {
				_ptr = NULL;
				_width = 0;
				_invW = 0;
			}
		}

		Texture1D::Texture1D(ID3D10Texture1D* pTexture, Renderer* pRender)
		{
			if (pTexture) {
				_ptr = pTexture;

				HRESULT hr;
				D3D10_TEXTURE1D_DESC desc;
				_ptr->GetDesc(&desc);

				_width = (float)desc.Width;
				_invW = 1.0f / _width;

				D3D10_SHADER_RESOURCE_VIEW_DESC resourceViewDesc;
				resourceViewDesc.Format = desc.Format;
				resourceViewDesc.ViewDimension = D3D10_SRV_DIMENSION_TEXTURE1D;
				resourceViewDesc.Texture1D.MostDetailedMip = 0;
				resourceViewDesc.Texture1D.MipLevels = desc.MipLevels;

				ID3D10ShaderResourceView* pResourceView;
				V(pRender->GetDevice()->CreateShaderResourceView(
					(ID3D10Resource *)_ptr,		//[in]   ID3D10Resource *pResource,
					&resourceViewDesc,			//[in]   const D3D10_SHADER_RESOURCE_VIEW_DESC *pDesc,
					&pResourceView				//[out]  ID3D10ShaderResourceView **ppSRView
					));
				if (SUCCEEDED(hr)) {
					_ResourceView = pResourceView;
				}
			}
			else {
				_ptr = NULL;
				_width = 0;
				_invW = 0;
			}
		}

		Texture1D* Texture1D::FromFile(LPCTSTR pFileName, Renderer* pRender) {
			ID3D10Resource* pResource = NULL;

			HRESULT hr = D3DX10CreateTextureFromFile(
				pRender->GetDevice(),	//[in]  ID3D10Device *pDevice,
				pFileName,				//[in]   LPCTSTR pSrcFile,
				NULL,					//[in]   D3DX10_IMAGE_LOAD_INFO *pLoadInfo,
				NULL,					//[in]   ID3DX10ThreadPump *pPump,
				&pResource,				//[out]  ID3D10Resource **ppTexture,
				NULL					//[out]  HRESULT *pHResult
				);

			if (SUCCEEDED(hr)) {
				ID3D10Texture1D* ptr = NULL;
				hr = pResource->QueryInterface(IID_ID3D10Texture1D, (LPVOID*)&ptr);
				pResource->Release();
				if (SUCCEEDED(hr)) {
					Texture1D* pTexture1D = new Texture1D(ptr);
					return pTexture1D;
				}
			}

			return NULL;
		}

		Texture1D* Texture1D::FromBuffer(Buffer& buf, Renderer* pRender) {
			ID3D10Resource* pResource = NULL;

			HRESULT hr = D3DX10CreateTextureFromMemory(
				pRender->GetDevice(),	//[in]   ID3D10Device *pDevice,
				buf.GetPtr(),			//[in]   LPCVOID pSrcData,
				buf.GetSize(),			//[in]   SIZE_T SrcDataSize,
				NULL,					//[in]   D3DX10_IMAGE_LOAD_INFO *pLoadInfo,
				NULL,					//[in]   ID3DX10ThreadPump *pPump,
				&pResource,				//[out]  ID3D10Resource **ppTexture,
				NULL					//[out]  HRESULT *pHResult
				);

			if (SUCCEEDED(hr)) {
				ID3D10Texture1D* ptr = NULL;
				hr = pResource->QueryInterface(IID_ID3D10Texture1D, (LPVOID*)&ptr);
				pResource->Release();
				if (SUCCEEDED(hr)) {
					Texture1D* pTexture1D = new Texture1D(ptr);
					return pTexture1D;
				}
			}

			return NULL;
		}
#pragma endregion class Texture1D
		//---------------------------------------------------------------------------------------------------------
		// class Texture2D
#pragma region class Texture2D
		Texture2D::Texture2D(Texture2D_Desc& desc, Renderer* pRender)
		{
			HRESULT hr;
			ID3D10Device* pDevice = pRender->GetDevice();

			V(pDevice->CreateTexture2D(
				&desc,		//[in]   const D3D10_TEXTURE2D_DESC *pDesc,
				NULL,		//[in]   const D3D10_SUBRESOURCE_DATA *pInitialData,
				&_ptr		//[out]  ID3D10Texture2D **ppTexture2D
				));

			if (SUCCEEDED(hr)) {
				_width = (float)desc.Width;
				_height = (float)desc.Height;
				_invW = 1.0f / _width;
				_invH = 1.0f / _height;

				D3D10_SHADER_RESOURCE_VIEW_DESC resourceViewDesc;
				resourceViewDesc.Format = desc.Format;
				resourceViewDesc.ViewDimension = D3D10_SRV_DIMENSION_TEXTURE2D;
				resourceViewDesc.Texture2D.MostDetailedMip = 0;
				resourceViewDesc.Texture2D.MipLevels = desc.MipLevels;

				ID3D10ShaderResourceView* pResourceView;
				V(pDevice->CreateShaderResourceView(
					(ID3D10Resource *)_ptr,		//[in]   ID3D10Resource *pResource,
					&resourceViewDesc,			//[in]   const D3D10_SHADER_RESOURCE_VIEW_DESC *pDesc,
					&pResourceView				//[out]  ID3D10ShaderResourceView **ppSRView
					));
				if (SUCCEEDED(hr)) {
					_ResourceView = pResourceView;
				}
			}
			else {
				_ptr = NULL;
				_width = 0;
				_height = 0;
				_invW = 0;
				_invH = 0;
			}
		}

		Texture2D::Texture2D(ID3D10Texture2D* pTexture, Renderer* pRender)
		{
			if (pTexture) {
				_ptr = pTexture;

				HRESULT hr;
				D3D10_TEXTURE2D_DESC desc;
				_ptr->GetDesc(&desc);

				_width = (float)desc.Width;
				_height = (float)desc.Height;
				_invW = 1.0f / _width;
				_invH = 1.0f / _height;

				D3D10_SHADER_RESOURCE_VIEW_DESC resourceViewDesc;
				resourceViewDesc.Format = desc.Format;
				resourceViewDesc.ViewDimension = D3D10_SRV_DIMENSION_TEXTURE2D;
				resourceViewDesc.Texture2D.MostDetailedMip = 0;
				resourceViewDesc.Texture2D.MipLevels = desc.MipLevels;

				ID3D10ShaderResourceView* pResourceView;
				V(pRender->GetDevice()->CreateShaderResourceView(
					(ID3D10Resource *)_ptr,		//[in]   ID3D10Resource *pResource,
					&resourceViewDesc,			//[in]   const D3D10_SHADER_RESOURCE_VIEW_DESC *pDesc,
					&pResourceView				//[out]  ID3D10ShaderResourceView **ppSRView
					));
				if (SUCCEEDED(hr)) {
					_ResourceView = pResourceView;
				}
			}
			else {
				_ptr = NULL;
				_width = 0;
				_height = 0;
				_invW = 0;
				_invH = 0;
			}
		}

		Texture2D* Texture2D::FromFile(LPCTSTR pFileName, Renderer* pRender) {
			ID3D10Resource* pResource = NULL;

			HRESULT hr = D3DX10CreateTextureFromFile(
				pRender->GetDevice(),	//[in]  ID3D10Device *pDevice,
				pFileName,				//[in]   LPCTSTR pSrcFile,
				NULL,					//[in]   D3DX10_IMAGE_LOAD_INFO *pLoadInfo,
				NULL,					//[in]   ID3DX10ThreadPump *pPump,
				&pResource,				//[out]  ID3D10Resource **ppTexture,
				NULL					//[out]  HRESULT *pHResult
				);

			if (SUCCEEDED(hr)) {
				ID3D10Texture2D* ptr = NULL;
				hr = pResource->QueryInterface(IID_ID3D10Texture2D, (LPVOID*)&ptr);
				pResource->Release();
				if (SUCCEEDED(hr)) {
					Texture2D* pTexture2D = new Texture2D(ptr);
					return pTexture2D;
				}
			}

			return NULL;
		}

		Texture2D* Texture2D::FromBuffer(Buffer& buf, Renderer* pRender) {
			ID3D10Resource* pResource = NULL;

			HRESULT hr = D3DX10CreateTextureFromMemory(
				pRender->GetDevice(),	//[in]   ID3D10Device *pDevice,
				buf.GetPtr(),			//[in]   LPCVOID pSrcData,
				buf.GetSize(),			//[in]   SIZE_T SrcDataSize,
				NULL,					//[in]   D3DX10_IMAGE_LOAD_INFO *pLoadInfo,
				NULL,					//[in]   ID3DX10ThreadPump *pPump,
				&pResource,				//[out]  ID3D10Resource **ppTexture,
				NULL					//[out]  HRESULT *pHResult
				);

			if (SUCCEEDED(hr)) {
				ID3D10Texture2D* ptr = NULL;
				hr = pResource->QueryInterface(IID_ID3D10Texture2D, (LPVOID*)&ptr);
				pResource->Release();
				if (SUCCEEDED(hr)) {
					Texture2D* pTexture2D = new Texture2D(ptr);
					return pTexture2D;
				}
			}

			return NULL;
		}
#pragma endregion class Texture2D
		//---------------------------------------------------------------------------------------------------------
		// class Texture3D
#pragma region class Texture3D
		Texture3D::Texture3D(Texture3D_Desc& desc, Renderer* pRender)
		{
			HRESULT hr;
			ID3D10Device* pDevice = pRender->GetDevice();

			V(pDevice->CreateTexture3D(
				&desc,		//[in]   const D3D10_TEXTURE3D_DESC *pDesc,
				NULL,		//[in]   const D3D10_SUBRESOURCE_DATA *pInitialData,
				&_ptr		//[out]  ID3D10Texture3D **ppTexture3D
				));

			if (SUCCEEDED(hr)) {
				_width = (float)desc.Width;
				_height = (float)desc.Height;
				_depth = (float)desc.Depth;
				_invW = 1.0f / _width;
				_invH = 1.0f / _height;
				_invD = 1.0f / _depth;

				D3D10_SHADER_RESOURCE_VIEW_DESC resourceViewDesc;
				resourceViewDesc.Format = desc.Format;
				resourceViewDesc.ViewDimension = D3D10_SRV_DIMENSION_TEXTURE3D;
				resourceViewDesc.Texture3D.MostDetailedMip = 0;
				resourceViewDesc.Texture3D.MipLevels = desc.MipLevels;

				ID3D10ShaderResourceView* pResourceView;
				V(pDevice->CreateShaderResourceView(
					(ID3D10Resource *)_ptr,		//[in]   ID3D10Resource *pResource,
					&resourceViewDesc,			//[in]   const D3D10_SHADER_RESOURCE_VIEW_DESC *pDesc,
					&pResourceView				//[out]  ID3D10ShaderResourceView **ppSRView
					));
				if (SUCCEEDED(hr)) {
					_ResourceView = pResourceView;
				}
			}
			else {
				_ptr = NULL;
				_width = 0;
				_height = 0;
				_depth = 0;
				_invW = 0;
				_invH = 0;
				_invD = 0;
			}
		}

		Texture3D::Texture3D(ID3D10Texture3D* pTexture, Renderer* pRender)
		{
			if (pTexture) {
				_ptr = pTexture;

				HRESULT hr;
				D3D10_TEXTURE3D_DESC desc;
				_ptr->GetDesc(&desc);

				_width = (float)desc.Width;
				_height = (float)desc.Height;
				_depth = (float)desc.Depth;
				_invW = 1.0f / _width;
				_invH = 1.0f / _height;
				_invD = 1.0f / _depth;

				D3D10_SHADER_RESOURCE_VIEW_DESC resourceViewDesc;
				resourceViewDesc.Format = desc.Format;
				resourceViewDesc.ViewDimension = D3D10_SRV_DIMENSION_TEXTURE3D;
				resourceViewDesc.Texture3D.MostDetailedMip = 0;
				resourceViewDesc.Texture3D.MipLevels = desc.MipLevels;

				ID3D10ShaderResourceView* pResourceView;
				V(pRender->GetDevice()->CreateShaderResourceView(
					(ID3D10Resource *)_ptr,		//[in]   ID3D10Resource *pResource,
					&resourceViewDesc,			//[in]   const D3D10_SHADER_RESOURCE_VIEW_DESC *pDesc,
					&pResourceView				//[out]  ID3D10ShaderResourceView **ppSRView
					));
				if (SUCCEEDED(hr)) {
					_ResourceView = pResourceView;
				}
			}
			else {
				_ptr = NULL;
				_width = 0;
				_height = 0;
				_depth = 0;
				_invW = 0;
				_invH = 0;
				_invD = 0;
			}
		}

		Texture3D* Texture3D::FromFile(LPCTSTR pFileName, Renderer* pRender) {
			ID3D10Resource* pResource = NULL;

			HRESULT hr = D3DX10CreateTextureFromFile(
				pRender->GetDevice(),	//[in]  ID3D10Device *pDevice,
				pFileName,				//[in]   LPCTSTR pSrcFile,
				NULL,					//[in]   D3DX10_IMAGE_LOAD_INFO *pLoadInfo,
				NULL,					//[in]   ID3DX10ThreadPump *pPump,
				&pResource,				//[out]  ID3D10Resource **ppTexture,
				NULL					//[out]  HRESULT *pHResult
				);

			if (SUCCEEDED(hr)) {
				ID3D10Texture3D* ptr = NULL;
				hr = pResource->QueryInterface(IID_ID3D10Texture3D, (LPVOID*)&ptr);
				pResource->Release();
				if (SUCCEEDED(hr)) {
					Texture3D* pTexture3D = new Texture3D(ptr);
					return pTexture3D;
				}
			}

			return NULL;
		}

		Texture3D* Texture3D::FromBuffer(Buffer& buf, Renderer* pRender)
		{
			ID3D10Resource* pResource = NULL;

			HRESULT hr = D3DX10CreateTextureFromMemory(
				pRender->GetDevice(),	//[in]   ID3D10Device *pDevice,
				buf.GetPtr(),			//[in]   LPCVOID pSrcData,
				buf.GetSize(),			//[in]   SIZE_T SrcDataSize,
				NULL,					//[in]   D3DX10_IMAGE_LOAD_INFO *pLoadInfo,
				NULL,					//[in]   ID3DX10ThreadPump *pPump,
				&pResource,				//[out]  ID3D10Resource **ppTexture,
				NULL					//[out]  HRESULT *pHResult
				);

			if (SUCCEEDED(hr)) {
				ID3D10Texture3D* ptr = NULL;
				hr = pResource->QueryInterface(IID_ID3D10Texture3D, (LPVOID*)&ptr);
				pResource->Release();
				if (SUCCEEDED(hr)) {
					Texture3D* pTexture3D = new Texture3D(ptr);
					return pTexture3D;
				}
			}

			return NULL;
		}
#pragma endregion class Texture3D
	} /* namespace Drawing */
} /* namespace System */

#endif