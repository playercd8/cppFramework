/*
* System.Drawing.Math_XNA.h
*
* Code Status: Drafts
*  Created on: Taiwan
*      Author: player
*
* References:
*	DirectXMath
*		http://msdn.microsoft.com/en-us/library/windows/desktop/hh437833.aspx
*	XNA Math Version 2.04
*		http://blogs.msdn.com/b/chuckw/archive/2011/02/23/xna-math-version-2-04.aspx
*	SimpleMath (DirectX Tool Kit)
*		http://directxtk.codeplex.com/
*	Working with D3DXMath
*		http://msdn.microsoft.com/en-us/library/windows/desktop/ff729728.aspx
*/

#include "../stdafx.h"
#if (_MATH_TYPE == _MATH_TYPE_XNA)

#ifndef SYSTEM_DRAWING_MATH_H_
#define SYSTEM_DRAWING_MATH_H_

#if _MSC_VER > 1000
#pragma once
#endif


#if (_DRAWING_MODE == _DRAWING_MODE_DX11)
#include "../DX11/DX11.h"
#elif (_DRAWING_MODE == _DRAWING_MODE_DX10)
#include "../DX10/DX10.h"
#elif (_DRAWING_MODE == _DRAWING_MODE_DX9)
#include "../DX9/DX9.h"
#elif (_DRAWING_MODE == _DRAWING_MODE_OPENGL)
#include "../OpenGL/OpenGL.h"
#endif

#include "./library/DXSDK/Include/xnamath.h"

#include <algorithm>    // std::swap
#include "../System.Math.h"
#pragma warning(disable : 4316)
#pragma warning(disable : 4800)

namespace System {
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

		//---------------------------------------------------------------------------------------------------------
		// Declared class
#pragma region Declared class

		//---------------------------------------------------------------------------------------------------------
		// Declared class ViewPort
#pragma region Declared class ViewPort

#if (_DRAWING_MODE == _DRAWING_MODE_DX11)
		typedef D3D11_VIEWPORT _ViewPort;
#elif (_DRAWING_MODE == _DRAWING_MODE_DX10)
		typedef D3D10_VIEWPORT _ViewPort;
#elif (_DRAWING_MODE == _DRAWING_MODE_DX9)
		typedef D3DVIEWPORT9 _ViewPort;
#endif

		class ViewPort : public _ViewPort {
		public:
			ViewPort();
			ViewPort(float x, float y, float w, float h, float minZ = 0, float maxZ = 1);
			ViewPort(Rect& bounds, float minZ = 0, float maxZ = 1);

			void SetViewPort(float x, float y, float w, float h, float minZ = 0, float maxZ = 1);

			operator _ViewPort* ();

			bool operator == (const ViewPort& Viewport) const;
			bool operator != (const ViewPort& Viewport) const;

			Rect& Bounds(Rect& out);
		};

#pragma endregion Declared class ViewPort

		//---------------------------------------------------------------------------------------------------------
		// Declared class Color
#pragma region Declared class Color
		typedef struct _Color {
			union {
				struct {
					float r, g, b, a;
				};
				float v[4];
				__m128 xmm;
#if (_DRAWING_MODE == _DRAWING_MODE_DX9)
				D3DCOLORVALUE dxColor;
#endif
			};
		} _Color;

		class Color : public  _Color
		{
		public:
			Color();
			Color(_Color& c);
			Color(float _r, float _g, float _b, float _a);
			Color(const float* pSrc);
			Color(const Color& c);
			Color(DWORD argb);

#if (_DRAWING_MODE == _DRAWING_MODE_DX9)
			Color(D3DCOLORVALUE& c);
			operator D3DCOLORVALUE*();
			operator D3DCOLORVALUE();
#endif

			// casting
			operator DWORD() const;
			operator float* ();
			operator const float* () const;

			// assignment operators
			Color& operator += (const Color& C);
			Color& operator -= (const Color& C);
			Color& operator *= (float num);
			Color& operator /= (float num);

			// unary operators
			Color operator + () const;
			Color operator - () const;

			// binary operators
			Color operator + (const Color& C) const;
			Color operator - (const Color& C) const;
			Color operator * (float num) const;
			Color operator / (float num) const;

			bool operator == (const Color& C) const;
			bool operator != (const Color& C) const;

			Color& Negative(const Color& C);
			Color& Add(const Color& C1, const Color& C2);
			Color& Subtract(const Color& C1, const Color& C2);
			Color& Scale(const Color& C, float scale);
			Color& Modulate(const Color& C1, const Color& C2);
			Color& Lerp(const Color& C1, const Color& C2, float scale);

			Color& Glyph(const Color& C);

			friend Color operator * (float num, const Color& c);
		};		
#pragma endregion Declared class Color

		//---------------------------------------------------------------------------------------------------------
		// Declared class Point
#pragma region Declared class Point

		typedef struct _Point {
			int x;
			int y;
		} _Point;

		class Point : public _Point {
		public:
			Point();
			Point(_Point& pt);
			Point(int X, int Y);
			Point(Point& pt);
			Point(Size& size);
#if defined(_WIN32) || defined(_WIN64)
			Point(LPARAM lParam);
#endif

			void Offset(int xOffset, int yOffset);
			void Offset(Point& pt);
			void Offset(Size& size);

			void SetPoint(int X, int Y);

			bool operator == (Point& pt) const;
			bool operator != (Point& pt) const;

			void operator += (Size& size);
			void operator -= (Size& size);

			void operator += (Point& pt);
			void operator -= (Point& pt);

			Point operator + (Size& size) const;
			Point operator - (Size& size) const;

			Point operator - () const;
			Point operator + (Point& pt) const;

			Size operator-(Point& pt) const;

			Rect operator+(Rect& rc) const;
			Rect operator-(Rect& rc) const;
		};

#pragma endregion Declared class Point

		//---------------------------------------------------------------------------------------------------------
		// Declared class Size
#pragma region Declared class Size

		typedef struct _Size {
			int cx;
			int cy;
		} _Size;

		class Size : public _Size {
		public:
			Size();
			Size(_Size& size);
			Size(int CX, int CY);
			Size(Size& size);
			Size(Point& pt);
			Size(DWORD dwSize);
#if defined(_WIN32) || defined(_WIN64)
			Size(SIZE& size);

			operator SIZE*();
#endif

			bool operator == (Size& size) const;
			bool operator != (Size& size) const;

			void operator += (Size& size);
			void operator -= (Size& size);

			void SetSize(int CX, int CY);

			Size operator + (Size& size) const;
			Size operator - (Size& size) const;

			Size operator - () const;

			Point operator + (Point& pt) const;
			Point operator - (Point& pt) const;

			inline Rect operator + (Rect& rc);
			inline Rect operator - (Rect& rc);
		};

#pragma endregion Declared class Size

		//---------------------------------------------------------------------------------------------------------
		// Declared class Rect

#pragma region Declared class Rect

		typedef struct _Rect {
			int left;
			int top;
			int right;
			int bottom;
		} _Rect;

		class Rect : public _Rect {
		public:
			Rect();
			Rect(_Rect& rc);
			Rect(int l, int t, int r, int b);
			Rect(Rect& rc);
			Rect(Rect* p);
			Rect(Point& pt, Size& size);
			Rect(Point& topLeft, Point& bottomRight);

#if defined(_WIN32) || defined(_WIN64)
			Rect(LPCRECT lpSrcRect);

			operator LPRECT();
			operator LPCRECT() const;
#endif

			int Width();
			int Height();

			Size getSize();

			Point& TopLeft();
			Point& BottomRight();
			const Point& TopLeft() const;
			const Point& BottomRight() const;

			Point CenterPoint() const;
			void SwapLeftRight();
			bool IsRectEmpty() const;
			bool IsRectNull() const;
			bool PtInRect(Point& pt) const;

			void SetRect(int x1, int y1, int x2, int y2);
			void SetRect(Point& topLeft, Point& bottomRight);
			void SetRectEmpty();
			void CopyRect(Rect& rc);
			bool EqualRect(Rect& rc) const;

			void InflateRect(int x, int y);
			void InflateRect(Size& size);
			void InflateRect(Rect& rc);
			void InflateRect(int l, int t, int r, int b);
			void DeflateRect(int x, int y);
			void DeflateRect(Size& size);
			void DeflateRect(Rect& rc);
			void DeflateRect(int l, int t, int r, int b);
			void OffsetRect(int x, int y);
			void OffsetRect(Size& size);
			void OffsetRect(Point& pt);
			void NormalizeRect();

			void MoveToY(int y);
			void MoveToX(int x);
			void MoveToXY(int x, int y);
			void MoveToXY(Point& pt);

			bool IntersectRect(Rect& rc1, Rect& rc2);
			bool UnionRect(Rect& rc1, Rect& rc2);
			bool SubtractRect(Rect& rc1, Rect& rc2);

			void operator = (Rect& rc);

			bool operator == (Rect& rc) const;
			bool operator != (Rect& rc) const;

			void operator += (Point& pt);
			void operator += (Size& size);
			void operator += (Rect& rc);
			void operator -= (Point& pt);
			void operator -= (Size& size);
			void operator -= (Rect& rc);

			void operator &= (Rect& rc);
			void operator |= (Rect& rc);

			// Operators returning CRect values
			Rect operator + (Point& pt);
			Rect operator - (Point& pt);
			Rect operator + (Rect& rc);
			Rect operator + (Size& size);
			Rect operator - (Size& size);
			Rect operator - (Rect& rc);

			Rect operator & (Rect& rc);
			Rect operator | (Rect& rc);

			Rect MulDiv(int nMultiplier, int nDivisor) const;
		};

#pragma endregion Declared class Rect		

		//---------------------------------------------------------------------------------------------------------
		// Declared class Vector2
#pragma region Declared class Vector2

		typedef _XMFLOAT2 _Vector2;

		class Vector2 :public _Vector2
		{
		public:
			Vector2();
			Vector2(_Vector2& vec);
			Vector2(float _x, float _y);
			Vector2(const float* pSrc);
			Vector2(Point& pt);

			Vector2(__m128 _xmm);
			Vector2& operator = (__m128 _xmm);
			operator __m128 ();

#if (_DRAWING_MODE == _DRAWING_MODE_DX10) || (_DRAWING_MODE == _DRAWING_MODE_DX9)
			Vector2(D3DXVECTOR2& vec);
			operator D3DXVECTOR2*();
#endif

			// casting
			operator float* ();
			operator const float* ();

			// assignment operators (Vector2)
			Vector2& operator += (const Vector2& vec);
			Vector2& operator -= (const Vector2& vec);
			Vector2& operator *= (const Vector2& vec);
			inline Vector2& operator /= (const Vector2& vec);

			// assignment operators (float)
			Vector2& operator += (const float num);
			Vector2& operator -= (const float num);
			Vector2& operator *= (const float num);
			Vector2& operator /= (const float num);

			// unary operators
			const Vector2& operator + ();
			Vector2 operator - () const;

			// binary operators
			Vector2 operator + (Vector2& vec);
			Vector2 operator - (Vector2& vec);
			Vector2 operator * (float num);
			Vector2 operator / (float num);

			bool operator == (const Vector2& vec) const;
			inline bool operator != (const Vector2& vec) const;

			float Length();
			float LengthSq();

			float Dot(const Vector2& vec);
			float Cross(const Vector2& vec);

			Vector2& Add(const Vector2& V1, const Vector2& V2);
			Vector2& Subtract(const Vector2& V1, const Vector2& V2);
			Vector2& Minimize(const Vector2& V1, const Vector2& V2);
			Vector2& Maximize(const Vector2& V1, const Vector2& V2);
			Vector2& Scale(const Vector2& V1, float scale);
			Vector2& Lerp(const Vector2& V1, const Vector2& V2, float scale);
			Vector2& Normalize(const Vector2& V1);

			Vector2& Hermite(const Vector2& Position0, const Vector2& Tangent0, const Vector2& Position1, const Vector2& Tangent1, float t);
			Vector2& CatmullRom(const Vector2& Position0, const Vector2& Position1, const Vector2& Position2, const Vector2& Position3, float t);
			Vector2& BaryCentric(const Vector2& Position0, const Vector2& Position1, const Vector2& Position2, float f, float g);
			Vector2& TransformCoord(const Vector2& V1, const Matrix& mat);
			Vector2& TransformNormal(const Vector2& V1, const Matrix& mat);

			Vector2* TransformCoordArray(Vector2* pOut, UINT OutputStride, const Vector2* pSrc, UINT InputStride, UINT VectorCount, const Matrix& mat);
			Vector2* TransformNormalArray(Vector2* pOut, UINT OutputStride, const Vector2* pSrc, UINT InputStride, UINT VectorCount, const Matrix& mat);

			Vector2& Reflect(const Vector2& V1, const Vector2& normal);

			friend Vector2 operator * (float num, const Vector2& vec);
		};

#pragma endregion Declared class Vector2

		//---------------------------------------------------------------------------------------------------------
		// Declared class Vector3
#pragma region Declared class Vector3
		typedef _XMFLOAT3 _Vector3;

		class Vector3 :public _Vector3
		{
		public:
			Vector3();
			Vector3(_Vector3& vec);
			Vector3(float _x, float _y, float _z);
			Vector3(const float* pSrc);

			Vector3(__m128 _xmm);
			Vector3& operator = (__m128 _xmm);
			operator __m128 ();

#if (_DRAWING_MODE == _DRAWING_MODE_DX10) || (_DRAWING_MODE == _DRAWING_MODE_DX9)
			Vector3(D3DVECTOR& vec);
			operator D3DVECTOR ();
#endif

			// casting
			operator float* ();
			operator const float* ();

			// assignment operators (Vector3)
			Vector3& operator += (const Vector3& vec);
			Vector3& operator -= (const Vector3& vec);
			Vector3& operator *= (const Vector3& vec);
			Vector3& operator /= (const Vector3& vec);

			// assignment operators (float)
			Vector3& operator += (float num);
			Vector3& operator -= (float num);
			Vector3& operator *= (float num);
			Vector3& operator /= (float num);

			// unary operators
			const Vector3& operator + ();
			Vector3 operator - ();

			// binary operators
			Vector3 operator + (const Vector3& vec);
			Vector3 operator  - (const Vector3& vec);
			Vector3 operator * (float num);
			Vector3 operator / (float num);

			bool operator == (const Vector3& vec) const;
			bool operator != (const Vector3& vec) const;

			float Length();
			float LengthSq();

			float Dot(const Vector3& vec);
			Vector3& Cross(const Vector3& V1, const Vector3& V2);

			Vector3& Add(const Vector3& V1, const Vector3& V2);
			Vector3& Subtract(const Vector3& V1, const Vector3& V2);
			Vector3& Minimize(const Vector3& V1, const Vector3& V2);
			Vector3& Maximize(const Vector3& V1, const Vector3& V2);
			Vector3& Scale(const Vector3& V1, float scale);
			Vector3& Lerp(const Vector3& V1, const Vector3& V2, float scale);
			Vector3& Normalize(const Vector3& V1);

