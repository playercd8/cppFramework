/*
 * System.Drawing.Light_DX9.cpp
 *
 *  Created on: Taiwan
 *      Author: player
 */

#include "../../include/stdafx.h"
#if (_DRAWING_MODE == _DRAWING_MODE_DX9)

#include "../../include/DX9/System.Drawing.Light.h"
#include "../../include/DX9/System.Drawing.Renderer.h"


namespace System {
namespace Drawing {

//---------------------------------------------------------------------------------------------------------
// class Light

	//Light::Light(Graphics& g, int index)  {
	//	_pDevice = g.GetDevice();
	//	_index = index;
	//}

	Light::Light(Light_Desc& desc)  {
		memcpy(this, &desc, sizeof(D3DLIGHT9));
	}

	//void Light::SetLight() {
	//	_pDevice->SetLight(_index, &_light);
	//}

	//void Light::SetEnable(bool isEnable) {
	//	_pDevice->LightEnable(_index, isEnable);
	//}

	////D3DLIGHT_DIRECTIONAL
	//Light::Light(Graphics& g, int index)  {
	//	_pDevice  = g.GetDevice();
	//	_index = index;

	//	ZeroMemory(&_light, sizeof(D3DLIGHT9));    // clear out the light struct for use
	//	_light.Type = D3DLIGHT_DIRECTIONAL;    // make the light type 'directional light'
	//	_light.Diffuse = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);    // set the light's color
	//	_light.Direction = D3DXVECTOR3(-1.0f, -0.3f, -1.0f);
	//}

	////D3DLIGHT_POINT
	//Light::Light(Graphics& g, int index)  {
	//	_pDevice = g.GetDevice();
	//	_index = index;

	//	ZeroMemory(&_light, sizeof(D3DLIGHT9));

	//	// Set up a white point light.
	//	_light.Type = D3DLIGHT_POINT;
	//	_light.Diffuse.r = 1.0f;
	//	_light.Diffuse.g = 1.0f;
	//	_light.Diffuse.b = 1.0f;
	//	_light.Ambient.r = 1.0f;
	//	_light.Ambient.g = 1.0f;
	//	_light.Ambient.b = 1.0f;
	//	_light.Specular.r = 1.0f;
	//	_light.Specular.g = 1.0f;
	//	_light.Specular.b = 1.0f;

	//	// Position it high in the scene and behind the user.
	//	// Remember, these coordinates are in world space, so
	//	// the user could be anywhere in world space, too. 
	//	// For the purposes of this example, assume the user
	//	// is at the origin of world space.
	//	_light.Position.x = 0.0f;
	//	_light.Position.y = 1000.0f;
	//	_light.Position.z = -100.0f;

	//	// Don't attenuate.
	//	_light.Attenuation0 = 1.0f;
	//	_light.Range = 1000.0f;
	//}





} /* namespace Drawing */
} /* namespace System */

#endif
