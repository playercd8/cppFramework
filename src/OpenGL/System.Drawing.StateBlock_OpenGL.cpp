/*
 * System.Drawing.StateBlock_OpenGL.cpp
 *
 *  Created on: Taiwan
 *      Author: player
 */

#include "../../include/stdafx.h"
#if (_DRAWING_MODE == _DRAWING_MODE_OpenGL)

#include "../../include/OpenGL/System.Drawing.StateBlock.h"
#include "../../include/OpenGL/System.Drawing.Renderer.h"


namespace System {
namespace Drawing {

//---------------------------------------------------------------------------------------------------------
// class StateBlock
/*
StateBlock::StateBlock(Graphics& g, StateBlock_Desc& desc) {
	_pDevice = g.GetDevice();

	HRESULT  hr = D3D10CreateStateBlock(
		_pDevice,		//[in]   ID3D10Device *pDevice,
		&desc,			//[in]   D3D10_STATE_BLOCK_MASK *pStateBlockMask,
		&_ptr			//[out]  ID3D10StateBlock **ppStateBlock
		);


	_ptr->Capture();
}


StateBlock::StateBlock(Graphics& g, ID3D10StateBlock* pStateBlock) {
	_pDevice = g.GetDevice();
	_ptr = pStateBlock;
}

void StateBlock::CaptureStateBlock() {
	_ptr->Capture();
}

void StateBlock::ApplyStateBlock() {
	_ptr->Apply();
}
*/

//---------------------------------------------------------------------------------------------------------
// class BlendState


BlendState::BlendState(BlendState_Desc& desc, Renderer* pRender) 
{
	HRESULT hr = pRender->GetDevice()->CreateBlendState(
		&desc,		//[in]   const D3D10_BLEND_DESC *pBlendStateDesc,
		&_ptr		//[out]  ID3D10BlendState **ppBlendState
		);
	if FAILED(hr) {
		_ptr = NULL;
	}
}

BlendState::BlendState(ID3D11BlendState* pBlendState) 
{
	_ptr = pBlendState;
}

//void BlendState::SetBlendState(const float& BlendFactor, UINT SampleMask) {
//	_pDeviceContext->OMSetBlendState(
//		_ptr,			//[in]  ID3D10BlendState *pBlendState,
//		&BlendFactor,	//[in]  const FLOAT BlendFactor,
//		SampleMask		//[in]  UINT SampleMask
//		);
//
//}

//---------------------------------------------------------------------------------------------------------
// class RasterizerState

RasterizerState::RasterizerState(RasterizerState_Desc& desc, Renderer* pRender) 
{
	HRESULT hr = pRender->GetDevice()->CreateRasterizerState(
		&desc,	//[in]   const D3D10_RASTERIZER_DESC *pRasterizerDesc,
		&_ptr	//[out]  ID3D10RasterizerState **ppRasterizerState
		);
	if FAILED(hr) {
		_ptr = NULL;
	}
}

RasterizerState::RasterizerState(ID3D11RasterizerState* pRasterizerState) 
{
	_ptr = pRasterizerState;
}

//void RasterizerState::SetRasterizerState() {
//	_pDeviceContext->RSSetState(_ptr);
//}

//---------------------------------------------------------------------------------------------------------
// class SamplerState


SamplerState::SamplerState(SamplerState_Desc& desc, Renderer* pRender) 
{
	HRESULT hr = pRender->GetDevice()->CreateSamplerState(
		&desc,		//[in]   const D3D11_SAMPLER_DESC *pSamplerDesc,
		&_ptr		//[out]  ID3D11SamplerState **ppSamplerState
		);
	if FAILED(hr) {
		_ptr = NULL;
	}

}

SamplerState::SamplerState(ID3D11SamplerState* pSamplerState) 
{
	_ptr = pSamplerState;
}

//void SamplerState::VSSetSamplers(UINT StartSlot, UINT NumSamplers) {
//	_pDeviceContext->VSSetSamplers(
//		StartSlot,		//[in]  UINT StartSlot,
//		NumSamplers,	//[in]  UINT NumSamplers,
//		&_ptr			//[in]  ID3D10SamplerState *const *ppSamplers
//		);
//
//}
//void SamplerState::GSSetSamplers(UINT StartSlot, UINT NumSamplers) {
//	_pDeviceContext->GSSetSamplers(
//		StartSlot,		//[in]   UINT StartSlot,
//		NumSamplers,	//[in]   UINT NumSamplers,
//		&_ptr			//[in]  ID3D10SamplerState *const *ppSamplers
//		);
//
//}
//void SamplerState::PSSetSamplers(UINT StartSlot, UINT NumSamplers) {
//	_pDeviceContext->PSSetSamplers(
//		StartSlot,		//[in]  UINT StartSlot,
//		NumSamplers,	//[in]  UINT NumSamplers,
//		&_ptr			//[in]  ID3D10SamplerState *const *ppSamplers
//		);
//}




} /* namespace Drawing */
} /* namespace System */

#endif
