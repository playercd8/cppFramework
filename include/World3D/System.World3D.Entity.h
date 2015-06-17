/*
* System.World3D.Entity.h
*
* Code Status: Drafts
*  Created on: Taiwan
*      Author: player
*/

#ifndef SYSTEM_WORLD3D_ENTITY_H_
#define SYSTEM_WORLD3D_ENTITY_H_

#if _MSC_VER > 1000
#pragma once
#endif

#include "../stdafx.h"
#include "../System.Collections.Map.h"
#include "../System.Drawing.Math.h"
#include "../System.String.h"
#include "../System.OOP.h"
#include "../System.Variant.h"

using namespace System::Collections;
using namespace System::Drawing;

namespace System {
	namespace Drawing {
		class Renderer;
	}

	namespace World3D {
		enum EntityEventType {
			Focus,
			Other
		};

		typedef struct EntityEvent {
			EntityEventType EventType;
			union {
				//Focus
				Entity* pFocus;
			};
		} EntityEvent;

		typedef struct _Entity {
			String ID;
			Vector3 Position;
			Vector3 Rotation;
			Vector3 Scale;
			Matrix WorldMatrix;	//將Position, Rotation 轉為World矩陣, 作為繪出時Entity在世界的位置

			union {
				DWORD Flags;
				struct {
					unsigned int Visibility : 1;		//可視
					unsigned int IsRotation : 1;		//旋轉
					unsigned int IsScale : 1;			//縮放
					unsigned int Reserve1 : 1;			//保留
					unsigned int Reserve2 : 1;
					unsigned int Reserve3 : 1;
					unsigned int Reserve4 : 1;
					unsigned int Reserve5 : 1;
				};
			};

			IAttributes<String, Variant>	Attributes;
			IAttributes<String, Variant>	Style;
		} _Entity;

		class Entity : public _Entity
		{
		public:
			inline Matrix& MakeWorldMatrix() {
				Matrix matTemp;  // Temp matrix for rotations.
				Matrix matRot;   // Final rotation matrix, applied to 
				IsRotation = false;

				// Using the left-to-right order of matrix concatenation,
				// apply the translation to the object's world position
				// before applying the rotations.
				WorldMatrix.Translation(Position);
				matRot.Identity();

				// Now, apply the orientation variables to the world matrix
				// Produce and combine the rotation matrices.
				if (Rotation.x != 0) {
					matRot.Multiply(matRot, matTemp.RotationX(Rotation.x));
					IsRotation = true;
				}
				if (Rotation.y != 0) {
					matRot.Multiply(matRot, matTemp.RotationY(Rotation.y));
					IsRotation = true;
				}
				if (Rotation.z != 0) {
					matRot.Multiply(matRot, matTemp.RotationZ(Rotation.z));
					IsRotation = true;
				}
				// Apply the rotation matrices to complete the world matrix.
				if (IsRotation) {
					WorldMatrix.Multiply(WorldMatrix, matRot);
				}

				return WorldMatrix;
			}

			

			//顯示
			virtual void Draw(Renderer* pRenderer) = 0;

			//事件處理
			virtual void OnEvent(EntityEvent& e) = 0;

			//private:
			//protected:
		};
	} /* namespace World3D */
} /* namespace System */

#endif /* SYSTEM_WORLD3D_ENTITY_H_ */
