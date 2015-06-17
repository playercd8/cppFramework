/*
* System.Drawing.Sprite.h
*
* Code Status: Drafts
*  Created on: Taiwan
*      Author: player
*/

#include "../stdafx.h"
#if (_DRAWING_MODE == _DRAWING_MODE_DX9)

#ifndef SYSTEM_DRAWING_SPRITE_H_
#define SYSTEM_DRAWING_SPRITE_H_

#if _MSC_VER > 1000
#pragma once
#endif

#include "DX9.h"
#include "../System.Application.h"
#include "../System.ComPtr.h"
#include "../System.Drawing.Math.h"
#include "System.Drawing.Texture.h"

namespace System {
	namespace Drawing {
		class Renderer;
		Renderer* GetDefaultRendererPtr();

		class Sprite : public ComPtr < ID3DXSprite >
		{
			//private:
			//protected:
		public:
			Sprite(Renderer* pRender = DefaultRendererPtr);

			void Begin(DWORD flags);
			void End();

			void Draw(Texture2D& texture, Rect& rcSrc, Vector3& vecCenter, Vector3& vecPosition, DWORD argb);
			void Draw(Texture2D& texture, Rect& rcSrc, float x, float y, int a);
		};

		enum SpriteFlags {
			DONOTSAVESTATE = D3DXSPRITE_DONOTSAVESTATE,
			DONOTMODIFY_RENDERSTATE = D3DXSPRITE_DONOTMODIFY_RENDERSTATE,
			OBJECTSPACE = D3DXSPRITE_OBJECTSPACE,
			BILLBOARD = D3DXSPRITE_BILLBOARD,
			ALPHABLEND = D3DXSPRITE_ALPHABLEND,
			SORT_TEXTURE = D3DXSPRITE_SORT_TEXTURE,
			SORT_DEPTH_FRONTTOBACK = D3DXSPRITE_SORT_DEPTH_FRONTTOBACK,
			SORT_DEPTH_BACKTOFRONT = D3DXSPRITE_SORT_DEPTH_BACKTOFRONT,
			DO_NOT_ADDREF_TEXTURE = D3DXSPRITE_DO_NOT_ADDREF_TEXTURE
		};
	} /* namespace Drawing */
} /* namespace System */

#endif /*  SYSTEM_DRAWING_SPRITE_H_ */
#endif