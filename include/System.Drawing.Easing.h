/*
* System.Drawing.Easing.h
*
* Code Status: Drafts
*  Created on: Taiwan
*      Author: player
*  References:
*		1. http://gsgd.co.uk/sandbox/jquery/easing/
*/

#ifndef SYSTEM_DRAWING_EASING_H_
#define SYSTEM_DRAWING_EASING_H_

#if _MSC_VER > 1000
#pragma once
#endif

#include "stdafx.h"
#include "System.Math.h"

namespace System {
	namespace Drawing {
		class Easing {
		public:
			float easeInQuad(float x, float t, float b, float c, float d) {
				return c*(t /= d)*t + b;
			}

			float easeOutQuad(float x, float t, float b, float c, float d) {
				return -c *(t /= d)*(t - 2.0f) + b;
			}

			float easeInOutQuad(float x, float t, float b, float c, float d) {
				if ((t /= d * 0.5f) < 1.0f) return c * 0.5f * t*t + b;
				return -0.5f * c * ((--t)*(t - 2.0f) - 1.0f) + b;
			}

			float easeInCubic(float x, float t, float b, float c, float d) {
				return c*(t /= d)*t*t + b;
			}

			float easeOutCubic(float x, float t, float b, float c, float d) {
				return c*((t = t / d - 1.0f)*t*t + 1.0f) + b;
			}
			float easeInOutCubic(float x, float t, float b, float c, float d) {
				if ((t /= d * 0.5f) < 1.0f) return c / 2.0f*t*t*t + b;
				return c * 0.5f * ((t -= 2.0f)*t*t + 2.0f) + b;
			}

			float easeInQuart(float x, float t, float b, float c, float d) {
				return c*(t /= d)*t*t*t + b;
			}

			float easeOutQuart(float x, float t, float b, float c, float d) {
				return -c * ((t = t / d - 1)*t*t*t - 1) + b;
			}

			float easeInOutQuart(float x, float t, float b, float c, float d) {
				if ((t /= d *0.5f) < 1) return c * 0.5f * Math::Pow(t, 4.0f) + b;
				return -c * 0.5f * ((t -= 2.0f)*t*t*t - 2.0f) + b;
			}

			float easeInQuint(float x, float t, float b, float c, float d) {
				return c*(t /= d)*Math::Pow(t, 4.0f) + b;
			}

			float easeOutQuint(float x, float t, float b, float c, float d) {
				return c*((t = t / d - 1)*Math::Pow(t, 4.0f) + 1.0f) + b;
			}

			float easeInOutQuint(float x, float t, float b, float c, float d) {
				if ((t /= d / 2.0f) < 1.0f) return c / 2.0f*Math::Pow(t, 5.0f) + b;
				return c * 0.5f * ((t -= 2.0f)*Math::Pow(t, 4.0f) + 2.0f) + b;
			}

			float easeInSine(float x, float t, float b, float c, float d) {
				return (float)(-c * Math::Cos((float)(t / d * Math::Float_PI_2)) + c + b);
			}

			float easeOutSine(float x, float t, float b, float c, float d) {
				return c * Math::Sin((float)(t / d * Math::Float_PI_2)) + b;
			}

			float easeInOutSine(float x, float t, float b, float c, float d) {
				return -0.5f * c * (Math::Cos((float)(t / d * Math::Float_PI)) - 1.0f) + b;
			}
			float easeInExpo(float x, float t, float b, float c, float d) {
				return (t == 0) ? b : c * Math::Pow(2.0f, 10.0f * (t / d - 1.0f)) + b;
			}

			float easeOutExpo(float x, float t, float b, float c, float d) {
				return (t == d) ? b + c : c * (-Math::Pow(2.0f, -10.0f * t / d) + 1.0f) + b;
			}

			float easeInOutExpo(float x, float t, float b, float c, float d) {
				if (t == 0) return b;
				if (t == d) return b + c;
				if ((t /= d * 0.5f) < 1) return c / 2 * Math::Pow(2.0f, 10.0f * (t - 1.0f)) + b;
				return c * 0.5f * (-Math::Pow(2.0f, -10.0f * --t) + 2.0f) + b;
			}

			float easeInCirc(float x, float t, float b, float c, float d) {
				return -c * (Math::Sqrt(1.0f - (t /= d)*t) - 1.0f) + b;
			}

			float easeOutCirc(float x, float t, float b, float c, float d) {
				return c * Math::Sqrt(1.0f - (t = t / d - 1.0f)*t) + b;
			}

