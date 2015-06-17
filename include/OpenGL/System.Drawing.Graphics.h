/*
* System.Drawing.Graphics.h
*
*  Created on: Taiwan
*      Author: player
*  References:
*	1. Windows DirectX Graphics Documentation
*/

#include "../stdafx.h"
#if (_DRAWING_MODE == _DRAWING_MODE_OpenGL)

#ifndef SYSTEM_DRAWING_GRAPHICS_H_
#define SYSTEM_DRAWING_GRAPHICS_H_

#if _MSC_VER > 1000
#pragma once
#endif

#include "OpenGL.h"
#include "../System.OOP.h"
#include "../System.Drawing.IGraphics.h"

namespace System {
	namespace Drawing {
		class Renderer;
		struct Renderer_Desc;

		class Graphics : public IGraphics, public Singleton < Graphics >
		{
			//private:
			//protected:

		public:
			Graphics();
			virtual ~Graphics();

			bool Initialize();
			Renderer* GetRenderer(Renderer_Desc& desc);
		};
	} /* namespace Drawing */
} /* namespace System */

#endif /*  SYSTEM_DRAWING_GRAPHICS_H_ */
#endif
