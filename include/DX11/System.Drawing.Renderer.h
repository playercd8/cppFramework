/*
* System.Drawing.Renderer.h
*
* Code Status: Drafts
*  Created on: Taiwan
*      Author: player
*/

#include "../stdafx.h"
#if (_DRAWING_MODE == _DRAWING_MODE_DX11)

#ifndef SYSTEM_DRAWING_RENDERER_H_
#define SYSTEM_DRAWING_RENDERER_H_

#if _MSC_VER > 1000
#pragma once
#endif

#include "DX11.h"
#include "System.Drawing.IndexBuffer.h"
#include "System.Drawing.Mesh.h"
#include "System.Drawing.RenderTargetView.h"
#include "System.Drawing.Shader.h"
#include "System.Drawing.Texture.h"
#include "System.Drawing.VertexBuffer.h"
#include "../System.Drawing.Camera.h"
#include "../System.Drawing.Math.h"

namespace System {
	namespace Drawing {
		class Scene;

		__declspec(align(16))
		typedef struct Renderer_Desc {
			//輸入
			UINT width;
			UINT height;
			BOOL vsync;
			BOOL isFullScreen;
			HWND hWnd;
			ViewPort _viewport;

			//輸出		
			__declspec(align(16))
			ID3D11Device* _pDevice;
			IDXGISwapChain* _pSwapChain;
			ID3D11DeviceContext* _pDeviceContext;
			ID3D11RenderTargetView* _pRenderTargetView;
			ID3D11Texture2D* _pDepthStencilBuffer;
			ID3D11DepthStencilState* _pDepthStencilState;
			ID3D11DepthStencilView* _pDepthStencilView;
			ID3D11RasterizerState* _pRasterState;
		}  Renderer_Desc;

		class Renderer : private Renderer_Desc
		{
		private:
			__declspec(align(16))
			Color _BkColor;
			DWORD _VertexFVF;

		public:
			Renderer(Renderer_Desc& desc);
			virtual ~Renderer();

			void Clear();
			void Present();
			void RenderScene(Scene& scene);

			//-------------------------------------------------------------------------
			//Set相關
			inline void SetBkColor(Color& color)
			{
				_BkColor = color;
			}

			inline void SetIndexBuffer(IndexBuffer& buffer, UINT Offset = 0)
			{
				_pDeviceContext->IASetIndexBuffer(
					buffer,
					DXGI_FORMAT_R32_UINT,
					Offset);
			}

			//inline void SetStreamSource(VertexBuffer& buffer, UINT StreamNumber = 0)
			//{
			//	_pDeviceContext->IASetVertexBuffers(
			//		StartSlot,		//[in]  UINT StartSlot,
			//		NumBuffers,		//[in]  UINT NumBuffers,
			//		&_ptr,			//[in]  ID3D11Buffer *const *ppVertexBuffers,
			//		&Strides,		//[in]  const UINT *pStrides,
			//		&Offsets		//[in]  const UINT *pOffsets
			//		);
			//}

			inline void SetShader(PixelShader shader, UINT NumClassInstances = 0)
			{
				_pDeviceContext->PSSetShader(
					shader,	//[in]  ID3D11PixelShader *pPixelShader,
					NULL,	//[in]  ID3D11ClassInstance *const *ppClassInstances,
					NumClassInstances//[in]  UINT NumClassInstances
					);
			}

			inline void SetShader(VertexShader shader, UINT NumClassInstances = 0)
			{
				_pDeviceContext->VSSetShader(
					shader,	//[in]  ID3D11VertexShader *pVertexShader,
					NULL,	//[in]  ID3D11ClassInstance *const *ppClassInstances,
					NumClassInstances	//[in]  UINT NumClassInstances
					);
			}

			//inline void SetRenderTargetView(DWORD NumViews, RenderTargetView& view) {
			//	//_pDevice->OMSetRenderTargets(NumViews, view);
			//}

			//inline void SetTexture(Texture1D& texture, DWORD id = 0) {
			//	//_pDevice->SetTexture(id, texture);
			//}

			//inline void SetTexture(Texture2D& texture, DWORD id = 0) {
			//	//_pDevice->SetTexture(id, texture);
			//}

			//inline void SetTexture(Texture3D& texture, DWORD id = 0) {
			//	//_pDevice->SetTexture(id, texture);
			//}

			//-------------------------------------------------------------------------
			//Matrix
			//inline void SetTransform(D3DTRANSFORMSTATETYPE State, D3DMATRIX* pMatrix) {
			//pDevice->SetTransform(State, pMatrix);
			//}

			//inline void SetCamera(Camera& camera) {
			//	pDevice->SetTransform(D3DTS_VIEW, &camera.GetViewMatrix());
			//}

			//-------------------------------------------------------------------------
			//Draw相關
			inline void DrawMesh(Mesh& mesh)
			{
				//mesh._Draw(_pDevice, pEffectTechnique, int Passes);
			}

			//void DrawTexture2D(Texture2D& texture, Vector2& dest1, Vector2& dest2, Vector2& src1, Vector2& src2, DWORD color);
			//void DrawTexture2D(Texture2D& texture, float x1, float y1, float x2, float y2, float sx1, float sy1, float sx2, float sy2, DWORD color);

			//以下為DX11專有
			ID3D11Device* GetDevice() const {
				return _pDevice;
			}

			//-------------------------------------------------------------------------
			//FVF
			//void SetFVF(DWORD FVF) {
			//	pDevice->SetFVF(FVF);
			//}

			//DWORD GetFVF() {
			//	DWORD FVF;
			//	pDevice->GetFVF(&FVF);
			//	return FVF;
			//}

			inline DWORD GetVertexFVF() {
				return _VertexFVF;
			}

			inline void SetVertexFVF(DWORD FVF) {
				_VertexFVF = FVF;
			}
		};
	} /* namespace Drawing */
} /* namespace System */

#endif /*  SYSTEM_DRAWING_RENDERER_H_ */
#endif
