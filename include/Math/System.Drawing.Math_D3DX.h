/*
* System.Drawing.Math_D3DX.h
*
* Code Status: Drafts
*  Created on: Taiwan
*      Author: player
*
*  References:
*	1. DirectX 9 SDK (d3dx9math.h and d3dx9math.inl)
*	2. DirectX 10 SDK (d3dx10math.h and d3dx10math.inl)
*	3. DirectXMath
*/

#include "../stdafx.h"
#if (_MATH_TYPE == _MATH_TYPE_D3DX)

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

#include "../System.Math.h"
#pragma warning(disable : 4316)

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

#if (_DRAWING_MODE == _DRAWING_MODE_DX10) ||  (_DRAWING_MODE == _DRAWING_MODE_DX9)
		typedef D3DXCOLOR _Color;
#else
		typedef struct _Color {
			union {
				struct {
					float r, g, b, a;
				};
				float v[4];
			};
		} _Color;
#endif

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

#if (_DRAWING_MODE == _DRAWING_MODE_DX10) ||  (_DRAWING_MODE == _DRAWING_MODE_DX9)
			operator D3DXCOLOR* ();
			operator const D3DXCOLOR* ();
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

			friend Color operator * (float num, const Color& C);
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

#if (_DRAWING_MODE == _DRAWING_MODE_DX10) ||  (_DRAWING_MODE == _DRAWING_MODE_DX9)
		typedef D3DXVECTOR2 _Vector2;
#else
		typedef struct _Vector2 {
			union {
				struct {
					float	x, y;
				};
				float v[2];
			};
		} _Vector2;
