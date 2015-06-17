/*
 * System.Drawing.StateBlock_DX9.cpp
 *
 *  Created on: Taiwan
 *      Author: player
 */

#include "../../include/stdafx.h"
#if (_DRAWING_MODE == _DRAWING_MODE_DX9)

#include "../../include/DX9/System.Drawing.StateBlock.h"
#include "../../include/DX9/System.Drawing.Renderer.h"

using namespace System::Collections;

namespace System {
namespace Drawing {

StateBlock::StateBlock(StateBlock_Desc& desc, Renderer* pRender) 
{
	HRESULT hr;
	IDirect3DDevice9* pDevice  = pRender->GetDevice();
	V(pDevice->CreateStateBlock(
		D3DSBT_ALL,		//[in]	D3DSTATEBLOCKTYPE Type,
		&_ptr			//[out]	IDirect3DStateBlock9 **ppSB
		));

	if (!desc.IsEmpty()) {
#if defined(_ENABLE_CPP11)
		for (auto& kv : desc.GetAll()) {
			V(pDevice->SetRenderState(kv.first, kv.second));
		}
#else
		Map<D3DRENDERSTATETYPE, DWORD>::Iterator pos = desc.GetHeadPosition();
		while (desc.iteratorValid(pos)) {
			pDevice->SetRenderState(pos->first, pos->second);
			pos++;
		}
#endif
	}

	_ptr->Capture();
}


StateBlock::StateBlock(IDirect3DStateBlock9* pStateBlock) {
	_ptr = pStateBlock;
}



} /* namespace Drawing */
} /* namespace System */

#endif
