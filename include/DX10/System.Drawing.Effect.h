/*
 * System.Drawing.Effect.h
 *
 * Code Status: Drafts
 *  Created on: Taiwan
 *      Author: player
 */

#include "../stdafx.h"
#if (_DRAWING_MODE == _DRAWING_MODE_DX10)

#ifndef SYSTEM_DRAWING_EFFECT_H_
#define SYSTEM_DRAWING_EFFECT_H_

#if _MSC_VER > 1000
#pragma once
#endif

#include "DX10.h"
#include "./library/DXSDK/Include/D3D10effect.h"
#include "../System.Buffer.h"
#include "../System.ComPtr.h"


namespace System {
	namespace Drawing {
		class Renderer;
		Renderer* GetDefaultRendererPtr();

		typedef struct Effect_Desc {
			LPCVOID pData; 
			SIZE_T DataLength;
			LPCSTR pSrcFileName;
			const D3D10_SHADER_MACRO* pDefines; 
			ID3D10Include* pInclude;
			LPCSTR pProfile;
			UINT HLSLFlags; 
			UINT FXFlags;
			ID3D10EffectPool* pEffectPool;
			ID3DX10ThreadPump* pPump;
		}  Effect_Desc;

		class Effect : public ComPtr < ID3D10Effect > {
			//private:
			//protected:
		public:
			Effect(Effect_Desc& desc, Renderer* pRender = DefaultRendererPtr);
			Effect(ID3D10Effect* pEffect = NULL);

			static Effect* FromFile(LPCTSTR pFileName, Renderer* pRender = DefaultRendererPtr);
			static Effect* FromBuffer(Buffer& buf, Renderer* pRender = DefaultRendererPtr);

		};
	} /* namespace Drawing */
} /* namespace System */

#endif /* SYSTEM_DRAWING_EFFECT_H_ */
#endif