			Vector3& Hermite(const Vector3& Position0, const Vector3& Tangent0, const Vector3& Position1, const Vector3& Tangent1, float t);
			Vector3& CatmullRom(const Vector3& Position0, const Vector3& Position1, const Vector3& Position2, const Vector3& Position3, float t);
			Vector3& BaryCentric(const Vector3& Position0, const Vector3& Position1, const Vector3& Position2, float f, float g);
			Vector3& TransformCoord(const Vector3& V1, const Matrix& mat);
			Vector3& TransformNormal(const Vector3& V1, const Matrix& mat);
			Vector3* TransformCoordArray(Vector3* pOut, UINT OutputStride, const Vector3* pSrc, UINT InputStride, UINT VectorCount, const Matrix& mat);
			Vector3* TransformNormalArray(Vector3* pOut, UINT OutputStride, const Vector3* pSrc, UINT InputStride, UINT VectorCount, const Matrix& mat);
			Vector3& Project(const Vector3& V1, const ViewPort& Viewport, const Matrix& matProjection, const Matrix& matView, const Matrix& matWorld);
			Vector3& Unproject(const Vector3& V1, const ViewPort& Viewport, const Matrix& matProjection, const Matrix& matView, const Matrix& matWorld);
			Vector3* ProjectArray(Vector3* pOut, UINT OutputStride, const Vector3* pSrc, UINT InputStride, UINT VectorCount, const ViewPort& Viewport, const Matrix& matProjection, const Matrix& matView, const Matrix& matWorld);
			Vector3* UnprojectArray(Vector3* pOut, UINT OutputStride, const Vector3* pSrc, UINT InputStride, UINT VectorCount, const ViewPort& Viewport, const Matrix& matProjection, const Matrix& matView, const Matrix& matWorld);
			Vector3& IntersectLineIntersectLine(const Plane& P, const Vector3 &LinePoint1, const Vector3 &LinePoint2);

			Vector3& Reflect(const Vector3& V1, const Vector3& normal);

			friend Vector3 operator * (float num, Vector3& vec);
		};
#pragma endregion Declared class Vector3

		//---------------------------------------------------------------------------------------------------------
		// Declared class Vector4
#pragma region Declared class Vector4
		//XMVECTOR
		typedef struct _Vector4 {
			union {
				struct {
					float	x, y, z, w;
				};
				float v[4];
				__m128 xmm;
			};
		} _Vector4;

		class Vector4 :public _Vector4
		{
		public:
			Vector4();
			Vector4(_Vector4& vec);
			Vector4(float _x, float _y, float _z, float _w);
			Vector4(const float* pSrc);

			Vector4(__m128 _xmm);
			Vector4& operator = (__m128 _xmm);
			operator __m128 ();

#if (_DRAWING_MODE == _DRAWING_MODE_DX10) || (_DRAWING_MODE == _DRAWING_MODE_DX9)
			Vector4(D3DXVECTOR4& vec);
			operator D3DXVECTOR4*();
#endif

			// casting
			operator float* ();
			operator const float* ();

			// assignment operators (Vector4)
			Vector4& operator += (const Vector4& vec);
			Vector4& operator -= (const Vector4& vec);
			Vector4& operator *= (const Vector4& vec);
			Vector4& operator /= (const Vector4& vec);

			// assignment operators (float)
			Vector4& operator += (float num);
			Vector4& operator -= (float num);
			Vector4& operator *= (float num);
			Vector4& operator /= (float num);

			// unary operators
			const Vector4& operator + ();
			Vector4 operator - () const;

			// binary operators
			Vector4 operator + (const Vector4& vec) const;
			Vector4 operator - (const Vector4& vec) const;
			Vector4 operator * (float num) const;
			Vector4 operator / (float num) const;

			bool operator == (const Vector4& vec) const;
			bool operator != (const Vector4& vec) const;

			float Length();
			float LengthSq();
			float Dot(const Vector4& vec);

			Vector4& Add(const Vector4& V1, const Vector4& V2);
			Vector4& Subtract(const Vector4& V1, const Vector4& V2);
			Vector4& Minimize(const Vector4& V1, const Vector4& V2);
			Vector4& Maximize(const Vector4& V1, const Vector4& V2);
			Vector4& Scale(const Vector4& V1, float scale);
			Vector4& Lerp(const Vector4& V1, const Vector4& V2, float scale);
			Vector4& Normalize(const Vector4& V1);

			Vector4& Hermite(const Vector4& Position0, const Vector4& Tangent0, const Vector4& Position1, const Vector4& Tangent1, float t);
			Vector4& CatmullRom(const Vector4& Position0, const Vector4& Position1, const Vector4& Position2, const Vector4& Position3, float t);
			Vector4& BaryCentric(const Vector4& Position0, const Vector4& Position1, const Vector4& Position2, float f, float g);
			Vector4& Transform(const Vector2& V1, const Matrix& mat);
			Vector4& Transform(const Vector3& V1, const Matrix& mat);
			Vector4& Transform(const Vector4& V1, const Matrix& mat);

			Vector4* TransformArray(Vector4* pOut, UINT OutputStride, const Vector2* pSrc, UINT InputStride, UINT VectorCount, const Matrix& mat);
			Vector4* TransformArray(Vector4* pOut, UINT OutputStride, const Vector3* pSrc, UINT InputStride, UINT VectorCount, const Matrix& mat);
			Vector4* TransformArray(Vector4* pOut, UINT OutputStride, const Vector4* pSrc, UINT InputStride, UINT VectorCount, const Matrix& mat);;

			Vector4& Reflect(const Vector4& V1, const Vector4& normal);

			friend Vector4 operator * (float num, const Vector4& vec);
		};
#pragma endregion Declared class Vector4

		//---------------------------------------------------------------------------------------------------------
		// class Matrix
		//
		// References:
		//	1. DirectX SDK(d3dx9math.h and d3dx9math.inl)
		//	2. http ://evanw.github.io/lightgl.js/docs/matrix.html
#pragma region Declared class Matrix

		typedef _XMMATRIX _Matrix;
		//typedef XMFLOAT4X4 _Matrix;

		__declspec(align(16))
		class Matrix : public _Matrix
		{
		public:
			Matrix();
			Matrix(_Matrix& mat);
			Matrix(const float* pSrc);
			Matrix(const Matrix& mat);
			Matrix(float f11, float f12, float f13, float f14,
				float f21, float f22, float f23, float f24,
				float f31, float f32, float f33, float f34,
				float f41, float f42, float f43, float f44);

			// casting operators
			operator float* ();
			operator const float* () const;

			// access grants
			float& operator () (UINT row, UINT col);
			float operator () (UINT row, UINT col) const;

			// assignment operators
			Matrix& operator *= (const Matrix& mat);
			Matrix& operator += (const Matrix& mat);
			Matrix& operator -= (const Matrix& mat);

			Matrix& operator *= (float f);
			Matrix& operator /= (float f);

			// unary operators
			Matrix operator + () const;
			Matrix operator - () const;

			// binary operators
			Matrix operator * (const Matrix& mat);
			Matrix operator + (const Matrix& mat) const;
			Matrix operator - (const Matrix& mat) const;

			Matrix operator * (float f) const;
			Matrix operator / (float f) const;

			bool operator == (const Matrix& mat) const;
			bool operator != (const Matrix& mat) const;

			Matrix& Transpose(const Matrix& mat);
			Matrix& Multiply(const Matrix& mat1, const Matrix& mat2);
			Matrix& MultiplyTranspose(const Matrix& mat1, const Matrix& mat2);
			Matrix& Inverse(const Matrix& mat);

			Matrix& Scaling(float sx, float sy, float sz);
			Matrix& Scaling(const Vector3& vec);
			Matrix& Translation(float x, float y, float z);
			Matrix& Translation(const Vector3& vec);
			Matrix& RotationAxis(const Vector3& vec, float Angle);
			Matrix& RotationX(float angle);
			Matrix& RotationY(float angle);
			Matrix& RotationZ(float angle);

			Matrix& Projection(float nearPlane, float farPlane, float fovHoriz, float fovVert);
			Matrix& PerspectiveLH(float w, float h, float zn, float zf);
			Matrix& PerspectiveRH(float w, float h, float zn, float zf);
			Matrix& PerspectiveFovLH(float fovY, float Aspect, float zn, float zf);
			Matrix& PerspectiveFovRH(float fovY, float Aspect, float zn, float zf);
			Matrix& PerspectiveOffCenterLH(float l, float r, float b, float t, float zn, float zf);
			Matrix& PerspectiveOffCenterRH(float l, float r, float b, float t, float zn, float zf);
			Matrix& OrthoLH(float w, float	h, float zn, float zf);
			Matrix& OrthoRH(float w, float	h, float zn, float zf);
			Matrix& OrthoOffCenterRH(float l, float r, float b, float t, float zn, float zf);
			Matrix& OrthoOffCenterLH(float l, float r, float b, float t, float zn, float zf);
			Matrix& LookAtLH(Vector3& vecEye, Vector3& vecAt, Vector3& vecUp);
			Matrix& LookAtRH(Vector3& vecEye, Vector3& vecAt, Vector3& vecUp);

			Matrix& Identity();
			bool IsIdentity();
			float Determinant();
			bool Decompose(Vector3& OutScale, Quaternion& OutRotation, Vector3& OutTranslation);
			Matrix& RotationYawPitchRoll(float Yaw, float Pitch, float Roll);
			Matrix& Transformation(const Vector3& ScalingCenter, const Quaternion& ScalingRotation, const Vector3& Scaling, const Vector3& RotationCenter, const Quaternion& Rotation, const Vector3& Translation);
			Matrix& Transformation2D(const Vector2& ScalingCenter, float ScalingRotation, const Vector2& Scaling, const Vector2& RotationCenter, float Rotation, const Vector2& Translation);
			Matrix& AffineTransformation(float Scaling, const Vector3& RotationCenter, const Quaternion& Rotation, const Vector3& Translation);
			Matrix& AffineTransformation2D(float Scaling, const Vector2& RotationCenter, float Rotation, const Vector2& Translation);
			Matrix& Shadow(const Vector4& Light, const Plane& plane);
			Matrix& Reflect(const Plane& plane);
			Matrix& RotationQuaternion(const Quaternion& Q);

			friend Matrix operator * (float f, const Matrix& mat);
		};

#pragma endregion Declared class Matrix

		//---------------------------------------------------------------------------------------------------------
		// Declared class Quaternion
#pragma region Declared class Quaternion

#if (_DRAWING_MODE == _DRAWING_MODE_DX11)
		//typedef XMVECTOR _Quaternion;
		typedef struct _Quaternion {
			union {
				struct {
					float x, y, z, w;
				};
				float v[4];
				__m128 xmm;
			};
		} _Quaternion;
#elif (_DRAWING_MODE == _DRAWING_MODE_DX10) || (_DRAWING_MODE == _DRAWING_MODE_DX9)
		typedef D3DXQUATERNION _Quaternion;
#endif

		class Quaternion :public _Quaternion
		{
		public:
			Quaternion();
			Quaternion(_Quaternion& vec);
			Quaternion(float _x, float _y, float _z, float _w);
			Quaternion(const float* pSrc);

			Quaternion(XMVECTOR& vec);
			operator XMVECTOR();

#if (_DRAWING_MODE == _DRAWING_MODE_DX10) || (_DRAWING_MODE == _DRAWING_MODE_DX9)
			//Quaternion(D3DXQUATERNION& vec);
			operator D3DXQUATERNION*();
#endif

			// casting
			operator float* ();
			operator const float* ();

			// assignment operators
			Quaternion& operator += (const Quaternion& q);
			Quaternion& operator -= (const Quaternion& q);
			Quaternion& operator *= (const Quaternion& q);
			Quaternion& operator *= (float num);
			Quaternion& operator /= (float num);

			// unary operators
			Quaternion operator + () const;
			Quaternion operator - () const;

			// binary operators
			Quaternion operator + (const Quaternion& q) const;
			Quaternion operator - (const Quaternion& q) const;
			Quaternion operator * (const Quaternion& q);
			Quaternion operator * (float num) const;
			Quaternion operator / (float num) const;

			bool operator == (const Quaternion& q) const;
			bool operator != (const Quaternion& q) const;

			float Length() const;
			float LengthSq() const;
			float Dot(const Quaternion& q) const;
			Quaternion& Identity();
			bool IsIdentity() const;
			Quaternion& Conjugate(Quaternion& q);
			Quaternion& ToAxisAngle(Vector3& Axis, float& Angle);

			Quaternion& RotationMatrix(const Matrix& mat);
			Quaternion& RotationAxis(const Vector3& Axis, float Angle);
			Quaternion& RotationYawPitchRoll(float Yaw, float Pitch, float Roll);

			Quaternion& Multiply(const Quaternion& Q1, const Quaternion& Q2);
			Quaternion& Normalize(const Quaternion& Q);
			Quaternion& Inverse(const Quaternion& Q);
			Quaternion& Ln(const Quaternion& Q);
			Quaternion& Exp(const Quaternion& Q);
			Quaternion& Slerp(const Quaternion& Q0, const Quaternion& Q1, float t);
			Quaternion& Squad(const Quaternion& Q0, const Quaternion& Q1, const Quaternion& Q2, const Quaternion& Q3, float t);
			void SquadSetup(Quaternion& AOut, Quaternion& BOut, Quaternion& COut, const Quaternion& q0, const Quaternion& q1, const Quaternion& q2, const Quaternion& q3);
			Quaternion& BaryCentric(const Quaternion& Q1, const Quaternion& Q2, const Quaternion& Q3, float f, float g);

			friend Quaternion operator * (float num, const Quaternion& q);
		};
#pragma endregion Declared class Quaternion

		//---------------------------------------------------------------------------------------------------------
		// Declared class Plane
#pragma region Declared class Plane

		//typedef D3DXPLANE _Plane;
		typedef struct _Plane {
			union {
				struct {
					float	a, b, c, d;
				};
				float v[4];
				__m128 xmm;
			};
		}  _Plane;

		class Plane :public _Plane {
		public:
			Plane();
			Plane(const float* pSrc);
			Plane(float _a, float _b, float _c, float _d);

			Plane(XMVECTOR& vec);
			operator XMVECTOR();

			// casting
			operator float* ();
			operator const float* () const;

			// assignment operators
			Plane& operator *= (float num);
			Plane& operator /= (float num);

			// unary operators
			Plane operator + () const;
			Plane operator - () const;

			// binary operators
			Plane operator * (float num) const;
			Plane operator / (float num) const;

			bool operator == (const Plane& plane) const;
			bool operator != (const Plane& plane) const;

			float Dot(const Vector4& vec);
			float DotCoord(const Vector3& vec);
			float DotNormal(const Vector3& vec);
			Plane& Scale(const Plane& P1, float s);
			Plane& Normalize(const Plane& P1);
			Plane& FromPointNormal(const Vector3& vecPoint, const Vector3& vecNormal);
			Plane& FromPoints(const Vector3& V1, const Vector3& V2, const Vector3& V3);
			Plane& Transform(const Plane& P1, const Matrix& mat);
			Plane* TransformArray(Plane* pOut, UINT OutputStride, const Plane* pSrc, UINT InputStride, UINT PlaneCount, const Matrix& mat);

			friend Plane operator * (float num, const Plane&);
		};
#pragma endregion Declared class Plane

		
#pragma endregion Declared class

		//---------------------------------------------------------------------------------------------------------
#pragma region Definition class

		//---------------------------------------------------------------------------------------------------------
		// Declared class ViewPort
#pragma region Declared class ViewPort
		inline ViewPort::ViewPort() {
		}

