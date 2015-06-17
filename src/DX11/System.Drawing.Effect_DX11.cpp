/*
* System.Drawing.Effect_DX11.cpp
*
* Code Status: Drafts
*  Created on: Taiwan
*      Author: player
*/

#include "../../include/stdafx.h"
#if (_DRAWING_MODE == _DRAWING_MODE_DX11)

#include "../../include/DX11/System.Drawing.Effect.h"
#include "../../include/DX11/System.Drawing.Renderer.h"
#include "../../include/System.IO.File.h"
#include "../../include/System.String.h"

using namespace System::IO;

namespace System {
	namespace Drawing {
		//---------------------------------------------------------------------------------------------------------
		// class Effect

		Effect::Effect(Effect_Desc& desc, Renderer* pRender)
		{
			HRESULT hr;

			V(D3DX11CreateEffectFromMemory(
				desc.pData,				//[in]   void *pData,
				desc.DataLength,		//[in]   SIZE_T DataLength,
				desc.FXFlags,			//[in]   UINT FXFlags,
				pRender->GetDevice(),	//[in]   ID3D11Device *pDevice,
				&_ptr					//[out]  ID3DX11Effect **ppEffect
				));
		

			if FAILED(hr) {
				SafeRelease(_ptr);
			}
		}

		Effect::Effect(ID3DX11Effect* pEffect)
		{
			_ptr = pEffect;
		}

		Effect* Effect::FromFile(LPCTSTR pFileName, Renderer* pRender)
		{
			Buffer buf = File.ReadFile(pFileName);

			Effect* pEffect = FromBuffer(buf, pRender);
			return pEffect;
		}

		Effect* Effect::FromBuffer(Buffer& buf, Renderer* pRender)
		{
			HRESULT hr;
			ID3DX11Effect* ptr = NULL;

			V(D3DX11CreateEffectFromMemory(
				buf.GetPtr(),			//[in]   void *pData,
				buf.GetSize(),			//[in]   SIZE_T DataLength,
				0,						//[in]   UINT FXFlags,
				pRender->GetDevice(),	//[in]   ID3D11Device *pDevice,
				&ptr					//[out]  ID3DX11Effect **ppEffect
				));
	

			if FAILED(hr) {
				SafeRelease(ptr);
				return NULL;
			}

			Effect* pEffect = new Effect(ptr);
			return pEffect;
		}

	} /* namespace Drawing */
} /* namespace System */

#endif
