/*
 * System.Drawing.Scene.h
 *
 * Code Status: Drafts
 *  Created on: Taiwan
 *      Author: player
 */

#ifndef SYSTEM_DRAWING_SCENE_H_
#define SYSTEM_DRAWING_SCENE_H_

#if _MSC_VER > 1000
	#pragma once
#endif

#include "stdafx.h"

namespace System {
namespace Drawing {

class Camera;

class Scene {
private:
	Camera* _pCamera;

public:
	Scene();
	virtual ~Scene();

	inline Camera* GetCamera() {
		return  _pCamera;
	}

	//Terrain 

	//SkyBox

	//
	

};

} /* namespace Drawing */
} /* namespace System */

#endif /* SYSTEM_DRAWING_SCENE_H_ */