		inline ViewPort::ViewPort(float x, float y, float w, float h, float minZ, float maxZ) {
			SetViewPort(x, y, w, h, minZ, maxZ);
		}

		inline ViewPort::ViewPort(Rect& bounds, float minZ, float maxZ) {
#pragma warning(disable : 4244)
			SetViewPort(bounds.left, bounds.top, bounds.Width(), bounds.Height(), minZ, maxZ);
#pragma warning(default : 4244)
		}

		inline void ViewPort::SetViewPort(float x, float y, float w, float h, float minZ, float maxZ) {
#if (_DRAWING_MODE == _DRAWING_MODE_DX11) || (_DRAWING_MODE == _DRAWING_MODE_DX10)
#pragma warning(disable : 4244)
			TopLeftX = x;
			TopLeftY = y;
			Width = w;
			Height = h;
			MinDepth = minZ;
			MaxDepth = maxZ;
#pragma warning(default : 4244)
#elif (_DRAWING_MODE == _DRAWING_MODE_DX9)
			X = (DWORD)x;
			Y = (DWORD)y;
			Width = (DWORD)w;
			Height = (DWORD)h;
			MinZ = minZ;
			MaxZ = maxZ;
#endif
		}

		inline ViewPort::operator _ViewPort* () {
			return this;
		}

		inline bool ViewPort::operator == (const ViewPort& Viewport) const {
#if (_DRAWING_MODE == _DRAWING_MODE_DX11) || (_DRAWING_MODE == _DRAWING_MODE_DX10)
			return TopLeftX == Viewport.TopLeftX &&
				TopLeftY == Viewport.TopLeftY &&
				Width == Viewport.Width &&
				Height == Viewport.Height &&
				MinDepth == Viewport.MinDepth &&
				MaxDepth == Viewport.MaxDepth;
#elif (_DRAWING_MODE == _DRAWING_MODE_DX9)
			return X == Viewport.X &&
				Y == Viewport.Y &&
				Width == Viewport.Width &&
				Height == Viewport.Height &&
				MinZ == Viewport.MinZ &&
				MaxZ == Viewport.MaxZ;
#endif
		}

		inline bool ViewPort::operator != (const ViewPort& Viewport) const {
			return !(*this == Viewport);
		}

		inline Rect& ViewPort::Bounds(Rect& out) {
#if (_DRAWING_MODE == _DRAWING_MODE_DX11) || (_DRAWING_MODE == _DRAWING_MODE_DX10)
#pragma warning(disable : 4244)
			out.left = TopLeftX;
			out.top = TopLeftY;
			out.right = TopLeftX + Width;
			out.bottom = TopLeftY + Height;
#pragma warning(default : 4244)
#elif (_DRAWING_MODE == _DRAWING_MODE_DX9)
			out.left = X;
			out.top = Y;
			out.right = X + Width;
			out.bottom = Y + Height;
#endif
			return out;
		}

#pragma endregion Declared class ViewPort
		//---------------------------------------------------------------------------------------------------------
		// Declared class Color
#pragma region Declared class Color

		inline Color::Color() {
			r = g = b = a = 0.0f;
		}

		inline Color::Color(_Color& c) {
			r = c.r;
			g = c.g;
			b = c.b;
			a = c.a;
		}

		inline Color::Color(float _r, float _g, float _b, float _a) {
			r = _r;
			g = _g;
			b = _b;
			a = _a;
		}

		inline Color::Color(const float* pSrc) {
			xmm = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(pSrc));
		}

		inline Color::Color(const Color& c) {
			r = c.r;
			g = c.g;
			b = c.b;
			a = c.a;
		}

		inline Color::Color(DWORD argb) {
			const float f = 1.0f / 255.0f;
			r = f * (float)(unsigned char)(argb >> 16);
			g = f * (float)(unsigned char)(argb >> 8);
			b = f * (float)(unsigned char)(argb);
			a = f * (float)(unsigned char)(argb >> 24);
		}

#if (_DRAWING_MODE == _DRAWING_MODE_DX9)
		inline Color::Color(D3DCOLORVALUE& c) {
			r = c.r;
			g = c.g;
			b = c.b;
			a = c.a;
		}

		inline Color::operator D3DCOLORVALUE*() {
			return &dxColor;
		}

		inline Color::operator D3DCOLORVALUE() {
			return dxColor;
		}
#endif
		// casting
		inline Color::operator DWORD() const {
			DWORD dwR = r >= 1.0f ? 0xff : r <= 0.0f ? 0x00 : (DWORD)(r * 255.0f + 0.5f);
			DWORD dwG = g >= 1.0f ? 0xff : g <= 0.0f ? 0x00 : (DWORD)(g * 255.0f + 0.5f);
			DWORD dwB = b >= 1.0f ? 0xff : b <= 0.0f ? 0x00 : (DWORD)(b * 255.0f + 0.5f);
			DWORD dwA = a >= 1.0f ? 0xff : a <= 0.0f ? 0x00 : (DWORD)(a * 255.0f + 0.5f);
			return (dwA << 24) | (dwR << 16) | (dwG << 8) | dwB;
		}

		inline Color::operator float* () {
			return reinterpret_cast<float*>(&r);
		}

		inline Color::operator const float* () const {
			return &r;
		}

		// assignment operators
		inline Color& Color::operator += (const Color& c) {
			xmm = XMVectorAdd(xmm, c.xmm);
			return *this;
		}

		inline Color& Color::operator -= (const Color& c) {
			xmm = XMVectorSubtract(xmm, c.xmm);
			return *this;
		}

		inline Color& Color::operator *= (float num) {
			xmm = XMVectorScale(xmm, num);
			return *this;			
		}

		inline Color& Color::operator /= (float num) {
			xmm = XMVectorDivide(xmm, XMVectorReplicate(num));
			return *this;
		}

		// unary operators
		inline Color Color::operator + () const {
			return *this;
		}
		inline Color Color::operator - () const {
			Color ret;
			ret.xmm = XMVectorSubtract(XMVectorReplicate(0.0f), xmm);
			return ret;
		}

		// binary operators
		inline Color Color::operator + (const Color& c) const {
			Color ret;
			ret.xmm = XMVectorAdd(xmm, c.xmm);
			return ret;

		}

		inline Color Color::operator - (const Color& c) const {
			Color ret;
			ret.xmm = XMVectorSubtract(xmm, c.xmm);
			return ret;
		}

		inline Color Color::operator * (float num) const {
			Color ret;
			ret.xmm = XMVectorScale(xmm, num);
			return ret;
		}

		inline Color Color::operator / (float num) const {
			Color ret;
			ret.xmm = XMVectorDivide(xmm, XMVectorReplicate(num));
			return ret;
		}

		inline bool Color::operator == (const Color& c) const {
			return (r == c.r) && (g == c.g) && (b == c.b) && (a == c.a);
		}

		inline bool Color::operator != (const Color& c) const {
			return (r != c.r) || (g != c.g) || (b != c.b) || (a == c.a);
		}

		inline Color& Color::Negative(const Color& C) {
			xmm = XMVectorSubtract(XMVectorReplicate(1.0f), C.xmm);
			return *this;
		}

		inline Color& Color::Add(const Color& C1, const Color& C2) {
			xmm = XMVectorAdd(C1.xmm, C2.xmm);
			return *this;
		}

		inline Color& Color::Subtract(const Color& C1, const Color& C2) {
			xmm = XMVectorSubtract(C1.xmm, C2.xmm);
			return *this;
		}

		inline Color& Color::Scale(const Color& C, float scale) {
			xmm = XMVectorScale(C.xmm, scale);
			return *this;
		}

		inline Color& Color::Modulate(const Color& C1, const Color& C2) {
			xmm = XMVectorMultiply(C1.xmm, C2.xmm);
			return *this;
		}

		inline Color& Color::Lerp(const Color& C1, const Color& C2, float scale) {
			xmm = XMVectorLerp(C1.xmm, C2.xmm, scale);
			return *this;
		}

		inline Color& Color::Glyph(const Color& C) {
			float glyph = ((C.r * 76) + (C.g * 150) + (C.b * 29)) / 255;
			r = g = b = glyph;
			a = a;
			return *this;
		}

		inline Color operator * (float num, const Color& c) {
			Color ret;
			ret.xmm = XMVectorScale(c.xmm, num);
			return ret;
		}

#pragma endregion Definition class Color

		//---------------------------------------------------------------------------------------------------------
		// Definition class Point
#pragma region Definition class Point

		inline Point::Point()	{
			x = 0;
			y = 0;
		}

		inline Point::Point(_Point& pt) {
			x = pt.x;
			y = pt.y;
		}

		// create from two integers
		inline Point::Point(int X, int Y) {
			x = X;
			y = Y;
		}

		// create from another point
		inline Point::Point(Point& pt) {
			x = pt.x;
			y = pt.y;
		}

		// create from a size
		inline Point::Point(Size& size) {
			x = size.cx;
			y = size.cy;
		}

#if defined(_WIN32) || defined(_WIN64)
		inline Point::Point(LPARAM lParam) {
			x = LOWORD(lParam);
			y = HIWORD(lParam);
		}
#endif

		// Operations

		// translate the point
		inline void Point::Offset(int xOffset, int yOffset) {
			x += xOffset;
			y += yOffset;
		}

		inline void Point::Offset(Point& pt) {
			x += pt.x;
			y += pt.y;
		}

		inline void Point::Offset(Size& size) {
			x += size.cx;
			y += size.cy;
		}

		inline void Point::SetPoint(int X, int Y) {
			x = X;
			y = Y;
		}

		inline bool Point::operator == (Point& pt) const {
			return (x == pt.x) && (y == pt.y);
		}

		inline bool Point::operator != (Point& pt) const {
			return (x != pt.x) || (y == pt.y);
		}

		inline void Point::operator += (Size& size) {
			x += size.cx;
			y += size.cy;
		}

		inline void Point::operator -= (Size& size) {
			x -= size.cx;
			y -= size.cy;
		}

		inline void Point::operator += (Point& pt) {
			x += pt.x;
			y += pt.y;
		}

		inline void Point::operator -= (Point& pt) {
			x -= pt.x;
			y -= pt.y;
		}

		// Operators returning CPoint values
		inline Point Point::operator + (Size& size) const {
			return Point(x + size.cx, y + size.cy);
		}
		inline Point Point::operator - (Size& size) const {
			return Point(x - size.cx, y - size.cy);
		}
		inline Point Point::operator - () const {
			return Point(-x, -y);
		}
		inline Point Point::operator + (Point& pt) const {
			return Point(x + pt.x, y + pt.y);
		}

		// Operators returning CSize values
		inline Size Point::operator - (Point& pt) const {
			return Size(x - pt.x, y - pt.y);
		}

		// Operators returning CRect values
		inline Rect Point::operator + (Rect& rc) const {
			return Rect(rc.left + x, rc.top + y, rc.right + x, rc.bottom + y);
		}
		inline Rect Point::operator - (Rect& rc) const {
			return Rect(rc.left - x, rc.top - y, rc.right - x, rc.bottom - y);
		}

#pragma endregion Definition class Point

		//---------------------------------------------------------------------------------------------------------
		// Definition class Size
#pragma region Definition class Size

		// Constructors
		// construct an uninitialized size
		inline Size::Size() {
			cx = 0;
			cy = 0;
		}

		inline Size::Size(_Size& size) {
			cx = size.cx;
			cy = size.cy;
		}

		// create from two integers
		inline Size::Size(int CX, int CY) {
			cx = CX;
			cy = CY;
		}

		// create from another size
		inline Size::Size(Size& size) {
			cx = size.cx;
			cy = size.cy;
		}

		// create from a point
		inline Size::Size(Point& pt) {
			cx = pt.x;
			cy = pt.y;
		}

		// create from a DWORD: cx = LOWORD(dw) cy = HIWORD(dw)
		inline Size::Size(DWORD dwSize) {
			cx = LOWORD(dwSize);
			cy = HIWORD(dwSize);
		}

#if defined(_WIN32) || defined(_WIN64)
		inline Size::Size(SIZE& size) {
			cx = size.cx;
			cy = size.cy;
		}

		inline Size::operator SIZE*() {
			return (SIZE*)this;
		}
#endif

		// Operations
		inline bool Size::operator == (Size& size) const {
			return (cx == size.cx) && (cy == size.cy);
		}

		inline bool Size::operator != (Size& size) const {
			return (cx != size.cx) || (cy == size.cy);
		}

		inline void Size::operator += (Size& size) {
			cx += size.cx;
			cy += size.cy;
		}

		inline void Size::operator -= (Size& size) {
			cx -= size.cx;
			cy -= size.cy;
		}

		inline void Size::SetSize(int CX, int CY) {
			cx = CX;
			cy = CY;
		}

		// Operators returning Size values
		inline Size Size::operator + (Size& size) const {
			return Size(cx + size.cx, cy + size.cy);
		}

		inline Size Size::operator - (Size& size) const {
			return Size(cx - size.cx, cy - size.cy);
		}

		inline Size Size::operator - () const {
			return Size(-cx, -cy);
		}

		// Operators returning Point values
		inline Point Size::operator + (Point& pt) const {
			return Point(cx + pt.x, cy + pt.y);
		}

		inline Point Size::operator - (Point& pt) const {
			return Point(cx - pt.x, cy - pt.y);
		}

		// Operators returning Rect values
		inline Rect Size::operator + (Rect& rc)  {
			return Rect(rc) + *this;
		}

		inline Rect Size::operator - (Rect& rc) {
			return Rect(rc) - *this;
		}

#pragma endregion Definition class Size

		//---------------------------------------------------------------------------------------------------------
		// Definition class Rect
#pragma region Definition class Rect

		inline Rect::Rect() {
			left = top = right = bottom = 0;
		}

		inline Rect::Rect(_Rect& rc) {
			left = rc.left;
			top = rc.top;
			right = rc.right;
			bottom = rc.bottom;
		}

		inline Rect::Rect(int l, int t, int r, int b) {
			left = l;
			top = t;
			right = r;
			bottom = b;
		}

		// copy constructor
		inline Rect::Rect(Rect& rc) {
			CopyRect(rc);
		}

		inline Rect::Rect(Rect* p) {
			CopyRect(*p);
		}

		// from a point and size
		inline Rect::Rect(Point& pt, Size& size) {
			left = pt.x;
			top = pt.y;
			right = pt.x + size.cx;
			bottom = pt.y + size.cy;
		}

		// from two points
		inline Rect::Rect(Point& topLeft, Point& bottomRight) {
			left = topLeft.x;
			top = topLeft.y;
			right = bottomRight.x;
			bottom = bottomRight.y;
		}

#if defined(_WIN32) || defined(_WIN64)
		// from a pointer to another rect
		inline Rect::Rect(LPCRECT lpSrcRect) {
			left = lpSrcRect->left;
			top = lpSrcRect->top;
			right = lpSrcRect->right;
			bottom = lpSrcRect->bottom;
		}

		inline Rect::operator LPRECT() {
			return reinterpret_cast<LPRECT>(this);
		}
		inline Rect::operator LPCRECT() const {
			return reinterpret_cast<LPCRECT>(this);
		}
