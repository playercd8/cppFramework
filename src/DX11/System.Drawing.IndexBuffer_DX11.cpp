/*
 * System.Drawing.IndexBuffer_DX11.cpp
 *
 *  Created on: Taiwan
 *      Author: player
 */

#include "../../include/stdafx.h"
#if (_DRAWING_MODE == _DRAWING_MODE_DX11)

#include "../../include/DX11/System.Drawing.IndexBuffer.h"
#include "../../include/DX11/System.Drawing.Renderer.h"

namespace System {
namespace Drawing {

IndexBuffer::IndexBuffer(void* pInitData, UINT Length, Renderer* pRender) 
{
	// Fill in a buffer description.
	D3D11_BUFFER_DESC bufferDesc;
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.ByteWidth = Length;
	bufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bufferDesc.CPUAccessFlags = 0;
	bufferDesc.MiscFlags = 0;

	// Fill in the subresource data.
	D3D11_SUBRESOURCE_DATA* pInitialData;
	D3D11_SUBRESOURCE_DATA InitData;
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
	HRESULT hr = pRender->GetDevice()->CreateBuffer(
		&bufferDesc,			//[in]   const D3D11_BUFFER_DESC *pDesc,
		pInitialData,			//[in]   const D3D11_SUBRESOURCE_DATA *pInitialData,
		&_ptr);					//[out]  ID3D11Buffer **ppBuffer
}

IndexBuffer::IndexBuffer(ID3D11Buffer* pIndexBuffer) 
{
	_ptr = NULL;

	if (pIndexBuffer) {
		D3D11_BUFFER_DESC desc;
		pIndexBuffer->GetDesc(&desc);

		if (desc.BindFlags & D3D11_BIND_INDEX_BUFFER) {
			_ptr = pIndexBuffer;
		}
	}
}


//void IndexBuffer::SetIndexBuffer(UINT Offset) {
//	_pDeviceContext->IASetIndexBuffer(_ptr, DXGI_FORMAT_R32_UINT, Offset);
//}

} /* namespace Drawing */
} /* namespace System */

#endif
