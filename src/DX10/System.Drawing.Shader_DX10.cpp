/*
 * System.Drawing.Shader_DX10.cpp
 *
 *  Created on: Taiwan
 *      Author: player
 */

#include "../../include/stdafx.h"
#if (_DRAWING_MODE == _DRAWING_MODE_DX10)

#include "../../include/DX10/System.Drawing.Renderer.h"
#include "../../include/DX10/System.Drawing.Shader.h"
#include "../../include/System.AutoPtr.h"
#include "../../include/System.ComPtr.h"
#include "../../include/System.String.h"

namespace System {
	namespace Drawing {
		//---------------------------------------------------------------------------------------------------------
		// class PixelShader

		LPCSTR PixelShader::_FunctionName = PixelShader_FunctionName;
		LPCSTR PixelShader::_Profile = PixelShader_Profile;

		PixelShader::PixelShader(const void* pShaderBytecode, int BytecodeLength, Renderer* pRender)
		{
			HRESULT hr;
			V(pRender->GetDevice()->CreatePixelShader(
				pShaderBytecode,	//[in]   const void *pShaderBytecode,
				BytecodeLength,		//[in]   SIZE_T BytecodeLength,
				&_ptr				//[out]  ID3D10PixelShader **ppPixelShader
				));
			if FAILED(hr)
				_ptr = NULL;
		}

		PixelShader::PixelShader(ID3D10PixelShader* pShader)
		{
			_ptr = pShader;
		}

		PixelShader* PixelShader::FromFile(LPCTSTR pFileName, Renderer* pRender)
		{
			HRESULT hr;
			ID3D10Blob* pBuffer = NULL;
			ID3D10Blob* pError = NULL;

			// Compile the pixel shader from the file
			V(D3DX10CompileFromFile(
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
				));

			if FAILED(hr) {
				if (pError != NULL) {
					if (pError->GetBufferSize() > 0)
						DXTrace(__FILE__, (DWORD)__LINE__, hr, String((char*)pError->GetBufferPointer()), _SHOW_ERR_MSGBOX);
					pError->Release();
				}
				SafeRelease(pBuffer);
				return NULL;
			}

			PixelShader* pPixelShader = new PixelShader(pBuffer->GetBufferPointer(), pBuffer->GetBufferSize(), pRender);
			SafeRelease(pBuffer);
			return pPixelShader;
		}

		PixelShader* PixelShader::FromBuffer(Buffer& buf, Renderer* pRender) {
			ID3D10Blob* pBuffer = NULL;
			ID3D10Blob* pError = NULL;

			HRESULT hr = D3DX10CompileFromMemory(
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

			if FAILED(hr) {
				if (pError != NULL) {
					if (pError->GetBufferSize() > 0)
						DXTrace(__FILE__, (DWORD)__LINE__, hr, String((char*)pError->GetBufferPointer()), _SHOW_ERR_MSGBOX);
					pError->Release();
				}
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

		//---------------------------------------------------------------------------------------------------------
		// class VertexShader

		LPCSTR VertexShader::_FunctionName = VertexShader_FunctionName;
		LPCSTR VertexShader::_Profile = VertexShader_Profile;

		VertexShader::VertexShader(const void* pShaderBytecode, int BytecodeLength, Renderer* pRender)
		{
			HRESULT hr;
			V(pRender->GetDevice()->CreateVertexShader(
				pShaderBytecode,	//[in]   const void *pShaderBytecode,
				BytecodeLength,		//[in]   SIZE_T BytecodeLength,
				&_ptr				//[out]  ID3D10VertexShader **ppVertexShader
				));
			if FAILED(hr)
				_ptr = NULL;
		}

		VertexShader::VertexShader(ID3D10VertexShader* pShader)
		{
			_ptr = pShader;
		}

		VertexShader* VertexShader::FromFile(LPCTSTR pFileName, Renderer* pRender)
		{
			HRESULT hr;
			ID3D10Blob* pBuffer = NULL;
			ID3D10Blob* pError = NULL;

			// Compile the pixel shader from the file
			V(D3DX10CompileFromFile(
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
				));

			if FAILED(hr) {
				if (pError != NULL) {
					if (pError->GetBufferSize() > 0)
						DXTrace(__FILE__, (DWORD)__LINE__, hr, String((char*)pError->GetBufferPointer()), _SHOW_ERR_MSGBOX);
					pError->Release();
				}
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

		VertexShader* VertexShader::FromBuffer(Buffer& buf, Renderer* pRender)
		{
			HRESULT hr;
			ID3D10Blob* pBuffer = NULL;
			ID3D10Blob* pError = NULL;

			V(D3DX10CompileFromMemory(
				(LPCSTR)buf.GetPtr(),	//[in]   LPCSTR pSrcData,
				buf.GetSize(),			//[in]   SIZE_T SrcDataLen,
				NULL,					//[in]   LPCSTR pFileName,
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
				));

			if FAILED(hr) {
				if (pError != NULL) {
					if (pError->GetBufferSize() > 0)
						DXTrace(__FILE__, (DWORD)__LINE__, hr, String((char*)pError->GetBufferPointer()), _SHOW_ERR_MSGBOX);
					pError->Release();
				}
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