#endif

		// Attributes (in addition to RECT members)

		// retrieves the width
		inline int Rect::Width() {
			return right - left;
		}

		// returns the height
		inline int Rect::Height() {
			return bottom - top;
		}

		inline Size Rect::getSize() {
			return Size(Width(), Height());
		}

		// reference to the top-left point
		inline Point& Rect::TopLeft() {
			return *((Point*)this);
		}

		// reference to the bottom-right point
		inline Point& Rect::BottomRight() {
			return *((Point*)this + 1);
		}

		// const reference to the top-left point
		inline const Point& Rect::TopLeft() const {
			return *((Point*)this);
		}

		// const reference to the bottom-right point
		inline const Point& Rect::BottomRight() const {
			return *((Point*)this + 1);
		}

		// the geometric center point of the rectangle
		inline Point Rect::CenterPoint() const {
			return Point((left + right) / 2, (top + bottom) / 2);
		}

		// swap the left and right
		inline void Rect::SwapLeftRight() {
			std::swap(left, right);
		}

		// returns true if rectangle has no area
		inline bool Rect::IsRectEmpty() const {
			return (left >= right) || (top >= bottom);
		}

		// returns true if rectangle is at (0,0) and has no area
		inline bool Rect::IsRectNull() const {
			return (left == 0) && (right == 0) && (top == 0) && (bottom == 0);
		}

		// returns true if point is within rectangle
		inline bool Rect::PtInRect(Point& pt) const {
			return (pt.x >= left) && (pt.y >= top) && (pt.x <= right) && (pt.y <= bottom);
		}

		// Operations

		// set rectangle from left, top, right, and bottom
		inline void Rect::SetRect(int x1, int y1, int x2, int y2) {
			left = x1;
			top = y1;
			right = x2;
			bottom = y2;
		}

		inline void Rect::SetRect(Point& topLeft, Point& bottomRight) {
			left = topLeft.x;
			top = topLeft.y;
			right = bottomRight.x;
			bottom = bottomRight.y;
		}

		// empty the rectangle
		inline void Rect::SetRectEmpty() {
			left = top = right = bottom = 0;
		}

		// copy from another rectangle
		inline void Rect::CopyRect(Rect& rc) {
			left = rc.left;
			top = rc.top;
			right = rc.right;
			bottom = rc.bottom;
		}

		// true if exactly the same as another rectangle
		inline bool Rect::EqualRect(Rect& rc) const {
			return (left == rc.left) && (top == rc.top) && (right == rc.right) && (bottom == rc.bottom);
		}

		// Inflate rectangle's width and height by
		// x units to the left and right ends of the rectangle
		// and y units to the top and bottom.
		inline void Rect::InflateRect(int x, int y) {
			left -= x;
			top -= y;
			right += x;
			bottom += y;
		}

		// Inflate rectangle's width and height by
		// size.cx units to the left and right ends of the rectangle
		// and size.cy units to the top and bottom.
		inline void Rect::InflateRect(Size& size) {
			left -= size.cx;
			top -= size.cy;
			right += size.cx;
			bottom += size.cy;
		}

		// Inflate rectangle's width and height by moving individual sides.
		// Left side is moved to the left, right side is moved to the right,
		// top is moved up and bottom is moved down.
		inline void Rect::InflateRect(Rect& rc) {
			left -= rc.left;
			top -= rc.top;
			right += rc.right;
			bottom += rc.bottom;
		}

		inline void Rect::InflateRect(int l, int t, int r, int b) {
			left -= l;
			top -= t;
			right += r;
			bottom += b;
		}

		// deflate the rectangle's width and height without
		// moving its top or left
		inline void Rect::DeflateRect(int x, int y) {
			left += x;
			top += y;
			right -= x;
			bottom -= y;
		}

		inline void Rect::DeflateRect(Size& size) {
			left += size.cx;
			top += size.cy;
			right -= size.cx;
			bottom -= size.cy;
		}

		inline void Rect::DeflateRect(Rect& rc) {
			left += rc.left;
			top += rc.top;
			right -= rc.right;
			bottom -= rc.bottom;
		}

		inline void Rect::DeflateRect(int l, int t, int r, int b) {
			left += l;
			top += t;
			right -= r;
			bottom -= b;
		}

		// translate the rectangle by moving its top and left
		inline void Rect::OffsetRect(int x, int y) {
			left += x;
			top += y;
			right += x;
			bottom += y;
		}

		inline void Rect::OffsetRect(Size& size) {
			left += size.cx;
			top += size.cy;
			right += size.cx;
			bottom += size.cy;
		}

		inline void Rect::OffsetRect(Point& pt) {
			left += pt.x;
			top += pt.y;
			right += pt.x;
			bottom += pt.y;
		}

		inline void Rect::NormalizeRect() {
			if (left > right) {
				std::swap(left, right);
			}
			if (top > bottom) {
				std::swap(top, bottom);
			}
		}

		// absolute position of rectangle
		inline void Rect::MoveToY(int y) {
			bottom = Height() + y;
			top = y;
		}

		inline void Rect::MoveToX(int x) {
			right = Width() + x;
			left = x;
		}

		inline void Rect::MoveToXY(int x, int y) {
			MoveToX(x);
			MoveToY(y);
		}

		inline void Rect::MoveToXY(Point& pt) {
			MoveToX(pt.x);
			MoveToY(pt.y);
		}

		// set this rectangle to intersection of two others
		inline bool Rect::IntersectRect(Rect& rc1, Rect& rc2) {
			bool isIntersect = !(rc2.left > rc1.right ||
				rc2.right < rc1.left ||
				rc2.top > rc1.bottom ||
				rc2.bottom < rc1.top);

			if (isIntersect) {
				left = max(rc1.left, rc2.left);
				top = max(rc1.top, rc2.top);
				right = min(rc1.right, rc2.right);
				bottom = min(rc1.bottom, rc2.bottom);
			}

			return isIntersect;
		}

		// set this rectangle to bounding union of two others
		inline bool Rect::UnionRect(Rect& rc1, Rect& rc2) {
			left = min(rc1.left, rc2.left);
			top = min(rc1.top, rc2.top);
			right = max(rc1.right, rc2.right);
			bottom = max(rc1.bottom, rc2.bottom);
			return (left < right) && (top < bottom);
		}

		// set this rectangle to minimum of two others
		inline bool Rect::SubtractRect(Rect& rc1, Rect& rc2) {
			return ::SubtractRect(*this, rc1, rc2);
		}

		// Additional Operations
		inline void Rect::operator = (Rect& rc) {
			CopyRect(rc);
		}

		inline bool Rect::operator == (Rect& rc) const {
			return EqualRect(rc);
		}

		inline bool Rect::operator != (Rect& rc) const {
			return !EqualRect(rc);
		}

		inline void Rect::operator += (Point& pt) {
			OffsetRect(pt);
		}

		inline void Rect::operator += (Size& size) {
			OffsetRect(size);
		}

		inline void Rect::operator += (Rect& rc) {
			InflateRect(rc);
		}

		inline void Rect::operator -= (Point& pt) {
			OffsetRect(-pt.x, -pt.y);
		}

		inline void Rect::operator -= (Size& size) {
			OffsetRect(-size.cx, -size.cy);
		}

		inline void Rect::operator -= (Rect& rc) {
			DeflateRect(rc);
		}

		inline void Rect::operator &= (Rect& rc) {
			IntersectRect(*this, rc);
		}

		inline void Rect::operator |= (Rect& rc) {
			UnionRect(*this, rc);
		}

		// Operators returning Rect values
		inline Rect Rect::operator + (Point& pt) {
			Rect rc(this);
			rc.OffsetRect(pt);
			return rc;
		}

		inline Rect Rect::operator - (Point& pt) {
			Rect rc(this);
			rc.OffsetRect(-pt.x, -pt.y);
			return rc;
		}

		inline Rect Rect::operator + (Rect& rc)  {
			Rect rc2(this);
			rc2.InflateRect(rc);
			return rc2;
		}

		inline Rect Rect::operator + (Size& size) {
			Rect rc(this);
			rc.OffsetRect(size);
			return rc;
		}

		inline Rect Rect::operator - (Size& size) {
			Rect rc(this);
			rc.OffsetRect(-size.cx, -size.cy);
			return rc;
		}

		inline Rect Rect::operator - (Rect& rc) {
			Rect rc2(this);
			rc2.DeflateRect(rc);
			return rc2;
		}

		inline Rect Rect::operator & (Rect& rc) {
			Rect rc2;
			rc2.IntersectRect(*this, rc);
			return rc2;
		}

		inline Rect Rect::operator | (Rect& rc) {
			Rect rc2;
			rc2.UnionRect(*this, rc);
			return rc2;
		}

		inline Rect Rect::MulDiv(int nMultiplier, int nDivisor) const {
			return Rect(
				::MulDiv(left, nMultiplier, nDivisor),
				::MulDiv(top, nMultiplier, nDivisor),
				::MulDiv(right, nMultiplier, nDivisor),
				::MulDiv(bottom, nMultiplier, nDivisor));
		}

#pragma endregion Definition class Rect

		//---------------------------------------------------------------------------------------------------------
		// Definition class Vector2
#pragma region Definition class Vector2

		inline Vector2::Vector2() {
			x = y = 0.0f;
		}

		inline Vector2::Vector2(_Vector2& vec) {
			x = vec.x;
			y = vec.y;
		}

		inline Vector2::Vector2(float _x, float _y) {
			x = _x;
			y = _y;
		}

		inline Vector2::Vector2(const float* pSrc) {
			x = *pSrc;
			y = pSrc[1];
		}

		inline Vector2::Vector2(Point& pt) {
			x = (float)pt.x;
			y = (float)pt.y;
		}

		inline Vector2::Vector2(__m128 _xmm) {
			XMStoreFloat2(this, _xmm);
		}

		inline Vector2& Vector2::operator = (__m128 _xmm) {
			XMStoreFloat2(this, _xmm);
			return *this;
		}

		inline Vector2::operator __m128 () {
			return XMLoadFloat2(this);
		}

#if (_DRAWING_MODE == _DRAWING_MODE_DX10) || (_DRAWING_MODE == _DRAWING_MODE_DX9)
		inline Vector2::Vector2(D3DXVECTOR2& vec) {
			x = vec.x;
			y = vec.y;
		}

		inline Vector2::operator D3DXVECTOR2*() {
			return reinterpret_cast<D3DXVECTOR2*>(this);
		}
#endif

		// casting
		inline Vector2::operator float* () {
			return &x;
		}

		inline Vector2::operator const float* () {
			return &x;
		}

		// assignment operators (Vector2)
		inline Vector2& Vector2::operator += (const Vector2& vec) {
			XMStoreFloat2(this, XMVectorAdd(XMLoadFloat2(this), XMLoadFloat2(&vec)));
			return *this;
		}

		inline Vector2& Vector2::operator -= (const Vector2& vec) {
			XMStoreFloat2(this, XMVectorSubtract(XMLoadFloat2(this), XMLoadFloat2(&vec)));
			return *this;
		}
		inline Vector2& Vector2::operator *= (const Vector2& vec) {
			XMStoreFloat2(this, XMVectorMultiply(XMLoadFloat2(this), XMLoadFloat2(&vec)));
			return *this;
		}

		inline Vector2& Vector2::operator /= (const Vector2& vec) {
			XMStoreFloat2(this, XMVectorDivide(XMLoadFloat2(this), XMLoadFloat2(&vec)));
			return *this;
		}

		// assignment operators (float)
		inline Vector2& Vector2::operator += (const float num) {
			XMStoreFloat2(this, XMVectorAdd(XMLoadFloat2(this), XMVectorReplicate(num)));
			return *this;
		}

		inline Vector2& Vector2::operator -= (const float num) {
			XMStoreFloat2(this, XMVectorSubtract(XMLoadFloat2(this), XMVectorReplicate(num)));
			return *this;
		}

		inline Vector2& Vector2::operator *= (float num) {
			XMStoreFloat2(this, XMVectorScale(XMLoadFloat2(this), num));
			return *this;
		}

		inline Vector2& Vector2::operator /= (float num) {
			XMStoreFloat2(this, XMVectorDivide(XMLoadFloat2(this), XMVectorReplicate(num)));
			return *this;
		}

		// unary operators
		inline const Vector2& Vector2::operator + () {
			return *this;
		}

		inline Vector2 Vector2::operator - () const {
			Vector2 ret;
			XMStoreFloat2(&ret, XMVectorSubtract(XMVectorZero(), XMLoadFloat2(this)));
			return ret;
		}

		// binary operators
		inline Vector2 Vector2::operator + (Vector2& vec)  {
			Vector2 ret;
			XMStoreFloat2(&ret, XMVectorAdd(XMLoadFloat2(this), XMLoadFloat2(&vec)));
			return ret;
		}

		inline Vector2 Vector2::operator - (Vector2& vec) {
			Vector2 ret;
			XMStoreFloat2(&ret, XMVectorSubtract(XMLoadFloat2(this), XMLoadFloat2(&vec)));
			return ret;
		}

		inline Vector2 Vector2::operator * (float num)  {
			Vector2 ret;
			XMStoreFloat2(&ret, XMVectorScale(XMLoadFloat2(this), num));
			return ret;
		}

		inline Vector2 Vector2::operator / (float num) {
			Vector2 ret;
			XMStoreFloat2(&ret, XMVectorDivide(XMLoadFloat2(this), XMVectorReplicate(num)));
			return ret;
		}

		inline bool Vector2::operator == (const Vector2& vec) const {
			return XMVector2Equal(XMLoadFloat2(this), XMLoadFloat2(&vec));
		}

		inline bool Vector2::operator != (const Vector2& vec) const {
			return XMVector2NotEqual(XMLoadFloat2(this), XMLoadFloat2(&vec));
		}

		inline float Vector2::Length() {
			return XMVectorGetX(XMVector2Length(XMLoadFloat2(this)));
		}

		inline float Vector2::LengthSq() {
			return XMVectorGetX(XMVector2LengthSq(XMLoadFloat2(this)));
		}

		/*
		<summary>向量的內積</summary>
		*/
		inline float Vector2::Dot(const Vector2& vec) {
			return XMVectorGetX(XMVector2Dot(XMLoadFloat2(this), XMLoadFloat2(&vec)));
		}

		/*
		<summary>向量的外積</summary>
		*/
		inline float Vector2::Cross(const Vector2& vec) {
			return XMVectorGetX(XMVector2Cross(XMLoadFloat2(this), XMLoadFloat2(&vec)));
		}

		inline Vector2& Vector2::Add(const Vector2& V1, const Vector2& V2) {
			XMStoreFloat2(this, XMVectorAdd(XMLoadFloat2(&V1), XMLoadFloat2(&V2)));
			return *this;
		}

		inline Vector2& Vector2::Subtract(const Vector2& V1, const Vector2& V2) {
			XMStoreFloat2(this, XMVectorSubtract(XMLoadFloat2(&V1), XMLoadFloat2(&V2)));
			return *this;
		}

		inline Vector2& Vector2::Minimize(const Vector2& V1, const Vector2& V2) {
			XMStoreFloat2(this, XMVectorMin(XMLoadFloat2(&V1), XMLoadFloat2(&V2)));
			return *this;
		}

		inline Vector2& Vector2::Maximize(const Vector2& V1, const Vector2& V2) {
			XMStoreFloat2(this, XMVectorMax(XMLoadFloat2(&V1), XMLoadFloat2(&V2)));
			return *this;
		}

		inline Vector2& Vector2::Scale(const Vector2& V1, float scale) {
			XMStoreFloat2(this, XMVectorScale(XMLoadFloat2(&V1), scale));
			return *this;
		}

		/*
		<summary>向量的線性內插植</summary>
		*/
		inline Vector2& Vector2::Lerp(const Vector2& V1, const Vector2& V2, float scale) {
			XMStoreFloat2(this, XMVectorLerp(XMLoadFloat2(&V1), XMLoadFloat2(&V2), scale));
			return *this;
		}

		inline Vector2& Vector2::Normalize(const Vector2& V1) {
			XMStoreFloat2(this, XMVector2Normalize(XMLoadFloat2(&V1)));
			return *this;
		}

		// Hermite interpolation between Position0, Tangent0 (when t == 0)
		// and Position1, Tangent1 (when t == 1).
		inline Vector2& Vector2::Hermite(const Vector2& Position0, const Vector2& Tangent0, const Vector2& Position1, const Vector2& Tangent1, float t) {
			XMStoreFloat2(this, XMVectorHermite(
				XMLoadFloat2(&Position0),
				XMLoadFloat2(&Tangent0),
				XMLoadFloat2(&Position1),
				XMLoadFloat2(&Tangent1),
				t));
			return *this;
		}

		// CatmullRom interpolation between V1 (when s == 0) and V2 (when s == 1)
		inline Vector2& Vector2::CatmullRom(const Vector2& Position0, const Vector2& Position1, const Vector2& Position2, const Vector2& Position3, float t) {
			XMStoreFloat2(this, XMVectorCatmullRom(
				XMLoadFloat2(&Position0),
				XMLoadFloat2(&Position1),
				XMLoadFloat2(&Position2),
				XMLoadFloat2(&Position3),
				t));
			return *this;
		}

		// Barycentric coordinates.  V1 + f(V2-V1) + g(V3-V1)
		inline Vector2& Vector2::BaryCentric(const Vector2& Position0, const Vector2& Position1, const Vector2& Position2, float f, float g) {
			XMStoreFloat2(this, XMVectorBaryCentric(
				XMLoadFloat2(&Position0),
				XMLoadFloat2(&Position1),
				XMLoadFloat2(&Position2),
				f, g));
			return *this;
		}

		// Transform (x, y, 0, 1) by matrix, project result back into w=1.
		inline Vector2& Vector2::TransformCoord(const Vector2& V1, const Matrix& mat) {
			XMStoreFloat2(this, XMVector2TransformCoord(XMLoadFloat2(&V1), mat));
			return *this;
		}

		// Transform (x, y, 0, 0) by matrix.
		inline Vector2& Vector2::TransformNormal(const Vector2& V1, const Matrix& mat) {
			XMStoreFloat2(this, XMVector2TransformNormal(XMLoadFloat2(&V1), mat));
			return *this;
		}

		// Transform Array (x, y, 0, 1) by matrix, project result back into w=1.
		inline Vector2* Vector2::TransformCoordArray(Vector2* pOut, UINT OutputStride, const Vector2* pSrc, UINT InputStride, UINT VectorCount, const Matrix& mat) {
			XMVector2TransformCoordStream(pOut, OutputStride, pSrc, InputStride, VectorCount, mat);
			return pOut;
		}

		// Transform Array (x, y, 0, 0) by matrix.
		inline Vector2* Vector2::TransformNormalArray(Vector2* pOut, UINT OutputStride, const Vector2* pSrc, UINT InputStride, UINT VectorCount, const Matrix& mat) {
			XMVector2TransformNormalStream(pOut, OutputStride, pSrc, InputStride, VectorCount, mat);
			return pOut;
		}

		inline Vector2& Vector2::Reflect(const Vector2& V1, const Vector2& normal) {
			XMVECTOR XV1 = XMLoadFloat2(&V1);
			XMVECTOR XNormal = XMLoadFloat2(&normal);
			XMVECTOR XNum = XMVectorScale(XMVector2Dot(XV1, XNormal), 2.0f);

			XMStoreFloat2(this, XMVectorSubtract(
				XV1,
				XMVectorMultiply(XNum, XNormal)));
			return *this;
		}

		inline Vector2 operator * (float num, const Vector2& vec) {
			Vector2 ret;
			XMStoreFloat2(&ret, XMVectorScale(XMLoadFloat2(&vec), num));
			return ret;
		}