#endif

		class Vector2 :public _Vector2
		{
		public:
			Vector2();
			Vector2(_Vector2& vec);
			Vector2(float _x, float _y);
			Vector2(const float* pSrc);
			Vector2(Point& pt);

#if (_DRAWING_MODE == _DRAWING_MODE_DX10) || (_DRAWING_MODE == _DRAWING_MODE_DX9)
			operator D3DXVECTOR2*();
			operator const D3DXVECTOR2*();
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

#if (_DRAWING_MODE == _DRAWING_MODE_DX10) ||  (_DRAWING_MODE == _DRAWING_MODE_DX9)
		typedef D3DXVECTOR3 _Vector3;
#else
		typedef struct _Vector3 {
			union {
				struct {
					float	x, y, z;
				};
				float v[3];
			};
		} _Vector3;
#endif

		class Vector3 :public _Vector3
		{
		public:
			Vector3();
			Vector3(_Vector3& vec);
			Vector3(float _x, float _y, float _z);
			Vector3(const float* pSrc);

#if (_DRAWING_MODE == _DRAWING_MODE_DX10) || (_DRAWING_MODE == _DRAWING_MODE_DX9)
			operator D3DXVECTOR3*();
			operator const D3DXVECTOR3*();

			//Vector3(D3DVECTOR& vec);
			//operator D3DVECTOR ();
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
			Vector3& IntersectLine(const Plane& P, const Vector3 &LinePoint1, const Vector3 &LinePoint2);

			Vector3& Reflect(const Vector3& V1, const Vector3& normal);

			friend Vector3 operator * (float num, Vector3& vec);
		};
#pragma endregion Declared class Vector3

		//---------------------------------------------------------------------------------------------------------
		// Declared class Vector4
#pragma region Declared class Vector4

#if (_DRAWING_MODE == _DRAWING_MODE_DX10) ||  (_DRAWING_MODE == _DRAWING_MODE_DX9)
		typedef D3DXVECTOR4 _Vector4;
#else
		typedef struct _Vector4 {
			union {
				struct {
					float	x, y, z, w;
				};
				float v[4];
			};
		} _Vector4;
#endif

		class Vector4 :public _Vector4
		{
		public:
			Vector4();
			Vector4(_Vector4& vec);
			Vector4(float _x, float _y, float _z, float _w);
			Vector4(const float* pSrc);

#if (_DRAWING_MODE == _DRAWING_MODE_DX10) || (_DRAWING_MODE == _DRAWING_MODE_DX9)
			operator D3DXVECTOR4*();
			operator const D3DXVECTOR4*();
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
		//	1. http ://evanw.github.io/lightgl.js/docs/matrix.html
#pragma region Declared class Matrix

#if (_DRAWING_MODE == _DRAWING_MODE_DX10) ||  (_DRAWING_MODE == _DRAWING_MODE_DX9)
		typedef D3DXMATRIX _Matrix;
#else
		typedef struct _Matrix {
			union {
				struct {
					float	_11, _12, _13, _14;
					float	_21, _22, _23, _24;
					float	_31, _32, _33, _34;
					float	_41, _42, _43, _44;
				};
				float m[4][4];
			};
		} _Matrix;
#endif

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

			operator D3DMATRIX* ();
			operator const D3DMATRIX* ();
			operator D3DXMATRIX* ();
			operator const D3DXMATRIX* ();

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

#if (_DRAWING_MODE == _DRAWING_MODE_DX10) ||  (_DRAWING_MODE == _DRAWING_MODE_DX9)
		typedef D3DXQUATERNION _Quaternion;
#else
		typedef struct _Quaternion {
			union {
				struct {
					float	x, y, z, w;
				};
				float v[4];
			};
		}  _Quaternion;
#endif

		class Quaternion :public _Quaternion
		{
		public:
			Quaternion();
			Quaternion(_Quaternion& vec);
			Quaternion(float _x, float _y, float _z, float _w);
			Quaternion(const float* pSrc);

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

#if (_DRAWING_MODE == _DRAWING_MODE_DX10) ||  (_DRAWING_MODE == _DRAWING_MODE_DX9)
		typedef D3DXPLANE _Plane;
#else
		typedef struct _Plane {
			union {
				struct {
					float	a, b, c, d;
				};
				float v[4];
			};
		}  _Plane;
#endif

		class Plane :public _Plane {
			Plane();
			Plane(const float* pSrc);
			Plane(float _a, float _b, float _c, float _d);

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
			out.left = TopLeftX;
			out.top = TopLeftY;
			out.right = TopLeftX + Width;
			out.bottom = TopLeftY + Height;
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

		inline Color::Color(_Color& C) {
			r = C.r;
			g = C.g;
			b = C.b;
			a = C.a;
		}

		inline Color::Color(float _r, float _g, float _b, float _a) {
			r = _r;
			g = _g;
			b = _b;
			a = _a;
		}

		inline Color::Color(const float* pSrc) {
			r = *pSrc;
			g = pSrc[1];
			b = pSrc[2];
			a = pSrc[3];
		}

		inline Color::Color(const Color& C) {
			r = C.r;
			g = C.g;
			b = C.b;
			a = C.a;
		}

		inline Color::Color(DWORD argb) {
			const float f = 1.0f / 255.0f;
			r = f * (float)(unsigned char)(argb >> 16);
			g = f * (float)(unsigned char)(argb >> 8);
			b = f * (float)(unsigned char)(argb);
			a = f * (float)(unsigned char)(argb >> 24);
		}

#if (_DRAWING_MODE == _DRAWING_MODE_DX10) ||  (_DRAWING_MODE == _DRAWING_MODE_DX9)
		inline Color::operator D3DXCOLOR* () {
			return this;
		}

		inline Color::operator const D3DXCOLOR* () {
			return this;
		}
#endif


#if (_DRAWING_MODE == _DRAWING_MODE_DX9)
		inline Color::Color(D3DCOLORVALUE& c) {
			r = c.r;
			g = c.g;
			b = c.b;
			a = c.a;
		}

		inline Color::operator D3DCOLORVALUE*() {
			return (D3DCOLORVALUE*)this;
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
		inline Color& Color::operator += (const Color& C) {
			r += C.r;
			g += C.g;
			b += C.b;
			a += C.a;
			return *this;
		}

		inline Color& Color::operator -= (const Color& C) {
			r -= C.r;
			g -= C.g;
			b -= C.b;
			a -= C.a;
			return *this;
		}

		inline Color& Color::operator *= (float num) {
			r *= num;
			g *= num;
			b *= num;
			a *= num;
			return *this;
		}

		inline Color& Color::operator /= (float num) {
			float inv = 1.0f / num;
			r *= inv;
			g *= inv;
			b *= inv;
			a *= inv;
			return *this;
		}

		// unary operators
		inline Color Color::operator + () const {
			return *this;
		}
		inline Color Color::operator - () const {
			return Color(-r, -g, -b, -a);
		}

		// binary operators
		inline Color Color::operator + (const Color& C) const {
			return Color(r + C.r, g + C.g, b + C.b, a + C.a);
		}

		inline Color Color::operator - (const Color& C) const {
			return Color(r - C.r, g - C.g, b - C.b, a - C.a);
		}

		inline Color Color::operator * (float num) const {
			return Color(r * num, g * num, b * num, a * num);
		}

		inline Color Color::operator / (float num) const {
			const float inv = 1.0f / num;
			return Color(r * inv, g * inv, b * inv, a * inv);
		}

		inline bool Color::operator == (const Color& c) const {
			return (r == c.r) && (g == c.g) && (b == c.b) && (a == c.a);
		}

		inline bool Color::operator != (const Color& C) const {
			return (r != C.r) || (g != C.g) || (b != C.b) || (a == C.a);
		}

		inline Color& Color::Negative(const Color& C) {
			D3DXColorNegative(this, &C);
			return *this;
		}

		inline Color& Color::Add(const Color& C1, const Color& C2) {
			D3DXColorAdd(this, &C1, &C2);
			return *this;
		}

		inline Color& Color::Subtract(const Color& C1, const Color& C2) {
			D3DXColorSubtract(this, &C1, &C2);
			return *this;
		}

		inline Color& Color::Scale(const Color& C, float scale) {
			D3DXColorScale(this, &C, scale);
			return *this;
		}

		inline Color& Color::Modulate(const Color& C1, const Color& C2) {
			D3DXColorModulate(this, &C1, &C2);
			return *this;
		}

		inline Color& Color::Lerp(const Color& C1, const Color& C2, float scale) {
			D3DXColorLerp(this, &C1, &C2, scale);
			return *this;
		}

		inline Color& Color::Glyph(const Color& C) {
			float glyph = ((C.r * 76) + (C.g * 150) + (C.b * 29)) / 255;
			r = g = b = glyph;
			a = a;
			return *this;
		}

		inline Color operator * (float num, const Color& c) {
			return Color(c.r * num, c.g * num, c.b * num, c.a * num);
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
#pragma warning(disable : 4800)
			return (bool)::SubtractRect(*this, rc1, rc2);
#pragma warning(default : 4800)
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

#if (_DRAWING_MODE == _DRAWING_MODE_DX10) || (_DRAWING_MODE == _DRAWING_MODE_DX9)
		inline Vector2::operator D3DXVECTOR2*() {
			return reinterpret_cast<D3DXVECTOR2*>(this);
		}

		inline Vector2::operator const D3DXVECTOR2*() {
			return reinterpret_cast<const D3DXVECTOR2*>(this);
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
			x += vec.x;
			y += vec.y;
			return *this;
		}

		inline Vector2& Vector2::operator -= (const Vector2& vec) {
			x -= vec.x;
			y -= vec.y;
			return *this;
		}
		inline Vector2& Vector2::operator *= (const Vector2& vec) {
			x *= vec.x;
			y *= vec.y;
			return *this;
		}

		inline Vector2& Vector2::operator /= (const Vector2& vec) {
			x /= vec.x;
			y /= vec.y;
			return *this;
		}

		// assignment operators (float)
		inline Vector2& Vector2::operator += (const float num) {
			x += num;
			y += num;
			return *this;
		}

		inline Vector2& Vector2::operator -= (const float num) {
			x -= num;
			y -= num;
			return *this;
		}

		inline Vector2& Vector2::operator *= (float num) {
			x *= num;
			y *= num;
			return *this;
		}

		inline Vector2& Vector2::operator /= (float num) {
			const float inv = 1.0f / num;
			x *= inv;
			y *= inv;
			return *this;
		}

		// unary operators
		inline const Vector2& Vector2::operator + () {
			return *this;
		}

		inline Vector2 Vector2::operator - () const {
			return Vector2(-x, -y);
		}

		// binary operators
		inline Vector2 Vector2::operator + (Vector2& vec)  {
			return Vector2(x + vec.x, y + vec.y);
		}

		inline Vector2 Vector2::operator - (Vector2& vec) {
			return Vector2(x - vec.x, y - vec.y);
		}

		inline Vector2 Vector2::operator * (float num)  {
			return Vector2(x*num, y*num);
		}

		inline Vector2 Vector2::operator / (float num) {
			const float inv = 1.0f / num;
			return Vector2(x*inv, y*inv);
		}

		inline bool Vector2::operator == (const Vector2& vec) const {
			return (x == vec.x) && (y == vec.y);
		}

		inline bool Vector2::operator != (const Vector2& vec) const {
			return (x != vec.x) || (y != vec.y);
		}

		inline float Vector2::Length() {
			return D3DXVec2Length(this);
		}

		inline float Vector2::LengthSq() {
			return D3DXVec2LengthSq(this);
		}

		/*
		<summary>向量的內積</summary>
		*/
		inline float Vector2::Dot(const Vector2& vec) {
			return D3DXVec2Dot(this, (Vector2&)vec);
		}

		/*
		<summary>向量的外積</summary>
		*/
		inline float Vector2::Cross(const Vector2& vec) {
			return D3DXVec2CCW(this, (Vector2&)vec);
		}

		inline Vector2& Vector2::Add(const Vector2& V1, const Vector2& V2) {
			D3DXVec2Add(this, &V1, &V2);
			return *this;
		}

		inline Vector2& Vector2::Subtract(const Vector2& V1, const Vector2& V2) {
			D3DXVec2Subtract(this, &V1, &V2);
			return *this;
		}

		inline Vector2& Vector2::Minimize(const Vector2& V1, const Vector2& V2) {
			D3DXVec2Minimize(this, &V1, &V2);
			return *this;
		}

		inline Vector2& Vector2::Maximize(const Vector2& V1, const Vector2& V2) {
			D3DXVec2Maximize(this, &V1, &V2);
			return *this;
		}

		inline Vector2& Vector2::Scale(const Vector2& V1, float scale) {
			D3DXVec2Scale(this, &V1, scale);
			return *this;
		}

		/*
		<summary>向量的線性內插植</summary>
		*/
		inline Vector2& Vector2::Lerp(const Vector2& V1, const Vector2& V2, float scale) {
			D3DXVec2Lerp(this, &V1, &V2, scale);
			return *this;
		}

		inline Vector2& Vector2::Normalize(const Vector2& V1) {
			D3DXVec2Normalize(this, &V1);
			return *this;
		}

		// Hermite interpolation between Position0, Tangent0 (when t == 0)
		// and Position1, Tangent1 (when t == 1).
		inline Vector2& Vector2::Hermite(const Vector2& Position0, const Vector2& Tangent0, const Vector2& Position1, const Vector2& Tangent1, float t) {
			D3DXVec2Hermite(this, &Position0, &Tangent0, &Position1, &Tangent1, t);
			return *this;
		}

		// CatmullRom interpolation between V1 (when s == 0) and V2 (when s == 1)
		inline Vector2& Vector2::CatmullRom(const Vector2& Position0, const Vector2& Position1, const Vector2& Position2, const Vector2& Position3, float t) {
			D3DXVec2CatmullRom(this, &Position0, &Position1, &Position2, &Position3, t);
			return *this;
		}

		// Barycentric coordinates.  V1 + f(V2-V1) + g(V3-V1)
		inline Vector2& Vector2::BaryCentric(const Vector2& Position0, const Vector2& Position1, const Vector2& Position2, float f, float g) {
			D3DXVec2BaryCentric(this, &Position0, &Position1, &Position2, f, g);
			return *this;
		}

		// Transform (x, y, 0, 1) by matrix, project result back into w=1.
		inline Vector2& Vector2::TransformCoord(const Vector2& V1, const Matrix& mat) {
			D3DXVec2TransformCoord(this, &V1, &mat);
			return *this;
		}

		// Transform (x, y, 0, 0) by matrix.
		inline Vector2& Vector2::TransformNormal(const Vector2& V1, const Matrix& mat) {
			D3DXVec2TransformNormal(this, &V1, &mat);
			return *this;
		}

		// Transform Array (x, y, 0, 1) by matrix, project result back into w=1.
		inline Vector2* Vector2::TransformCoordArray(Vector2* pOut, UINT OutputStride, const Vector2* pSrc, UINT InputStride, UINT VectorCount, const Matrix& mat) {
			D3DXVec2TransformCoordArray(pOut, OutputStride, pSrc, InputStride, &mat, VectorCount);
			return pOut;
		}

		// Transform Array (x, y, 0, 0) by matrix.
		inline Vector2* Vector2::TransformNormalArray(Vector2* pOut, UINT OutputStride, const Vector2* pSrc, UINT InputStride, UINT VectorCount, const Matrix& mat) {
			D3DXVec2TransformNormalArray(pOut, OutputStride, pSrc, InputStride, &mat, VectorCount);
			return pOut;
		}

		inline Vector2& Vector2::Reflect(const Vector2& V1, const Vector2& normal) {
			float num = const_cast<Vector2&>(V1).Dot(normal) * 2.0f;
			x = V1.x - num * normal.x;
			y = V1.y - num * normal.y;
			return *this;
		}

		inline Vector2 operator * (float num, const Vector2& vec) {
			return Vector2(num * vec.x, num * vec.y);
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

#if (_DRAWING_MODE == _DRAWING_MODE_DX10) || (_DRAWING_MODE == _DRAWING_MODE_DX9)
		inline Vector3::operator D3DXVECTOR3*() {
			return this;
		}

		inline Vector3::operator const D3DXVECTOR3*() {
			return this;
		}

		/*	inline Vector3::Vector3(D3DVECTOR& vec) {
				dxVector = vec;
				}

				inline Vector3::operator D3DVECTOR () {
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
			x += vec.x;
			y += vec.y;
			z += vec.z;
			return *this;
		}

		inline Vector3& Vector3::operator -= (const Vector3& vec) {
			x -= vec.x;
			y -= vec.y;
			z -= vec.z;
			return *this;
		}

		inline Vector3& Vector3::operator *= (const Vector3& vec) {
			x *= vec.x;
			y *= vec.y;
			z *= vec.z;
			return *this;
		}

		inline Vector3& Vector3::operator /= (const Vector3& vec) {
			x /= vec.x;
			y /= vec.y;
			z /= vec.z;
			return *this;
		}

		// assignment operators (float)
		inline Vector3& Vector3::operator += (float num) {
			x += num;
			y += num;
			z += num;
			return *this;
		}

		inline Vector3& Vector3::operator -= (float num) {
			x -= num;
			y -= num;
			z -= num;
			return *this;
		}

		inline Vector3& Vector3::operator *= (float num) {
			x *= num;
			y *= num;
			z *= num;
			return *this;
		}

		inline Vector3& Vector3::operator /= (float num) {
			const float inv = 1.0f / num;
			x *= inv;
			y *= inv;
			z *= inv;
			return *this;
		}

		// unary operators
		inline const Vector3& Vector3::operator + () {
			return *this;
		}

		inline Vector3 Vector3::operator - () {
			return Vector3(-x, -y, -z);
		}

		// binary operators
		inline Vector3 Vector3::operator + (const Vector3& vec) {
			return Vector3(x + vec.x, y + vec.y, z + vec.z);
		}

		inline Vector3 Vector3::operator  - (const Vector3& vec) {
			return Vector3(x - vec.x, y - vec.y, z - vec.z);
		}

		inline Vector3 Vector3::operator * (float num) {
			return Vector3(x*num, y*num, z*num);
		}

		inline Vector3 Vector3::operator / (float num) {
			const float inv = 1.0f / num;
			return Vector3(x*inv, y*inv, z*inv);
		}

		inline bool Vector3::operator == (const Vector3& vec) const {
			return (x == vec.x) && (y == vec.y) && (z == vec.z);
		}

		inline bool Vector3::operator != (const Vector3& vec) const {
			return (x != vec.x) || (y != vec.y) || (z != vec.z);
		}

		inline float Vector3::Length() {
			return D3DXVec3Length(this);
		}

		inline float Vector3::LengthSq() {
			return D3DXVec3LengthSq(this);
		}

		/*
		<summary>向量的內積</summary>
		*/
		inline float Vector3::Dot(const Vector3& vec) {
			return D3DXVec3Dot(this, const_cast<Vector3&>(vec));
		}

		/*
		<summary>向量的外積</summary>
		*/
		inline Vector3& Vector3::Cross(const Vector3& V1, const Vector3& V2) {
			D3DXVec3Cross(this, &V1, &V2);
			return *this;
		}

		inline Vector3& Vector3::Add(const Vector3& V1, const Vector3& V2) {
			D3DXVec3Add(this, &V1, &V2);
			return *this;
		}

		inline Vector3& Vector3::Subtract(const Vector3& V1, const Vector3& V2) {
			D3DXVec3Subtract(this, &V1, &V2);
			return *this;
		}

		inline Vector3& Vector3::Minimize(const Vector3& V1, const Vector3& V2) {
			D3DXVec3Minimize(this, &V1, &V2);
			return *this;
		}

		inline Vector3& Vector3::Maximize(const Vector3& V1, const Vector3& V2) {
			D3DXVec3Maximize(this, &V1, &V2);
			return *this;
		}

		inline Vector3& Vector3::Scale(const Vector3& V1, float scale) {
			D3DXVec3Scale(this, &V1, scale);
			return *this;
		}

		/*
		<summary>向量的線性內插植</summary>
		*/
		inline Vector3& Vector3::Lerp(const Vector3& V1, const Vector3& V2, float scale) {
			D3DXVec3Lerp(this, &V1, &V2, scale);
			return *this;
		}

		inline Vector3& Vector3::Normalize(const Vector3& V1) {
			D3DXVec3Normalize(this, &V1);
			return *this;
		}

		// Hermite interpolation between Position0, Tangent0 (when t == 0)
		// and Position1, Tangent1 (when t == 1).
		inline Vector3& Vector3::Hermite(const Vector3& Position0, const Vector3& Tangent0, const Vector3& Position1, const Vector3& Tangent1, float t) {
			D3DXVec3Hermite(this, &Position0, &Tangent0, &Position1, &Tangent1, t);
			return *this;
		}

		// CatmullRom interpolation between V1 (when s == 0) and V2 (when s == 1)
		inline Vector3& Vector3::CatmullRom(const Vector3& Position0, const Vector3& Position1, const Vector3& Position2, const Vector3& Position3, float t) {
			D3DXVec3CatmullRom(this, &Position0, &Position1, &Position2, &Position3, t);
			return *this;
		}

		// Barycentric coordinates.  V1 + f(V2-V1) + g(V3-V1)
		inline Vector3& Vector3::BaryCentric(const Vector3& Position0, const Vector3& Position1, const Vector3& Position2, float f, float g) {
			D3DXVec3BaryCentric(this, &Position0, &Position1, &Position2, f, g);
			return *this;
		}

		// Transform (x, y, z, 1) by matrix, project result back into w=1.
		inline Vector3& Vector3::TransformCoord(const Vector3& V1, const Matrix& mat) {
			D3DXVec3TransformCoord(this, &V1, &mat);
			return *this;
		}

		// Transform (x, y, z, 0) by matrix.  If you transforming a normal by a
		// non-affine matrix, the matrix you pass to this function should be the
		// transpose of the inverse of the matrix you would use to transform a coord.
		inline Vector3& Vector3::TransformNormal(const Vector3& V1, const Matrix& mat) {
			D3DXVec3TransformNormal(this, &V1, &mat);
			return *this;
		}

		// Transform Array (x, y, z, 1) by matrix, project result back into w=1.
		inline Vector3* Vector3::TransformCoordArray(Vector3* pOut, UINT OutputStride, const Vector3* pSrc, UINT InputStride, UINT VectorCount, const Matrix& mat) {
			D3DXVec3TransformCoordArray(pOut, OutputStride, pSrc, InputStride, &mat, VectorCount);
			return pOut;
		}

		// Transform (x, y, z, 0) by matrix.  If you transforming a normal by a
		// non-affine matrix, the matrix you pass to this function should be the
		// transpose of the inverse of the matrix you would use to transform a coord.
		inline Vector3* Vector3::TransformNormalArray(Vector3* pOut, UINT OutputStride, const Vector3* pSrc, UINT InputStride, UINT VectorCount, const Matrix& mat) {
			D3DXVec3TransformNormalArray(pOut, OutputStride, pSrc, InputStride, &mat, VectorCount);
			return pOut;
		}

		// Project vector from object space into screen space
		inline Vector3& Vector3::Project(const Vector3& V1, const ViewPort& Viewport, const Matrix& matProjection, const Matrix& matView, const Matrix& matWorld) {
			D3DXVec3Project(this, &V1, &Viewport, &matProjection, &matView, &matWorld);
			return *this;
		}

		// Project vector from screen space into object space
		inline Vector3& Vector3::Unproject(const Vector3& V1, const ViewPort& Viewport, const Matrix& matProjection, const Matrix& matView, const Matrix& matWorld) {
			D3DXVec3Unproject(this, &V1, &Viewport, &matProjection, &matView, &matWorld);
			return *this;
		}

		// Project vector Array from object space into screen space
		inline Vector3* Vector3::ProjectArray(Vector3* pOut, UINT OutputStride, const Vector3* pSrc, UINT InputStride, UINT VectorCount, const ViewPort& Viewport, const Matrix& matProjection, const Matrix& matView, const Matrix& matWorld) {
			D3DXVec3ProjectArray(pOut, OutputStride, pSrc, InputStride, &Viewport, &matProjection, &matView, &matWorld, VectorCount);
			return pOut;
		}

		// Project vector Array from screen space into object space
		Vector3* Vector3::UnprojectArray(Vector3* pOut, UINT OutputStride, const Vector3* pSrc, UINT InputStride, UINT VectorCount, const ViewPort& Viewport, const Matrix& matProjection, const Matrix& matView, const Matrix& matWorld) {
			D3DXVec3UnprojectArray(pOut, OutputStride, pSrc, InputStride, &Viewport, &matProjection, &matView, &matWorld, VectorCount);
			return pOut;
		}

		inline Vector3& Vector3::Reflect(const Vector3& V1, const Vector3& normal) {
			float num = const_cast<Vector3&>(V1).Dot(normal) * 2.0f;
			x = V1.x - num * normal.x;
			y = V1.y - num * normal.y;
			z = V1.z - num * normal.z;
			return *this;
		}

		// Find the intersection between a plane and a line.  If the line is
		// parallel to the plane, NULL is returned.
		inline Vector3& Vector3::IntersectLineIntersectLine(const Plane& P, const Vector3 &LinePoint1, const Vector3 &LinePoint2) {
			D3DXPlaneIntersectLine(this, &P, &LinePoint1, &LinePoint2);
			return *this;
		}

		inline Vector3 operator * (float num, Vector3& vec) {
			return Vector3(num * vec.x, num * vec.y, num * vec.z);
		}

#pragma endregion Definition class Vector3

		//---------------------------------------------------------------------------------------------------------
		// Definition class Vector4
#pragma region Definition class Vector4

		inline Vector4::Vector4() {
			x = y = z = w = 0.0f;
		}

		inline Vector4::Vector4(_Vector4& vec) {
			x = vec.x;
			y = vec.y;
			z = vec.z;
			w = vec.w;
		}

		inline Vector4::Vector4(float _x, float _y, float _z, float _w) {
			x = _x;
			y = _y;
			z = _z;
			w = _w;
		}

		inline Vector4::Vector4(const float* pSrc) {
			x = *pSrc;
			y = pSrc[1];
			z = pSrc[2];
			w = pSrc[3];
		};

#if (_DRAWING_MODE == _DRAWING_MODE_DX10) || (_DRAWING_MODE == _DRAWING_MODE_DX9)
		inline Vector4::operator D3DXVECTOR4*() {
			return reinterpret_cast<D3DXVECTOR4*>(this);
		}

		inline Vector4::operator const D3DXVECTOR4*() {
			return reinterpret_cast<const D3DXVECTOR4*>(this);
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
			x += vec.x;
			y += vec.y;
			z += vec.z;
			w += vec.w;
			return *this;
		}

		inline Vector4& Vector4::operator -= (const Vector4& vec) {
			x -= vec.x;
			y -= vec.y;
			z -= vec.z;
			w -= vec.w;
			return *this;
		}

		inline Vector4& Vector4::operator *= (const Vector4& vec) {
			x *= vec.x;
			y *= vec.y;
			z *= vec.z;
			w *= vec.w;
			return *this;
		}

		inline Vector4& Vector4::operator /= (const Vector4& vec) {
			x /= vec.x;
			y /= vec.y;
			z /= vec.z;
			w /= vec.w;
			return *this;
		}

		// assignment operators (float)
		inline Vector4& Vector4::operator += (float num) {
			x += num;
			y += num;
			z += num;
			w += num;
			return *this;
		}

		inline Vector4& Vector4::operator -= (float num) {
			x -= num;
			y -= num;
			z -= num;
			w -= num;
			return *this;
		}

		inline Vector4& Vector4::operator *= (float num) {
			x *= num;
			y *= num;
			z *= num;
			w *= num;
			return *this;
		}

		inline Vector4& Vector4::operator /= (float num) {
			const float inv = 1.0f / num;
			x *= inv;
			y *= inv;
			z *= inv;
			w *= inv;
			return *this;
		}

		// unary operators
		inline const Vector4& Vector4::operator + () {
			return *this;
		}

		inline Vector4 Vector4::operator - () const {
			return Vector4(-x, -y, -z, -w);
		}

		// binary operators
		inline Vector4 Vector4::operator + (const Vector4& vec) const {
			return Vector4(x + vec.x, y + vec.y, z + vec.z, w + vec.w);
		}

		inline Vector4 Vector4::operator - (const Vector4& vec) const {
			return Vector4(x - vec.x, y - vec.y, z - vec.z, w - vec.w);
		}

		inline Vector4 Vector4::operator * (float num) const {
			return Vector4(x*num, y*num, z*num, w*num);
		}

		inline Vector4 Vector4::operator / (float num) const {
			const float inv = 1.0f / num;
			return Vector4(x*inv, y*inv, z*inv, w*inv);
		}

		inline bool Vector4::operator == (const Vector4& vec) const {
			return (x == vec.x) && (y == vec.y) && (z == vec.z) && (w == vec.w);
		}
		inline bool Vector4::operator != (const Vector4& vec) const {
			return (x != vec.x) || (y != vec.y) || (z != vec.z) || (w != vec.w);
		}

		inline float Vector4::Length() {
			return D3DXVec4Length(this);
		}

		inline float Vector4::LengthSq() {
			return D3DXVec4LengthSq(this);;
		}

		/*
		<summary>向量的內積</summary>
		*/
		inline float Vector4::Dot(const Vector4& vec) {
			return D3DXVec4Dot(this, (Vector4&)vec);
		}

		inline Vector4& Vector4::Add(const Vector4& V1, const Vector4& V2) {
			D3DXVec4Add(this, &V1, &V1);
			return *this;
		}

		inline Vector4& Vector4::Subtract(const Vector4& V1, const Vector4& V2) {
			D3DXVec4Subtract(this, &V1, &V1);
			return *this;
		}

		inline Vector4& Vector4::Minimize(const Vector4& V1, const Vector4& V2) {
			D3DXVec4Minimize(this, &V1, &V1);
			return *this;
		}

		inline Vector4& Vector4::Maximize(const Vector4& V1, const Vector4& V2) {
			D3DXVec4Maximize(this, &V1, &V2);
			return *this;
		}

		inline Vector4& Vector4::Scale(const Vector4& V1, float scale) {
			D3DXVec4Scale(this, &V1, scale);
			return *this;
		}

		/*
		<summary>向量的線性內插植</summary>
		*/
		inline Vector4& Vector4::Lerp(const Vector4& V1, const Vector4& V2, float scale) {
			D3DXVec4Lerp(this, &V1, &V2, scale);
			return *this;
		}

		inline Vector4& Vector4::Normalize(const Vector4& V1) {
			D3DXVec4Normalize(this, &V1);
			return *this;
		}

		// Hermite interpolation between Position0, Tangent0 (when t == 0)
		// and Position1, Tangent1 (when t == 1).
		inline Vector4& Vector4::Hermite(const Vector4& Position0, const Vector4& Tangent0, const Vector4& Position1, const Vector4& Tangent1, float t) {
			D3DXVec4Hermite(this, &Position0, &Tangent0, &Position1, &Tangent1, t);
			return *this;
		}

		// CatmullRom interpolation between V1 (when s == 0) and V2 (when s == 1)
		inline Vector4& Vector4::CatmullRom(const Vector4& Position0, const Vector4& Position1, const Vector4& Position2, const Vector4& Position3, float t) {
			D3DXVec4CatmullRom(this, &Position0, &Position1, &Position2, &Position3, t);
			return *this;
		}

		// Barycentric coordinates.  V1 + f(V2-V1) + g(V3-V1)
		inline Vector4& Vector4::BaryCentric(const Vector4& Position0, const Vector4& Position1, const Vector4& Position2, float f, float g) {
			D3DXVec4BaryCentric(this, &Position0, &Position1, &Position2, f, g);
			return *this;
		}

		// Transform (x, y, 0, 1) by matrix.
		inline Vector4& Vector4::Transform(const Vector2& V1, const Matrix& mat) {
			D3DXVec2Transform(this, &V1, &mat);
			return *this;
		}

		// Transform (x, y, z, 1) by matrix.
		inline Vector4& Vector4::Transform(const Vector3& V1, const Matrix& mat) {
			D3DXVec3Transform(this, &V1, &mat);
			return *this;
		}

		// Transform vector by matrix.
		inline Vector4& Vector4::Transform(const Vector4& V1, const Matrix& mat) {
			D3DXVec4Transform(this, &V1, &mat);
			return *this;
		}

		// Transform Array (x, y, 0, 1) by matrix.
		inline Vector4* Vector4::TransformArray(Vector4* pOut, UINT OutputStride, const Vector2* pSrc, UINT InputStride, UINT VectorCount, const Matrix& mat) {
			D3DXVec2TransformArray(pOut, OutputStride, pSrc, InputStride, &mat, VectorCount);
			return pOut;
		}

		// Transform Array (x, y, z, 1) by matrix.
		inline Vector4* Vector4::TransformArray(Vector4* pOut, UINT OutputStride, const Vector3* pSrc, UINT InputStride, UINT VectorCount, const Matrix& mat) {
			D3DXVec3TransformArray(pOut, OutputStride, pSrc, InputStride, &mat, VectorCount);
			return pOut;
		}

		// Transform vector array by matrix.
		inline Vector4* Vector4::TransformArray(Vector4* pOut, UINT OutputStride, const Vector4* pSrc, UINT InputStride, UINT VectorCount, const Matrix& mat) {
			D3DXVec4TransformArray(pOut, OutputStride, pSrc, InputStride, &mat, VectorCount);
			return pOut;
		}

		inline Vector4& Vector4::Reflect(const Vector4& V1, const Vector4& normal) {
			float num = const_cast<Vector4&>(V1).Dot(normal) * 2.0f;
			x = V1.x - num * normal.x;
			y = V1.y - num * normal.y;
			z = V1.z - num * normal.z;
			w = V1.w - num * normal.w;
			return *this;
		}
		inline Vector4 operator * (float num, const Vector4& vec) {
			return Vector4(num * vec.x, num * vec.y, num * vec.z, num * vec.w);
		}

#pragma endregion class Vector4

		//---------------------------------------------------------------------------------------------------------
		// Definition class Matrix
		//
		// References:
		//	1. http ://evanw.github.io/lightgl.js/docs/matrix.html
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
			_11 = f11; _12 = f12; _13 = f13; _14 = f14;
			_21 = f21; _22 = f22; _23 = f23; _24 = f24;
			_31 = f31; _32 = f32; _33 = f33; _34 = f34;
			_41 = f41; _42 = f42; _43 = f43; _44 = f44;
		}

		inline Matrix::operator D3DMATRIX* () {
			return this;
		}
		inline Matrix::operator const D3DMATRIX* () {
			return this;
		}

		inline Matrix::operator D3DXMATRIX* () {
			return this;
		}

		inline Matrix::operator const D3DXMATRIX* () {
			return this;
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
			_11 += mat._11; _12 += mat._12; _13 += mat._13; _14 += mat._14;
			_21 += mat._21; _22 += mat._22; _23 += mat._23; _24 += mat._24;
			_31 += mat._31; _32 += mat._32; _33 += mat._33; _34 += mat._34;
			_41 += mat._41; _42 += mat._42; _43 += mat._43; _44 += mat._44;
			return *this;
		}

		inline Matrix& Matrix::operator -= (const Matrix& mat) {
			_11 -= mat._11; _12 -= mat._12; _13 -= mat._13; _14 -= mat._14;
			_21 -= mat._21; _22 -= mat._22; _23 -= mat._23; _24 -= mat._24;
			_31 -= mat._31; _32 -= mat._32; _33 -= mat._33; _34 -= mat._34;
			_41 -= mat._41; _42 -= mat._42; _43 -= mat._43; _44 -= mat._44;
			return *this;
		}

		inline Matrix& Matrix::operator *= (float f) {
			_11 *= f; _12 *= f; _13 *= f; _14 *= f;
			_21 *= f; _22 *= f; _23 *= f; _24 *= f;
			_31 *= f; _32 *= f; _33 *= f; _34 *= f;
			_41 *= f; _42 *= f; _43 *= f; _44 *= f;
			return *this;
		}

		inline Matrix& Matrix::operator /= (float f) {
			float inv = 1.0f / f;
			_11 *= inv; _12 *= inv; _13 *= inv; _14 *= inv;
			_21 *= inv; _22 *= inv; _23 *= inv; _24 *= inv;
			_31 *= inv; _32 *= inv; _33 *= inv; _34 *= inv;
			_41 *= inv; _42 *= inv; _43 *= inv; _44 *= inv;
			return *this;
		}

		// unary operators
		inline Matrix Matrix::operator + () const {
			return *this;
		}

		inline Matrix Matrix::operator - () const {
			return Matrix(
				-_11, -_12, -_13, -_14,
				-_21, -_22, -_23, -_24,
				-_31, -_32, -_33, -_34,
				-_41, -_42, -_43, -_44
				);
		}

		// binary operators
		inline Matrix Matrix::operator * (const Matrix& mat) {
			Matrix ret;
			return ret.Multiply(*this, mat);
		}

		inline Matrix Matrix::operator + (const Matrix& mat) const {
			return Matrix(
				_11 + mat._11, _12 + mat._12, _13 + mat._13, _14 + mat._14,
				_21 + mat._21, _22 + mat._22, _23 + mat._23, _24 + mat._24,
				_31 + mat._31, _32 + mat._32, _33 + mat._33, _34 + mat._34,
				_41 + mat._41, _42 + mat._42, _43 + mat._43, _44 + mat._44
				);
		}

		inline Matrix Matrix::operator - (const Matrix& mat) const {
			return Matrix(
				_11 - mat._11, _12 - mat._12, _13 - mat._13, _14 - mat._14,
				_21 - mat._21, _22 - mat._22, _23 - mat._23, _24 - mat._24,
				_31 - mat._31, _32 - mat._32, _33 - mat._33, _34 - mat._34,
				_41 - mat._41, _42 - mat._42, _43 - mat._43, _44 - mat._44
				);
		}

		inline Matrix Matrix::operator * (float f) const {
			return Matrix(
				_11 * f, _12 * f, _13 * f, _14 * f,
				_21 * f, _22 * f, _23 * f, _24 * f,
				_31 * f, _32 * f, _33 * f, _34 * f,
				_41 * f, _42 * f, _43 * f, _44 * f
				);
		}

		inline Matrix Matrix::operator / (float f) const {
			float inv = 1.0f / f;
			return Matrix(
				_11 * inv, _12 * inv, _13 * inv, _14 * inv,
				_21 * inv, _22 * inv, _23 * inv, _24 * inv,
				_31 * inv, _32 * inv, _33 * inv, _34 * inv,
				_41 * inv, _42 * inv, _43 * inv, _44 * inv
				);
		}

		inline bool Matrix::operator == (const Matrix& mat) const {
			return 0 == memcmp(this, &mat, sizeof(_Matrix));
		}

		inline bool Matrix::operator != (const Matrix& mat) const {
			return 0 != memcmp(this, &mat, sizeof(_Matrix));
		}

		inline Matrix& Matrix::Transpose(const Matrix& mat) {
			D3DXMatrixTranspose(this, &mat);
			return *this;
		}

		//Determines the product of two matrices.
		inline Matrix& Matrix::Multiply(const Matrix& mat1, const Matrix& mat2) {
			D3DXMatrixMultiply(this, &mat1, &mat2);
			return *this;
		}

		//Calculates the transposed product of two matrices.
		inline Matrix& Matrix::MultiplyTranspose(const Matrix& mat1, const Matrix& mat2) {
			Matrix temp;
			return Transpose(temp.Multiply(mat1, mat2));
		}

		//Calculates the inverse of a matrix.
		inline Matrix& Matrix::Inverse(const Matrix& mat) {
			FLOAT Determinant;
			D3DXMatrixInverse(this, &Determinant, &mat);
			return *this;
		}

		// Build a matrix which scales by (sx, sy, sz)
		inline Matrix& Matrix::Scaling(float sx, float sy, float sz) {
			D3DXMatrixScaling(this, sx, sy, sz);
			return *this;
		}

		inline Matrix& Matrix::Scaling(const Vector3& vec) {
			D3DXMatrixScaling(this, vec.x, vec.y, vec.z);
			return *this;
		}

		// Build a matrix which translates by (x, y, z)
		inline Matrix& Matrix::Translation(float x, float y, float z) {
			D3DXMatrixTranslation(this, x, y, z);
			return *this;
		}

		//Returns the matrix transpose of a matrix.
		inline Matrix& Matrix::Translation(const Vector3& vec) {
			D3DXMatrixTranslation(this, vec.x, vec.y, vec.z);
			return *this;
		}

		//Build a matrix which rotates around an arbitrary axis
		inline Matrix& Matrix::RotationAxis(const Vector3& vec, float Angle) {
			D3DXMatrixRotationAxis(this, &vec, Angle);
			return *this;
		}

		//Build a matrix which rotates around the X axis
		inline Matrix& Matrix::RotationX(float angle) {
			D3DXMatrixRotationX(this, angle);
			return *this;
		}

		//Build a matrix which rotates around the Y axis
		inline Matrix& Matrix::RotationY(float angle) {
			D3DXMatrixRotationY(this, angle);
			return *this;
		}

		//Build a matrix which rotates around the Z axis
		inline Matrix& Matrix::RotationZ(float angle) {
			D3DXMatrixRotationZ(this, angle);
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
			D3DXMatrixPerspectiveLH(this, w, h, zn, zf);
			return *this;
		}

		inline Matrix& Matrix::PerspectiveRH(float w, float h, float zn, float zf) {
			D3DXMatrixPerspectiveRH(this, w, h, zn, zf);
			return *this;
		}

		inline Matrix& Matrix::PerspectiveFovLH(float fovY, float Aspect, float zn, float zf) {
			D3DXMatrixPerspectiveFovLH(this, fovY, Aspect, zn, zf);
			return *this;
		}

		inline Matrix& Matrix::PerspectiveFovRH(float fovY, float Aspect, float zn, float zf) {
			D3DXMatrixPerspectiveFovRH(this, fovY, Aspect, zn, zf);
			return *this;
		}

		inline Matrix& Matrix::PerspectiveOffCenterLH(float l, float r, float b, float t, float zn, float zf) {
			D3DXMatrixPerspectiveOffCenterLH(this, l, r, b, t, zn, zf);
			return *this;
		}

		inline Matrix& Matrix::PerspectiveOffCenterRH(float l, float r, float b, float t, float zn, float zf) {
			D3DXMatrixPerspectiveOffCenterRH(this, l, r, b, t, zn, zf);
			return *this;
		}

		//Builds a left-handed orthographic projection matrix.
		inline Matrix& Matrix::OrthoLH(float w, float	h, float zn, float zf) {
			D3DXMatrixOrthoLH(this, w, h, zn, zf);
			return *this;
		}

		//Builds a right-handed orthographic projection matrix.
		inline Matrix& Matrix::OrthoRH(float w, float	h, float zn, float zf) {
			D3DXMatrixOrthoRH(this, w, h, zn, zf);
			return *this;
		}

		//Builds a customized, right-handed orthographic projection matrix.
		inline Matrix& Matrix::OrthoOffCenterRH(float l, float r, float b, float t, float zn, float zf) {
			D3DXMatrixOrthoOffCenterRH(this, l, r, b, t, zn, zf);
			return *this;
		}

		//Builds a customized, left-handed orthographic projection matrix.
		inline Matrix& Matrix::OrthoOffCenterLH(float l, float r, float b, float t, float zn, float zf) {
			D3DXMatrixOrthoOffCenterLH(this, l, r, b, t, zn, zf);
			return *this;
		}

		inline Matrix& Matrix::LookAtLH(Vector3& vecEye, Vector3& vecAt, Vector3& vecUp) {
			D3DXMatrixLookAtLH(this, vecEye, vecAt, vecUp);
			return *this;
		}

		inline Matrix& Matrix::LookAtRH(Vector3& vecEye, Vector3& vecAt, Vector3& vecUp) {
			D3DXMatrixLookAtRH(this, vecEye, vecAt, vecUp);
			return *this;
		}

		inline Matrix& Matrix::Identity() {
			D3DXMatrixIdentity(this);
			return *this;
		}

		inline bool Matrix::IsIdentity() {
#pragma warning(disable : 4800)
			return (bool)D3DXMatrixIsIdentity(this);
#pragma warning(default : 4800)
		}

		inline float Matrix::Determinant() {
			return D3DXMatrixDeterminant(this);
		}

		inline bool Matrix::Decompose(Vector3& OutScale, Quaternion& OutRotation, Vector3& OutTranslation) {
			return (S_OK == D3DXMatrixDecompose(&OutScale, &OutRotation, &OutTranslation, this));
		}

		inline Matrix& Matrix::RotationYawPitchRoll(float Yaw, float Pitch, float Roll)  {
			D3DXMatrixRotationYawPitchRoll(this, Yaw, Pitch, Roll);
			return *this;
		}

		inline Matrix& Matrix::Transformation(const Vector3& ScalingCenter, const Quaternion& ScalingRotation, const Vector3& Scaling, const Vector3& RotationCenter, const Quaternion& Rotation, const Vector3& Translation)  {
			D3DXMatrixTransformation(this, &ScalingCenter, &ScalingRotation, &Scaling, &RotationCenter, &Rotation, &Translation);
			return *this;
		}

		inline Matrix& Matrix::Transformation2D(const Vector2& ScalingCenter, float ScalingRotation, const Vector2& Scaling, const Vector2& RotationCenter, float Rotation, const Vector2& Translation) {
			D3DXMatrixTransformation2D(this, &ScalingCenter, ScalingRotation, &Scaling, &RotationCenter, Rotation, &Translation);
			return *this;
		}

		inline Matrix& Matrix::AffineTransformation(float Scaling, const Vector3& RotationCenter, const Quaternion& Rotation, const Vector3& Translation) {
			D3DXMatrixAffineTransformation(this, Scaling, &RotationCenter, &Rotation, &Translation);
			return *this;
		}

		inline Matrix& Matrix::AffineTransformation2D(float Scaling, const Vector2& RotationCenter, float Rotation, const Vector2& Translation) {
			D3DXMatrixAffineTransformation2D(this, Scaling, &RotationCenter, Rotation, &Translation);
			return *this;
		}

		inline Matrix& Matrix::Shadow(const Vector4& Light, const Plane& plane) {
			D3DXMatrixShadow(this, &Light, &plane);
			return *this;
		}

		inline Matrix& Matrix::Reflect(const Plane& plane) {
			D3DXMatrixReflect(this, &plane);
			return *this;
		}

		inline Matrix& Matrix::RotationQuaternion(const Quaternion& Q) {
			D3DXMatrixRotationQuaternion(this, &Q);
			return *this;
		}

		inline Matrix operator * (float f, const Matrix& mat) {
			return Matrix(
				f * mat._11, f * mat._12, f * mat._13, f * mat._14,
				f * mat._21, f * mat._22, f * mat._23, f * mat._24,
				f * mat._31, f * mat._32, f * mat._33, f * mat._34,
				f * mat._41, f * mat._42, f * mat._43, f * mat._44
				);
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
			x += q.x;
			y += q.y;
			z += q.z;
			w += q.w;
			return *this;
		}

		inline Quaternion& Quaternion::operator -= (const Quaternion& q) {
			x -= q.x;
			y -= q.y;
			z -= q.z;
			w -= q.w;
			return *this;
		}

		inline Quaternion& Quaternion::operator *= (const Quaternion& q) {
			D3DXQuaternionMultiply(this, this, &q);
			return *this;
		}

		inline Quaternion& Quaternion::operator *= (float num) {
			x *= num;
			y *= num;
			z *= num;
			w *= num;
			return *this;
		}

		inline Quaternion& Quaternion::operator /= (float num) {
			float fInv = 1.0f / num;
			x *= fInv;
			y *= fInv;
			z *= fInv;
			w *= fInv;
			return *this;
		}

		// unary operators
		inline Quaternion Quaternion::operator + () const {
			return *this;
		}

		inline Quaternion Quaternion::operator - () const {
			return Quaternion(-x, -y, -z, -w);
		}

		// binary operators
		inline Quaternion Quaternion::operator + (const Quaternion& q) const {
			return Quaternion(x + q.x, y + q.y, z + q.z, w + q.w);
		}

		inline Quaternion Quaternion::operator - (const Quaternion& q) const {
			return Quaternion(x - q.x, y - q.y, z - q.z, w - q.w);
		}

		inline Quaternion Quaternion::operator * (const Quaternion& q) {
			Quaternion ret;
			D3DXQuaternionMultiply(&ret, this, &q);
			return ret;
		}

		inline Quaternion Quaternion::operator * (float num) const {
			return Quaternion(x * num, y * num, z * num, w * num);
		}

		inline Quaternion Quaternion::operator / (float num) const {
			float fInv = 1.0f / num;
			return Quaternion(x * fInv, y * fInv, z * fInv, w * fInv);
		}

		inline bool Quaternion::operator == (const Quaternion& q) const {
			return x == q.x && y == q.y && z == q.z && w == q.w;
		}

		inline bool Quaternion::operator != (const Quaternion& q) const {
			return x != q.x || y != q.y || z != q.z || w != q.w;
		}

		inline float Quaternion::Length() const {
			return D3DXQuaternionLength(this);
		}

		// Length squared, or "norm"
		inline float Quaternion::LengthSq() const {
			return D3DXQuaternionLengthSq(this);
		}

		inline float Quaternion::Dot(const Quaternion& q) const {
			return D3DXQuaternionDot(this, &q);
		}

		// (0, 0, 0, 1)
		inline Quaternion& Quaternion::Identity() {
			D3DXQuaternionIdentity(this);
			return *this;
		}

		inline bool Quaternion::IsIdentity() const {
#pragma warning(disable : 4800)
			return (bool)D3DXQuaternionIsIdentity(this);
#pragma warning(default : 4800)
		}

		// (-x, -y, -z, w)
		inline Quaternion& Quaternion::Conjugate(Quaternion& q) {
			D3DXQuaternionConjugate(this, q);
			return *this;
		}

		// Compute a quaternin's axis and angle of rotation. Expects unit quaternions.
		inline Quaternion& Quaternion::ToAxisAngle(Vector3& Axis, float& Angle) {
			D3DXQuaternionToAxisAngle(this, &Axis, &Angle);
			return *this;
		}

		// Build a quaternion from a rotation matrix.
		inline Quaternion& Quaternion::RotationMatrix(const Matrix& mat) {
			D3DXQuaternionRotationMatrix(this, &mat);
			return *this;
		}

		// Rotation about arbitrary axis.
		inline Quaternion& Quaternion::RotationAxis(const Vector3& Axis, float Angle) {
			D3DXQuaternionRotationAxis(this, &Axis, Angle);
			return *this;
		}

		// Yaw around the Y axis, a pitch around the X axis,
		// and a roll around the Z axis.
		inline Quaternion& Quaternion::RotationYawPitchRoll(float Yaw, float Pitch, float Roll) {
			D3DXQuaternionRotationYawPitchRoll(this, Yaw, Pitch, Roll);
			return *this;
		}

		// Quaternion multiplication.  The result represents the rotation Q2
		// followed by the rotation Q1.  (Out = Q2 * Q1)
		inline Quaternion& Quaternion::Multiply(const Quaternion& Q1, const Quaternion& Q2) {
			D3DXQuaternionMultiply(this, &Q1, &Q2);
			return *this;
		}

		inline Quaternion& Quaternion::Normalize(const Quaternion& Q) {
			D3DXQuaternionNormalize(this, &Q);
			return *this;
		}

		// Conjugate and re-norm
		inline Quaternion& Quaternion::Inverse(const Quaternion& Q) {
			D3DXQuaternionInverse(this, &Q);
			return *this;
		}

		// Expects unit quaternions.
		// if q = (cos(theta), sin(theta) * v); ln(q) = (0, theta * v)
		inline Quaternion& Quaternion::Ln(const Quaternion& Q) {
			D3DXQuaternionLn(this, &Q);
			return *this;
		}

		// Expects pure quaternions. (w == 0)  w is ignored in calculation.
		// if q = (0, theta * v); exp(q) = (cos(theta), sin(theta) * v)
		inline Quaternion& Quaternion::Exp(const Quaternion& Q) {
			D3DXQuaternionExp(this, &Q);
			return *this;
		}

		// Spherical linear interpolation between Q1 (t == 0) and Q2 (t == 1).
		// Expects unit quaternions.
		inline Quaternion& Quaternion::Slerp(const Quaternion& Q0, const Quaternion& Q1, float t) {
			D3DXQuaternionSlerp(this, &Q0, &Q1, t);
			return *this;
		}

		// Spherical quadrangle interpolation.
		// Slerp(Slerp(Q1, C, t), Slerp(A, B, t), 2t(1-t))
		inline Quaternion& Quaternion::Squad(const Quaternion& Q0, const Quaternion& Q1, const Quaternion& Q2, const Quaternion& Q3, float t) {
			D3DXQuaternionSquad(this, &Q0, &Q1, &Q2, &Q3, t);
			return *this;
		}

		// Setup control points for spherical quadrangle interpolation
		// from Q1 to Q2.  The control points are chosen in such a way
		// to ensure the continuity of tangents with adjacent segments.
		inline void Quaternion::SquadSetup(Quaternion& AOut, Quaternion& BOut, Quaternion& COut,
			const Quaternion& q0, const Quaternion& q1, const Quaternion& q2, const Quaternion& q3) {
			D3DXQuaternionSquadSetup(AOut, BOut, COut, &q0, &q1, &q2, &q3);
		}

		// Barycentric interpolation.
		// Slerp(Slerp(Q1, Q2, f+g), Slerp(Q1, Q3, f+g), g/(f+g))
		inline Quaternion& Quaternion::BaryCentric(const Quaternion& Q1, const Quaternion& Q2, const Quaternion& Q3, float f, float g) {
			D3DXQuaternionBaryCentric(this, &Q1, &Q2, &Q3, f, g);
			return *this;
		}

		inline Quaternion operator * (float num, const Quaternion& q) {
			return Quaternion(num * q.x, num * q.y, num * q.z, num * q.w);
		}

#pragma endregion Definition class Quaternion

		//---------------------------------------------------------------------------------------------------------
		// Definition class Plane
#pragma region Definition class Plane

		inline Plane::Plane() {
		}

		inline Plane::Plane(const float* pSrc) {
			a = pSrc[0];
			b = pSrc[1];
			c = pSrc[2];
			d = pSrc[3];
		}

		inline Plane::Plane(float _a, float _b, float _c, float _d) {
			a = _a;
			b = _b;
			c = _c;
			d = _d;
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
			a *= num;
			b *= num;
			c *= num;
			d *= num;
			return *this;
		}

		inline Plane& Plane::operator /= (float num) {
			const float inv = 1.0f / num;
			a *= inv;
			b *= inv;
			c *= inv;
			d *= inv;
			return *this;
		}

		// unary operators
		inline Plane Plane::operator + () const {
			return *this;
		}

		inline Plane Plane::operator - () const {
			return Plane(-a, -b, -c, -d);
		}

		// binary operators
		inline Plane Plane::operator * (float num) const {
			return Plane(a * num, b * num, c * num, d * num);
		}

		inline Plane Plane::operator / (float num) const {
			const float inv = 1.0f / num;
			return Plane(a * inv, b * inv, c * inv, d * inv);
		}

		inline bool Plane::operator == (const Plane& p) const {
			return a == p.a && b == p.b && c == p.c && d == p.d;
		}

		inline bool Plane::operator != (const Plane& p) const {
			return a != p.a || b != p.b || c != p.c || d != p.d;
		}

		// ax + by + cz + dw
		inline float Plane::Dot(const Vector4& vec) {
			return D3DXPlaneDot(this, &vec);
		}

		// ax + by + cz + d
		inline float Plane::DotCoord(const Vector3& vec) {
			return D3DXPlaneDotCoord(this, &vec);
		}

		// ax + by + cz
		inline float Plane::DotNormal(const Vector3& vec) {
			return D3DXPlaneDotNormal(this, &vec);
		}

		inline Plane& Plane::Scale(const Plane& P1, float s) {
			D3DXPlaneScale(this, &P1, s);
			return *this;
		}

		// Normalize plane (so that |a,b,c| == 1)
		inline Plane& Plane::Normalize(const Plane& P1) {
			D3DXPlaneNormalize(this, &P1);
			return *this;
		}

		// Construct a plane from a point and a normal
		inline Plane& Plane::FromPointNormal(const Vector3& vecPoint, const Vector3& vecNormal) {
			D3DXPlaneFromPointNormal(this, &vecPoint, &vecNormal);
			return *this;
		}

		// Construct a plane from 3 points
		inline Plane& Plane::FromPoints(const Vector3& V1, const Vector3& V2, const Vector3& V3) {
			D3DXPlaneFromPoints(this, &V1, &V2, &V3);
			return *this;
		}

		// Transform a plane by a matrix.  The vector (a,b,c) must be normal.
		// M should be the inverse transpose of the transformation desired.
		inline Plane& Plane::Transform(const Plane& P1, const Matrix& mat) {
			D3DXPlaneTransform(this, &P1, &mat);
			return *this;
		}

		// Transform an array of planes by a matrix.  The vectors (a,b,c) must be normal.
		// M should be the inverse transpose of the transformation desired.
		inline Plane* Plane::TransformArray(Plane* pOut, UINT OutputStride, const Plane* pSrc, UINT InputStride, UINT PlaneCount, const Matrix& mat) {
			D3DXPlaneTransformArray(pOut, OutputStride, pSrc, InputStride, &mat, PlaneCount);
			return pOut;
		}

		inline Plane operator * (float num, const Plane& p) {
			return Plane(num * p.a, num * p.b, num * p.c, num * p.d);
		}

#pragma endregion Definition class Plane

#pragma endregion Definition class

		//---------------------------------------------------------------------------------------------------------
	} /* namespace Drawing */
} /* namespace System */

#pragma warning(default:4316)

#include "System.Drawing.Colors.h"
#endif /*  SYSTEM_DRAWING_MATH_H_ */
#endif