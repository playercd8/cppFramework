/*
* System.Drawing.Effect.h
*
* Code Status: Drafts
*  Created on: Taiwan
*      Author: player
*/

#include "../stdafx.h"
#if (_DRAWING_MODE == _DRAWING_MODE_OpenGL)

#ifndef SYSTEM_DRAWING_EFFECT_H_
#define SYSTEM_DRAWING_EFFECT_H_

#if _MSC_VER > 1000
#pragma once
#endif

#include "OpenGL.h"
//#include "./library/DXSDK/lib/Effects11/Inc/d3dx11effect.h"
//#include "./library/DXSDK/include/d3dx11effect.h"
#include "../System.Buffer.h"
#include "../System.ComPtr.h"


namespace System {
	namespace Drawing {
		class Renderer;
		Renderer* GetDefaultRendererPtr();

		typedef struct Effect_Desc {
			void* pData;
			SIZE_T DataLength;
			UINT FXFlags;
		}  Effect_Desc;

		class Effect {
			//private:
			//protected:
		public:
			Effect(Effect_Desc& desc, Renderer* pRender = DefaultRendererPtr);
			//Effect(ID3DX11Effect* pEffect = NULL);

			static Effect* FromFile(LPCTSTR pFileName, Renderer* pRender = DefaultRendererPtr);
			static Effect* FromBuffer(Buffer& buf, Renderer* pRender = DefaultRendererPtr);

		};
	} /* namespace Drawing */
} /* namespace System */

#endif /* SYSTEM_DRAWING_EFFECT_H_ */
#endif
