/*
 * System.Drawing.Texture_OpenGL.cpp
 *
 *  Created on: Taiwan
 *      Author: player
 */

#include "../../include/stdafx.h"
#if (_DRAWING_MODE == _DRAWING_MODE_OpenGL)

#include "../../include/OpenGL/System.Drawing.Texture.h"
#include "../../include/OpenGL/System.Drawing.Renderer.h"

namespace System {
	namespace Drawing {
		//---------------------------------------------------------------------------------------------------------
		// class Texture1D
#pragma region class Texture1D
		Texture1D::Texture1D(Texture1D_Desc& desc, Renderer* pRender)
		{
			glTexImage1D(GL_TEXTURE_1D,
				desc.level,
				desc.internalFormat,
				desc.width,
				desc.border,
				desc.format,
				desc.type,
				desc.pPixelsData);

			_width = (float)desc.width;
			_invW = 1.0f / _width;
		}

		Texture1D* Texture1D::FromFile(LPCTSTR pFileName, Renderer* pRender) {
		}

		Texture1D* Texture1D::FromBuffer(Buffer& buf, Renderer* pRender) {
		}
#pragma endregion class Texture1D
		//---------------------------------------------------------------------------------------------------------
		// class Texture2D
#pragma region class Texture2D
		Texture2D::Texture2D(Texture2D_Desc& desc, Renderer* pRender)
		{
			glTexImage2D(GL_TEXTURE_2D,
				desc.level,
				desc.internalFormat,
				desc.width,
				desc.height,
				desc.border,
				desc.format,
				desc.type,
				desc.pPixelsData);

			_width = (float)desc.width;
			_height = (float)desc.height;
			_invW = 1.0f / _width;
			_invH = 1.0f / _height;
		}

		Texture2D* Texture2D::FromFile(LPCTSTR pFileName, Renderer* pRender)
		{
			return NULL;
		}

		Texture2D* Texture2D::FromBuffer(Buffer& buf, Renderer* pRender)
		{
			return NULL;
		}
#pragma endregion class Texture2D
		//---------------------------------------------------------------------------------------------------------
		// class Texture3D
#pragma region class Texture3D
		Texture3D::Texture3D(Texture3D_Desc& desc, Renderer* pRender) {
			glTexImage3D(GL_TEXTURE_3D,
				desc.level,
				desc.internalFormat,
				desc.width,
				desc.height,
				desc.depth,
				desc.border,
				desc.format,
				desc.type,
				desc.pPixelsData);

			_width = (float)desc.width;
			_height = (float)desc.height;
			_depth = (float)desc.depth;
			_invW = 1.0f / _width;
			_invH = 1.0f / _height;
			_invD = 1.0f / _depth;
		}

		Texture3D* Texture3D::FromFile(LPCTSTR pFileName, Renderer* pRender)
		{
			return NULL;
		}

		Texture3D* Texture3D::FromBuffer(Buffer& buf, Renderer* pRender)
		{
			return NULL;
		}
#pragma endregion class Texture3D
	} /* namespace Drawing */
} /* namespace System */

#endif