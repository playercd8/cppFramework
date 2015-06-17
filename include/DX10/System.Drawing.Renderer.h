/*
* System.Drawing.Renderer.h
*
* Code Status: Drafts
*  Created on: Taiwan
*      Author: player
*/

#include "../stdafx.h"
#if (_DRAWING_MODE == _DRAWING_MODE_DX10)

#ifndef SYSTEM_DRAWING_RENDERER_H_
#define SYSTEM_DRAWING_RENDERER_H_

#if _MSC_VER > 1000
#pragma once
#endif

#include "DX10.h"
#include "../System.Drawing.Camera.h"
#include "../System.Drawing.Math.h"
#include "System.Drawing.IndexBuffer.h"
#include "System.Drawing.Mesh.h"
#include "System.Drawing.RenderTargetView.h"
#include "System.Drawing.Shader.h"
#include "System.Drawing.Texture.h"
#include "System.Drawing.VertexBuffer.h"

namespace System {
	namespace Drawing {
		class Scene;

		typedef D3D10_BLEND Blend_Type;
		typedef D3D10_BLEND_OP BlendFunction_Type;
		typedef D3D10_FILL_MODE Fill_Mode;

		typedef struct Renderer_Desc {
			//輸入
			UINT width;
			UINT height;
			bool vsync;
			bool isFullScreen;
			HWND hWnd;
			ViewPort _viewport;

			//輸出
			ID3D10Device* _pDevice;
			IDXGISwapChain* _pSwapChain;
			ID3D10RenderTargetView* _pRenderTargetView;
			ID3D10Texture2D* _pDepthStencilBuffer;
			ID3D10DepthStencilState* _pDepthStencilState;
			ID3D10DepthStencilView* _pDepthStencilView;
			ID3D10RasterizerState* _pRasterState;
		}  Renderer_Desc;

		class Renderer : private Renderer_Desc
		{
		private:
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
				_pDevice->IASetIndexBuffer(
					buffer,
					DXGI_FORMAT_R32_UINT,
					Offset
					);
			}

			//inline void SetStreamSource(VertexBuffer& buffer, UINT StreamNumber = 0)
			//{
			//_pDevice->IASetVertexBuffers(
			//	buffer,					//[in]  ID3D10Buffer *pIndexBuffer,
			//	DXGI_FORMAT_R32_UINT,	//[in]  DXGI_FORMAT Format,
			//	&StreamNumber			//[in]  UINT Offset

			//	);
			//pDevice->SetFVF(buffer.GetFVF());
			//pDevice->SetStreamSource(
			//	StreamNumber,				//[in]  UINT StreamNumber,
			//	buffer,						//[in]  IDirect3DVertexBuffer9 *pStreamData,
			//	0,							//[in]  UINT OffsetInBytes,
			//	buffer.GetStride()			//[in]  UINT Stride
			//	);
			//}

			inline void SetShader(PixelShader shader)
			{
				_pDevice->PSSetShader(shader);
			}

			inline void SetShader(VertexShader shader)
			{
				_pDevice->VSSetShader(shader);
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

			//以下為DX10專有
			ID3D10Device* GetDevice() const {
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
