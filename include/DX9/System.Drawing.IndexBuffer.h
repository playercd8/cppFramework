/*
 * System.Drawing.IndexBuffer.h
 *
 * Code Status: Drafts
 *  Created on: Taiwan
 *      Author: player
 */

#include "../stdafx.h"
#if (_DRAWING_MODE == _DRAWING_MODE_DX9)

#ifndef SYSTEM_DRAWING_INDEXBUFFER_H_
#define SYSTEM_DRAWING_INDEXBUFFER_H_

#if _MSC_VER > 1000
#pragma once
#endif

#include "DX9.h"
#include "../System.ComPtr.h"

namespace System {
	namespace Drawing {
		class Renderer;
		Renderer* GetDefaultRendererPtr();

		class IndexBuffer : public ComPtr < IDirect3DIndexBuffer9 > {
			//private:
			//protected:
		public:
			IndexBuffer(void* pInitData, UINT Length, Renderer* pRender = DefaultRendererPtr);
			IndexBuffer(IDirect3DIndexBuffer9* pIndexBuffer = NULL);
		};
	} /* namespace Drawing */
} /* namespace System */

#endif /* SYSTEM_DRAWING_INDEXBUFFER_H_ */
#endif
