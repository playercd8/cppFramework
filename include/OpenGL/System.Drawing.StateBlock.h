/*
 * System.Drawing.StateBlock.h
 *
 *  Created on: Taiwan
 *      Author: player
 */

#include "../stdafx.h"
#if (_DRAWING_MODE == _DRAWING_MODE_OpenGL)

#ifndef SYSTEM_DRAWING_STATEBLOCK_H_
#define SYSTEM_DRAWING_STATEBLOCK_H_

#if _MSC_VER > 1000
	#pragma once
#endif

#include "OpenGL.h"
#include "../System.ComPtr.h"

namespace System {
namespace Drawing {

class Renderer;
Renderer* GetDefaultRendererPtr();

//---------------------------------------------------------------------------------------------------------
// class StateBlock
/*
typedef D3D10_STATE_BLOCK_MASK  StateBlock_Desc;

class StateBlock : public ComPtr<ID3D10StateBlock> {
protected:
	ID3D10Device* _pDevice;

public:
	StateBlock(Graphics& g, StateBlock_Desc& desc);
	StateBlock(Graphics& g, ID3D10StateBlock* pStateBlock = NULL);

	void CaptureStateBlock();
	void ApplyStateBlock();
};
*/

//---------------------------------------------------------------------------------------------------------
// class BlendState

typedef D3D11_BLEND_DESC BlendState_Desc;

class BlendState : public ComPtr<ID3D11BlendState> {
protected:
	ID3D11DeviceContext* _pDeviceContext;

public:
	BlendState(BlendState_Desc& desc, Renderer* pRender = DefaultRendererPtr);
	BlendState(ID3D11BlendState* pBlendState = NULL);

	//void SetBlendState(const float& BlendFactor, UINT SampleMask);
};

//---------------------------------------------------------------------------------------------------------
// class RasterizerState

typedef D3D11_RASTERIZER_DESC  RasterizerState_Desc;

class RasterizerState : public ComPtr<ID3D11RasterizerState> {
//protected:
public:
	RasterizerState(RasterizerState_Desc& desc, Renderer* pRender = DefaultRendererPtr);
	RasterizerState(ID3D11RasterizerState* pRasterizerState = NULL);

	//void SetRasterizerState();
};

//---------------------------------------------------------------------------------------------------------
// class SamplerState


typedef D3D11_SAMPLER_DESC   SamplerState_Desc;

class SamplerState : public ComPtr<ID3D11SamplerState> {
//protected:
public:
	SamplerState(SamplerState_Desc& desc, Renderer* pRender = DefaultRendererPtr);
	SamplerState(ID3D11SamplerState* pSamplerState = NULL);

	//void VSSetSamplers(UINT StartSlot, UINT NumSamplers);
	//void GSSetSamplers(UINT StartSlot, UINT NumSamplers);
	//void PSSetSamplers(UINT StartSlot, UINT NumSamplers);
};


} /* namespace Drawing */
} /* namespace System */

#endif /* SYSTEM_DRAWING_STATEBLOCK_H_ */
#endif
