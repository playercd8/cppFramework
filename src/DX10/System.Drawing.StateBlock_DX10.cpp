/*
 * System.Drawing.StateBlock_DX10.cpp
 *
 *  Created on: Taiwan
 *      Author: player
 */

#include "../../include/stdafx.h"
#if (_DRAWING_MODE == _DRAWING_MODE_DX10)

#include "../../include/DX10/System.Drawing.Renderer.h"
#include "../../include/DX10/System.Drawing.StateBlock.h"

namespace System {
	namespace Drawing {
		//---------------------------------------------------------------------------------------------------------
		// class StateBlock

		StateBlock::StateBlock(StateBlock_Desc& desc, Renderer* pRender)
		{
			HRESULT hr;
			V(D3D10CreateStateBlock(
				pRender->GetDevice(),		//[in]   ID3D10Device *pDevice,
				&desc,						//[in]   D3D10_STATE_BLOCK_MASK *pStateBlockMask,
				&_ptr						//[out]  ID3D10StateBlock **ppStateBlock
				));

			if FAILED(hr)
				_ptr = NULL;
			else
				_ptr->Capture();
		}

		StateBlock::StateBlock(ID3D10StateBlock* pStateBlock)
		{
			_ptr = pStateBlock;
		}

		//---------------------------------------------------------------------------------------------------------
		// class BlendState

		BlendState::BlendState(BlendState_Desc& desc, Renderer* pRender)
		{
			HRESULT hr;
			V(pRender->GetDevice()->CreateBlendState(
				&desc,		//[in]   const D3D10_BLEND_DESC *pBlendStateDesc,
				&_ptr		//[out]  ID3D10BlendState **ppBlendState
				));
			if FAILED(hr)
				_ptr = NULL;
		}

		BlendState::BlendState(ID3D10BlendState* pBlendState)
		{
			_ptr = pBlendState;
		}

		//void BlendState::SetBlendState(const float& BlendFactor, UINT SampleMask) {
		//	_pDevice->OMSetBlendState(
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
			HRESULT hr;
			V(pRender->GetDevice()->CreateRasterizerState(
				&desc,	//[in]   const D3D10_RASTERIZER_DESC *pRasterizerDesc,
				&_ptr	//[out]  ID3D10RasterizerState **ppRasterizerState
				));
			if FAILED(hr)
				_ptr = NULL;
		}

		RasterizerState::RasterizerState(ID3D10RasterizerState* pRasterizerState)
		{
			_ptr = pRasterizerState;
		}

		//void RasterizerState::SetRasterizerState() {
		//	_pDevice->RSSetState(_ptr);
		//}

		//---------------------------------------------------------------------------------------------------------
		// class SamplerState

		SamplerState::SamplerState(SamplerState_Desc& desc, Renderer* pRender)
		{
			HRESULT hr;
			V(pRender->GetDevice()->CreateSamplerState(
				&desc,		//[in]   const D3D10_SAMPLER_DESC *pSamplerDesc,
				&_ptr		//[out]  ID3D10SamplerState **ppSamplerState
				));
			if FAILED(hr)
				_ptr = NULL;
		}

		SamplerState::SamplerState(ID3D10SamplerState* pSamplerState)
		{
			_ptr = pSamplerState;
		}
		//
		//void SamplerState::VSSetSamplers(UINT StartSlot, UINT NumSamplers) {
		//	_pDevice->VSSetSamplers(
		//		StartSlot,		//[in]  UINT StartSlot,
		//		NumSamplers,	//[in]  UINT NumSamplers,
		//		&_ptr			//[in]  ID3D10SamplerState *const *ppSamplers
		//		);
		//
		//}
		//void SamplerState::GSSetSamplers(UINT StartSlot, UINT NumSamplers) {
		//	_pDevice->GSSetSamplers(
		//		StartSlot,		//[in]   UINT StartSlot,
		//		NumSamplers,	//[in]   UINT NumSamplers,
		//		&_ptr			//[in]  ID3D10SamplerState *const *ppSamplers
		//		);
		//
		//}
		//void SamplerState::PSSetSamplers(UINT StartSlot, UINT NumSamplers) {
		//	_pDevice->PSSetSamplers(
		//		StartSlot,		//[in]  UINT StartSlot,
		//		NumSamplers,	//[in]  UINT NumSamplers,
		//		&_ptr			//[in]  ID3D10SamplerState *const *ppSamplers
		//		);
		//}
	} /* namespace Drawing */
} /* namespace System */

#endif