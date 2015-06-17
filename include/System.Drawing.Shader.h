/*
* System.Drawing.Shader.h
*
* Code Status: Drafts
*  Created on: Taiwan
*      Author: player
*/

#include "stdafx.h"

#if (_DRAWING_MODE == _DRAWING_MODE_DX11)
	#include "DX11/System.Drawing.Shader.h"
#elif (_DRAWING_MODE == _DRAWING_MODE_DX10)
	#include "DX10/System.Drawing.Shader.h"
#elif (_DRAWING_MODE == _DRAWING_MODE_DX9)
	#include "DX9/System.Drawing.Shader.h"
#elif (_DRAWING_MODE == _DRAWING_MODE_OPENGL)
	#include "OpenGL/System.Drawing.Shader.h"
#endif
