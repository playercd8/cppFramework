/*
* System.Drawing.Graphics.h
*
* Code Status: Drafts
*  Created on: Taiwan
*      Author: player
*/

#include "../stdafx.h"
#if (_DRAWING_MODE == _DRAWING_MODE_DX9)

#ifndef SYSTEM_DRAWING_GRAPHICS_H_
#define SYSTEM_DRAWING_GRAPHICS_H_

#if _MSC_VER > 1000
#pragma once
#endif

#include "DX9.h"
#include "../System.OOP.h"
#include "../System.Drawing.IGraphics.h"

namespace System {
	namespace Drawing {
		class Renderer;
		struct Renderer_Desc;

		class Graphics : public IGraphics, public Singleton < Graphics >
		{
		private:
			IDirect3D9* _pD3D9;
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
