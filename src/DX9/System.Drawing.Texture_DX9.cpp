/*
 * System.Drawing.Texture_DX9.cpp
 *
 *  Created on: Taiwan
 *      Author: player
 */

#include "../../include/stdafx.h"
#if (_DRAWING_MODE == _DRAWING_MODE_DX9)

#include "../../include/DX9/System.Drawing.Texture.h"
#include "../../include/DX9/System.Drawing.Renderer.h"


namespace System {
namespace Drawing {

//---------------------------------------------------------------------------------------------------------
// class Texture1D

Texture1D::Texture1D(Texture1D_Desc& desc, Renderer* pRender)
{
	HRESULT hr;
	IDirect3DCubeTexture9* pTexture;

	V(pRender->GetDevice()->CreateCubeTexture(
					desc.Width,			//[in]	UINT EdgeLength,
					desc.Levels,		//[in]	UINT Levels,
					desc.Usage,			//[in]	DWORD Usage,
					desc.Format,		//[in]	D3DFORMAT Format
					desc.Pool,			//[in]	D3DPOOL Pool
					&pTexture,			//[out, retval]  IDirect3DCubeTexture9 **ppCubeTexture,
					desc.pSharedHandle	//[in]	HANDLE *pSharedHandle
					));
	if (SUCCEEDED(hr)) {
		_pTexture = pTexture;
		_ptr = pTexture;

		_width = (float)desc.Width;
		_invW = 1.0f / _width;

	}
	else {
		_ptr = NULL;
		_width = 0;
		_invW = 0;
	}
}

Texture1D::Texture1D(IDirect3DCubeTexture9* pTexture) 
{
	HRESULT hr;
	if (pTexture) {
		_pTexture = pTexture;
		_ptr = pTexture;

		D3DSURFACE_DESC desc;
		V(pTexture->GetLevelDesc(0, &desc));
		
		_width = (float)desc.Width;
		_invW = 1.0f / _width;
	}
	else {
		_ptr = NULL;
		_width = 0;
		_invW = 0;
	}
}


Texture1D* Texture1D::FromFile(LPCTSTR pFileName, Renderer* pRender) 
{
	HRESULT hr;
	IDirect3DCubeTexture9* ptr = NULL;
	V(D3DXCreateCubeTextureFromFile(
					pRender->GetDevice(),	//[in]	LPDIRECT3DDEVICE9 pDevice,
					pFileName,				//[in]	LPCTSTR pSrcFile,
					&ptr					//[out]	LPDIRECT3DCUBETEXTURE9 *ppCubeTexture
					));
	
	if (SUCCEEDED(hr)) {
		Texture1D* pTexture1D = new Texture1D(ptr);
		return pTexture1D;
	}

	return NULL;
}

Texture1D* Texture1D::FromBuffer(Buffer& buf, Renderer* pRender) 
{
	HRESULT hr;
	IDirect3DCubeTexture9* ptr = NULL;

	V(D3DXCreateCubeTextureFromFileInMemory(
					pRender->GetDevice(),		//[in]	LPDIRECT3DDEVICE9 pDevice,
					buf.GetPtr(),				//[in]	LPCVOID pSrcData,
					buf.GetSize(),				//[in]	UINT SrcDataSize,
					&ptr						//[out]	LPDIRECT3DCUBETEXTURE9 *ppCubeTexture
					));

	if (SUCCEEDED(hr)) {
		Texture1D* pTexture1D = new Texture1D(ptr);
		return pTexture1D;
	}

	return NULL;
}

//---------------------------------------------------------------------------------------------------------
// class Texture2D

Texture2D::Texture2D(Texture2D_Desc& desc, Renderer* pRender)
{
	HRESULT hr;
	IDirect3DTexture9* pTexture;

	V(pRender->GetDevice()->CreateTexture(
					desc.Width,			//[in]	UINT Width,
					desc.Height,		//[in]	UINT Height,
					desc.Levels,		//[in]	UINT Levels,
					desc.Usage,			//[in]	DWORD Usage,
					desc.Format,		//[in]	D3DFORMAT Format,
					desc.Pool,			//[in]	D3DPOOL Pool,
					&pTexture,			//[out]	IDirect3DTexture9 **ppTexture,
					desc.pSharedHandle	//[in]	HANDLE *pSharedHandle
					));

	if (SUCCEEDED(hr)) {
		_pTexture = pTexture;
		_ptr = pTexture;

		_width = (float)desc.Width;
		_height = (float)desc.Height;
		_invW = 1.0f / _width;
		_invH = 1.0f / _height;
	} else {
		_ptr = NULL;
		_width = 0;
		_height = 0;
		_invW = 0;
		_invH = 0;
	}
}

Texture2D::Texture2D(IDirect3DTexture9* pTexture) 
{
	HRESULT hr;
	if (pTexture) {
		_pTexture = pTexture;
		_ptr = pTexture;

		D3DSURFACE_DESC desc;
		V(pTexture->GetLevelDesc(0, &desc));

		_width = (float)desc.Width;
		_height = (float)desc.Height;
		_invW = 1.0f / _width;
		_invH = 1.0f / _height;
	} else {
		_ptr = NULL;
		_width = 0;
		_height = 0;
		_invW = 0;
		_invH = 0;
	}	
}

Texture2D* Texture2D::FromFile(LPCTSTR pFileName, Renderer* pRender) 
{
	HRESULT hr;
	IDirect3DTexture9* ptr = NULL;
	V(D3DXCreateTextureFromFile(
					pRender->GetDevice(),	//[in]   LPDIRECT3DDEVICE9 pDevice,
					pFileName,				//[in]   LPCTSTR pSrcFile,
					&ptr					//[out]  LPDIRECT3DTEXTURE9 *ppTexture
					));

	if (SUCCEEDED(hr)) {
		Texture2D* pTexture2D = new Texture2D(ptr);
		return pTexture2D;
	} 
		
	return NULL;
}

Texture2D* Texture2D::FromBuffer(Buffer& buf, Renderer* pRender) 
{
	HRESULT hr;
	IDirect3DTexture9* ptr = NULL;

	V(D3DXCreateTextureFromFileInMemory(
					pRender->GetDevice(),	//[in]	LPDIRECT3DDEVICE9 pDevice,
					buf.GetPtr(),			//[in]  LPCVOID pSrcData,
					buf.GetSize(),			//[in]	UINT SrcDataSize,
					&ptr					//[out]  LPDIRECT3DTEXTURE9 *ppTexture
					));

	if (SUCCEEDED(hr)) {
		Texture2D* pTexture2D = new Texture2D(ptr);
		return pTexture2D;
	}

	return NULL;
}


//---------------------------------------------------------------------------------------------------------
// class Texture3D

Texture3D::Texture3D(Texture3D_Desc& desc, Renderer* pRender) 
{
	HRESULT hr;
	IDirect3DVolumeTexture9* pTexture;

	V(pRender->GetDevice()->CreateVolumeTexture(
					desc.Width,			//[in]	UINT Width,
					desc.Height,		//[in]	UINT Height,
					desc.Depth,			//[in]	UINT Depth,
					desc.Levels,		//[in]	UINT Levels,
					desc.Usage,			//[in]	DWORD Usage,
					desc.Format,		//[in]	D3DFORMAT Format,
					desc.Pool,			//[in]	D3DPOOL Pool,
					&pTexture,			//[out]  IDirect3DVolumeTexture9 **ppVolumeTexture,
					desc.pSharedHandle	//[in]	HANDLE *pSharedHandle
					));

	if (SUCCEEDED(hr)) {
		_pTexture = pTexture;
		_ptr = pTexture;

		_width = (float)desc.Width;
		_height = (float)desc.Height;
		_depth = (float)desc.Depth;
		_invW = 1.0f / _width;
		_invH = 1.0f / _height;
		_invD = 1.0f / _depth;
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

Texture3D::Texture3D(IDirect3DVolumeTexture9* pTexture) 
{
	HRESULT hr;
	if (pTexture) {
		_pTexture = pTexture;
		_ptr = pTexture;

		D3DVOLUME_DESC desc;
		V(pTexture->GetLevelDesc(0, &desc));

		_width = (float)desc.Width;
		_height = (float)desc.Height;
		_depth = (float)desc.Depth;
		_invW = 1.0f / _width;
		_invH = 1.0f / _height;
		_invD = 1.0f / _depth;
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

Texture3D* Texture3D::FromFile(LPCTSTR pFileName, Renderer* pRender) 
{
	HRESULT hr;
	IDirect3DVolumeTexture9* pTexture = NULL;
	V(D3DXCreateVolumeTextureFromFile(
					pRender->GetDevice(),	//[in]   LPDIRECT3DDEVICE9 pDevice,
					pFileName,				//[in]   LPCTSTR pSrcFile,
					&pTexture				//[out]  LPDIRECT3DTEXTURE9 *ppTexture
					));
	
	if (SUCCEEDED(hr)) {
		Texture3D* pTexture3D = new Texture3D(pTexture);
		return pTexture3D;
	}

	return NULL;	
}

Texture3D* Texture3D::FromBuffer(Buffer& buf, Renderer* pRender) 
{
	HRESULT hr;
	IDirect3DVolumeTexture9* pTexture = NULL;
	V(D3DXCreateVolumeTextureFromFileInMemory(
					pRender->GetDevice(),	//[in]   LPDIRECT3DDEVICE9 pDevice,
					buf.GetPtr(),			//[in]   LPCVOID pSrcFile,
					buf.GetSize(),			//[in]   UINT SrcData,
					&pTexture				//[out]	 LPDIRECT3DVOLUMETEXTURE9 ppVolumeTexture
					));

	if (SUCCEEDED(hr)) {
		Texture3D* pTexture3D = new Texture3D(pTexture);
		return pTexture3D;
	}

	return NULL;
}

} /* namespace Drawing */
} /* namespace System */

#endif
