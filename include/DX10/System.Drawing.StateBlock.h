/*
 * System.Drawing.StateBlock.h
 *
 *  Created on: Taiwan
 *      Author: player
 */

#include "../stdafx.h"
#if (_DRAWING_MODE == _DRAWING_MODE_DX10)

#ifndef SYSTEM_DRAWING_STATEBLOCK_H_
#define SYSTEM_DRAWING_STATEBLOCK_H_

#if _MSC_VER > 1000
#pragma once
#endif

#include "DX10.h"
#include "../System.ComPtr.h"

namespace System {
	namespace Drawing {
		class Renderer;
		Renderer* GetDefaultRendererPtr();

		//---------------------------------------------------------------------------------------------------------
		// class StateBlock

		typedef D3D10_STATE_BLOCK_MASK  StateBlock_Desc;

		class StateBlock : public ComPtr < ID3D10StateBlock > {
			//private:
			//protected:

		public:
			StateBlock(StateBlock_Desc& desc, Renderer* pRender = DefaultRendererPtr);
			StateBlock(ID3D10StateBlock* pStateBlock = NULL);

			inline void CaptureStateBlock() {
				_ptr->Capture();
			}

			inline void ApplyStateBlock() {
				_ptr->Apply();
			}
		};

		//---------------------------------------------------------------------------------------------------------
		// class BlendState

		typedef D3D10_BLEND_DESC BlendState_Desc;

		class BlendState : public ComPtr < ID3D10BlendState > {
			//private:
			//protected:

		public:
			BlendState(BlendState_Desc& desc, Renderer* pRender = DefaultRendererPtr);
			BlendState(ID3D10BlendState* pBlendState = NULL);

			//void SetBlendState(const float& BlendFactor, UINT SampleMask);
		};

		//---------------------------------------------------------------------------------------------------------
		// class RasterizerState

		typedef D3D10_RASTERIZER_DESC  RasterizerState_Desc;

		class RasterizerState : public ComPtr < ID3D10RasterizerState > {
			//private:
			//protected:

		public:
			RasterizerState(RasterizerState_Desc& desc, Renderer* pRender = DefaultRendererPtr);
			RasterizerState(ID3D10RasterizerState* pRasterizerState = NULL);

			//void SetRasterizerState();
		};

		//---------------------------------------------------------------------------------------------------------
		// class SamplerState

		typedef D3D10_SAMPLER_DESC   SamplerState_Desc;

		class SamplerState : public ComPtr < ID3D10SamplerState > {
			//private:
			//protected:

		public:
			SamplerState(SamplerState_Desc& desc, Renderer* pRender = DefaultRendererPtr);
			SamplerState(ID3D10SamplerState* pSamplerState = NULL);

			//void VSSetSamplers(UINT StartSlot, UINT NumSamplers);
			//void GSSetSamplers(UINT StartSlot, UINT NumSamplers);
			//void PSSetSamplers(UINT StartSlot, UINT NumSamplers);
		};
	} /* namespace Drawing */
} /* namespace System */

#endif /* SYSTEM_DRAWING_STATEBLOCK_H_ */
#endif
