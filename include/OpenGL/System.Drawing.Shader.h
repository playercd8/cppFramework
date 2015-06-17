/*
 * System.Drawing.Shader.h
 *
 *  Created on: Taiwan
 *      Author: player
 */

#include "../stdafx.h"
#if (_DRAWING_MODE == _DRAWING_MODE_OpenGL)

#ifndef SYSTEM_DRAWING_SHADER_H_
#define SYSTEM_DRAWING_SHADER_H_

#if _MSC_VER > 1000
	#pragma once
#endif

#include "OpenGL.h"
#include "../System.Buffer.h"

namespace System {
namespace Drawing {

class Renderer;
Renderer* GetDefaultRendererPtr();

class PixelShader : public ComPtr<ID3D11PixelShader> {
protected:
	ID3D11DeviceContext*  _pDeviceContext;
public:
	PixelShader(const void* pShaderBytecode, int BytecodeLength, Renderer* pRender = GetDefaultRendererPtr());
	PixelShader(ID3D11PixelShader* pShader = NULL);

	static PixelShader* FromFile(LPCTSTR pFileName, Renderer* pRender = GetDefaultRendererPtr());
	static PixelShader* FromBuffer(Buffer& buf, Renderer* pRender = GetDefaultRendererPtr());

	// Set a pixel shader
	//void SetShader(UINT NumClassInstances = 0);

	static LPCSTR _FunctionName;
	static LPCSTR _Profile;
};


class VertexShader: public ComPtr<ID3D11VertexShader> {
//protected:
public:
	VertexShader(const void* pShaderBytecode, int BytecodeLength, Renderer* pRender = GetDefaultRendererPtr());
	VertexShader(ID3D11VertexShader* pShader = NULL);

	static VertexShader* FromFile(LPCTSTR pFileName, Renderer* pRender = GetDefaultRendererPtr());
	static VertexShader* FromBuffer(Buffer& buf, Renderer* pRender = GetDefaultRendererPtr());

	// Set a vertex shader
	//void SetShader(UINT NumClassInstances = 0);

	static LPCSTR _FunctionName;
	static LPCSTR _Profile;

};




} /* namespace Drawing */
} /* namespace System */

#endif /* SYSTEM_DRAWING_SHADER_H_ */
#endif
