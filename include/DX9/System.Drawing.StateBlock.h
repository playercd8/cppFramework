/*
 * System.Drawing.StateBlock.h
 *
 * Code Status: Drafts
 *  Created on: Taiwan
 *      Author: player
 */

#include "../stdafx.h"
#if (_DRAWING_MODE == _DRAWING_MODE_DX9)

#ifndef SYSTEM_DRAWING_STATEBLOCK_H_
#define SYSTEM_DRAWING_STATEBLOCK_H_

#if _MSC_VER > 1000
#pragma once
#endif

#include "DX9.h"
#include "../System.Collections.Map.h"
#include "../System.ComPtr.h"

using namespace System::Collections;

namespace System {
	namespace Drawing {
		class Renderer;
		Renderer* GetDefaultRendererPtr();

		//參考:  D3DRENDERSTATETYPE
		typedef Map<D3DRENDERSTATETYPE, DWORD> StateBlock_Desc;

		class StateBlock : public ComPtr < IDirect3DStateBlock9 > {
			//private:
			//protected:
		public:
			StateBlock(StateBlock_Desc& desc, Renderer* pRender = DefaultRendererPtr);
			StateBlock(IDirect3DStateBlock9* pStateBlock = NULL);

			inline void CaptureStateBlock() {
				_ptr->Capture();
			}

			inline void ApplyStateBlock() {
				_ptr->Apply();
			}
		};
	} /* namespace Drawing */
} /* namespace System */

#endif /* SYSTEM_DRAWING_STATEBLOCK_H_ */
#endif
