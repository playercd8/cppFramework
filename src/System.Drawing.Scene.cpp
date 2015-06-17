/*
 * System.Drawing.Scene.cpp
 *
 * Code Status: Drafts
 *  Created on: Taiwan
 *      Author: player
 */


#if _MSC_VER > 1000
	#pragma once
#endif

#include "../include/System.Drawing.Scene.h"
#include "../include/System.Drawing.Camera.h"
#include "../include/System.Drawing.Math.h"


namespace System {
namespace Drawing {


Scene::Scene() {
	_pCamera = new Camera();
}

Scene::~Scene() {

}



} /* namespace Drawing */
} /* namespace System */


