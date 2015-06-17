/*
 * System.Drawing.Shader_DX9.cpp
 *
 *  Created on: Taiwan
 *      Author: player
 */

#include "../../include/stdafx.h"
#if (_DRAWING_MODE == _DRAWING_MODE_DX9)

#include "../../include/DX9/System.Drawing.Shader.h"
#include "../../include/DX9/System.Drawing.Renderer.h"
#include "../../include/System.String.h"

namespace System {
	namespace Drawing {
		//---------------------------------------------------------------------------------------------------------
		// class PixelShader

		LPCSTR PixelShader::_FunctionName = PixelShader_FunctionName;
		LPCSTR PixelShader::_Profile = PixelShader_Profile;

		PixelShader::PixelShader(const void* pShaderBytecode, int BytecodeLength, Renderer* pRender) {
			HRESULT hr;
			V(pRender->GetDevice()->CreatePixelShader(
				(const DWORD*)pShaderBytecode,
				&_ptr
				));

			if FAILED(hr)
				_ptr = NULL;
		}

		PixelShader::PixelShader(IDirect3DPixelShader9* pShader) {
			_ptr = pShader;
		}

		PixelShader* PixelShader::FromFile(LPCTSTR pFileName, Renderer* pRender) {
			HRESULT hr;
			ID3DXConstantTable* pConstantTable = NULL;
			ID3DXBuffer* pBuffer = NULL;
			ID3DXBuffer* pError = NULL;

			V(D3DXCompileShaderFromFile(
				pFileName,			//[in]	LPCSTR pSrcFile,
				NULL,				//[in]	const D3DXMACRO *pDefines,
				NULL,				//[in]   LPD3DXINCLUDE pInclude,
				_FunctionName,		//[in]   LPCSTR pFunctionName,
				_Profile,			//[in]   LPCSTR pProfile
				D3DXSHADER_DEBUG,	//[in]   DWORD Flags
				&pBuffer,			//[out]  LPD3DXBUFFER *ppShader,
				&pError,				//[out]  LPD3DXBUFFER *ppErrorMsgs,
				&pConstantTable		//[out]  LPD3DXCONSTANTTABLE *ppConstantTable
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

		PixelShader* PixelShader::FromBuffer(Buffer& buf, Renderer* pRender)
		{
			HRESULT hr;
			ID3DXConstantTable* pConstantTable = NULL;
			ID3DXBuffer* pBuffer = NULL;
			ID3DXBuffer* pError = NULL;

			V(D3DXCompileShader(
				(LPCSTR)buf.GetPtr(),	//[in]   LPCSTR pSrcData,
				buf.GetSize(),			//[in]   UINT srcDataLen,
				NULL,					//[in]   const D3DXMACRO *pDefines,
				NULL,					//[in]   LPD3DXINCLUDE pInclude,
				_FunctionName,			//[in]   LPCSTR pFunctionName,
				_Profile,				//[in]   LPCSTR pProfile
				D3DXSHADER_DEBUG,	//[in]   DWORD Flags
				&pBuffer,			//[out]  LPD3DXBUFFER *ppShader,
				&pError,				//[out]  LPD3DXBUFFER *ppErrorMsgs,
				&pConstantTable		//[out]  LPD3DXCONSTANTTABLE *ppConstantTable
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

		//---------------------------------------------------------------------------------------------------------
		// class VertexShader

		LPCSTR VertexShader::_FunctionName = VertexShader_FunctionName;
		LPCSTR VertexShader::_Profile = VertexShader_Profile;

		VertexShader::VertexShader(const void* pShaderBytecode, int BytecodeLength, Renderer* pRender)
		{
			HRESULT hr;
			V(pRender->GetDevice()->CreateVertexShader(
				(const DWORD*)pShaderBytecode,
				&_ptr));

			if FAILED(hr)
				_ptr = NULL;
		}

		VertexShader::VertexShader(IDirect3DVertexShader9* pShader)
		{
			_ptr = pShader;
		}

		VertexShader* VertexShader::FromFile(LPCTSTR pFileName, Renderer* pRender)
		{
			HRESULT hr;
			ID3DXConstantTable* pConstantTable = NULL;
			ID3DXBuffer* pBuffer = NULL;
			ID3DXBuffer* pError = NULL;

			V(D3DXCompileShaderFromFile(
				pFileName,			//[in]	LPCSTR pSrcFile,
				NULL,				//[in]	const D3DXMACRO *pDefines,
				NULL,				//[in]   LPD3DXINCLUDE pInclude,
				_FunctionName,		//[in]   LPCSTR pFunctionName,
				_Profile,			//[in]   LPCSTR pProfile
				D3DXSHADER_DEBUG,	//[in]   DWORD Flags
				&pBuffer,			//[out]  LPD3DXBUFFER *ppShader,
				&pError,			//[out]  LPD3DXBUFFER *ppErrorMsgs,
				&pConstantTable		//[out]  LPD3DXCONSTANTTABLE *ppConstantTable
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

			VertexShader* pVertexShader = new VertexShader(pBuffer->GetBufferPointer(), pBuffer->GetBufferSize(), pRender);
			SafeRelease(pBuffer);
			return pVertexShader;
		}

		VertexShader* VertexShader::FromBuffer(Buffer& buf, Renderer* pRender)
		{
			HRESULT hr;
			ID3DXConstantTable* pConstantTable = NULL;
			ID3DXBuffer* pBuffer = NULL;
			ID3DXBuffer* pError = NULL;

			V(D3DXCompileShader(
				(LPCSTR)buf.GetPtr(),	//[in]   LPCSTR pSrcData,
				buf.GetSize(),			//[in]   UINT srcDataLen,
				NULL,					//[in]   const D3DXMACRO *pDefines,
				NULL,					//[in]   LPD3DXINCLUDE pInclude,
				_FunctionName,			//[in]   LPCSTR pFunctionName,
				_Profile,				//[in]   LPCSTR pProfile
				D3DXSHADER_DEBUG,		//[in]   DWORD Flags
				&pBuffer,				//[out]  LPD3DXBUFFER *ppShader,
				&pError,				//[out]  LPD3DXBUFFER *ppErrorMsgs,
				&pConstantTable			//[out]  LPD3DXCONSTANTTABLE *ppConstantTable
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

			VertexShader* pVertexShader = new VertexShader(pBuffer->GetBufferPointer(), pBuffer->GetBufferSize(), pRender);
			SafeRelease(pBuffer);
			return pVertexShader;
		}
	} /* namespace Drawing */
} /* namespace System */

#endif /* SYSTEM_DRAWING_SHADER_H_ */