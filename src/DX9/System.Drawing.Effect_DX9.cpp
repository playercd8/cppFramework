/*
 * System.Drawing.Effect_DX9.cpp
 *
 * Code Status: Drafts
 *  Created on: Taiwan
 *      Author: player
 */

#include "../../include/stdafx.h"
#if (_DRAWING_MODE == _DRAWING_MODE_DX9)

#include "../../include/DX9/System.Drawing.Effect.h"
#include "../../include/DX9/System.Drawing.Renderer.h"
#include "../../include/System.String.h"

namespace System {
	namespace Drawing {
		//---------------------------------------------------------------------------------------------------------
		// class Effect

		Effect::Effect(Effect_Desc& desc, Renderer* pRender)
		{
			HRESULT hr;
			ID3DXBuffer* pError = NULL;

			if (desc.pSkipConstants) {
				V(D3DXCreateEffectEx(
					pRender->GetDevice(),	//[in]   LPDIRECT3DDEVICE9 pDevice,
					desc.pSrcData,			//[in]   LPCVOID pSrcData,
					desc.SrcDataLen,		//[in]   UINT SrcDataLen,
					desc.pDefines,			//[in]   const D3DXMACRO *pDefines,
					desc.pInclude,			//[in]   LPD3DXINCLUDE pInclude,
					desc.pSkipConstants,	//[in]   LPCSTR pSkipConstants,
					desc.Flags,				//[in]   DWORD Flags,
					desc.pPool,				//[in]   LPD3DXEFFECTPOOL pPool,
					&_ptr,					//[out]  LPD3DXEFFECT *ppEffect,
					&pError					//[out]  LPD3DXBUFFER *ppCompilationErrors
					));
			}
			else {
				V(D3DXCreateEffect(
					pRender->GetDevice(),	//[in]   LPDIRECT3DDEVICE9 pDevice,
					desc.pSrcData,			//[in]   LPCVOID pSrcData,
					desc.SrcDataLen,		//[in]   UINT SrcDataLen,
					desc.pDefines,			//[in]   const D3DXMACRO *pDefines,
					desc.pInclude,			//[in]   LPD3DXINCLUDE pInclude,
					desc.Flags,				//[in]   DWORD Flags,
					desc.pPool,				//[in]   LPD3DXEFFECTPOOL pPool,
					&_ptr,					//[out]  LPD3DXEFFECT *ppEffect,
					&pError					//[out]  LPD3DXBUFFER *ppCompilationErrors
					));
			}

			if FAILED(hr) {
				if (pError != NULL) {
					if (pError->GetBufferSize() > 0)
						DXTrace(__FILE__, (DWORD)__LINE__, hr, String((char*)pError->GetBufferPointer()), _SHOW_ERR_MSGBOX);
					pError->Release();
				}
				SafeRelease(_ptr);
			}
		}

		Effect::Effect(ID3DXEffect* pEffect)
		{
			_ptr = pEffect;
		}

		Effect* Effect::FromFile(LPCTSTR pFileName, Renderer* pRender)
		{
			HRESULT hr;
			ID3DXEffect* ptr = NULL;
			ID3DXBuffer* pError = NULL;

			V(D3DXCreateEffectFromFile(
				pRender->GetDevice(),	//[in]    LPDIRECT3DDEVICE9 pDevice,
				pFileName,				//[in]   LPCTSTR pSrcFile,
				NULL,					//[in]   const D3DXMACRO *pDefines,
				NULL,					//[in]   LPD3DXINCLUDE pInclude,
				0,						//[in]   DWORD Flags,
				NULL,					//[in]   LPD3DXEFFECTPOOL pPool,
				&ptr,					//[out]  LPD3DXEFFECT *ppEffect,
				&pError					//[out]  LPD3DXBUFFER *ppCompilationErrors
				));

			if FAILED(hr) {
				if (pError != NULL) {
					if (pError->GetBufferSize() > 0)
						DXTrace(__FILE__, (DWORD)__LINE__, hr, String((char*)pError->GetBufferPointer()), _SHOW_ERR_MSGBOX);
					pError->Release();
				}
				SafeRelease(ptr);
				return NULL;
			}

			Effect* pEffect = new Effect(ptr);
			return pEffect;
		}

		Effect* Effect::FromBuffer(Buffer& buf, Renderer* pRender)
		{
			HRESULT hr;
			LPD3DXEFFECT ptr;
			LPD3DXBUFFER pError;

			V(D3DXCreateEffect(
				pRender->GetDevice(),	//[in]   LPDIRECT3DDEVICE9 pDevice,
				buf.GetPtr(),			//[in]   LPCVOID pSrcData,
				buf.GetSize(),			//[in]   UINT SrcDataLen,
				NULL,					//[in]   const D3DXMACRO *pDefines,
				NULL,					//[in]   LPD3DXINCLUDE pInclude,
				0,						//[in]   DWORD Flags,
				NULL,					//[in]   LPD3DXEFFECTPOOL pPool,
				&ptr,					//[out]  LPD3DXEFFECT *ppEffect,
				&pError					//[out]  LPD3DXBUFFER *ppCompilationErrors
				));

			if FAILED(hr) {
				if (pError != NULL) {
					if (pError->GetBufferSize() > 0)
						DXTrace(__FILE__, (DWORD)__LINE__, hr, String((char*)pError->GetBufferPointer()), _SHOW_ERR_MSGBOX);
					pError->Release();
				}
				SafeRelease(ptr);
				return NULL;
			}

			Effect* pEffect = new Effect(ptr);
			return pEffect;
		}
	} /* namespace Drawing */
} /* namespace System */

#endif