#pragma endregion Definition class Vector2

		//---------------------------------------------------------------------------------------------------------
		// Definition class Vector3
#pragma region Definition class Vector3

		inline Vector3::Vector3() {
			x = y = z = 0.0f;
		}

		inline Vector3::Vector3(_Vector3& vec) {
			x = vec.x;
			y = vec.y;
			z = vec.z;
		}

		inline Vector3::Vector3(float _x, float _y, float _z) {
			x = _x;
			y = _y;
			z = _z;
		}

		inline Vector3::Vector3(const float* pSrc) {
			x = *pSrc;
			y = pSrc[1];
			z = pSrc[2];
		}

		inline Vector3::Vector3(__m128 _xmm) {
			XMStoreFloat3(this, _xmm);
		}

		inline Vector3& Vector3::operator = (__m128 _xmm) {
			XMStoreFloat3(this, _xmm);
			return *this;
		}

		inline Vector3::operator __m128 () {
			return XMLoadFloat3(this);
		}

#if (_DRAWING_MODE == _DRAWING_MODE_DX10) || (_DRAWING_MODE == _DRAWING_MODE_DX9)
		inline Vector3::Vector3(D3DVECTOR& vec) {
			x = vec.x;
			y = vec.y;
			z = vec.z;
		}

		/*inline Vector3::operator D3DVECTOR () {
			return dxVector;
			}*/
#endif

		// casting
		inline Vector3::operator float* () {
			return &x;
		}

		inline Vector3::operator const float* () {
			return &x;
		}

		// assignment operators (Vector3)
		inline Vector3& Vector3::operator += (const Vector3& vec) {
			XMStoreFloat3(this, XMVectorAdd(XMLoadFloat3(this), XMLoadFloat3(&vec)));
			return *this;
		}

		inline Vector3& Vector3::operator -= (const Vector3& vec) {
			XMStoreFloat3(this, XMVectorSubtract(XMLoadFloat3(this), XMLoadFloat3(&vec)));
			return *this;
		}

		inline Vector3& Vector3::operator *= (const Vector3& vec) {
			XMStoreFloat3(this, XMVectorMultiply(XMLoadFloat3(this), XMLoadFloat3(&vec)));
			return *this;
		}

		inline Vector3& Vector3::operator /= (const Vector3& vec) {
			XMStoreFloat3(this, XMVectorDivide(XMLoadFloat3(this), XMLoadFloat3(&vec)));
			return *this;
		}

		// assignment operators (float)
		inline Vector3& Vector3::operator += (float num) {
			XMStoreFloat3(this, XMVectorAdd(XMLoadFloat3(this), XMVectorReplicate(num)));
			return *this;
		}

		inline Vector3& Vector3::operator -= (float num) {
			XMStoreFloat3(this, XMVectorSubtract(XMLoadFloat3(this), XMVectorReplicate(num)));
			return *this;
		}

		inline Vector3& Vector3::operator *= (float num) {
			XMStoreFloat3(this, XMVectorScale(XMLoadFloat3(this), num));
			return *this;
		}

		inline Vector3& Vector3::operator /= (float num) {
			XMStoreFloat3(this, XMVectorDivide(XMLoadFloat3(this), XMVectorReplicate(num)));
			return *this;
		}

		// unary operators
		inline const Vector3& Vector3::operator + () {
			return *this;
		}

		inline Vector3 Vector3::operator - () {
			Vector3 ret;
			XMStoreFloat3(&ret, XMVectorSubtract(XMVectorZero(), XMLoadFloat3(this)));
			return ret;
		}

		// binary operators
		inline Vector3 Vector3::operator + (const Vector3& vec) {
			Vector3 ret;
			XMStoreFloat3(&ret, XMVectorAdd(XMLoadFloat3(this), XMLoadFloat3(&vec)));
			return ret;
		}

		inline Vector3 Vector3::operator  - (const Vector3& vec) {
			Vector3 ret;
			XMStoreFloat3(&ret, XMVectorSubtract(XMLoadFloat3(this), XMLoadFloat3(&vec)));
			return ret;
		}

		inline Vector3 Vector3::operator * (float num) {
			Vector3 ret;
			XMStoreFloat3(&ret, XMVectorScale(XMLoadFloat3(this), num));
			return ret;
		}

		inline Vector3 Vector3::operator / (float num) {
			Vector3 ret;
			XMStoreFloat3(&ret, XMVectorDivide(XMLoadFloat3(this), XMVectorReplicate(num)));
			return ret;
		}

		inline bool Vector3::operator == (const Vector3& vec) const {
			return XMVector3Equal(XMLoadFloat3(this), XMLoadFloat3(&vec));
		}

		inline bool Vector3::operator != (const Vector3& vec) const {
			return XMVector3NotEqual(XMLoadFloat3(this), XMLoadFloat3(&vec));
		}

		inline float Vector3::Length() {
			return XMVectorGetX(XMVector3Length(XMLoadFloat3(this)));
		}

		inline float Vector3::LengthSq() {
			return XMVectorGetX(XMVector3LengthSq(XMLoadFloat3(this)));
		}

		/*
		<summary>向量的內積</summary>
		*/
		inline float Vector3::Dot(const Vector3& vec) {
			return XMVectorGetX(XMVector3Dot(XMLoadFloat3(this), XMLoadFloat3(&vec)));
		}

		/*
		<summary>向量的外積</summary>
		*/
		inline Vector3& Vector3::Cross(const Vector3& V1, const Vector3& V2) {
			XMStoreFloat3(this, XMVector3Cross(XMLoadFloat3(&V1), XMLoadFloat3(&V2)));
			return *this;
		}

		inline Vector3& Vector3::Add(const Vector3& V1, const Vector3& V2) {
			XMStoreFloat3(this, XMVectorAdd(XMLoadFloat3(&V1), XMLoadFloat3(&V2)));
			return *this;
		}

		inline Vector3& Vector3::Subtract(const Vector3& V1, const Vector3& V2) {
			XMStoreFloat3(this, XMVectorSubtract(XMLoadFloat3(&V1), XMLoadFloat3(&V2)));
			return *this;
		}

		inline Vector3& Vector3::Minimize(const Vector3& V1, const Vector3& V2) {
			XMStoreFloat3(this, XMVectorMin(XMLoadFloat3(&V1), XMLoadFloat3(&V2)));
			return *this;
		}

		inline Vector3& Vector3::Maximize(const Vector3& V1, const Vector3& V2) {
			XMStoreFloat3(this, XMVectorMax(XMLoadFloat3(&V1), XMLoadFloat3(&V2)));
			return *this;
		}

		inline Vector3& Vector3::Scale(const Vector3& V1, float scale) {
			XMStoreFloat3(this, XMVectorScale(XMLoadFloat3(&V1), scale));
			return *this;
		}

		/*
		<summary>向量的線性內插植</summary>
		*/
		inline Vector3& Vector3::Lerp(const Vector3& V1, const Vector3& V2, float scale) {
			XMStoreFloat3(this, XMVectorLerp(XMLoadFloat3(&V1), XMLoadFloat3(&V2), scale));
			return *this;
		}

		inline Vector3& Vector3::Normalize(const Vector3& V1) {
			XMStoreFloat3(this, XMVector3Normalize(XMLoadFloat3(&V1)));
			return *this;
		}

		// Hermite interpolation between Position0, Tangent0 (when t == 0)
		// and Position1, Tangent1 (when t == 1).
		inline Vector3& Vector3::Hermite(const Vector3& Position0, const Vector3& Tangent0, const Vector3& Position1, const Vector3& Tangent1, float t) {
			XMStoreFloat3(this, XMVectorHermite(
				XMLoadFloat3(&Position0),
				XMLoadFloat3(&Tangent0),
				XMLoadFloat3(&Position1),
				XMLoadFloat3(&Tangent1),
				t));
			return *this;
		}

		// CatmullRom interpolation between V1 (when s == 0) and V2 (when s == 1)
		inline Vector3& Vector3::CatmullRom(const Vector3& Position0, const Vector3& Position1, const Vector3& Position2, const Vector3& Position3, float t) {
			XMStoreFloat3(this, XMVectorCatmullRom(
				XMLoadFloat3(&Position0),
				XMLoadFloat3(&Position1),
				XMLoadFloat3(&Position2),
				XMLoadFloat3(&Position3),
				t));
			return *this;
		}

		// Barycentric coordinates.  V1 + f(V2-V1) + g(V3-V1)
		inline Vector3& Vector3::BaryCentric(const Vector3& Position0, const Vector3& Position1, const Vector3& Position2, float f, float g) {
			XMStoreFloat3(this, XMVectorBaryCentric(
				XMLoadFloat3(&Position0),
				XMLoadFloat3(&Position1),
				XMLoadFloat3(&Position2),
				f, g));
			return *this;
		}

		// Transform (x, y, z, 1) by matrix, project result back into w=1.
		inline Vector3& Vector3::TransformCoord(const Vector3& V1, const Matrix& mat) {
			XMStoreFloat3(this, XMVector3TransformCoord(XMLoadFloat3(&V1), mat));
			return *this;
		}

		// Transform (x, y, z, 0) by matrix.  If you transforming a normal by a
		// non-affine matrix, the matrix you pass to this function should be the
		// transpose of the inverse of the matrix you would use to transform a coord.
		inline Vector3& Vector3::TransformNormal(const Vector3& V1, const Matrix& mat) {
			XMStoreFloat3(this, XMVector3TransformNormal(XMLoadFloat3(&V1), mat));
			return *this;
		}

		// Transform Array (x, y, z, 1) by matrix, project result back into w=1.
		inline Vector3* Vector3::TransformCoordArray(Vector3* pOut, UINT OutputStride, const Vector3* pSrc, UINT InputStride, UINT VectorCount, const Matrix& mat) {
			XMVector3TransformCoordStream(pOut, OutputStride, pSrc, InputStride, VectorCount, mat);
			return pOut;
		}

		// Transform (x, y, z, 0) by matrix.  If you transforming a normal by a
		// non-affine matrix, the matrix you pass to this function should be the
		// transpose of the inverse of the matrix you would use to transform a coord.
		inline Vector3* Vector3::TransformNormalArray(Vector3* pOut, UINT OutputStride, const Vector3* pSrc, UINT InputStride, UINT VectorCount, const Matrix& mat) {
			XMVector3TransformNormalStream(pOut, OutputStride, pSrc, InputStride, VectorCount, mat);
			return pOut;
		}

		// Project vector from object space into screen space
		inline Vector3& Vector3::Project(const Vector3& V1, const ViewPort& Viewport, const Matrix& matProjection, const Matrix& matView, const Matrix& matWorld) {
#if (_DRAWING_MODE == _DRAWING_MODE_DX11) || (_DRAWING_MODE == _DRAWING_MODE_DX10)
			XMStoreFloat3(this, XMVector3Project(
				XMLoadFloat3(&V1),
				Viewport.TopLeftX, Viewport.TopLeftY, Viewport.Width, Viewport.Height,
				Viewport.MinDepth, Viewport.MaxDepth,
				matProjection, matView, matWorld));
#elif (_DRAWING_MODE == _DRAWING_MODE_DX9)
#pragma warning(disable : 4244)
			XMStoreFloat3(this, XMVector3Project(
				XMLoadFloat3(&V1),
				Viewport.X, Viewport.Y, Viewport.Width, Viewport.Height,
				Viewport.MinZ, Viewport.MaxZ,
				matProjection, matView, matWorld));
#pragma warning(default : 4244)
#endif
			return *this;
		}

		// Project vector from screen space into object space
		inline Vector3& Vector3::Unproject(const Vector3& V1, const ViewPort& Viewport, const Matrix& matProjection, const Matrix& matView, const Matrix& matWorld) {
#if (_DRAWING_MODE == _DRAWING_MODE_DX11) || (_DRAWING_MODE == _DRAWING_MODE_DX10)
			XMStoreFloat3(this, XMVector3Unproject(
				XMLoadFloat3(&V1),
				Viewport.TopLeftX, Viewport.TopLeftY, Viewport.Width, Viewport.Height,
				Viewport.MinDepth, Viewport.MaxDepth,
				matProjection, matView, matWorld));
#elif (_DRAWING_MODE == _DRAWING_MODE_DX9)
#pragma warning(disable : 4244)
			XMStoreFloat3(this, XMVector3Unproject(
				XMLoadFloat3(&V1),
				Viewport.X, Viewport.Y, Viewport.Width, Viewport.Height,
				Viewport.MinZ, Viewport.MaxZ,
				matProjection, matView, matWorld));
#pragma warning(default : 4244)
#endif	
			return *this;
		}

		// Project vector Array from object space into screen space
		inline Vector3* Vector3::ProjectArray(Vector3* pOut, UINT OutputStride, const Vector3* pSrc, UINT InputStride, UINT VectorCount, const ViewPort& Viewport, const Matrix& matProjection, const Matrix& matView, const Matrix& matWorld) {
#if (_DRAWING_MODE == _DRAWING_MODE_DX11) || (_DRAWING_MODE == _DRAWING_MODE_DX10)
			XMVector3ProjectStream(pOut, OutputStride, pSrc,
				InputStride, VectorCount,
				Viewport.TopLeftX, Viewport.TopLeftY, Viewport.Width, Viewport.Height,
				Viewport.MinDepth, Viewport.MaxDepth,
				matProjection, matView, matWorld);
#elif (_DRAWING_MODE == _DRAWING_MODE_DX9)
#pragma warning(disable : 4244)
			XMVector3ProjectStream(pOut, OutputStride, pSrc,
				InputStride, VectorCount,
				Viewport.X, Viewport.Y, Viewport.Width, Viewport.Height,
				Viewport.MinZ, Viewport.MaxZ,
				matProjection, matView, matWorld);
#pragma warning(default : 4244)
#endif
			return pOut;
		}

		// Project vector Array from screen space into object space
		inline Vector3* Vector3::UnprojectArray(Vector3* pOut, UINT OutputStride, const Vector3* pSrc, UINT InputStride, UINT VectorCount, const ViewPort& Viewport, const Matrix& matProjection, const Matrix& matView, const Matrix& matWorld) {
#if (_DRAWING_MODE == _DRAWING_MODE_DX11) || (_DRAWING_MODE == _DRAWING_MODE_DX10)
			XMVector3UnprojectStream(pOut, OutputStride, pSrc,
				InputStride, VectorCount,
				Viewport.TopLeftX, Viewport.TopLeftY, Viewport.Width, Viewport.Height,
				Viewport.MinDepth, Viewport.MaxDepth,
				matProjection, matView, matWorld);
#elif (_DRAWING_MODE == _DRAWING_MODE_DX9)
#pragma warning(disable : 4244)
			XMVector3UnprojectStream(pOut, OutputStride, pSrc,
				InputStride, VectorCount,
				Viewport.X, Viewport.Y, Viewport.Width, Viewport.Height,
				Viewport.MinZ, Viewport.MaxZ,
				matProjection, matView, matWorld);
#pragma warning(default : 4244)
#endif
			return pOut;
		}

		// Find the intersection between a plane and a line.  If the line is
		// parallel to the plane, NULL is returned.
		inline Vector3& Vector3::IntersectLineIntersectLine(const Plane& P, const Vector3 &LinePoint1, const Vector3 &LinePoint2) {
			XMStoreFloat3(this,	XMPlaneIntersectLine(
				XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&P)),
				XMLoadFloat3(&LinePoint1),
				XMLoadFloat3(&LinePoint2)));
			return *this;
		}

		inline Vector3& Vector3::Reflect(const Vector3& V1, const Vector3& normal) {
			XMVECTOR XV1 = XMLoadFloat3(&V1);
			XMVECTOR XNormal = XMLoadFloat3(&normal);
			XMVECTOR XNum = XMVectorScale(XMVector3Dot(XV1, XNormal), 2.0f);

			XMStoreFloat3(this, XMVectorSubtract(
				XV1,
				XMVectorMultiply(XNum, XNormal)));
			return *this;		
		}

		inline Vector3 operator * (float num, Vector3& vec) {
			Vector3 ret;
			XMStoreFloat3(&ret, XMVectorScale(XMLoadFloat3(&vec), num));
			return ret;
		}

