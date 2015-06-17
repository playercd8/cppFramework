/*
* System.Drawing.Sprite.h
*
*  Created on: Taiwan
*      Author: player
*/

#include "../stdafx.h"
#if (_DRAWING_MODE == _DRAWING_MODE_DX11)

#ifndef SYSTEM_DRAWING_SPRITE_H_
#define SYSTEM_DRAWING_SPRITE_H_

#if _MSC_VER > 1000
	#pragma once
#endif

#include "DX11.h"

#include "System.Drawing.Texture.h"
#include "../System.ComPtr.h"
#include "../System.Drawing.Math.h"


namespace System {
namespace Drawing {

class Renderer;
Renderer* GetDefaultRendererPtr();

//class Sprite {
//
//};

} /* namespace Drawing */
} /* namespace System */

#endif /*  SYSTEM_DRAWING_SPRITE_H_ */
#endif
