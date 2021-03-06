﻿/*
 * System.Drawing.VertexBuffer_OpenGL.cpp
 *
 *  Created on: Taiwan
 *      Author: player
 */

#include "../../include/stdafx.h"
#if (_DRAWING_MODE == _DRAWING_MODE_OpenGL)

#include "../../include/OpenGL/System.Drawing.VertexBuffer.h"
#include "../../include/OpenGL/System.Drawing.Renderer.h"

namespace System {
namespace Drawing {


VertexBuffer::VertexBuffer(void* pInitData, UINT Length, Renderer* pRender)
{

	// Fill in a buffer description.
	D3D11_BUFFER_DESC bufferDesc;
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.ByteWidth = Length;
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
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

VertexBuffer::VertexBuffer(ID3D11Buffer* pVertexBuffer) 
{
	_ptr = NULL;

	if (pVertexBuffer) {
		D3D11_BUFFER_DESC desc;
		pVertexBuffer->GetDesc(&desc);

		if (desc.BindFlags & D3D11_BIND_VERTEX_BUFFER) {
			_ptr = pVertexBuffer;
		}
	}
}


} /* namespace Drawing */
} /* namespace System */

#endif
