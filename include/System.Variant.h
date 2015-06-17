/*
* System.Variant.h
*
* Code Status: Drafts
*  Created on: Taiwan
*      Author: player
*/

#ifndef SYSTEM_VARIANT_H_
#define SYSTEM_VARIANT_H_

#if _MSC_VER > 1000
#pragma once
#endif

#include "stdafx.h"

namespace System {
	class Buffer;
	class DateTime;

	namespace Drawing {
		class ViewPort;
		class Color;
		class Point;
		class Rect;
		class Size;
		class Vector2;
		class Vector3;
		class Vector4;
		class Matrix;
		class Quaternion;
		class Plane;

		class Camera;
		class Effect;
		class Font;
		class Light;
		class Mesh;
		class Texture1D;
		class Texture2D;
		class Texture3D;
	} /* namespace Drawing */
} /* namespace System */

//using namespace System::Drawing;

namespace System {
	enum VariantType {
		VT_Empty = 0,
		VT_INT,
		VT_FLOAT,
		
		VT_VoidPtr,
		VT_CSTR,
		VT_CWSTR,

		VT_Buffer,
		VT_DateTime,

		VT_ViewPort,
		VT_Color,
		VT_Point,
		VT_Rect,
		VT_Size,
		VT_Vector2,
		VT_Vector3,
		VT_Vector4,
		VT_Matrix,
		VT_Quaternion,
		VT_Plane,

		VT_Camera,
		VT_Effect,
		VT_Font,
		VT_Light,
		VT_Mesh,
		VT_Texture1D,
		VT_Texture2D,
		VT_Texture3D,

		VT_Unknown = 0xffff
	};

	typedef struct _Variant {
		VariantType type;
		union {
			INT vINT;
			FLOAT vFLOAT;

			void* pVoid;
			LPCSTR pStr;
			LPCWSTR pWStr;

			Buffer* pBuffer;
			DateTime* pDateTime;

			Drawing::ViewPort* pViewPort;
			Drawing::Color* pColor;
			Drawing::Point* pPoint;
			Drawing::Rect* pRect;
			Drawing::Size* pSize;
			Drawing::Vector2* pVector2;
			Drawing::Vector3* pVector3;
			Drawing::Vector4* pVector4;
			Drawing::Matrix* pMatrix;
			Drawing::Quaternion* pQuaternion;
			Drawing::Plane* pPlane;

			Drawing::Camera* pCamera;
			Drawing::Effect* pEffect;
			Drawing::Font* pFont;
			Drawing::Light* pLight;
			Drawing::Mesh* pMesh;
			Drawing::Texture1D* pTexture1D;
			Drawing::Texture2D* pTexture2D;
			Drawing::Texture3D* pTexture3D;
		};
	} _Variant;

	class Variant :public _Variant
	{
	public:
		Variant()				{ type = VariantType::VT_Empty; }
		Variant(_Variant& var)	{ *this = var; }

		Variant(INT val)		{ type = VariantType::VT_INT;		vINT = val; }
		Variant(float val)		{ type = VariantType::VT_FLOAT;		vFLOAT = val; }
		
		Variant(void* ptr)		{ type = VariantType::VT_VoidPtr;	pVoid = ptr; }
		Variant(LPCSTR ptr)		{ type = VariantType::VT_CSTR;		pStr = ptr; }
		Variant(LPCWSTR ptr)	{ type = VariantType::VT_CWSTR;		pWStr = ptr; }

		Variant(Buffer* ptr)	{ type = VariantType::VT_Buffer;	pBuffer = ptr; }
		Variant(DateTime* ptr)	{ type = VariantType::VT_DateTime;	pDateTime = ptr; }		

		Variant(Drawing::ViewPort* ptr)		{ type = VariantType::VT_ViewPort;	pViewPort = ptr; }
		Variant(Drawing::Color* ptr)		{ type = VariantType::VT_Color;		pColor = ptr; }
		Variant(Drawing::Point* ptr)		{ type = VariantType::VT_Point;		pPoint = ptr; }
		Variant(Drawing::Rect* ptr)			{ type = VariantType::VT_Rect;		pRect = ptr; }
		Variant(Drawing::Size* ptr)			{ type = VariantType::VT_Size;		pSize = ptr; }
		Variant(Drawing::Vector2* ptr)		{ type = VariantType::VT_Vector2;	pVector2 = ptr; }
		Variant(Drawing::Vector3* ptr)		{ type = VariantType::VT_Vector3;	pVector3 = ptr; }
		Variant(Drawing::Vector4* ptr)		{ type = VariantType::VT_Vector4;	pVector4 = ptr; }
		Variant(Drawing::Matrix* ptr)		{ type = VariantType::VT_Matrix;	pMatrix = ptr; }
		Variant(Drawing::Quaternion* ptr)	{ type = VariantType::VT_Quaternion; pQuaternion = ptr; }
		Variant(Drawing::Plane* ptr)		{ type = VariantType::VT_Plane;		pPlane = ptr; }

		Variant(Drawing::Camera* ptr)		{ type = VariantType::VT_Camera;	pCamera = ptr; }
		Variant(Drawing::Effect* ptr)		{ type = VariantType::VT_Effect;	pEffect = ptr; }
		Variant(Drawing::Font* ptr)			{ type = VariantType::VT_Font;		pFont = ptr; }
		Variant(Drawing::Light* ptr)		{ type = VariantType::VT_Light;		pLight = ptr; }
		Variant(Drawing::Mesh* ptr)			{ type = VariantType::VT_Mesh;		pMesh = ptr; }
		Variant(Drawing::Texture1D* ptr)	{ type = VariantType::VT_Texture1D;	pTexture1D = ptr; }
		Variant(Drawing::Texture2D* ptr)	{ type = VariantType::VT_Texture2D;	pTexture2D = ptr; }
		Variant(Drawing::Texture3D* ptr)	{ type = VariantType::VT_Texture3D;	pTexture3D = ptr; }

		~Variant()	{
		}

		bool CheckType(VariantType _type) const {
			return type == _type;
		}


		//String ToString() {}
	};
} /* namespace System */

#endif /* SYSTEM_VARIANT_H_ */
