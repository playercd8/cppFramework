/*
 * System.Drawing.Light.h
 *
 *  Created on: Taiwan
 *      Author: player
 */

#include "../stdafx.h"
#if (_DRAWING_MODE == _DRAWING_MODE_OpenGL)

#ifndef SYSTEM_DRAWING_LIGHT_H_
#define SYSTEM_DRAWING_LIGHT_H_

#if _MSC_VER > 1000
	#pragma once
#endif

#include "OpenGL.h"
#include "../System.ComPtr.h"

namespace System {
namespace Drawing {

class Renderer;
Renderer* GetDefaultRendererPtr();

//class Light {
//
//};


} /* namespace Drawing */
} /* namespace System */

#endif /* SYSTEM_DRAWING_LIGHT_H_ */
#endif