#pragma endregion Definition class Vector3

		//---------------------------------------------------------------------------------------------------------
		// Definition class Vector4
#pragma region Definition class Vector4

		inline Vector4::Vector4() {
			xmm = XMVectorZero();
		}

		inline Vector4::Vector4(_Vector4& vec) {
			xmm = XMVectorSet(vec.x, vec.y, vec.z, vec.w);
		}

		inline Vector4::Vector4(float _x, float _y, float _z, float _w) {
			xmm = XMVectorSet(_x, _y, _z, _w);
		}

		inline Vector4::Vector4(const float* pSrc) {
			xmm = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(pSrc));
		};

		inline Vector4::Vector4(__m128 _xmm) {
			xmm = _xmm;
		}

		inline Vector4& Vector4::operator = (__m128 _xmm) {
			xmm = _xmm;
			return *this;
		}

		inline Vector4::operator __m128 () {
			return xmm;
		}
#if (_DRAWING_MODE == _DRAWING_MODE_DX10) || (_DRAWING_MODE == _DRAWING_MODE_DX9)
		inline Vector4::Vector4(D3DXVECTOR4& vec) {
			x = vec.x;
			y = vec.y;
			z = vec.z;
			w = vec.w;
		}

		inline Vector4::operator D3DXVECTOR4*() {
			return reinterpret_cast<D3DXVECTOR4*>(this);
		}
#endif

		// casting
		inline Vector4::operator float* () {
			return &x;
		}

		inline Vector4::operator const float* () {
			return &x;
		}

		// assignment operators (Vector4)
		inline Vector4& Vector4::operator += (const Vector4& vec) {
			xmm = XMVectorAdd(xmm, vec.xmm);
			return *this;
		}

		inline Vector4& Vector4::operator -= (const Vector4& vec) {
			xmm = XMVectorSubtract(xmm, vec.xmm);
			return *this;
		}

		inline Vector4& Vector4::operator *= (const Vector4& vec) {
			xmm = XMVectorMultiply(xmm, vec.xmm);
			return *this;
		}

		inline Vector4& Vector4::operator /= (const Vector4& vec) {
			xmm = XMVectorDivide(xmm, vec.xmm);
			return *this;
		}

		// assignment operators (float)
		inline Vector4& Vector4::operator += (float num) {
			xmm = XMVectorAdd(xmm, XMVectorReplicate(num));
			return *this;
		}

		inline Vector4& Vector4::operator -= (float num) {
			xmm = XMVectorSubtract(xmm, XMVectorReplicate(num));
			return *this;
		}

		inline Vector4& Vector4::operator *= (float num) {
			xmm = XMVectorMultiply(xmm, XMVectorReplicate(num));
			return *this;
		}

		inline Vector4& Vector4::operator /= (float num) {
			xmm = XMVectorDivide(xmm, XMVectorReplicate(num));
			return *this;
		}

		// unary operators
		inline const Vector4& Vector4::operator + () {
			return *this;
		}

		inline Vector4 Vector4::operator - () const {
			Vector4 ret;
			ret.xmm = XMVectorSubtract(XMVectorZero(), xmm);
			return ret;
		}

		// binary operators
		inline Vector4 Vector4::operator + (const Vector4& vec) const {
			Vector4 ret;
			ret.xmm = XMVectorAdd(xmm, vec.xmm);
			return ret;
		}

		inline Vector4 Vector4::operator - (const Vector4& vec) const {
			Vector4 ret;
			ret.xmm = XMVectorSubtract(xmm, vec.xmm);
			return ret;
		}

		inline Vector4 Vector4::operator * (float num) const {
			Vector4 ret;
			ret.xmm = XMVectorMultiply(xmm, XMVectorReplicate(num));
			return ret;
		}

		inline Vector4 Vector4::operator / (float num) const {
			Vector4 ret;
			ret.xmm = XMVectorDivide(xmm, XMVectorReplicate(num));
			return ret;
		}

		inline bool Vector4::operator == (const Vector4& vec) const {
			return XMVector4Equal(xmm, vec.xmm);
		}

		inline bool Vector4::operator != (const Vector4& vec) const {
			return XMVector4NotEqual(xmm, vec.xmm);
		}

		inline float Vector4::Length() {
			return XMVectorGetX(XMVector4Length(xmm));
		}

		inline float Vector4::LengthSq() {
			return XMVectorGetX(XMVector4LengthSq(xmm));
		}

		/*
		<summary>向量的內積</summary>
		*/
		inline float Vector4::Dot(const Vector4& vec) {
			return XMVectorGetX(XMVector4Dot(xmm, vec.xmm));
		}

		inline Vector4& Vector4::Add(const Vector4& V1, const Vector4& V2) {
			xmm = XMVectorAdd(V1.xmm, V2.xmm);
			return *this;
		}

		inline Vector4& Vector4::Subtract(const Vector4& V1, const Vector4& V2) {
			xmm = XMVectorSubtract(V1.xmm, V2.xmm);
			return *this;
		}

		inline Vector4& Vector4::Minimize(const Vector4& V1, const Vector4& V2) {
			xmm = XMVectorMin(V1.xmm, V2.xmm);
			return *this;
		}

		inline Vector4& Vector4::Maximize(const Vector4& V1, const Vector4& V2) {
			xmm = XMVectorMax(V1.xmm, V2.xmm);
			return *this;
		}

		inline Vector4& Vector4::Scale(const Vector4& V1, float scale) {
			xmm = XMVectorMultiply(V1.xmm, XMVectorReplicate(scale));
			return *this;
		}

		/*
		<summary>向量的線性內插植</summary>
		*/
		inline Vector4& Vector4::Lerp(const Vector4& V1, const Vector4& V2, float scale) {
			xmm = XMVectorLerp(V1.xmm, V2.xmm, scale);
			return *this;
		}

		inline Vector4& Vector4::Normalize(const Vector4& V1) {
			xmm = XMVector4Normalize(V1.xmm);
			return *this;
		}

		// Hermite interpolation between Position0, Tangent0 (when t == 0)
		// and Position1, Tangent1 (when t == 1).
		inline Vector4& Vector4::Hermite(const Vector4& Position0, const Vector4& Tangent0, const Vector4& Position1, const Vector4& Tangent1, float t) {
			xmm = XMVectorHermite(Position0.xmm, Tangent0.xmm, Position1.xmm, Tangent1.xmm, t);
			return *this;
		}

		// CatmullRom interpolation between V1 (when s == 0) and V2 (when s == 1)
		inline Vector4& Vector4::CatmullRom(const Vector4& Position0, const Vector4& Position1, const Vector4& Position2, const Vector4& Position3, float t) {
			xmm = XMVectorCatmullRom(Position0.xmm, Position1.xmm, Position2.xmm, Position3.xmm, t);
			return *this;
		}

		// Barycentric coordinates.  V1 + f(V2-V1) + g(V3-V1)
		inline Vector4& Vector4::BaryCentric(const Vector4& Position0, const Vector4& Position1, const Vector4& Position2, float f, float g) {
			xmm = XMVectorBaryCentric(Position0.xmm, Position1.xmm, Position2.xmm, f, g);
			return *this;
		}

		// Transform (x, y, 0, 1) by matrix.
		inline Vector4& Vector4::Transform(const Vector2& V1, const Matrix& mat) {
			xmm = XMVector2Transform(XMLoadFloat2(&V1), mat);
			return *this;
		}

		// Transform (x, y, z, 1) by matrix.
		inline Vector4& Vector4::Transform(const Vector3& V1, const Matrix& mat) {
			xmm = XMVector3Transform(XMLoadFloat3(&V1), mat);
			return *this; 
		}

		// Transform vector by matrix.
		inline Vector4& Vector4::Transform(const Vector4& V1, const Matrix& mat) {
			xmm = XMVector4Transform(V1.xmm, mat);
			return *this;
		}

		// Transform Array (x, y, 0, 1) by matrix.
		inline Vector4* Vector4::TransformArray(Vector4* pOut, UINT OutputStride, const Vector2* pSrc, UINT InputStride, UINT VectorCount, const Matrix& mat) {
			XMVector2TransformStream(reinterpret_cast<XMFLOAT4*>(pOut), OutputStride, pSrc, InputStride, VectorCount, mat);
			return pOut;
		}

		// Transform Array (x, y, z, 1) by matrix.
		inline Vector4* Vector4::TransformArray(Vector4* pOut, UINT OutputStride, const Vector3* pSrc, UINT InputStride, UINT VectorCount, const Matrix& mat) {
			XMVector3TransformStream(reinterpret_cast<XMFLOAT4*>(pOut), OutputStride, pSrc, InputStride, VectorCount, mat);
			return pOut;
		}

		// Transform vector array by matrix.
		inline Vector4* Vector4::TransformArray(Vector4* pOut, UINT OutputStride, const Vector4* pSrc, UINT InputStride, UINT VectorCount, const Matrix& mat) {
			XMVector4TransformStream(reinterpret_cast<XMFLOAT4*>(pOut), OutputStride, (XMFLOAT4*)pSrc, InputStride, VectorCount, mat);
			return pOut;
		}

		inline Vector4& Vector4::Reflect(const Vector4& V1, const Vector4& normal) {
			XMVECTOR XV1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&V1));
			XMVECTOR XNormal = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&normal));
			XMVECTOR XNum = XMVectorScale(XMVector4Dot(XV1, XNormal), 2.0f);

			XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(this), XMVectorSubtract(
				XV1,
				XMVectorMultiply(XNum, XNormal)));
			return *this;
		}

		inline Vector4 operator * (float num, const Vector4& vec) {
			Vector4 ret;
			ret.xmm = XMVectorScale(vec.xmm, num);
			return ret;
		}

#pragma endregion class Vector4

		//---------------------------------------------------------------------------------------------------------
		// Definition class Matrix
		//
		// References:
		//	1. DirectX SDK(d3dx9math.h and d3dx9math.inl)
		//	2. http ://evanw.github.io/lightgl.js/docs/matrix.html

