/*
 * System.Drawing.Effect.h
 *
 * Code Status: Drafts
 *  Created on: Taiwan
 *      Author: player
 */

#include "../stdafx.h"
#if (_DRAWING_MODE == _DRAWING_MODE_DX9)

#ifndef SYSTEM_DRAWING_EFFECT_H_
#define SYSTEM_DRAWING_EFFECT_H_

#if _MSC_VER > 1000
#pragma once
#endif

#include "DX9.h"
#include "../System.Buffer.h"
#include "../System.ComPtr.h"
#include "./library/DXSDK/Include/d3dx9effect.h"

namespace System {
	namespace Drawing {
		class Renderer;
		Renderer* GetDefaultRendererPtr();

		typedef struct Effect_Desc {
			LPCVOID pSrcData;
			UINT SrcDataLen;
			const D3DXMACRO *pDefines;
			LPD3DXINCLUDE pInclude;
			LPCSTR pSkipConstants;
			DWORD Flags;
			LPD3DXEFFECTPOOL pPool;
		}  Effect_Desc;

		class Effect : public ComPtr < ID3DXEffect > {
			//private:
			//protected:
		public:
			Effect(Effect_Desc& desc, Renderer* pRender = DefaultRendererPtr);
			Effect(ID3DXEffect* pEffect = NULL);

			static Effect* FromFile(LPCTSTR pFileName, Renderer* pRender = DefaultRendererPtr);
			static Effect* FromBuffer(Buffer& buf, Renderer* pRender = DefaultRendererPtr);
		};
	} /* namespace Drawing */
} /* namespace System */

#endif /* SYSTEM_DRAWING_EFFECT_H_ */
#endif
