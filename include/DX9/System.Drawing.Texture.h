/*
 * System.Drawing.Texture.h
 *
 * Code Status: Drafts
 *  Created on: Taiwan
 *      Author: player
 */

#include "../stdafx.h"
#if (_DRAWING_MODE == _DRAWING_MODE_DX9)

#ifndef SYSTEM_DRAWING_TEXTURE_H_
#define SYSTEM_DRAWING_TEXTURE_H_

#if _MSC_VER > 1000
#pragma once
#endif

#include "DX9.h"
#include "../System.Buffer.h"
#include "../System.ComPtr.h"
#include "../System.Drawing.Math.h"

namespace System {
	namespace Drawing {
		class Renderer;
		Renderer* GetDefaultRendererPtr();

		typedef struct Texture1D_Desc {
			UINT Width;
			UINT Levels;
			DWORD Usage;
			D3DFORMAT Format;
			D3DPOOL Pool;
			HANDLE* pSharedHandle;
		} Texture1D_Desc;

		typedef struct Texture2D_Desc {
			UINT Width;
			UINT Height;
			UINT Levels;
			DWORD Usage;
			D3DFORMAT Format;
			D3DPOOL Pool;
			HANDLE* pSharedHandle;
		} Texture2D_Desc;

		typedef struct Texture3D_Desc {
			UINT Width;
			UINT Height;
			UINT Depth;
			UINT Levels;
			DWORD Usage;
			D3DFORMAT Format;
			D3DPOOL Pool;
			HANDLE* pSharedHandle;
		} Texture3D_Desc;

		//---------------------------------------------------------------------------------------------------------
		// class Texture1D

		class Texture1D : public ComPtr < IDirect3DBaseTexture9 > {
			//private:
		protected:
			ComPtr<IDirect3DCubeTexture9> _pTexture;
			float _width;
			float _invW;
			friend class Renderer;

		public:
			Texture1D(Texture1D_Desc& desc, Renderer* pRender = DefaultRendererPtr);
			Texture1D(IDirect3DCubeTexture9* pTexture = NULL);

			static Texture1D* FromFile(LPCTSTR pFileName, Renderer* pRender = DefaultRendererPtr);
			static Texture1D* FromBuffer(Buffer& buf, Renderer* pRender = DefaultRendererPtr);

			inline operator IDirect3DCubeTexture9*() {
				return _pTexture;
			}
		};

		//---------------------------------------------------------------------------------------------------------
		// class Texture2D

		class Texture2D : public ComPtr < IDirect3DBaseTexture9 > {
			//private:
		protected:
			ComPtr<IDirect3DTexture9> _pTexture;
			float _width;
			float _height;
			float _invW;
			float _invH;
			friend class Renderer;

		public:
			Texture2D(Texture2D_Desc& desc, Renderer* pRender = DefaultRendererPtr);
			Texture2D(IDirect3DTexture9* pTexture = NULL);

			static Texture2D* FromFile(LPCTSTR pFileName, Renderer* pRender = DefaultRendererPtr);
			static Texture2D* FromBuffer(Buffer& buf, Renderer* pRender = DefaultRendererPtr);

			inline operator IDirect3DTexture9*() {
				return _pTexture;
			}
		};

		//---------------------------------------------------------------------------------------------------------
		// class Texture3D

		class Texture3D : public ComPtr < IDirect3DBaseTexture9 > {
			//private:
		protected:
			ComPtr<IDirect3DVolumeTexture9> _pTexture;
			float _width;
			float _height;
			float _depth;
			float _invW;
			float _invH;
			float _invD;
			friend class Renderer;

		public:
			Texture3D(Texture3D_Desc& desc, Renderer* pRender = DefaultRendererPtr);
			Texture3D(IDirect3DVolumeTexture9* pTexture = NULL);

			static Texture3D* FromFile(LPCTSTR pFileName, Renderer* pRender = DefaultRendererPtr);
			static Texture3D* FromBuffer(Buffer& buf, Renderer* pRender = DefaultRendererPtr);

			inline operator IDirect3DVolumeTexture9*() {
				return _pTexture;
			}
		};
	} /* namespace Drawing */
} /* namespace System */

#endif /* SYSTEM_DRAWING_TEXTURE_H_ */
#endif
