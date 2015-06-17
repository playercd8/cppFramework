/*
 * System.Formula.Kinematics.h
 *
 * Code Status: Drafts
 *  Created on: Taiwan
 *      Author: player
 */

#ifndef SYSTEM_FORMULA_KINEMATICS_H_
#define SYSTEM_FORMULA_KINEMATICS_H_

#if _MSC_VER > 1000
#pragma once
#endif

#include "stdafx.h"
#include "System.Drawing.Math.h"
#include "System.Math.h"

using namespace System::Drawing;

namespace System {
	namespace Formula {
		namespace Kinematics {
			//<summary>
			//圓周運動 (Circular motion)
			//</summary>
			class CircularMotion {
				//<summary>
				//移動到, 等速圓周運動(2D)
				//</summary>
				//<param name="to">移動後的位置(傳出)</param>
				//<param name="p0">圓心位置(傳入)</param>
				//<param name="r">圓的半徑(傳入)</param>
				//<param name="v">角速度(傳入)</param>
				//<param name="t">經過的時間(傳入)</param>
				//<returns></returns>
				//<remarks></remarks>
				inline void MoveTo(Vector2& to, Vector2& p0, float r, float v, float t) {
					to.x = p0.x + (r * Math::Cos(v*t));
					to.y = p0.y + (r * Math::Sin(v*t));
				}
			};

			//<summary>
			//線性運動 (Linear motion)
			//</summary>
			class LinearMotion {
				//<summary>
				//移動到, 等速直線運動(2D)
				//</summary>
				//<param name="to">移動後的位置(傳出)</param>
				//<param name="from">移動前的位置(傳入)</param>
				//<param name="v">速度(傳入)</param>
				//<param name="t">經過的時間(傳入)</param>
				//<returns></returns>
				//<remarks></remarks>
				inline void MoveTo(Vector2& to, Vector2& from, Vector2& v, float t) {
					to.x = from.x + (v.x * t);
					to.y = from.y + (v.y * t);
				}

				//<summary>
				//移動到, 等速直線運動(3D)
				//</summary>
				//<param name="to">移動後的位置(傳出)</param>
				//<param name="from">移動前的位置(傳入)</param>
				//<param name="v">速度(傳入)</param>
				//<param name="t">經過的時間(傳入)</param>
				//<returns></returns>
				//<remarks></remarks>
				inline void MoveTo(Vector3& to, Vector3& from, Vector3& v, float t) {
					to.x = from.x + (v.x * t);
					to.y = from.y + (v.y * t);
					to.z = from.z + (v.z * t);
				}

				//<summary>
				//移動到, 等加速直線運動(2D)
				//</summary>
				//<param name="to">移動後的位置(傳出)</param>
				//<param name="from">移動前的位置(傳入)</param>
				//<param name="v1">初速(傳入)</param>
				//<param name="a">加速度(傳入)</param>
				//<param name="t">經過的時間(傳入)</param>
				//<returns></returns>
				//<remarks></remarks>
				inline void MoveTo(Vector2& to, Vector2& from, Vector2& v1, Vector2& a, float t) {
					to.x = (t / 2 * a.x + v1.x) * t + from.x;
					to.y = (t / 2 * a.y + v1.y) * t + from.y;
				}

				//<summary>
				//移動到, 等加速直線運動(3D)
				//</summary>
				//<param name="to">移動後的位置(傳出)</param>
				//<param name="from">移動前的位置(傳入)</param>
				//<param name="v1">初速(傳入)</param>
				//<param name="a">加速度(傳入)</param>
				//<param name="t">經過的時間(傳入)</param>
				//<returns></returns>
				//<remarks></remarks>
				inline void MoveTo(Vector3& to, Vector3& from, Vector3& v1, Vector3& a, float t) {
					to.x = (t / 2 * a.x + v1.x) * t + from.x;
					to.y = (t / 2 * a.y + v1.y) * t + from.y;
					to.z = (t / 2 * a.z + v1.z) * t + from.z;
				}

				//<summary>
				//最後速度, 等加速直線運動(2D)
				//</summary>
				//<param name="v2">最後速度(傳出)</param>
				//<param name="v1">初速(傳入)</param>
				//<param name="a">加速度(傳入)</param>
				//<param name="t">經過時間(傳入)</param>
				//<returns></returns>
				//<remarks></remarks>
				inline void LastSpeed(Vector2& v2, Vector2& v1, Vector2& a, float t) {
					v2.x = a.x * t + v1.x;
					v2.y = a.y * t + v1.y;
				}

