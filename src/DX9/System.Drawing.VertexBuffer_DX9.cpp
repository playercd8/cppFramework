/*
 * System.Drawing.VertexBuffer_DX9.cpp
 *
 *  Created on: Taiwan
 *      Author: player
 */

#include "../../include/stdafx.h"
#if (_DRAWING_MODE == _DRAWING_MODE_DX9)

#include "../../include/DX9/System.Drawing.VertexBuffer.h"
#include "../../include/DX9/System.Drawing.Renderer.h"

namespace System {
	namespace Drawing {
		VertexBuffer::VertexBuffer(void* pInitData, UINT Length, Renderer* pRender)
		{
			HRESULT hr;
			_FVF = pRender->GetVertexFVF();
			_Stride = StrideAnalytics(_FVF);

			DWORD Usage = 0;
			D3DPOOL Pool = D3DPOOL_DEFAULT;

			V(pRender->GetDevice()->CreateVertexBuffer(
				Length,			//[in]	UINT Length,
				Usage,			//[in]	DWORD Usage,
				_FVF,			//[in]	DWORD FVF,
				Pool,			//[in]	D3DPOOL Pool,
				&_ptr,			//[out]	IDirect3DVertexBuffer9 **ppVertexBuffer,
				NULL			//[in]	HANDLE *pSharedHandle
				));

			if FAILED(hr) {
				_ptr = NULL;
				return;
			}

			if (pInitData) {
				// Discard and refill the used portion of the vertex buffer.
				const DWORD dwLockFlags = D3DLOCK_DISCARD;

				// Lock the vertex buffer.
				void* pBytes;
				V(_ptr->Lock(0, 0, &pBytes, dwLockFlags));
				if (SUCCEEDED(hr)) {
					// Copy the vertices into the vertex buffer.
					memcpy(pBytes, pInitData, Length);
					_ptr->Unlock();
				}
			}
		}

		VertexBuffer::VertexBuffer(IDirect3DVertexBuffer9* pVertexBuffer) 
		{
			_ptr = pVertexBuffer;
			_FVF = 0;
			_Stride = 0;
			if (_ptr) {
				D3DVERTEXBUFFER_DESC desc;
				if (SUCCEEDED(_ptr->GetDesc(&desc))) {
					_FVF = desc.FVF;
					_Stride = StrideAnalytics(_FVF);
				}
			}
		}

		//Stride of the component, in byte
		int VertexBuffer::StrideAnalytics(DWORD FVF) 
		{
			int Stride = 0;

			DWORD posType = FVF & D3DFVF_POSITION_MASK;
			switch (posType) {
			case D3DFVF_XYZ:
				Stride += 3 * sizeof(float);	//座標(float*3)
				break;
			case D3DFVF_XYZRHW:
				Stride += 4 * sizeof(float);	//座標(float*4, 不執行座標轉換, x與y直接對應Surface, z為0, rhw 為1)
				break;
			case D3DFVF_XYZB1:
				Stride += 4 * sizeof(float);	//座標+1Beta (float*4 , X, Y, Z and 1 Beta)
				break;
			case D3DFVF_XYZB2:
				Stride += 5 * sizeof(float);	//座標+2Beta (float*5 , X, Y, Z and 2 Beta)
				break;
			case D3DFVF_XYZB3:
				Stride += 6 * sizeof(float);	//座標+3Beta (float*6 , X, Y, Z and 3 Beta)
				break;
			case D3DFVF_XYZB4:
				Stride += 7 * sizeof(float);	//座標+4Beta (float*7 , X, Y, Z and 4 Beta)
				break;
			case D3DFVF_XYZB5:
				Stride += 8 * sizeof(float);	//座標+5Beta (float*8 , X, Y, Z and 5 Beta)
				break;
			case D3DFVF_XYZW:
				Stride += 4 * sizeof(float);	//座標(float*4, X, Y, Z, W)
				break;
			}

			if (FVF & D3DFVF_NORMAL)	Stride += 3 * sizeof(float);	//法線(float*3)
			if (FVF & D3DFVF_PSIZE)		Stride += sizeof(float);		//頂點Size (float*1)
			if (FVF & D3DFVF_DIFFUSE)	Stride += sizeof(DWORD); 		//基本色 (DWORD)
			if (FVF & D3DFVF_SPECULAR)	Stride += sizeof(DWORD); 		//鏡面反射色 (DWORD)

			int texount = (FVF & D3DFVF_TEXCOUNT_MASK) >> D3DFVF_TEXCOUNT_SHIFT;
			if (texount) {
				DWORD texSize, texSizeMask, texSizeShift;
				for (int i = 0; i < texount; i++) {
					texSizeShift = i * 2 + 16;
					texSizeMask = 3 << texSizeShift;
					texSize = (FVF & texSizeMask) >> texSizeShift;
					switch (texSize) {
					case D3DFVF_TEXTUREFORMAT2:
						Stride += 2 * sizeof(float); 	//貼圖來源(2個float, u 與 v)
						break;
					case D3DFVF_TEXTUREFORMAT3:
						Stride += 3 * sizeof(float); 	//貼圖來源(3個float)
						break;
					case D3DFVF_TEXTUREFORMAT4:
						Stride += 4 * sizeof(float); 	//貼圖來源(4個float)
						break;
					case  D3DFVF_TEXTUREFORMAT1:
						Stride += sizeof(float); 		//貼圖來源(1個float)
						break;
					}
				}
			}

			return Stride;
		}
	} /* namespace Drawing */
} /* namespace System */

#endif