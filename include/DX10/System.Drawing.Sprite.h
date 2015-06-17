/*
* System.Drawing.Sprite.h
*
*  Created on: Taiwan
*      Author: player
*/

#include "../stdafx.h"
#if (_DRAWING_MODE == _DRAWING_MODE_DX10)

#ifndef SYSTEM_DRAWING_SPRITE_H_
#define SYSTEM_DRAWING_SPRITE_H_

#if _MSC_VER > 1000
#pragma once
#endif

#include "DX10.h"
#include "../System.ComPtr.h"
#include "../System.Drawing.Math.h"
#include "System.Drawing.Texture.h"

namespace System {
	namespace Drawing {
		class Renderer;
		Renderer* GetDefaultRendererPtr();

		class Sprite : public ComPtr < ID3DX10Sprite >
		{
			//private:
			//protected:

		public:
			Sprite(Renderer* pRender = DefaultRendererPtr);
			void Begin(DWORD flags);
			void End();

			void Draw(Texture2D& texture, Rect& rcSrc, Vector3& vecCenter, Vector3& vecPosition, DWORD argb);
			void Draw(Texture2D& texture, Rect& rcSrc, float x, float y, int a);

			//Sprite(Graphics& g) {
			//	HRESULT hr = D3DX10CreateSprite(
			//		g.GetDevice(),	//[in]   ID3D10Device *pDevice,
			//		4096,			//[in]   UINT cDeviceBufferSize,
			//		&_ptr			//[out]  LPD3DX10SPRITE *ppSprite
			//		);
			//}
			//virtual ~Sprite() {
			//}

			//void Begin(DWORD flags) {
			//	_ptr->Begin(flags);
			//}
			//
			//void End() {
			//	_ptr->End();
			//}

			//void Draw(Texture2D& texture, Rect& rcSrc, Vector3& vecCenter, Vector3& vecPosition, DWORD argb) {
			//	_ptr->Draw(texture, rcSrc, vecCenter, vecPosition, argb);
			//}

			//void Draw(Texture2D& texture, Rect& rcSrc, float x, float y, int a) {
			//		Vector3 vecCenter(0.0f, 0.0f, 0.0f), vecPosition(x, y, 0.0f);
			//		_ptr->Draw(texture, rcSrc, vecCenter, vecPosition, D3DCOLOR_ARGB(a, 255, 255, 255));
			//}
		};

		//D3DX10_SPRITE_FLAG
		enum SpriteFlags {
			SORT_TEXTURE = D3DX10_SPRITE_SORT_TEXTURE,
			SORT_DEPTH_BACK_TO_FRONT = D3DX10_SPRITE_SORT_DEPTH_BACK_TO_FRONT,
			SORT_DEPTH_FRONT_TO_BACK = D3DX10_SPRITE_SORT_DEPTH_FRONT_TO_BACK,
			SAVE_STATE = D3DX10_SPRITE_SAVE_STATE,
			ADDREF_TEXTURES = D3DX10_SPRITE_ADDREF_TEXTURES
		};
	} /* namespace Drawing */
} /* namespace System */

#endif /*  SYSTEM_DRAWING_SPRITE_H_ */
#endif