#pragma region Definition class Matrix

		inline Matrix::Matrix() {
		}

		inline Matrix::Matrix(_Matrix& mat) {
			memcpy(&_11, &mat, sizeof(_Matrix));
		}
		inline Matrix::Matrix(const float* pSrc) {
			memcpy(&_11, pSrc, sizeof(_Matrix));
		}

		inline Matrix::Matrix(const Matrix& mat) {
			memcpy(&_11, &mat, sizeof(_Matrix));
		}

		inline Matrix::Matrix(float f11, float f12, float f13, float f14,
			float f21, float f22, float f23, float f24,
			float f31, float f32, float f33, float f34,
			float f41, float f42, float f43, float f44) {
			*this = XMMatrixSet(
				f11, f12, f13, f14,
				f21, f22, f23, f24,
				f31, f32, f33, f34,
				f41, f42, f43, f44);
		}

		// casting operators
		inline Matrix::operator float* () {
			return (float*)&_11;
		}

		inline Matrix::operator const float* () const {
			return (const float*)&_11;
		}

		// access grants
		inline float& Matrix::operator() (UINT row, UINT col) {
			return m[row][col];
		}

		inline float Matrix::operator() (UINT row, UINT col) const {
			return m[row][col];
		}

		// assignment operators
		inline Matrix& Matrix::operator *= (const Matrix& mat) {
			return Multiply(*this, mat);
		}

		inline Matrix& Matrix::operator += (const Matrix& mat) {
			r[0] = XMVectorAdd(r[0], mat.r[0]);
			r[1] = XMVectorAdd(r[1], mat.r[1]);
			r[2] = XMVectorAdd(r[2], mat.r[2]);
			r[3] = XMVectorAdd(r[3], mat.r[3]);
			return *this;
		}

		inline Matrix& Matrix::operator -= (const Matrix& mat) {
			r[0] = XMVectorSubtract(r[0], mat.r[0]);
			r[1] = XMVectorSubtract(r[1], mat.r[1]);
			r[2] = XMVectorSubtract(r[2], mat.r[2]);
			r[3] = XMVectorSubtract(r[3], mat.r[3]);
			return *this;
		}

		inline Matrix& Matrix::operator *= (float f) {
			XMVECTOR x = XMVectorReplicate(f);
			r[0] = XMVectorMultiply(r[0], x);
			r[1] = XMVectorMultiply(r[1], x);
			r[2] = XMVectorMultiply(r[2], x);
			r[3] = XMVectorMultiply(r[3], x);
			return *this;
		}

		inline Matrix& Matrix::operator /= (float f) {
			XMVECTOR x = XMVectorReplicate(f);
			r[0] = XMVectorDivide(r[0], x);
			r[1] = XMVectorDivide(r[1], x);
			r[2] = XMVectorDivide(r[2], x);
			r[3] = XMVectorDivide(r[3], x);
			return *this;
		}

		// unary operators
		inline Matrix Matrix::operator + () const {
			return *this;
		}

		inline Matrix Matrix::operator - () const {
			Matrix ret;
			XMVECTOR x = XMVectorZero();
			ret.r[0] = XMVectorSubtract(x, r[0]);
			ret.r[1] = XMVectorSubtract(x, r[1]);
			ret.r[2] = XMVectorSubtract(x, r[2]);
			ret.r[3] = XMVectorSubtract(x, r[3]);
			return ret;
		}

		// binary operators
		inline Matrix Matrix::operator * (const Matrix& mat) {
			Matrix ret;
			return ret.Multiply(*this, mat);
		}

		inline Matrix Matrix::operator + (const Matrix& mat) const {
			Matrix ret;
			ret.r[0] = XMVectorAdd(r[0], mat.r[0]);
			ret.r[1] = XMVectorAdd(r[1], mat.r[1]);
			ret.r[2] = XMVectorAdd(r[2], mat.r[2]);
			ret.r[3] = XMVectorAdd(r[3], mat.r[3]);
			return ret;
		}

		inline Matrix Matrix::operator - (const Matrix& mat) const {
			Matrix ret;
			ret.r[0] = XMVectorSubtract(r[0], mat.r[0]);
			ret.r[1] = XMVectorSubtract(r[1], mat.r[1]);
			ret.r[2] = XMVectorSubtract(r[2], mat.r[2]);
			ret.r[3] = XMVectorSubtract(r[3], mat.r[3]);
			return ret;
		}

		inline Matrix Matrix::operator * (float f) const {
			Matrix ret;
			XMVECTOR x = XMVectorReplicate(f);
			ret.r[0] = XMVectorMultiply(r[0], x);
			ret.r[1] = XMVectorMultiply(r[1], x);
			ret.r[2] = XMVectorMultiply(r[2], x);
			ret.r[3] = XMVectorMultiply(r[3], x);
			return ret;
		}

		inline Matrix Matrix::operator / (float f) const {
			Matrix ret;
			XMVECTOR x = XMVectorReplicate(f);
			ret.r[0] = XMVectorDivide(r[0], x);
			ret.r[1] = XMVectorDivide(r[1], x);
			ret.r[2] = XMVectorDivide(r[2], x);
			ret.r[3] = XMVectorDivide(r[3], x);
			return ret;
		}

		inline bool Matrix::operator == (const Matrix& mat) const {
			return (XMVector4Equal(r[0], mat.r[0])
				&& XMVector4Equal(r[1], mat.r[1])
				&& XMVector4Equal(r[2], mat.r[2])
				&& XMVector4Equal(r[3], mat.r[3])) != 0;
		}

		inline bool Matrix::operator != (const Matrix& mat) const {
			return (XMVector4NotEqual(r[0], mat.r[0])
				&& XMVector4NotEqual(r[1], mat.r[1])
				&& XMVector4NotEqual(r[2], mat.r[2])
				&& XMVector4NotEqual(r[3], mat.r[3])) != 0;
		}

		inline Matrix& Matrix::Transpose(const Matrix& mat) {
			*this = XMMatrixTranspose(mat);
			return *this;
		}

		//Determines the product of two matrices.
		inline Matrix& Matrix::Multiply(const Matrix& mat1, const Matrix& mat2) {
			*this = XMMatrixMultiply(mat1, mat2);
			return *this;
		}

		//Calculates the transposed product of two matrices.
		inline Matrix& Matrix::MultiplyTranspose(const Matrix& mat1, const Matrix& mat2) {
			Matrix temp;
			return Transpose(temp.Multiply(mat1, mat2));
		}

		//Calculates the inverse of a matrix.
		inline Matrix& Matrix::Inverse(const Matrix& mat) {
			XMVECTOR det;

			__declspec(align(16))
			Matrix mat0 = mat;

			*this = XMMatrixInverse(&det, mat0);
			return *this;
		}

		// Build a matrix which scales by (sx, sy, sz)
		inline Matrix& Matrix::Scaling(float sx, float sy, float sz) {
			*this = XMMatrixScaling(sx, sy, sz);
			return *this;
		}

		inline Matrix& Matrix::Scaling(const Vector3& vec) {
			*this = XMMatrixScaling(vec.x, vec.y, vec.z);
			return *this;
		}

		// Build a matrix which translates by (x, y, z)
		inline Matrix& Matrix::Translation(float x, float y, float z) {
			*this = XMMatrixTranslation(x, y, z);
			return *this;
		}

		//Returns the matrix transpose of a matrix.
		inline Matrix& Matrix::Translation(const Vector3& vec) {
			*this = XMMatrixTranslation(vec.x, vec.y, vec.z);
			return *this;
		}

		//Build a matrix which rotates around an arbitrary axis
		inline Matrix& Matrix::RotationAxis(const Vector3& vec, float Angle) {
			XMVECTOR a = XMLoadFloat3(&vec);
			*this = XMMatrixRotationAxis(a, Angle);
			return *this;
		}

		//Build a matrix which rotates around the X axis
		inline Matrix& Matrix::RotationX(float angle) {
			*this = XMMatrixRotationX(angle);
			return *this;
		}

		//Build a matrix which rotates around the Y axis
		inline Matrix& Matrix::RotationY(float angle) {
			*this = XMMatrixRotationY(angle);
			return *this;
		}

		//Build a matrix which rotates around the Z axis
		inline Matrix& Matrix::RotationZ(float angle) {
			*this = XMMatrixRotationZ(angle);
			return *this;
		}

		inline Matrix& Matrix::Projection(
			float nearPlane, // Distance to near clipping plane
			float farPlane,  // Distance to far clipping plane
			float fovHoriz,  // Horizontal field of view angle, in radians
			float fovVert)   // Vertical field of view angle, in radians
		{
			float    h, w, Q;

			w = (float)1.0f / tan(fovHoriz * 0.5f);  // 1/tan(x) == cot(x)
			h = (float)1.0f / tan(fovVert * 0.5f);   // 1/tan(x) == cot(x)
			Q = farPlane / (farPlane - nearPlane);

			memset(this, 0, sizeof(Matrix));

			_11 = w;
			_22 = h;
			_33 = Q;
			_43 = -Q * nearPlane;
			_34 = 1;
			return *this;
		}

		inline Matrix& Matrix::PerspectiveLH(float w, float h, float zn, float zf) {
			*this = XMMatrixPerspectiveLH(w, h, zn, zf);
			return *this;
		}

		inline Matrix& Matrix::PerspectiveRH(float w, float h, float zn, float zf) {
			*this = XMMatrixPerspectiveRH(w, h, zn, zf);
			return *this;
		}

		inline Matrix& Matrix::PerspectiveFovLH(float fovY, float Aspect, float zn, float zf) {
			*this = XMMatrixPerspectiveFovLH(fovY, Aspect, zn, zf);
			return *this;
		}

		inline Matrix& Matrix::PerspectiveFovRH(float fovY, float Aspect, float zn, float zf) {
			*this = XMMatrixPerspectiveFovRH(fovY, Aspect, zn, zf);
			return *this;
		}

		inline Matrix& Matrix::PerspectiveOffCenterLH(float l, float r, float b, float t, float zn, float zf) {
			*this = XMMatrixPerspectiveOffCenterLH(l, r, b, t, zn, zf);
			return *this;
		}

		inline Matrix& Matrix::PerspectiveOffCenterRH(float l, float r, float b, float t, float zn, float zf) {
			*this = XMMatrixPerspectiveOffCenterRH(l, r, b, t, zn, zf);
			return *this;
		}

		//Builds a left-handed orthographic projection matrix.
		inline Matrix& Matrix::OrthoLH(float w, float	h, float zn, float zf) {
			*this = XMMatrixOrthographicLH(w, h, zn, zf);
			return *this;
		}

		//Builds a right-handed orthographic projection matrix.
		inline Matrix& Matrix::OrthoRH(float w, float	h, float zn, float zf) {
			*this = XMMatrixOrthographicRH(w, h, zn, zf);
			return *this;
		}

		//Builds a customized, right-handed orthographic projection matrix.
		inline Matrix& Matrix::OrthoOffCenterRH(float l, float r, float b, float t, float zn, float zf) {
			*this = XMMatrixOrthographicOffCenterRH(l, r, b, t, zn, zf);
			return *this;
		}

		//Builds a customized, left-handed orthographic projection matrix.
		inline Matrix& Matrix::OrthoOffCenterLH(float l, float r, float b, float t, float zn, float zf) {
			*this = XMMatrixOrthographicOffCenterLH(l, r, b, t, zn, zf);
			return *this;
		}

		inline Matrix& Matrix::LookAtLH(Vector3& vecEye, Vector3& vecAt, Vector3& vecUp) {
			XMVECTOR eyev = XMLoadFloat3(&vecEye);
			XMVECTOR targetv = XMLoadFloat3(&vecAt);
			XMVECTOR upv = XMLoadFloat3(&vecUp);
			*this = XMMatrixLookAtLH(eyev, targetv, upv);
			return *this;
		}

		inline Matrix& Matrix::LookAtRH(Vector3& vecEye, Vector3& vecAt, Vector3& vecUp) {
			XMVECTOR eyev = XMLoadFloat3(&vecEye);
			XMVECTOR targetv = XMLoadFloat3(&vecAt);
			XMVECTOR upv = XMLoadFloat3(&vecUp);
			*this = XMMatrixLookAtRH(eyev, targetv, upv);
			return *this;
		}

		inline Matrix& Matrix::Identity() {
			*this = XMMatrixIdentity();
			return *this;
		}

		inline bool Matrix::IsIdentity() {
			return XMMatrixIsIdentity(*this);
		}

		inline float Matrix::Determinant() {
			return XMVectorGetX(XMMatrixDeterminant(*this));
		}

		inline bool Matrix::Decompose(Vector3& OutScale, Quaternion& OutRotation, Vector3& OutTranslation) {
			XMVECTOR XOutScale = XMLoadFloat3(&OutScale);
			XMVECTOR XOutRotQuat = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&OutRotation));
			XMVECTOR XOutTrans = XMLoadFloat3(&OutTranslation);
			return XMMatrixDecompose(&XOutScale, &XOutRotQuat, &XOutTrans, *this);
		}

		inline Matrix& Matrix::RotationYawPitchRoll(float Yaw, float Pitch, float Roll)  {
			*this = XMMatrixRotationRollPitchYaw(Pitch, Yaw, Roll);
			return *this;
		}

		inline Matrix& Matrix::Transformation(const Vector3& ScalingCenter, const Quaternion& ScalingRotation, const Vector3& Scaling, const Vector3& RotationCenter, const Quaternion& Rotation, const Vector3& Translation)  {
			*this = XMMatrixTransformation(
				XMLoadFloat3(&ScalingCenter),
				XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&ScalingRotation)),
				XMLoadFloat3(&Scaling),
				XMLoadFloat3(&RotationCenter),
				XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&Rotation)),
				XMLoadFloat3(&Translation));
			return *this;
		}

		inline Matrix& Matrix::Transformation2D(const Vector2& ScalingCenter, float ScalingRotation, const Vector2& Scaling, const Vector2& RotationCenter, float Rotation, const Vector2& Translation) {
			*this = XMMatrixTransformation2D(
				XMLoadFloat2(&ScalingCenter),
				ScalingRotation,
				XMLoadFloat2(&Scaling),
				XMLoadFloat2(&RotationCenter),
				Rotation,
				XMLoadFloat2(&Translation));
			return *this;
		}

		inline Matrix& Matrix::AffineTransformation(float Scaling, const Vector3& RotationCenter, const Quaternion& Rotation, const Vector3& Translation) {
			*this = XMMatrixAffineTransformation(
				XMVectorReplicate(Scaling),
				XMLoadFloat3(&RotationCenter),
				XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&Rotation)),
				XMLoadFloat3(&Translation));
			return *this;
		}

		inline Matrix& Matrix::AffineTransformation2D(float Scaling, const Vector2& RotationCenter, float Rotation, const Vector2& Translation) {
			*this = XMMatrixAffineTransformation2D(
				XMVectorReplicate(Scaling),
				XMLoadFloat2(&RotationCenter),
				Rotation,
				XMLoadFloat2(&Translation));
			return *this;
		}

		inline Matrix& Matrix::Shadow(const Vector4& Light, const Plane& plane) {
			*this = XMMatrixShadow(plane.xmm, Light.xmm);
			return *this;
		}

		inline Matrix& Matrix::Reflect(const Plane& plane) {
			*this = XMMatrixReflect(plane.xmm);
			return *this;
		}

		inline Matrix& Matrix::RotationQuaternion(const Quaternion& Q) {
			*this = XMMatrixRotationQuaternion(const_cast<Quaternion&>(Q));
			return *this;
		}

		inline Matrix operator * (float f, const Matrix& mat) {
			Matrix ret;
			XMVECTOR x = XMVectorReplicate(f);
			ret.r[0] = XMVectorMultiply(mat.r[0], x);
			ret.r[1] = XMVectorMultiply(mat.r[1], x);
			ret.r[2] = XMVectorMultiply(mat.r[2], x);
			ret.r[3] = XMVectorMultiply(mat.r[3], x);
			return ret;
		}

