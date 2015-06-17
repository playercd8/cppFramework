/*
 * System.Drawing.Shader.h
 *
 *  Created on: Taiwan
 *      Author: player
 */

#include "../stdafx.h"
#if (_DRAWING_MODE == _DRAWING_MODE_DX10)

#ifndef SYSTEM_DRAWING_SHADER_H_
#define SYSTEM_DRAWING_SHADER_H_

#if _MSC_VER > 1000
#pragma once
#endif

#include "DX10.h"
#include "../System.Buffer.h"
#include "../System.ComPtr.h"

namespace System {
	namespace Drawing {
		class Renderer;
		Renderer* GetDefaultRendererPtr();

		class PixelShader : public ComPtr < ID3D10PixelShader > {
			//private:
			//protected:

		public:
			PixelShader(const void* pShaderBytecode, int BytecodeLength, Renderer* pRender = DefaultRendererPtr);
			PixelShader(ID3D10PixelShader* pShader = NULL);

			static PixelShader* FromFile(LPCTSTR pFileName, Renderer* pRender = DefaultRendererPtr);
			static PixelShader* FromBuffer(Buffer& buf, Renderer* pRender = DefaultRendererPtr);

			static LPCSTR _FunctionName;
			static LPCSTR _Profile;
		};

		class VertexShader : public ComPtr < ID3D10VertexShader > {
			//private:
			//protected:

		public:
			VertexShader(const void* pShaderBytecode, int BytecodeLength, Renderer* pRender = DefaultRendererPtr);
			VertexShader(ID3D10VertexShader* pShader = NULL);

			static VertexShader* FromFile(LPCTSTR pFileName, Renderer* pRender = DefaultRendererPtr);
			static VertexShader* FromBuffer(Buffer& buf, Renderer* pRender = DefaultRendererPtr);

			static LPCSTR _FunctionName;
			static LPCSTR _Profile;
		};
	} /* namespace Drawing */
} /* namespace System */

#endif /* SYSTEM_DRAWING_SHADER_H_ */
#endif
