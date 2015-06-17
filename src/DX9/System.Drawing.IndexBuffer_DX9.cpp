/*
 * System.Drawing.IndexBuffer_DX9.cpp
 *
 *  Created on: Taiwan
 *      Author: player
 */

#include "../../include/stdafx.h"
#if (_DRAWING_MODE == _DRAWING_MODE_DX9)

#include "../../include/DX9/System.Drawing.IndexBuffer.h"
#include "../../include/DX9/System.Drawing.Renderer.h"

namespace System {
	namespace Drawing {
		IndexBuffer::IndexBuffer(void* pInitData, UINT Length, Renderer* pRender)
		{
			HRESULT hr;
			DWORD Usage = 0;
			D3DFORMAT Format = D3DFMT_INDEX16;
			D3DPOOL Pool = D3DPOOL_DEFAULT;

			V(pRender->GetDevice()->CreateIndexBuffer(
				Length,				//[in]	UINT Length,
				Usage,				//[in]	DWORD Usage,
				Format,				//[in]	D3DFORMAT Format,
				Pool,				//[in]	D3DPOOL Pool,
				&_ptr,				//[out]	IDirect3DIndexBuffer9 **ppIndexBuffer,
				NULL				//[in]	HANDLE *pSharedHandle
				));

			if FAILED(hr) {
				_ptr = NULL;
				return;
			}

			if (pInitData) {
				// Discard and refill the used portion of the index buffer.
				const DWORD dwLockFlags = D3DLOCK_DISCARD;

				// Lock the vertex buffer.
				void* pBytes;
				V(_ptr->Lock(0, 0, &pBytes, dwLockFlags));
				if (SUCCEEDED(hr)) {
					// Copy the vertices into the index buffer.
					memcpy(pBytes, pInitData, Length);
					_ptr->Unlock();
				}
			}
		}

		IndexBuffer::IndexBuffer(IDirect3DIndexBuffer9* pIndexBuffer)
		{
			_ptr = pIndexBuffer;
		}
	} /* namespace Drawing */
} /* namespace System */

#endif