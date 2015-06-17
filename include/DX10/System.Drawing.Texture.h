/*
 * System.Drawing.Texture.h
 *
 *  Created on: Taiwan
 *      Author: player
 */

#include "../stdafx.h"
#if (_DRAWING_MODE == _DRAWING_MODE_DX10)

#ifndef SYSTEM_DRAWING_TEXTURE_H_
#define SYSTEM_DRAWING_TEXTURE_H_

#if _MSC_VER > 1000
#pragma once
#endif

#include "DX10.h"
#include "System.Drawing.Graphics.h"
#include "../System.Buffer.h"
#include "../System.ComPtr.h"

namespace System {
	namespace Drawing {
		class Renderer;
		Renderer* GetDefaultRendererPtr();

		typedef D3D10_TEXTURE1D_DESC Texture1D_Desc;
		typedef D3D10_TEXTURE2D_DESC Texture2D_Desc;
		typedef D3D10_TEXTURE3D_DESC Texture3D_Desc;

		//---------------------------------------------------------------------------------------------------------
		// class Texture1D
#pragma region class Texture1D
		class Texture1D : public ComPtr < ID3D10Texture1D > {
		protected:
			ComPtr<ID3D10ShaderResourceView>  _ResourceView;
			float _width;
			float _invW;
			friend class Renderer;
		public:
			Texture1D(Texture1D_Desc& desc, Renderer* pRender = DefaultRendererPtr);
			Texture1D(ID3D10Texture1D* pTexture = NULL, Renderer* pRender = DefaultRendererPtr);

			operator ID3D10ShaderResourceView*() {
				return _ResourceView.GetPtr();
			}

			static Texture1D* FromFile(LPCTSTR pFileName, Renderer* pRender = DefaultRendererPtr);
			static Texture1D* FromBuffer(Buffer& buf, Renderer* pRender = DefaultRendererPtr);
		};
#pragma endregion class Texture1D
		//---------------------------------------------------------------------------------------------------------
		// class Texture2D
#pragma region class Texture2D
		class Texture2D : public ComPtr < ID3D10Texture2D > {
		protected:
			ComPtr<ID3D10ShaderResourceView>  _ResourceView;
			float _width;
			float _height;
			float _invW;
			float _invH;
			friend class Renderer;
		public:
			Texture2D(Texture2D_Desc& desc, Renderer* pRender = DefaultRendererPtr);
			Texture2D(ID3D10Texture2D* pTexture = NULL, Renderer* pRender = DefaultRendererPtr);

			operator ID3D10ShaderResourceView*() {
				return _ResourceView.GetPtr();
			}

			static Texture2D* FromFile(LPCTSTR pFileName, Renderer* pRender = DefaultRendererPtr);
			static Texture2D* FromBuffer(Buffer& buf, Renderer* pRender = DefaultRendererPtr);
		};
#pragma endregion class Texture2D
		//---------------------------------------------------------------------------------------------------------
		// class Texture3D
#pragma region class Texture3D
		class Texture3D : public ComPtr < ID3D10Texture3D > {
		protected:
			ComPtr<ID3D10ShaderResourceView>  _ResourceView;
			float _width;
			float _height;
			float _depth;
			float _invW;
			float _invH;
			float _invD;
			friend class Renderer;
		public:
			Texture3D(Texture3D_Desc& desc, Renderer* pRender = DefaultRendererPtr);
			Texture3D(ID3D10Texture3D* pTexture = NULL, Renderer* pRender = DefaultRendererPtr);

			operator ID3D10ShaderResourceView*() {
				return _ResourceView.GetPtr();
			}

			static Texture3D* FromFile(LPCTSTR pFileName, Renderer* pRender = DefaultRendererPtr);
			static Texture3D* FromBuffer(Buffer& buf, Renderer* pRender = DefaultRendererPtr);
		};
#pragma region class Texture3D
	} /* namespace Drawing */
} /* namespace System */

#endif /* SYSTEM_DRAWING_TEXTURE_H_ */
#endif
