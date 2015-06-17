/*
* System.Drawing.Sprite_DX9.cpp
*
*  Created on: Taiwan
*      Author: player
*/

#include "../../include/stdafx.h"
#if (_DRAWING_MODE == _DRAWING_MODE_DX9)

#include "../../include/DX9/System.Drawing.Sprite.h"
#include "../../include/DX9/System.Drawing.Renderer.h"


namespace System {
namespace Drawing {

//---------------------------------------------------------------------------------------------------------
// class Sprite


Sprite::Sprite(Renderer* pRender) 
{
	HRESULT hr;
	V(D3DXCreateSprite(pRender->GetDevice(), &_ptr));
	if FAILED(hr)
		_ptr = NULL;
}

void Sprite::Begin(DWORD flags) {
	_ptr->Begin(flags);
}

void Sprite::End() {
	_ptr->End();
}

void Sprite::Draw(Texture2D& texture, Rect& rcSrc, Vector3& vecCenter, Vector3& vecPosition, DWORD argb) {
	HRESULT hr;
	V(_ptr->Draw(
		texture,
		rcSrc, 
		(D3DXVECTOR3*)&vecCenter,
		(D3DXVECTOR3*)&vecPosition, 
		argb));
}

void Sprite::Draw(Texture2D& texture, Rect& rcSrc, float x, float y, int a) {
	HRESULT hr;
	Vector3 vecCenter(0.0f, 0.0f, 0.0f), vecPosition(x, y, 0.0f);
	V(_ptr->Draw(
			texture, 
			rcSrc,
			(D3DXVECTOR3*)&vecCenter,
			(D3DXVECTOR3*)&vecPosition,
			D3DCOLOR_ARGB(a, 255, 255, 255)));
}



} /* namespace Drawing */
} /* namespace System */


#endif
