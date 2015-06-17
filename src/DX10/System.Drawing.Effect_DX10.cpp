/*
 * System.Drawing.Effect_DX10.cpp
 *
 * Code Status: Drafts
 *  Created on: Taiwan
 *      Author: player
 */

#include "../../include/stdafx.h"
#if (_DRAWING_MODE == _DRAWING_MODE_DX10)

#include "../../include/DX10/System.Drawing.Effect.h"
#include "../../include/DX10/System.Drawing.Renderer.h"
#include "../../include/System.String.h"

namespace System {
	namespace Drawing {
		//---------------------------------------------------------------------------------------------------------
		// class Effect

		Effect::Effect(Effect_Desc& desc, Renderer* pRender) 
		{
			HRESULT hr;
			ID3D10Blob* pError = NULL;

			V(D3DX10CreateEffectFromMemory(
				desc.pData,				//[in]   LPCVOID pData,
				desc.DataLength,		//[in]   SIZE_T DataLength,
				desc.pSrcFileName,		//[in]   LPCSTR pSrcFileName,
				desc.pDefines,			//[in]   const D3D10_SHADER_MACRO *pDefines,
				desc.pInclude,			//[in]   ID3D10Include *pInclude,
				desc.pProfile,			//[in]   LPCSTR pProfile,
				desc.HLSLFlags,			//[in]   UINT HLSLFlags,
				desc.FXFlags,			//[in]   UINT FXFlags,
				pRender->GetDevice(),	//[in]   ID3D10Device *pDevice,
				desc.pEffectPool,		//[in]   ID3D10EffectPool *pEffectPool,
				desc.pPump,				//[in]   ID3DX10ThreadPump *pPump,
				&_ptr,					//[out]  ID3D10Effect **ppEffect,
				&pError,				//[out]  ID3D10Blob **ppErrors,
				NULL					//[out]  HRESULT *pHResult
				));

			if FAILED(hr) {
				if (pError != NULL) {
					if (pError->GetBufferSize() > 0)
						DXTrace(__FILE__, (DWORD)__LINE__, hr, String((char*)pError->GetBufferPointer()), _SHOW_ERR_MSGBOX);
					pError->Release();
				}
				SafeRelease(_ptr);
			}
		}

		Effect::Effect(ID3D10Effect* pEffect)
		{
			_ptr = pEffect;
		}

		Effect* Effect::FromFile(LPCTSTR pFileName, Renderer* pRender)
		{
			HRESULT hr;
			ID3D10Effect* ptr = NULL;
			ID3D10Blob* pError = NULL;

			V(D3DX10CreateEffectFromFile(
				pFileName,				//[in]	LPCTSTR pFileName,
				NULL,					//[in]	const D3D10_SHADER_MACRO *pDefines,
				NULL,					//[in]	ID3D10Include *pInclude,
				NULL,					//[in]	LPCSTR pProfile,
				NULL,					//[in]	UINT HLSLFlags,
				0,						//[in]	UINT FXFlags,
				pRender->GetDevice(),	//[in]	ID3D10Device *pDevice,
				NULL,					//[in]	ID3D10EffectPool *pEffectPool,
				NULL,					//[in]	ID3DX10ThreadPump *pPump,
				&ptr,					//[out]  ID3D10Effect **ppEffect,
				&pError,				//[out]  ID3D10Blob **ppErrors,
				NULL					//[out]  HRESULT *pHResult
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
			ID3D10Effect* ptr = NULL;
			ID3D10Blob* pError = NULL;

			V(D3DX10CreateEffectFromMemory(
				buf.GetPtr(),			//[in]   LPCVOID pData,
				buf.GetSize(),			//[in]   SIZE_T DataLength,
				NULL,					//[in]   LPCSTR pSrcFileName,
				NULL,					//[in]   const D3D10_SHADER_MACRO *pDefines,
				NULL,					//[in]   ID3D10Include *pInclude,
				NULL,					//[in]   LPCSTR pProfile,
				0,						//[in]   UINT HLSLFlags,
				0,						//[in]   UINT FXFlags,
				pRender->GetDevice(),	//[in]   ID3D10Device *pDevice,
				NULL,					//[in]   ID3D10EffectPool *pEffectPool,
				NULL,					//[in]   ID3DX10ThreadPump *pPump,
				&ptr,					//[out]  ID3D10Effect **ppEffect,
				&pError,				//[out]  ID3D10Blob **ppErrors,
				NULL					//[out]  HRESULT *pHResult
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