/*
 * System.Drawing.Camera.h
 *
 * Code Status: Drafts
 *  Created on: Taiwan
 *      Author: player
 */

#ifndef SYSTEM_DRAWING_CAMERA_H_
#define SYSTEM_DRAWING_CAMERA_H_

#if _MSC_VER > 1000
#pragma once
#endif

#include "stdafx.h"
#include "System.Drawing.Math.h"

namespace System {
	namespace Drawing {
		class Camera {
		private:
			Vector3 _vecEyePt;       // Attributes for view matrix
			Vector3 _vecLookatPt;
			Vector3 _vecUpVec;
			Vector3 _vecView;
			Vector3 _vecCross;

			__declspec(align(16))
			Matrix  _matView;
			
			__declspec(align(16))
			Matrix  _matBillboard; // Special matrix for billboarding effects

			float       _fFOV;         // Attributes for projection matrix
			float       _fAspect;
			float       _fNearPlane;
			float       _fFarPlane;

			__declspec(align(16))
			Matrix		_matProj;

		public:
			Camera() {
				// Set attributes for the view matrix
				Vector3 vecEyePt(0.0f, 0.0f, 0.0f);
				Vector3 vecLookatPt(0.0f, 0.0f, 1.0f);
				Vector3 vecUpVec(0.0f, 1.0f, 0.0f);
				SetViewParams(vecEyePt, vecLookatPt, vecUpVec);

				// Set attributes for the projection matrix
				SetProjParams(Math::Constants::_PIDIV4, 1.0f, 1.0f, 1000.0f);
			}

			virtual ~Camera() {
			}

			// Access functions
			inline const Vector3& GetEyePt() {
				return _vecEyePt;
			}

			inline Vector3& GetLookatPt() {
				return _vecLookatPt;
			}

			inline const Vector3& GetUpVec() {
				return _vecUpVec;
			}

			inline const Vector3& GetViewDir() {
				return _vecView;
			}

			inline const Vector3& GetCross() {
				return _vecCross;
			}

			inline float GetFOV() const {
				return _fFOV;
			}

			inline const float GetAspect() {
				return _fAspect;
			}

			inline const float GetNearPlane() {
				return _fNearPlane;
			}

			inline const float GetFarPlane() {
				return _fFarPlane;
			}

			inline const Matrix& GetViewMatrix() const {
				return _matView;
			}

#if defined(D3DMATRIX_DEFINED)
			inline const D3DMATRIX* GetViewMatrix() {
				return reinterpret_cast<const D3DMATRIX*>(&_matView);
			}
#endif

			inline const Matrix& GetBillboardMatrix() {
				return _matBillboard;
			}

			inline const Matrix& GetProjMatrix() const {
				return _matProj;
			}

			void SetViewParams(Vector3& vecEyePt, Vector3& vecLookatPt, Vector3& vecUpVec) {
				// Set attributes for the view matrix
				_vecEyePt = vecEyePt;
				_vecLookatPt = vecLookatPt;
				_vecUpVec = vecUpVec;
				Vector3 vecDir = _vecLookatPt - _vecEyePt;

				_vecView.Normalize(vecDir);
				_vecCross.Cross(_vecView, _vecUpVec);

				_matView.LookAtLH(_vecEyePt, _vecLookatPt, _vecUpVec);

				_matBillboard.Inverse(_matView);

				_matBillboard._41 = 0.0f;
				_matBillboard._42 = 0.0f;
				_matBillboard._43 = 0.0f;
			}

			void SetProjParams(float fFOV, float fAspect, float fNearPlane, float fFarPlane) {
				_fFOV = fFOV;
				_fAspect = fAspect;
				_fNearPlane = fNearPlane;
				_fFarPlane = fFarPlane;

				_matProj.PerspectiveFovLH(fFOV, fAspect, fNearPlane, fFarPlane);
			}
		};
	} /* namespace Drawing */
} /* namespace System */

#endif /* SYSTEM_DRAWING_CAMERA_H_ */
