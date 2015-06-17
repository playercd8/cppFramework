/*
* System.Drawing.Renderer_OpenGL.cpp
*
*  Created on: Taiwan
*      Author: player
*/


#include "../../include/stdafx.h"

#if (_DRAWING_MODE == _DRAWING_MODE_OpenGL)
#include "../../include/OpenGL/System.Drawing.Renderer.h"
#include "../../include/System.ComPtr.h"

namespace System {
namespace Drawing {


Renderer::Renderer(Renderer_Desc& desc)
{
	memcpy(this, &desc, sizeof(Renderer_Desc));
}


Renderer::~Renderer()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	wglMakeCurrent(_hDC, NULL);
	if (_hrc)
	{
		wglDeleteContext(_hrc);
		_hrc = NULL;
	}

	if (_hDC) 
	{
		ReleaseDC(hWnd, _hDC);
	}
}


void Renderer::Clear()
{
	// Clear the back buffer.
	glClearColor(_BkColor.r, _BkColor.g, _BkColor.b, _BkColor.a);
	//_pDeviceContext->ClearRenderTargetView(_pRenderTargetView, _BkColor);

	// Clear the depth buffer.
	//_pDeviceContext->ClearDepthStencilView(_pDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
}

void Renderer::Present()
{
	SwapBuffers(_hDC);
	// Present the back buffer to the screen since rendering is complete.
	//if (vsync) {
	//	// Lock to screen refresh rate.
	//	_pSwapChain->Present(1, 0);
	//}
	//else {
	//	// Present as fast as possible.
	//	_pSwapChain->Present(0, 0);
	//}
}


//頂點格式
struct D3DTLVERTEX {
	float x, y, z;
	float rhw;
	DWORD color;
	float tu0, tv0;

	//enum { FVF = D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1 };
};

//
//void Renderer::DrawTexture2D(Texture2D& texture, Vector2& dest1, Vector2& dest2, Vector2& src1, Vector2& src2, DWORD color) 
//{
//	float _invW = texture._invW;
//	float _invH = texture._invH;
//
//	D3DTLVERTEX v[] = {
//			{ dest1.x, dest1.y, 0, 1, color, src1.x * _invW, src1.y * _invH },
//			{ dest2.x, dest1.y, 0, 1, color, src2.x * _invW, src1.y * _invH },
//			{ dest1.x, dest2.y, 0, 1, color, src1.x * _invW, src2.y * _invH },
//			{ dest2.x, dest2.y, 0, 1, color, src2.x * _invW, src2.y * _invH },
//	};
//
//	//pDevice->SetTexture(0, texture);
//	//pDevice->SetFVF(D3DTLVERTEX::FVF);
//	//pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, v, sizeof(D3DTLVERTEX));
//}
//
//void Renderer::DrawTexture2D(Texture2D& texture, float x1, float y1, float x2, float y2,
//		float sx1, float sy1, float sx2, float sy2, DWORD color) 		
//{
//	float _invW = texture._invW;
//	float _invH = texture._invH;
//
//	D3DTLVERTEX v[] = {
//			{ x1, y1, 0, 1, color, sx1 * _invW, sy1 * _invH },
//			{ x2, y1, 0, 1, color, sx2 * _invW, sy1 * _invH },
//			{ x1, y2, 0, 1, color, sx1 * _invW, sy2 * _invH },
//			{ x2, y2, 0, 1, color, sx2 * _invW, sy2 * _invH },
//	};
//
//	//pDevice->SetTexture(0, texture);
//	//pDevice->SetFVF(D3DTLVERTEX::FVF);
//	//pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, v, sizeof(D3DTLVERTEX));
//}

void Renderer::RenderScene(Scene& scene)
{

}



} /* namespace Drawing */
} /* namespace System */

#endif