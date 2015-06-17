/*
* System.Drawing.Renderer.h
*
* Code Status: Drafts
*  Created on: Taiwan
*      Author: player
*/

#include "../stdafx.h"
#if (_DRAWING_MODE == _DRAWING_MODE_DX9)

#ifndef SYSTEM_DRAWING_RENDERER_H_
#define SYSTEM_DRAWING_RENDERER_H_

#if _MSC_VER > 1000
#pragma once
#endif

#include "DX9.h"
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
		class Font;
		class Scene;

		typedef D3DBLEND Blend_Type;
		typedef D3DBLENDOP BlendFunction_Type;
		typedef D3DFILLMODE Fill_Mode;

		typedef struct Renderer_Desc {
			//輸入
			UINT width;
			UINT height;
			bool vsync;
			bool isFullScreen;
			HWND hWnd;
			ViewPort _viewport;

			//輸出
			IDirect3DDevice9* _pDevice;
			IDirect3DSwapChain9* _pSwapChain;
		}  Renderer_Desc;

		class Renderer : private Renderer_Desc
		{
		private:
			D3DCOLOR _BkColor;
			DWORD _VertexFVF;

		public:
			Renderer(Renderer_Desc& desc);
			virtual ~Renderer();

			void Clear();
			void Present();
			void RenderScene(Scene& scene);

			//-------------------------------------------------------------------------
			//Set相關
			//-------------------------------------------------------------------------

			inline void SetBkColor(Color& color) {
				_BkColor = color;
			}

			inline void SetIndexBuffer(IndexBuffer& buffer, UINT Offset = 0) {
				_pDevice->SetIndices(
					buffer	//[in]  IDirect3DIndexBuffer9 *pIndexData
					);
			}

			inline void SetStreamSource(VertexBuffer& buffer, UINT StreamNumber = 0) {
				_pDevice->SetFVF(buffer.GetFVF());
				_pDevice->SetStreamSource(
					StreamNumber,				//[in]  UINT StreamNumber,
					buffer,						//[in]  IDirect3DVertexBuffer9 *pStreamData,
					0,							//[in]  UINT OffsetInBytes,
					buffer.GetStride()			//[in]  UINT Stride
					);
			}

			inline void SetShader(PixelShader shader) {
				_pDevice->SetPixelShader(shader);
			}

			inline void SetShader(VertexShader shader) {
				_pDevice->SetVertexShader(shader);
			}

			inline void SetRenderTargetView(DWORD NumViews, RenderTargetView& view) {
				_pDevice->SetRenderTarget(NumViews, view);
			}

			inline void SetTexture(Texture1D& texture, DWORD id = 0) {
				_pDevice->SetTexture(id, texture);
			}

			inline void SetTexture(Texture2D& texture, DWORD id = 0) {
				_pDevice->SetTexture(id, texture);
			}

			inline void SetTexture(Texture3D& texture, DWORD id = 0) {
				_pDevice->SetTexture(id, texture);
			}

			//-------------------------------------------------------------------------
			//Matrix
			inline void SetTransform(D3DTRANSFORMSTATETYPE State, D3DMATRIX* pMatrix) {
				_pDevice->SetTransform(State, pMatrix);
			}

			inline void SetCamera(Camera& camera) {
				const D3DMATRIX* pMatrix = camera.GetViewMatrix();
				_pDevice->SetTransform(D3DTS_VIEW, pMatrix);
			}

			//-------------------------------------------------------------------------
			//Draw相關
			inline void DrawMesh(Mesh& mesh) {
				mesh._Draw(_pDevice);
			}

			void DrawTexture2D(Texture2D& texture, Vector2& dest1, Vector2& dest2, Vector2& src1, Vector2& src2, DWORD color);
			void DrawTexture2D(Texture2D& texture, float x1, float y1, float x2, float y2, float sx1, float sy1, float sx2, float sy2, DWORD color);

			void DrawText(Font& font, LPCTSTR pString, int count, LPRECT pRect, DWORD format, DWORD color);

			//以下為DX9專有
			IDirect3DDevice9* GetDevice() const {
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
