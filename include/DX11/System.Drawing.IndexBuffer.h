/*
 * System.Drawing.IndexBuffer.h
 *
 *  Created on: Taiwan
 *      Author: player
 */

#include "../stdafx.h"
#if (_DRAWING_MODE == _DRAWING_MODE_DX11)

#ifndef SYSTEM_DRAWING_INDEXBUFFER_H_
#define SYSTEM_DRAWING_INDEXBUFFER_H_

#if _MSC_VER > 1000
	#pragma once
#endif

#include "DX11.h"
#include "../System.ComPtr.h"


namespace System {
namespace Drawing {

class Renderer;
Renderer* GetDefaultRendererPtr();

class IndexBuffer : public ComPtr<ID3D11Buffer> {
//protected:
public:
	IndexBuffer(void* pInitData, UINT Length, Renderer* pRender = DefaultRendererPtr);
	IndexBuffer(ID3D11Buffer* pIndexBuffer = NULL);

	//void SetIndexBuffer(UINT Offset = 0);

};


} /* namespace Drawing */
} /* namespace System */

#endif /* SYSTEM_DRAWING_INDEXBUFFER_H_ */
#endif
