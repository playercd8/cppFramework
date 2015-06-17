/*
* System.Drawing.Effect_OpenGL.cpp
*
* Code Status: Drafts
*  Created on: Taiwan
*      Author: player
*/

#include "../../include/stdafx.h"
#if (_DRAWING_MODE == _DRAWING_MODE_OpenGL)

#include "../../include/OpenGL/System.Drawing.Effect.h"
#include "../../include/OpenGL/System.Drawing.Renderer.h"
#include "../../include/System.IO.File.h"
#include "../../include/System.String.h"

using namespace System::IO;

namespace System {
	namespace Drawing {
		//---------------------------------------------------------------------------------------------------------
		// class Effect

		Effect::Effect(Effect_Desc& desc, Renderer* pRender)
		{
			
		}


		Effect* Effect::FromFile(LPCTSTR pFileName, Renderer* pRender)
		{
			Buffer buf = File.ReadFile(pFileName);

			Effect* pEffect = FromBuffer(buf, pRender);
			return pEffect;
		}

		Effect* Effect::FromBuffer(Buffer& buf, Renderer* pRender)
		{
			

			//Effect* pEffect = new Effect(ptr);
			//return pEffect;

			return NULL;
		}

	} /* namespace Drawing */
} /* namespace System */

#endif
