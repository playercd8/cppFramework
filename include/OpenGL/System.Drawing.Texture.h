/*
 * System.Drawing.Texture_OpenGL.h
 *
 *  Created on: Taiwan
 *      Author: player
 */

#include "../stdafx.h"
#if (_DRAWING_MODE == _DRAWING_MODE_OPENGL)

#ifndef SYSTEM_DRAWING_TEXTURE_H_
#define SYSTEM_DRAWING_TEXTURE_H_

#if _MSC_VER > 1000
#pragma once
#endif

#include "OpenGL.h"
#include "../System.Buffer.h"
//#include "../System.ComPtr.h"

namespace System {
	namespace Drawing {
		class Renderer;
		Renderer* GetDefaultRendererPtr();


		typedef struct Texture1D_Desc {
			//GLenum target;
			GLint level;
			GLint internalFormat;
			GLsizei width;
			GLint border;
			GLenum format;
			GLenum type;
			const GLvoid* pPixelsData;
		}  Texture1D_Desc;

		typedef struct Texture2D_Desc {
			//GLenum target;
			GLint level;
			GLint internalFormat;
			GLsizei width;
			GLsizei height;
			GLint border;
			GLenum format;
			GLenum type;
			const GLvoid* pPixelsData;
		}  Texture2D_Desc;


		typedef struct Texture3D_Desc {
			//GLenum target;
			GLint level;
			GLint internalFormat;
			GLsizei width;
			GLsizei height;
			GLsizei depth;
			GLint border;
			GLenum format;
			GLenum type;
			const GLvoid* pPixelsData;
		}  Texture3D_Desc;


		//---------------------------------------------------------------------------------------------------------
		// class Texture1D
#pragma region class Texture1D
		class Texture1D  {
		protected:
			float _width;
			float _invW;
			friend class Renderer;
		public:
			Texture1D(Texture1D_Desc& desc, Renderer* pRender = DefaultRendererPtr);


			static Texture1D* FromFile(LPCTSTR pFileName, Renderer* pRender = DefaultRendererPtr);
			static Texture1D* FromBuffer(Buffer& buf, Renderer* pRender = DefaultRendererPtr);
		};
#pragma endregion class Texture1D
		//---------------------------------------------------------------------------------------------------------
		// class Texture2D
#pragma region class Texture2D
		class Texture2D  {
		protected:
			float _width;
			float _height;
			float _invW;
			float _invH;
			friend class Renderer;
		public:
			Texture2D(Texture2D_Desc& desc, Renderer* pRender = DefaultRendererPtr);

			static Texture2D* FromFile(LPCTSTR pFileName, Renderer* pRender = DefaultRendererPtr);
			static Texture2D* FromBuffer(Buffer& buf, Renderer* pRender = DefaultRendererPtr);
		};
#pragma endregion class Texture2D
		//---------------------------------------------------------------------------------------------------------
		// class Texture3D
#pragma region class Texture3D
		class Texture3D  {
		protected:
			float _width;
			float _height;
			float _depth;
			float _invW;
			float _invH;
			float _invD;
			friend class Renderer;
		public:
			Texture3D(Texture3D_Desc& desc, Renderer* pRender = DefaultRendererPtr);


			static Texture3D* FromFile(LPCTSTR pFileName, Renderer* pRender = DefaultRendererPtr);
			static Texture3D* FromBuffer(Buffer& buf, Renderer* pRender = DefaultRendererPtr);
		};
#pragma endregion class Texture3D
	} /* namespace Drawing */
} /* namespace System */

#endif /* SYSTEM_DRAWING_TEXTURE_H_ */
#endif