			float easeInOutCirc(float x, float t, float b, float c, float d) {
				if ((t /= d * 0.5f) < 1.0f) return -c * 0.5f * (Math::Sqrt(1.0f - t*t) - 1.0f) + b;
				return c * 0.5f * (Math::Sqrt(1 - (t -= 2.0f)*t) + 1.0f) + b;
			}

			float easeInElastic(float x, float t, float b, float c, float d) {
				float s = 1.70158f; float p = 0; float a = c;
				if (t == 0) return b;  if ((t /= d) == 1.0f) return b + c;  if (!p) p = d*0.3f;
				if (a < Math::Abs(c)) { a = c; s = p * 0.25f; }
				else s = (float)(p / Math::Float_PIx2 * Math::ArcSin((float)(c / a)));
				return  (float)(-(a*Math::Pow(2.0f, 10 * (t -= 1)) * Math::Sin((t*d - s)* Math::Float_PIx2 / p)) + b);
			}

			float easeOutElastic(float x, float t, float b, float c, float d) {
				float s = 1.70158f; float p = 0.0f; float a = c;
				if (t == 0) return b;  if ((t /= d) == 1.0f) return b + c;  if (!p) p = d*0.3f;
				if (a < Math::Abs(c)) { a = c; s = p * 0.25f; }
				else s = (float)(p / Math::Float_PIx2 * Math::ArcSin(c / a));
				return (float)(a*Math::Pow(2.0f, -10.0f * t) * Math::Sin((t*d - s)* Math::Float_PIx2 / p) + c + b);
			}

			float easeInOutElastic(float x, float t, float b, float c, float d) {
				float s = 1.70158f; float p = 0.0f; float a = c;
				if (t == 0.0f) return b;  if ((t /= d * 0.5f) == 2.0f) return b + c;  if (!p) p = d*(0.3f*1.5f);
				if (a < Math::Abs(c)) { a = c; s = p * 0.25f; }
				else s = (float)(p / Math::Float_PIx2 * Math::ArcSin(c / a));
				if (t < 1.0f) return (float)(-0.5f * (a*Math::Pow(2.0f, 10.0f * (t -= 1.0f)) * Math::Sin((t*d - s)* Math::Float_PIx2 / p)) + b);
				return (float)(a*Math::Pow(2.0f, -10 * (t -= 1)) * Math::Sin((t*d - s)* Math::Float_PIx2 / p)*0.5f + c + b);
			}

			float easeInBack(float x, float t, float b, float c, float d, float s = 1.70158f) {
				return c*(t /= d)*t*((s + 1.0f)*t - s) + b;
			}

			float easeOutBack(float x, float t, float b, float c, float d, float s = 1.70158f) {
				return c*((t = t / d - 1.0f)*t*((s + 1.0f)*t + s) + 1.0f) + b;
			}

			float easeInOutBack(float x, float t, float b, float c, float d, float s = 1.70158f) {
				if ((t /= d * 0.5f) < 1.0f) return c * 0.5f * (t*t*(((s *= 1.525f) + 1.0f)*t - s)) + b;
				return c * 0.5f * ((t -= 2.0f)*t*(((s *= (1.525f)) + 1.0f)*t + s) + 2.0f) + b;
			}

			float easeInBounce(float x, float t, float b, float c, float d) {
				return c - easeOutBounce(x, d - t, 0.0f, c, d) + b;
			}

			float easeOutBounce(float x, float t, float b, float c, float d) {
				if ((t /= d) < (1 / 2.75f)) {
					return c*(7.5625f*t*t) + b;
				}
				else if (t < (2.0f / 2.75f)) {
					return c*(7.5625f*(t -= (1.5f / 2.75f))*t + 0.75f) + b;
				}
				else if (t < (2.5 / 2.75)) {
					return c*(7.5625f*(t -= (2.25f / 2.75f))*t + 0.9375f) + b;
				}
				else {
					return c*(7.5625f*(t -= (2.625f / 2.75f))*t + 0.984375f) + b;
				}
			}

			float easeInOutBounce(float x, float t, float b, float c, float d) {
				if (t < d / 2) return easeInBounce(x, t*2.0f, 0, c, d) * 0.5f + b;
				return easeOutBounce(x, t*2.0f - d, 0, c, d) * 0.5f + c*0.5f + b;
			}
		};
	} /* namespace Drawing */
} /* namespace System */

#endif /* SYSTEM_DRAWING_EASING_H_ */
