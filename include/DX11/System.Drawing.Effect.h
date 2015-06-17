/*
* System.Drawing.Effect.h
*
* Code Status: Drafts
*  Created on: Taiwan
*      Author: player
*/

#include "../stdafx.h"
#if (_DRAWING_MODE == _DRAWING_MODE_DX11)

#ifndef SYSTEM_DRAWING_EFFECT_H_
#define SYSTEM_DRAWING_EFFECT_H_

#if _MSC_VER > 1000
#pragma once
#endif

#include "DX11.h"
#include "./library/DXSDK/include/d3dx11effect.h"
#include "../System.Buffer.h"
#include "../System.ComPtr.h"

#if defined(_M_IX86)
	#if defined(_DEBUG)
		#pragma comment(lib, "./Debug/Effects11.lib")
	#else
		#pragma comment(lib, "./Release/Effects11.lib")
#endif
	#pragma comment(lib, "./library/DXSDK/lib/x86/d3dcompiler.lib")
#elif defined(_M_X64)
	#if defined(_DEBUG)
		#pragma comment(lib, "./library/DXSDK/lib/Effects11/x64/Debug/Effects11.lib")
	#else
		#pragma comment(lib, "./library/DXSDK/lib/Effects11/x64/Release/Effects11.lib")
	#endif
	#pragma comment(lib, "./library/DXSDK/lib/x64/d3dcompiler.lib.lib")
#endif

namespace System {
	namespace Drawing {
		class Renderer;
		Renderer* GetDefaultRendererPtr();

		typedef struct Effect_Desc {
			void* pData;
			SIZE_T DataLength;
			UINT FXFlags;
		}  Effect_Desc;

		class Effect : public ComPtr < ID3DX11Effect > {
			//private:
			//protected:
		public:
			Effect(Effect_Desc& desc, Renderer* pRender = DefaultRendererPtr);
			Effect(ID3DX11Effect* pEffect = NULL);

			static Effect* FromFile(LPCTSTR pFileName, Renderer* pRender = DefaultRendererPtr);
			static Effect* FromBuffer(Buffer& buf, Renderer* pRender = DefaultRendererPtr);

		};
	} /* namespace Drawing */
} /* namespace System */

#endif /* SYSTEM_DRAWING_EFFECT_H_ */
#endif
