/*
 * System.Drawing.Shader.h
 *
 * Code Status: Drafts
 *  Created on: Taiwan
 *      Author: player
 */

#include "../stdafx.h"
#if (_DRAWING_MODE == _DRAWING_MODE_DX9)

#ifndef SYSTEM_DRAWING_SHADER_H_
#define SYSTEM_DRAWING_SHADER_H_

#if _MSC_VER > 1000
#pragma once
#endif

#include "DX9.h"
#include "../System.AutoPtr.h"
#include "../System.Buffer.h"
#include "../System.ComPtr.h"

namespace System {
	namespace Drawing {
		class Renderer;
		Renderer* GetDefaultRendererPtr();

		class PixelShader : public ComPtr < IDirect3DPixelShader9 > {
			//private:
			//protected:
		public:
			PixelShader(const void* pShaderBytecode, int BytecodeLength = 0, Renderer* pRender = DefaultRendererPtr);
			PixelShader(IDirect3DPixelShader9* pShader = NULL);

			static PixelShader* FromFile(LPCTSTR pFileName, Renderer* pRender = DefaultRendererPtr);
			static PixelShader* FromBuffer(Buffer& buf, Renderer* pRender = DefaultRendererPtr);

			static LPCSTR _FunctionName;
			static LPCSTR _Profile;
		};

		class VertexShader : public ComPtr < IDirect3DVertexShader9 > {
			//private:
			//protected:
		public:
			VertexShader(const void* pShaderBytecode, int BytecodeLength = 0, Renderer* pRender = DefaultRendererPtr);
			VertexShader(IDirect3DVertexShader9* pShader = NULL);

			static VertexShader* FromFile(LPCTSTR pFileName, Renderer* pRender = DefaultRendererPtr);
			static VertexShader* FromBuffer(Buffer& buf, Renderer* pRender = DefaultRendererPtr);

			static LPCSTR _FunctionName;
			static LPCSTR _Profile;
		};
	} /* namespace Drawing */
} /* namespace System */

#endif /* SYSTEM_DRAWING_SHADER_H_ */
#endif