#pragma endregion Definition class Matrix

		//---------------------------------------------------------------------------------------------------------
		// Definition class Quaternion
#pragma region Definition class Quaternion

		inline Quaternion::Quaternion() {
			x = y = z = w = 0.0f;
		}

		inline Quaternion::Quaternion(_Quaternion& vec) {
			x = vec.x;
			y = vec.y;
			z = vec.z;
			w = vec.w;
		}

		inline Quaternion::Quaternion(float _x, float _y, float _z, float _w) {
			x = _x;
			y = _y;
			z = _z;
			w = _w;
		}

		inline Quaternion::Quaternion(const float* pSrc) {
			x = pSrc[0];
			y = pSrc[1];
			z = pSrc[2];
			w = pSrc[3];
		}

		inline Quaternion::Quaternion(XMVECTOR& vec) {
			XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(this), vec);
		}

		inline Quaternion::operator XMVECTOR() {
			return XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(this));
		}

#if (_DRAWING_MODE == _DRAWING_MODE_DX10) || (_DRAWING_MODE == _DRAWING_MODE_DX9)
		inline Quaternion::operator D3DXQUATERNION*() {
			return reinterpret_cast<D3DXQUATERNION*>(this);
		}
#endif

		// casting
		inline Quaternion::operator float* () {
			return &x;
		}

		inline Quaternion::operator const float* () {
			return &x;
		}

		// assignment operators
		inline Quaternion& Quaternion::operator += (const Quaternion& q) {
			XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(this), XMVectorAdd(
				XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(this)),
				XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&q))
				));
			return *this;
		}

		inline Quaternion& Quaternion::operator -= (const Quaternion& q) {
			XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(this), XMVectorSubtract(
				XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(this)),
				XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&q))
				));
			return *this;
		}

		inline Quaternion& Quaternion::operator *= (const Quaternion& q) {
			return Multiply(*this, q);
		}

		inline Quaternion& Quaternion::operator *= (float num) {
			XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(this), XMVectorMultiply(
				XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(this)),
				XMVectorReplicate(num)
				));
			return *this;
		}

		inline Quaternion& Quaternion::operator /= (float num) {
			XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(this), XMVectorDivide(
				XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(this)),
				XMVectorReplicate(num)
				));
			return *this;
		}

		// unary operators
		inline Quaternion Quaternion::operator + () const {
			return *this;
		}

		inline Quaternion Quaternion::operator - () const {
			Quaternion ret;
			XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&ret), XMVectorSubtract(
				XMVectorZero(),
				XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(this))
				));
			return ret;
		}

		// binary operators
		inline Quaternion Quaternion::operator + (const Quaternion& q) const {
			return Quaternion(x + q.x, y + q.y, z + q.z, w + q.w);
			Quaternion ret;
			XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&ret), XMVectorAdd(
				XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(this)),
				XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&q))
				));
			return ret;
		}

		inline Quaternion Quaternion::operator - (const Quaternion& q) const {
			Quaternion ret;
			XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&ret), XMVectorSubtract(
				XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(this)),
				XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&q))
				));
			return ret;
		}

		inline Quaternion Quaternion::operator * (const Quaternion& q) {
			Quaternion ret;
			return ret.Multiply(*this, q);
		}

		inline Quaternion Quaternion::operator * (float num) const {
			Quaternion ret;
			XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&ret), XMVectorMultiply(
				XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(this)),
				XMVectorReplicate(num)
				));
			return ret;
		}

		inline Quaternion Quaternion::operator / (float num) const {
			Quaternion ret;
			XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&ret), XMVectorDivide(
				XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(this)),
				XMVectorReplicate(num)
				));
			return ret;
		}

		inline bool Quaternion::operator == (const Quaternion& q) const {
			return XMQuaternionEqual(
				XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(this)),
				XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&q))
				);
		}

		inline bool Quaternion::operator != (const Quaternion& q) const {
			return XMQuaternionNotEqual(
				XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(this)),
				XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&q))
				);
		}

		inline float Quaternion::Length() const {
			return XMVectorGetX(XMQuaternionLength(
				XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(this))
				));
		}

		// Length squared, or "norm"
		inline float Quaternion::LengthSq() const {
			return XMVectorGetX(XMQuaternionLengthSq(
				XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(this))
				));
		}

		inline float Quaternion::Dot(const Quaternion& q) const {
			return XMVectorGetX(XMQuaternionDot(
				XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(this)),
				(Quaternion&)q));
		}

		// (0, 0, 0, 1)
		inline Quaternion& Quaternion::Identity() {
			*this = XMQuaternionIdentity();
			return *this;
		}

		inline bool Quaternion::IsIdentity() const {
			return XMQuaternionIsIdentity(
				XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(this))
				);
		}

		// (-x, -y, -z, w)
		inline Quaternion& Quaternion::Conjugate(Quaternion& q) {
			*this = XMQuaternionConjugate(q);
			return *this;
		}

		// Compute a quaternin's axis and angle of rotation. Expects unit quaternions.
		inline Quaternion& Quaternion::ToAxisAngle(Vector3& Axis, float& Angle) {
			XMVECTOR retAxis;
			XMQuaternionToAxisAngle(&retAxis, &Angle, *this);
			XMStoreFloat3(&Axis, retAxis);
			return *this;
		}

		// Build a quaternion from a rotation matrix.
		inline Quaternion& Quaternion::RotationMatrix(const Matrix& mat) {
			*this = XMQuaternionRotationMatrix(mat);
			return *this;
		}

		// Rotation about arbitrary axis.
		inline Quaternion& Quaternion::RotationAxis(const Vector3& Axis, float Angle) {
			XMVECTOR xAxis = XMLoadFloat3(&Axis);
			*this = XMQuaternionRotationAxis(xAxis, Angle);
			return *this;
		}

		// Yaw around the Y axis, a pitch around the X axis,
		// and a roll around the Z axis.
		inline Quaternion& Quaternion::RotationYawPitchRoll(float Yaw, float Pitch, float Roll) {
			*this = XMQuaternionRotationRollPitchYaw(Pitch, Yaw, Roll);
			return *this;
		}

		// Quaternion multiplication.  The result represents the rotation Q2
		// followed by the rotation Q1.  (Out = Q2 * Q1)
		inline Quaternion& Quaternion::Multiply(const Quaternion& Q1, const Quaternion& Q2) {
			*this = XMQuaternionMultiply((Quaternion&)Q1, (Quaternion&)Q2);
			return *this;
		}

		inline Quaternion& Quaternion::Normalize(const Quaternion& Q) {
			*this = XMQuaternionNormalize(XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&Q)));
			return *this;
		}

		// Conjugate and re-norm
		inline Quaternion& Quaternion::Inverse(const Quaternion& Q) {
			*this = XMQuaternionInverse(XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&Q)));
			return *this;
		}

		// Expects unit quaternions.
		// if q = (cos(theta), sin(theta) * v); ln(q) = (0, theta * v)
		inline Quaternion& Quaternion::Ln(const Quaternion& Q) {
			*this = XMQuaternionLn(XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&Q)));
			return *this;
		}

		// Expects pure quaternions. (w == 0)  w is ignored in calculation.
		// if q = (0, theta * v); exp(q) = (cos(theta), sin(theta) * v)
		inline Quaternion& Quaternion::Exp(const Quaternion& Q) {
			*this = XMQuaternionExp(XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&Q)));
			return *this;
		}

		// Spherical linear interpolation between Q1 (t == 0) and Q2 (t == 1).
		// Expects unit quaternions.
		inline Quaternion& Quaternion::Slerp(const Quaternion& Q0, const Quaternion& Q1, float t) {
			*this = XMQuaternionSlerp(
				XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&Q0)),
				XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&Q1)),
				t);
			return *this;
		}

		// Spherical quadrangle interpolation.
		// Slerp(Slerp(Q1, C, t), Slerp(A, B, t), 2t(1-t))
		inline Quaternion& Quaternion::Squad(const Quaternion& Q0, const Quaternion& Q1, const Quaternion& Q2, const Quaternion& Q3, float t) {
			*this = XMQuaternionSquad(
				XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&Q0)),
				XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&Q1)),
				XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&Q2)),
				XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&Q3)),
				t);
			return *this;
		}

		// Setup control points for spherical quadrangle interpolation
		// from Q1 to Q2.  The control points are chosen in such a way
		// to ensure the continuity of tangents with adjacent segments.
		inline void Quaternion::SquadSetup(Quaternion& AOut, Quaternion& BOut, Quaternion& COut, const Quaternion& q0, const Quaternion& q1, const Quaternion& q2, const Quaternion& q3) {
			XMVECTOR QA, QB, QC;
			XMQuaternionSquadSetup(
				&QA, &QB, &QC,
				XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&q0)),
				XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&q1)),
				XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&q2)),
				XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&q3))
				);
			XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&AOut), QA);
			XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&BOut), QB);
			XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&COut), QC);
		}

		// Barycentric interpolation.
		// Slerp(Slerp(Q1, Q2, f+g), Slerp(Q1, Q3, f+g), g/(f+g))
		inline Quaternion& Quaternion::BaryCentric(const Quaternion& Q1, const Quaternion& Q2, const Quaternion& Q3, float f, float g) {
			*this = XMQuaternionBaryCentric(
				XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&Q1)),
				XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&Q2)),
				XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&Q3)),
				f, g);
			return *this;
		}
		
		inline Quaternion operator * (float num, const Quaternion& q) {
			Quaternion ret;
			XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&ret), XMVectorMultiply(
				XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&q)),
				XMVectorReplicate(num)
				));
			return ret;
		}

#pragma endregion Definition class Quaternion

		//---------------------------------------------------------------------------------------------------------
		// Definition class Plane
#pragma region Definition class Plane
		inline Plane::Plane() {
		}

		inline Plane::Plane(const float* pSrc) {
			XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(this),
				XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(pSrc)));
		}

		inline Plane::Plane(float _a, float _b, float _c, float _d) {
			a = _a;
			b = _b;
			c = _c;
			d = _d;
		}

		inline Plane::Plane(XMVECTOR& vec) {
			XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(this), vec);
		}

		inline Plane::operator XMVECTOR() {
			return XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(this));
		}

		// casting
		inline Plane::operator float* () {
			return &a;
		}

		inline Plane::operator const float* () const {
			return &a;
		}

		// assignment operators
		inline Plane& Plane::operator *= (float num) {
			XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(this), XMVectorMultiply(
				XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(this)),
				XMVectorReplicate(num)
				));
			return *this;
		}

		inline Plane& Plane::operator /= (float num) {
			XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(this), XMVectorDivide(
				XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(this)),
				XMVectorReplicate(num)
				));
			return *this;
		}

		// unary operators
		inline Plane Plane::operator + () const {
			return *this;
		}

		inline Plane Plane::operator - () const {
			Plane ret;
			XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&ret), XMVectorSubtract(
				XMVectorZero(),
				XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(this))
				));
			return ret;
		}

		// binary operators
		inline Plane Plane::operator * (float num) const {
			Plane ret;
			XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&ret), XMVectorMultiply(
				XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(this)),
				XMVectorReplicate(num)
				));
			return ret;
		}

		inline Plane Plane::operator / (float num) const {
			Plane ret;
			XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&ret), XMVectorDivide(
				XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(this)),
				XMVectorReplicate(num)
				));
			return ret;
		}

		inline bool Plane::operator == (const Plane& p) const {
			return XMPlaneEqual(
				XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(this)),
				XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&p))
				);
		}

		inline bool Plane::operator != (const Plane& p) const {
			return XMPlaneNotEqual(
				XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(this)),
				XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&p))
				);
		}

		// ax + by + cz + dw
		inline float Plane::Dot(const Vector4& vec) {
			return XMVectorGetX(XMPlaneDot(
				XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(this)),
				XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&vec))
				));
		}

		// ax + by + cz + d
		inline float Plane::DotCoord(const Vector3& vec) {
			return XMVectorGetX(XMPlaneDotCoord(
				XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(this)),
				XMLoadFloat3(&vec)
				));
		}

		// ax + by + cz
		inline float Plane::DotNormal(const Vector3& vec) {
			return XMVectorGetX(XMPlaneDotNormal(
				XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(this)),
				XMLoadFloat3(&vec)
				));
		}

		inline Plane& Plane::Scale(const Plane& P1, float s) {
			XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(this), XMVectorScale(
				XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&P1)),
				s));
			return *this;
		}

		// Normalize plane (so that |a,b,c| == 1)
		inline Plane& Plane::Normalize(const Plane& P1) {
			XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(this), XMPlaneNormalize(
				XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&P1))
				));
			return *this;
		}		

		// Construct a plane from a point and a normal
		inline Plane& Plane::FromPointNormal(const Vector3& vecPoint, const Vector3& vecNormal) {
			XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(this), XMPlaneFromPointNormal(
				XMLoadFloat3(&vecPoint),
				XMLoadFloat3(&vecNormal)
				));
			return *this;
		}

		// Construct a plane from 3 points
		inline Plane& Plane::FromPoints(const Vector3& vec1, const Vector3& vec2, const Vector3& vec3) {
			XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(this), XMPlaneFromPoints(
				XMLoadFloat3(&vec1),
				XMLoadFloat3(&vec2),
				XMLoadFloat3(&vec3)
				));
			return *this;
		}

		// Transform a plane by a matrix.  The vector (a,b,c) must be normal.
		// M should be the inverse transpose of the transformation desired.
		inline Plane& Plane::Transform(const Plane& P1, const Matrix& mat) {
			XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(this), XMPlaneTransform(
				XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&P1)),
				mat));
			return *this;
		}

		// Transform an array of planes by a matrix.  The vectors (a,b,c) must be normal.
		// M should be the inverse transpose of the transformation desired.
		inline Plane* Plane::TransformArray(Plane* pOut, UINT OutputStride, const Plane* pSrc, UINT InputStride, UINT PlaneCount, const Matrix& mat) {
			XMPlaneTransformStream(
				reinterpret_cast<XMFLOAT4*>(pOut),
				OutputStride,
				reinterpret_cast<const XMFLOAT4*>(pSrc),
				InputStride,
				PlaneCount,
				mat);

			return pOut;
		}

		inline Plane operator * (float num, const Plane& p) {
			Plane ret;
			XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&ret), XMVectorMultiply(
				XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&p)),
				XMVectorReplicate(num)
				));
			return ret;
		}

#pragma endregion Definition class Plane

#pragma endregion Definition class
		//---------------------------------------------------------------------------------------------------------
	} /* namespace Drawing */
} /* namespace System */

#pragma warning(default:4800)
#pragma warning(default:4316)


#include "System.Drawing.Colors.h"
#endif /*  SYSTEM_DRAWING_MATH_H_ */

#endif