/*
 * System.Drawing.Mesh.h
 *
 *  Created on: Taiwan
 *      Author: player
 */

#include "../stdafx.h"
#if (_DRAWING_MODE == _DRAWING_MODE_DX11)

#ifndef SYSTEM_DRAWING_MESH_H_
#define SYSTEM_DRAWING_MESH_H_

#if _MSC_VER > 1000
	#pragma once
#endif

namespace System {
namespace Drawing {

class Renderer;
Renderer* GetDefaultRendererPtr();

class Mesh {}
;


} /* namespace Drawing */
} /* namespace System */

#endif /* SYSTEM_DRAWING_MESH_H_ */
#endif
