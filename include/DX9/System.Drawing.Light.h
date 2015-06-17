/*
 * System.Drawing.Light.h
 *
 * Code Status: Drafts
 *  Created on: Taiwan
 *      Author: player
 */

#include "../stdafx.h"
#if (_DRAWING_MODE == _DRAWING_MODE_DX9)

#ifndef SYSTEM_DRAWING_LIGHT_H_
#define SYSTEM_DRAWING_LIGHT_H_

#if _MSC_VER > 1000
#pragma once
#endif

#include "DX9.h"
#include "../System.ComPtr.h"
#include "../System.Drawing.Math.h"

namespace System {
	namespace Drawing {
		class Renderer;
		Renderer* GetDefaultRendererPtr();

		typedef	D3DLIGHT9 Light_Desc;
		//D3DLIGHTTYPE

		class Light : public D3DLIGHT9 {
			//private:
			//protected:
		public:
			Light() {}
			Light(Light_Desc& desc); 

			//方向光（Directional Light）
			//方向光是一組沒有衰減的平行光，類似太陽光的效果。
			void InitDirectionalLight(Vector3& direction, Color& color)
			{
				::ZeroMemory(this, sizeof(D3DLIGHT9));

				Type = D3DLIGHT_DIRECTIONAL;	//光源類型
				Ambient = color * 0.4f;			//環境光
				Diffuse = color;				//擴散光
				Specular = color * 0.6f;		//反射光-
				Direction = direction;			//光線進行方向
			}
			
			//點光（Point Light）
			//從一個點向周圍均勻發射的光，有最大的照明範圍，亮度隨距離衰減，最明顯的一個例子就是我們家裡用的燈泡。
			void InitPointLight(Vector3& position, Color& color)
			{
				::ZeroMemory(this, sizeof(D3DLIGHT9));

				Type = D3DLIGHT_POINT;
				Ambient = color * 0.4f;
				Diffuse = color;
				Specular = color * 0.6f;
				Position = position;
				Range = 1000.0f;
				Falloff = 1.0f;
				Attenuation0 = 1.0f;
				Attenuation1 = 0.0f;
				Attenuation2 = 0.0f;
			}


			//聚光燈（Spot Light）
			//最複雜的一種燈，有光源點位置、有方向、有範圍、有發光的內徑和外徑，光照強度還會隨距離衰減。類似的例子是電筒。
			void InitSpotLight(Vector3& position, Vector3& direction, Color& color)
			{
				::ZeroMemory(this, sizeof(D3DLIGHT9));

				Type = D3DLIGHT_SPOT;
				Ambient = color * 0.4f;
				Diffuse = color;
				Specular = color * 0.6f;
				Position = position;
				Direction = direction;
				Range = 1000.0f;
				Falloff = 1.0f;
				Attenuation0 = 1.0f;
				Attenuation1 = 0.0f;
				Attenuation2 = 0.0f;
				Theta = 0.5f;
				Phi = 0.7f;
			}

			//void SetLight();
			//void SetEnable(bool isEnable);

			
			
		};
	} /* namespace Drawing */
} /* namespace System */

#endif /* SYSTEM_DRAWING_LIGHT_H_ */
#endif
