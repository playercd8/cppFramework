/*
 * System.Drawing.Shader_DX11.cpp
 *
 *  Created on: Taiwan
 *      Author: player
 */

#include "../../include/stdafx.h"
#if (_DRAWING_MODE == _DRAWING_MODE_DX11)

#include "../../include/System.AutoPtr.h"
#include "../../include/System.ComPtr.h"
#include "../../include/DX11/System.Drawing.Shader.h"
#include "../../include/DX11/System.Drawing.Renderer.h"

namespace System {
namespace Drawing {


//---------------------------------------------------------------------------------------------------------
// class PixelShader

LPCSTR PixelShader::_FunctionName = PixelShader_FunctionName;
LPCSTR PixelShader::_Profile = PixelShader_Profile;

PixelShader::PixelShader(const void* pShaderBytecode, int BytecodeLength, Renderer* pRender) {

	HRESULT hr = pRender->GetDevice()->CreatePixelShader(
		pShaderBytecode,	//[in]   const void *pShaderBytecode,
		BytecodeLength,		//[in]   SIZE_T BytecodeLength,
		NULL,				//[in]   ID3D11ClassLinkage *pClassLinkage,
		&_ptr				//[out]  ID3D11PixelShader **ppPixelShader
		);

	if FAILED(hr) {
		_ptr = NULL;
	}
}

PixelShader::PixelShader(ID3D11PixelShader* pShader)  
{
	_ptr = pShader;
}

PixelShader* PixelShader::FromFile(LPCTSTR pFileName, Renderer* pRender) {
	ID3D10Blob* pBuffer = NULL;
	ID3D10Blob* pError = NULL;

	// Compile the pixel shader from the file
	HRESULT hr = D3DX11CompileFromFile(
		pFileName,				//[in]	LPCTSTR pSrcFile,
		NULL,					//[in]	const D3D10_SHADER_MACRO *pDefines,
		NULL,					//[in]   LPD3D10INCLUDE pInclude,
		_FunctionName,			//[in]   LPCSTR pFunctionName,
		_Profile,				//[in]   LPCSTR pProfile,
		D3D10_SHADER_DEBUG,		//[in]   UINT Flags1,
		NULL,					//[in]   UINT Flags2,
		NULL,					//[in]   ID3DX10ThreadPump *pPump,
		&pBuffer,				//[out]  ID3D10Blob **ppShader,
		&pError,				//[out]  ID3D10Blob **ppErrorMsgs,
		NULL					//[out]  HRESULT *pHResult
		);


	if (pError != NULL) {
		//bError->GetBufferPointer()
		SafeRelease(pError);
		SafeRelease(pBuffer);
		return NULL;
	}
	if FAILED(hr) {
		SafeRelease(pBuffer);
		return NULL;
	}

	PixelShader* pPixelShader = new PixelShader(
		pBuffer->GetBufferPointer(),
		pBuffer->GetBufferSize(),
		pRender);
	SafeRelease(pBuffer);
	return pPixelShader;
}


PixelShader* PixelShader::FromBuffer(Buffer& buf, Renderer* pRender) {
	ID3D10Blob* pBuffer = NULL;
	ID3D10Blob* pError = NULL;

	HRESULT hr = D3DX11CompileFromMemory(
		(LPCSTR)buf.GetPtr(),		//[in]   LPCSTR pSrcData,
		buf.GetSize(),		//[in]   SIZE_T SrcDataLen,
		NULL,				//[in]   LPCSTR pFileName,
		NULL,				//[in]   const D3D10_SHADER_MACRO *pDefines,
		NULL,				//[in]   LPD3D10INCLUDE pInclude,
		_FunctionName,		//[in]   LPCSTR pFunctionName,
		_Profile,			//[in]   LPCSTR pProfile,
		D3D10_SHADER_DEBUG, //[in]   UINT Flags1,
		NULL,				//[in]   UINT Flags2,
		NULL,				//[in]   ID3DX10ThreadPump *pPump,
		&pBuffer,			//[out]  ID3D10Blob **ppShader,
		&pError,			//[out]  ID3D10Blob **ppErrorMsgs,
		NULL				//[out]  HRESULT *pHResult
		);

	if (pError != NULL) {
		//bError->GetBufferPointer()
		SafeRelease(pError);
		SafeRelease(pBuffer);
		return NULL;
	}
	if FAILED(hr) {
		SafeRelease(pBuffer);
		return NULL;
	}

	PixelShader* pPixelShader = new PixelShader(
		pBuffer->GetBufferPointer(), 
		pBuffer->GetBufferSize(),
		pRender
		);
	SafeRelease(pBuffer);
	return pPixelShader;
}

//---------------------------------------------------------------------------------------------------------
// class VertexShader

LPCSTR VertexShader::_FunctionName = VertexShader_FunctionName;
LPCSTR VertexShader::_Profile = VertexShader_Profile;

VertexShader::VertexShader(const void* pShaderBytecode, int BytecodeLength, Renderer* pRender) 
{
	HRESULT hr = pRender->GetDevice()->CreateVertexShader(
		pShaderBytecode,	//[in]   const void *pShaderBytecode,
		BytecodeLength,		//[in]   SIZE_T BytecodeLength,
		NULL,				//[in]   ID3D11ClassLinkage *pClassLinkage,
		&_ptr				//[out]  ID3D11VertexShader **ppVertexShader
		);
	if FAILED(hr) {
		_ptr = NULL;
	}

}

VertexShader::VertexShader(ID3D11VertexShader* pShader)
{
	_ptr = pShader;
}

VertexShader* VertexShader::FromFile(LPCTSTR pFileName, Renderer* pRender) {
	ID3D10Blob* pBuffer = NULL;
	ID3D10Blob* pError = NULL;

	// Compile the pixel shader from the file
	HRESULT hr = D3DX11CompileFromFile(
		pFileName,				//[in]   LPCTSTR pSrcFile,
		NULL,					//[in]   const D3D10_SHADER_MACRO *pDefines,
		NULL,					//[in]   LPD3D10INCLUDE pInclude,
		_FunctionName,			//[in]   LPCSTR pFunctionName,
		_Profile,				//[in]   LPCSTR pProfile,
		D3D10_SHADER_DEBUG,		//[in]   UINT Flags1,
		NULL,					//[in]   UINT Flags2,
		NULL,					//[in]   ID3DX10ThreadPump *pPump,
		&pBuffer,				//[out]  ID3D10Blob **ppShader,
		&pError,				//[out]  ID3D10Blob **ppErrorMsgs,
		NULL					//[out]  HRESULT *pHResult
		);

	if (pError != NULL) {
		//bError->GetBufferPointer()
		SafeRelease(pError);
		SafeRelease(pBuffer);
		return NULL;
	}
	if FAILED(hr) {
		SafeRelease(pBuffer);
		return NULL;
	}

	VertexShader* pVertexShader = new VertexShader(
		pBuffer->GetBufferPointer(), 
		pBuffer->GetBufferSize(),
		pRender);
	SafeRelease(pBuffer);
	return pVertexShader;
}


VertexShader* VertexShader::FromBuffer(Buffer& buf, Renderer* pRender) {
	ID3D10Blob* pBuffer = NULL;
	ID3D10Blob* pError = NULL;

	HRESULT hr = D3DX11CompileFromMemory(
		(LPCSTR)buf.GetPtr(),		//[in]   LPCSTR pSrcData,
		buf.GetSize(),		//[in]   SIZE_T SrcDataLen,
		NULL,				//[in]   LPCSTR pFileName,
		NULL,				//[in]   const D3D10_SHADER_MACRO *pDefines,
		NULL,				//[in]   LPD3D10INCLUDE pInclude,
		_FunctionName,		//[in]   LPCSTR pFunctionName,
		_Profile,			//[in]   LPCSTR pProfile,
		D3D10_SHADER_DEBUG, //[in]   UINT Flags1,
		NULL,				//[in]   UINT Flags2,
		NULL,				//[in]   ID3DX10ThreadPump *pPump,
		&pBuffer,			//[out]  ID3D10Blob **ppShader,
		&pError,			//[out]  ID3D10Blob **ppErrorMsgs,
		NULL				//[out]  HRESULT *pHResult
		);

	if (pError != NULL) {
		//bError->GetBufferPointer()
		SafeRelease(pError);
		SafeRelease(pBuffer);
		return NULL;
	}
	if FAILED(hr) {
		SafeRelease(pBuffer);
		return NULL;
	}

	VertexShader* pVertexShader = new VertexShader(
		pBuffer->GetBufferPointer(), 
		pBuffer->GetBufferSize(),
		pRender);
	SafeRelease(pBuffer);
	return pVertexShader;
}


} /* namespace Drawing */
} /* namespace System */

#endif /* SYSTEM_DRAWING_TEXTURE_H_ */