				//<summary>
				//最後速度, 等加速直線運動(3D)
				//</summary>
				//<param name="v2">最後速度(傳出)</param>
				//<param name="v1">初速(傳入)</param>
				//<param name="a">加速度(傳入)</param>
				//<param name="t">經過時間(傳入)</param>
				//<returns></returns>
				//<remarks></remarks>
				inline void LastSpeed(Vector3& v2, Vector3& v1, Vector3& a, float t) {
					v2.x = a.x * t + v1.x;
					v2.y = a.y * t + v1.y;
					v2.z = a.z * t + v1.z;
				}

				//<summary>
				//加速度, (2D)
				//</summary>
				//<param name="v1">初速(傳入)</param>
				//<param name="v2">最後速度(傳入)</param>
				//<param name="a">加速度(傳出)</param>
				//<param name="t">經過的時間(傳入)</param>
				//<returns></returns>
				//<remarks></remarks>
				inline void Acceleration(Vector2& v1, Vector2& v2, Vector2& a, float t) {
					a.x = (v2.x - v1.x) / t;
					a.y = (v2.y - v1.y) / t;
				}

				//<summary>
				//加速度, (3D)
				//</summary>
				//<param name="v1">初速(傳入)</param>
				//<param name="v2">最後速度(傳入)</param>
				//<param name="a">加速度(傳出)</param>
				//<param name="t">經過的時間(傳入)</param>
				//<returns></returns>
				//<remarks></remarks>
				inline void Acceleration(Vector3& v1, Vector3& v2, Vector3& a, float t) {
					a.x = (v2.x - v1.x) / t;
					a.y = (v2.y - v1.y) / t;
					a.z = (v2.z - v1.z) / t;
				}

				//<summary>
				//加速度, 等加速直線運動(2D)
				//</summary>
				//<param name="to">移動後的位置(傳入)</param>
				//<param name="from">移動前的位置(傳入)</param>
				//<param name="v1">初速(傳入)</param>
				//<param name="a">加速度(傳出)</param>
				//<param name="t">經過的時間(傳入)</param>
				//<returns></returns>
				//<remarks></remarks>
				inline void Acceleration(Vector2& to, Vector2& from, Vector2& v1, Vector2& a, float t) {
					a.x = ((to.x - from.x) / t - v1.x) * 2 / t;
					a.y = ((to.y - from.y) / t - v1.y) * 2 / t;
				}

				//<summary>
				//加速度, 等加速直線運動(2D)
				//</summary>
				//<param name="to">移動後的位置(傳入)</param>
				//<param name="from">移動前的位置(傳入)</param>
				//<param name="v1">初速(傳入)</param>
				//<param name="a">加速度(傳出)</param>
				//<param name="t">經過的時間(傳入)</param>
				//<returns></returns>
				//<remarks></remarks>
				inline void Acceleration(Vector3& to, Vector3& from, Vector3& v1, Vector3& a, float t) {
					a.x = ((to.x - from.x) / t - v1.x) * 2 / t;
					a.y = ((to.y - from.y) / t - v1.y) * 2 / t;
					a.z = ((to.z - from.z) / t - v1.z) * 2 / t;
				}
			};

			//<summary>
			//重力
			//</summary>
			class Gravitational {
				//<summary>
				//重力加速度（Gravitational acceleration）
				//</summary>
				//<param name="m">質量(傳入)</param>
				//<param name="r">距離(傳入)</param>
				//<returns>重力加速度</returns>
				//<remarks></remarks>
				inline float Acceleration(float m, float r) {
					float G = 6.67384E-11L;
					return (G * m) / (r * r);
				}

				//<summary>
				//萬有引力（UniversalGravitation）
				//</summary>
				//<param name="m1">質量1(傳入)</param>
				//<param name="m2">質量2(傳入)</param>
				//<param name="r">距離(傳入)</param>
				//<returns>萬有引力</returns>
				//<remarks>萬有引力常數 G =6.67259E-11 N m2/kg2</remarks>
				inline float Universal(float m1, float m2, float r) {
					float G = 6.67384E-11L;
					return (G * m1 * m2) / (r * r);
				}
			};
		} /* namespace Kinematics */
	} /* namespace Formula */
} /* namespace System */

#endif /* SYSTEM_FORMULA_KINEMATICS_H_ */
