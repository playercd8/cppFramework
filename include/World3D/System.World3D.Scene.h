/*
* System.World3D.Scene.h
*
* Code Status: Drafts
*  Created on: Taiwan
*      Author: player
*/

#ifndef SYSTEM_WORLD3D_SCENE_H_
#define SYSTEM_WORLD3D_SCENE_H_

#if _MSC_VER > 1000
#pragma once
#endif

#include "../stdafx.h"
#include "../System.Collections.Map.h"
#include "../System.Drawing.Math.h"
#include "../System.String.h"
#include "../System.OOP.h"
#include "System.World3D.Entity.h"

using namespace System::Collections;
using namespace System::Drawing;

namespace System {
	namespace Drawing {
		class Renderer;
	}

	namespace World3D {
		class SceneNode {
		public:
		};

		class Scene
		{
		public:
			Scene()
			{
			}

			virtual ~Scene()
			{
			}
		};
	} /* namespace World3D */
} /* namespace System */

#endif /* SYSTEM_WORLD3D_SCENE_H_ */
