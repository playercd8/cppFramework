/*
 * System.Drawing.IndexBuffer_DX10.cpp
 *
 *  Created on: Taiwan
 *      Author: player
 */

#include "../../include/stdafx.h"
#if (_DRAWING_MODE == _DRAWING_MODE_DX10)

#include "../../include/DX10/System.Drawing.IndexBuffer.h"
#include "../../include/DX10/System.Drawing.Renderer.h"

namespace System {
	namespace Drawing {
		IndexBuffer::IndexBuffer(void* pInitData, UINT Length, Renderer* pRender)
		{
			HRESULT hr;
			// Fill in a buffer description.
			D3D10_BUFFER_DESC bufferDesc;
			bufferDesc.Usage = D3D10_USAGE_DEFAULT;
			bufferDesc.ByteWidth = Length;
			bufferDesc.BindFlags = D3D10_BIND_INDEX_BUFFER;
			bufferDesc.CPUAccessFlags = 0;
			bufferDesc.MiscFlags = 0;

			// Fill in the subresource data.
			D3D10_SUBRESOURCE_DATA* pInitialData;
			D3D10_SUBRESOURCE_DATA InitData;
			if (pInitData != NULL) {
				InitData.pSysMem = pInitData;
				InitData.SysMemPitch = 0;
				InitData.SysMemSlicePitch = 0;
				pInitialData = &InitData;
			}
			else {
				pInitialData = NULL;
			}

			// Create the vertex buffer.
			V(pRender->GetDevice()->CreateBuffer(
				&bufferDesc,			//[in]   const D3D11_BUFFER_DESC *pDesc,
				pInitialData,			//[in]   const D3D11_SUBRESOURCE_DATA *pInitialData,
				&_ptr					//[out]  ID3D11Buffer **ppBuffer
				));

			if FAILED(hr) 
				_ptr = NULL;
		}

		IndexBuffer::IndexBuffer(ID3D10Buffer* pIndexBuffer) {
			_ptr = NULL;

			if (pIndexBuffer) {
				D3D10_BUFFER_DESC desc;
				pIndexBuffer->GetDesc(&desc);

				if (desc.BindFlags & D3D10_BIND_INDEX_BUFFER) {
					_ptr = pIndexBuffer;
				}
			}
		}
	} /* namespace Drawing */
} /* namespace System */

#endif