/*
 * System.Drawing.VertexBuffer.h
 *
 * Code Status: Drafts
 *  Created on: Taiwan
 *      Author: player
 */

#include "../stdafx.h"
#if (_DRAWING_MODE == _DRAWING_MODE_DX9)

#ifndef SYSTEM_DRAWING_VERTEXBUFFER_H_
#define SYSTEM_DRAWING_VERTEXBUFFER_H_

#if _MSC_VER > 1000
#pragma once
#endif

#include "DX9.h"
#include "../System.ComPtr.h"

namespace System {
	namespace Drawing {
		class Renderer;
		Renderer* GetDefaultRendererPtr();

		enum FVF_TYPE {
			XYZ = D3DFVF_XYZ,			//座標(float*3)
			XYZRHW = D3DFVF_XYZRHW,		//座標(float*4, 不執行座標轉換, x與y直接對應Surface, z為0, rhw 為1)
			XYZB1 = D3DFVF_XYZB1,		//座標+1Beta (float*4 , X, Y, Z and 1 Beta)
			XYZB2 = D3DFVF_XYZB2,		//座標+2Beta (float*5 , X, Y, Z and 2 Beta)
			XYZB3 = D3DFVF_XYZB3,		//座標+3Beta (float*6 , X, Y, Z and 3 Beta)
			XYZB4 = D3DFVF_XYZB4,		//座標+4Beta (float*7 , X, Y, Z and 4 Beta)
			XYZB5 = D3DFVF_XYZB5,		//座標+5Beta (float*6 , X, Y, Z and 5 Beta)
			XYZW = D3DFVF_XYZW,			//座標(float*4, X, Y, Z, W)

			NORMAL = D3DFVF_NORMAL,		//法線(float*3)
			PSIZE = D3DFVF_PSIZE,		//頂點Size (float*1)
			DIFFUSE = D3DFVF_DIFFUSE,	//基本色 (DWORD)
			SPECULAR = D3DFVF_SPECULAR,	//鏡面反射色 (DWORD)

			TEX1 = D3DFVF_TEX1,			//貼圖來源, D3DFVF_TEXCOORDSIZE1() ~D3DFVF_TEXCOORDSIZE4() 指定, 預設(2個float, u 與 v)
			TEX2 = D3DFVF_TEX2,			//貼圖來源, D3DFVF_TEXCOORDSIZE1() ~D3DFVF_TEXCOORDSIZE4() 指定
			TEX3 = D3DFVF_TEX2,			//貼圖來源, D3DFVF_TEXCOORDSIZE1() ~D3DFVF_TEXCOORDSIZE4() 指定
			TEX4 = D3DFVF_TEX4,			//貼圖來源, D3DFVF_TEXCOORDSIZE1() ~D3DFVF_TEXCOORDSIZE4() 指定
			TEX5 = D3DFVF_TEX5,			//貼圖來源, D3DFVF_TEXCOORDSIZE1() ~D3DFVF_TEXCOORDSIZE4() 指定
			TEX6 = D3DFVF_TEX6,			//貼圖來源, D3DFVF_TEXCOORDSIZE1() ~D3DFVF_TEXCOORDSIZE4() 指定
			TEX7 = D3DFVF_TEX7,			//貼圖來源, D3DFVF_TEXCOORDSIZE1() ~D3DFVF_TEXCOORDSIZE4() 指定
			TEX8 = D3DFVF_TEX8,			//貼圖來源, D3DFVF_TEXCOORDSIZE1() ~D3DFVF_TEXCOORDSIZE4() 指定
		};

		class VertexBuffer : public ComPtr < IDirect3DVertexBuffer9 > {
			//private:
		protected:
			DWORD _FVF;
			UINT _Stride;

		public:
			VertexBuffer(void* pInitData, UINT Length, Renderer* pRender = DefaultRendererPtr);
			VertexBuffer(IDirect3DVertexBuffer9* pVertexBuffer = NULL);

			inline DWORD GetFVF() {
				return _FVF;
			}

			inline DWORD GetStride() {
				return _Stride;
			}

			//Stride of the component, in byte
			static int StrideAnalytics(DWORD FVF);
		};
	} /* namespace Drawing */
} /* namespace System */

#endif /* SYSTEM_DRAWING_VERTEXBUFFER_H_ */
#endif
