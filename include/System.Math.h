/*
 * System.Math.h
 *
 * Code Status: Drafts
 *  Created on: Taiwan
 *      Author: player
 */

#ifndef SYSTEM_MATH_H_
#define SYSTEM_MATH_H_

#if _MSC_VER > 1000
#pragma once
#endif

#include <algorithm>
#include <cmath>
#include <vector>

namespace System {
	/*
	<summary>
	Provides constants and static methods for trigonometric, logarithmic, and other common mathematical functions.
	提供常數和靜態方法，三角函數，對數和其他常見的數學函數。
	</summary>
	*/
	namespace Math {
		/*
		<summary>
		Provides constants
		提供常數
		</summary>
		*/
		namespace Constants {
			//常數的數值精度
			typedef float ConstantType;
			//typedef double ConstantType;
			//typedef long double ConstantType;

			///<summary>常數 E</summary>
			const ConstantType _E = std::exp(static_cast<ConstantType>(1));

			//<summary>常數 log2(e)</summary>
			const ConstantType _LOG2E = std::log2(static_cast<ConstantType>(_E));

			//<summary>常數 log10(e)</summary>
			const ConstantType _LOG10E = std::log10(static_cast<ConstantType>(_E));

			//<summary>常數 ln(2)</summary>
			const ConstantType _LN2 = std::log(static_cast<ConstantType>(2));

			//<summary>常數 ln(10)</summary>
			const ConstantType _LN10 = std::log(static_cast<ConstantType>(10));

			//<summary>常數 PI</summary>
			const ConstantType _PI = std::atan(static_cast<ConstantType>(1)) * static_cast<ConstantType>(4);

			//<summary>常數 1/PI</summary>
			const ConstantType _1DIVPI = static_cast<ConstantType>(1) / _PI;

			//<summary>常數 2*PI</summary>
			const ConstantType _2PI = static_cast<ConstantType>(2) * _PI;

			//<summary>常數 1/(2*PI)</summary>
			const ConstantType _1DIV2PI = static_cast<ConstantType>(1) / _2PI;

			//<summary>常數 PI/2</summary>
			const ConstantType _PIDIV2 = _PI / static_cast<ConstantType>(2);

			//<summary>常數 2/PI</summary>
			const ConstantType _2DIVPI = static_cast<ConstantType>(2) / _PI;

			//<summary>常數 PI/4</summary>
			const ConstantType _PIDIV4 = _PI / static_cast<ConstantType>(4);

			//<summary>常數 4/PI</summary>
			const ConstantType _4DIVPI = static_cast<ConstantType>(4) / _PI;

			//<summary>常數 PI/180</summary>
			const ConstantType _PIDIV180 = _PI / static_cast<ConstantType>(180);

			//<summary>常數 180/PI</summary>
			const ConstantType _180DIVPI = static_cast<ConstantType>(180) / _PI;

			//<summary>常數 2/sqrt(pi)</summary>
			const ConstantType _2DIVSQRTPI = static_cast<ConstantType>(2) / std::sqrt(_PI);

			//<summary>常數 sqrt(2)</summary>
			const ConstantType _SQRT2 = std::sqrt(static_cast<ConstantType>(2));

			//<summary>常數 1/sqrt(2)</summary>
			const ConstantType _1DIVSQRT2 = static_cast<ConstantType>(1) / std::sqrt(static_cast<ConstantType>(2));
		} /* namespace Constants */

		//-----------------------------------------------
		//角度轉換
		template <typename T> inline T ToRadian(T degree) {
			return degree * Constants::_PIDIV180;
		}

		template <typename T> inline T ToDegree(T radian) {
			return radian * Constants::_180DIVPI;
		}
		//-----------------------------------------------

		//<summary>絕對值</summary>
		template <typename T> inline T Abs(T x) {
			return (x >= static_cast<T>(0)) ? x : -x;
		}

		//<summary>距離</summary>
		template <typename T> inline T Distance(T value1, T value2) {
			return Math::Abs(value1 - value2);
		}

		//<summary>夾鉗 ( min < value < max )</summary>
		template <typename T> inline T Clamp(T value, T min, T max) {
			return Min(Max(min, value), max);
		}

		//<summary>大於或等於 x 的最小整數值</summary>
		template <typename T> inline T Ceiling(T x) {
			return std::ceil(x);
		}

		//<summary>階乘 (n!)</summary>
		template <typename T> T Factorial(T n) {
			T ret = n;
			for (T x = n-1; x > 1; x--)
				ret *= x;
		
			return ret;
		}

		//<summary>排列 Permutation (在n個之中隨機取出k個, 有幾種)</summary>
		template <typename T> T Permutation(T n, T k) {
			T ret = 1;
			for (T x = n; x >= k; x--)
				ret *= x;
			return ret;
		}

		//<summary>組合 Combination (在n個之中隨機取出k個, 組合有幾種)</summary>
		template <typename T> T Combination(T n, T k) {
			T ret = 1;
			for (T x = n; x >= k; x--)
				ret *= x;

			return (ret / Factorial(k));
		}

		//<summary>小於或等於 x 的最小整數值</summary>
		template <typename T> inline T Floor(T x) {
			return std::floor(x);
		}

		//<summary>線性內插值</summary>
		template <typename T> inline T Lerp(T value1, T value2, T amount) {
			return value1 + (value2 - value1) * amount;
		}

		//-----------------------------------------------
		// 2個傳入參數

		//<summary>算術平均數</summary>
		template <typename T> inline T Average(T x, T y) {
			return (x + y) / static_cast<T>(2);
		}

		//<summary>最小值</summary>
		template <typename T> inline T Min(T x, T y) {
			return (x <= y) ? x : y;
		}

		//<summary>最大值</summary>
		template <typename T> inline T Max(T x, T y) {
			return (x >= y) ? x : y;
		}

		//<summary>加總</summary>
		template <typename T> inline T Sum(T x, T y) {
			return (x + y);
		}

		//-----------------------------------------------
		// 多個傳入參數 (使用陣列)

		//<summary>算術平均數</summary>
		template <typename T> inline T Average(int count, T arg[]) {
			T sum = 0;

			for (int i = 0; i < count; i++)
				sum += arg[i];

			return sum / count;
		}

		//<summary>最小值</summary>
		template <typename T> inline T Min(int count, T arg[]) {
			T ret = arg[0];
			T x;

			for (int i = 1; i < count; i++) {
				x = arg[i];
				if (ret > x)
					ret = x;
			}

			return ret;
		}

		//<summary>最大值</summary>
		template <typename T> T Max(int count, T arg[]) {
			T ret = arg[0];
			T x;

			for (int i = 1; i < count; i++) {
				x = arg[i];
				if (ret < x)
					ret = x;
			}

			return ret;
		}

		//<summary>加總</summary>
		template <typename T> T Sum(int count, T arg[]) {
			T sum = 0;

			/* access all the arguments assigned to valist */
			for (int i = 0; i < count; i++)
				sum += arg[i];

			return sum;
		}
				
		//-----------------------------------------------
		// 多個傳入參數 (動態傳入參數)

		//<summary>算術平均數</summary>
		//<remarks>
		//1.若傳入浮點數, 限定使用double; 因為浮點數在推入堆疊時, 若無明確宣告資料型別, 會當成double來存放
		//2.若傳入整數, 限定使用int; 因為整數在推入堆疊時, 若無明確宣告資料型別, 會當成int來存放
		//</remarks>
		template <typename T> T Average(int count, T arg1, T arg2, ...) {
			va_list valist;
			T sum = 0;

			/* initialize valist for num number of arguments */
			va_start(valist, count);

			/* access all the arguments assigned to valist */
			for (int i = 0; i < count; i++)
				sum += va_arg(valist, T);

			/* clean memory reserved for valist */
			va_end(valist);

			return sum / count;
		}

		//<summary>最小值</summary>
		//<remarks>
		//1.若傳入浮點數, 限定使用double; 因為浮點數在推入堆疊時, 若無明確宣告資料型別, 會當成double來存放
		//2.若傳入整數, 限定使用int; 因為整數在推入堆疊時, 若無明確宣告資料型別, 會當成int來存放
		//</remarks>
		template <typename T> T Min(int count, T arg1, T arg2, ...) {
			va_list valist;

			/* initialize valist for num number of arguments */
			va_start(valist, count);
			T ret = va_arg(valist, T);
			T x;

			/* access all the arguments assigned to valist */
			for (int i = 1; i < count; i++) {
				x = va_arg(valist, T);
				if (ret > x)
					ret = x;
			}

			/* clean memory reserved for valist */
			va_end(valist);

			return ret;
		}

		//<summary>最大值</summary>
		//<remarks>
		//1.若傳入浮點數, 限定使用double; 因為浮點數在推入堆疊時, 若無明確宣告資料型別, 會當成double來存放
		//2.若傳入整數, 限定使用int; 因為整數在推入堆疊時, 若無明確宣告資料型別, 會當成int來存放
		//</remarks>
		template <typename T> T Max(int count, T arg1, T arg2, ...) {
			va_list valist;

			/* initialize valist for num number of arguments */
			va_start(valist, count);
			T ret = va_arg(valist, T);
			T x;

			/* access all the arguments assigned to valist */
			for (int i = 1 ; i < count; i++) {
				x = va_arg(valist, T);
				if (ret < x)
					ret = x;
			}

			/* clean memory reserved for valist */
			va_end(valist);

			return ret;
		}

		//<summary>加總</summary>
		//<remarks>
		//1.若傳入浮點數, 限定使用double; 因為浮點數在推入堆疊時, 若無明確宣告資料型別, 會當成double來存放
		//2.若傳入整數, 限定使用int; 因為整數在推入堆疊時, 若無明確宣告資料型別, 會當成int來存放
		//</remarks>
		template <typename T> T Sum(int count, T arg1, T arg2, ...) {
			va_list valist;
			T sum = T(0);

			/* initialize valist for num number of arguments */
			va_start(valist, count);

			/* access all the arguments assigned to valist */
			for (int i = 0; i < count; i++)
				sum += va_arg(valist, T);

			/* clean memory reserved for valist */
			va_end(valist);

			return sum;
		}

		//-----------------------------------------------
		// 多個傳入參數 (配合STL使用)
		//<summary>算術平均數</summary>
		template<typename T, typename I = std::vector<T>::iterator>
		inline T Average(I _F, I _L) {
			T total = static_cast<T>(0);
			T count = static_cast<T>(0);
			for (; _F != _L; ++_F, ++count)
				total += *_F;
			return (total / count);
		}

		//<summary>最小值</summary>
		template<typename T, typename I = std::vector<T>::iterator>
		inline T Min(I _F, I _L) {
			T ret = *_F;
			_F++;
			for (; _F != _L; ++_F)
				if (ret > *_F)
					ret = *_F;
			return ret;
		}

		//<summary>最大值</summary>
		template<typename T, typename I = std::vector<T>::iterator>
		inline T Max(I _F, I _L) {
			T ret = *_F;
			_F++;
			for (; _F != _L; ++_F)
				if (ret < *_F)
					ret = *_F;
			return ret;
		}

		//<summary>加總</summary>
		template<typename T, typename I = std::vector<T>::iterator>
		inline T Sum(I _F, I _L) {
			T ret = static_cast<T>(0);
			for (; _F != _L; ++_F)
				ret += *_F;
			return ret;
		}

		//-----------------------------------------------

		template <typename T> inline T Exp(T num) {
			return std::exp(num);
		}

		template <typename T> inline T Log(T num) {
			return std::log(num);
		}

		template <typename T> inline T Log10(T num) {
			return std::log10(num);
		}

		//<summary>指數</summary>
		template <typename T> inline T Pow(T base, T expx) {
			return std::pow(base, expx);
		}

		//<summary>正負號</summary>
		template <typename T> inline int Sign(T x) {
			if (x < static_cast<T>(0))
				return -1;
			if (x > static_cast<T>(0))
				return 1;
			return 0;
		}

		//<summary>平方根 (Square root)</summary>
		template <typename T> inline T Sqrt(T x) {
			return std::sqrt(x);
		}

		//-----------------------------------------------
		//三角函數

		//<summary>三角函數Sine</summary>
		template <typename T> inline T Sin(T x) {
			return std::sin(x);
		}

		//<summary>三角函數Cosine</summary>
		template <typename T> inline T Cos(T x) {
			return std::cos(x);
		}

		//<summary>三角函數Tangent</summary>
		template <typename T> inline T Tan(T x) {
			return std::tan(x);
		}

		//<summary>三角函數Cotangent</summary>
		template <typename T> inline T Cot(T x) {
			return static_cast<T>(1) / std::tan(x);
		}

		//<summary>三角函數Secant</summary>
		template <typename T> inline T Sec(T x) {
			return static_cast<T>(1) / std::cos(x);
		}

		//<summary>三角函數Cosecant</summary>
		template <typename T> inline T Csc(T x) {
			return static_cast<T>(1) / std::sin(x);
		}

		//-----------------------------------------------
		//反三角函數

		//<summary>反三角函數Arcsine</summary>
		template <typename T> inline T ArcSin(T x) {
			return std::asin(x);
		}

		//<summary>反三角函數Arccosine</summary>
		template <typename T> inline T ArcCos(T x) {
			return std::acos(x);
		}

		//<summary>反三角函數Arctangent</summary>
		template <typename T> inline T ArcTan(T x) {
			return std::atan(x);
		}

		//<summary>反三角函數Arccotangent</summary>
		template <typename T> inline T ArcCot(T x) {
			return Constant::_PIDIV2 - std::atan(x);
		}

		//<summary>反三角函數Arcsecant</summary>
		template <typename T> inline T ArcSec(T x) {
			return std::acos(static_cast<T>(1) / x);
		}

		//<summary>反三角函數Arccosecant</summary>
		template <typename T> inline T ArcCsc(T x) {
			return std::asin(static_cast<T>(1) / x);
		}

		//-----------------------------------------------
		//雙曲函數

		//<summary>雙曲函數Hyperbolic Sine</summary>
		template <typename T>
		inline T Sinh(T x) {
			return std::sinh(x);
		}

		//<summary>雙曲函數Hyperbolic Cosine</summary>
		template <typename T> inline T Cosh(T x) {
			return std::cosh(x);
		}

		//<summary>雙曲函數Hyperbolic Tangent</summary>
		template <typename T> inline T Tanh(T x) {
			return std::tanh(x);
		}

		//<summary>雙曲函數Hyperbolic Cotangent</summary>
		template <typename T> inline T Coth(T x) {
			return static_cast<T>(1) / std::tanh(x);
		}

		//<summary>雙曲函數Hyperbolic Secant</summary>
		template <typename T> inline T Sech(T x) {
			return static_cast<T>(1) / std::cosh(x);
		}

		//<summary>雙曲函數Hyperbolic Cosecant</summary>
		template <typename T> inline T Csch(T x) {
			return static_cast<T>(1) / std::sinh(x);
		}

		//-----------------------------------------------
		//反雙曲函數
		template <typename T> inline T ArcSinh(T x) {
			return Log(x + Sqrt(x*x + static_cast<T>(1)));
		}

		template <typename T> inline T ArcCosh(T x) {
			return Log(x + Sqrt(x*x - static_cast<T>(1)));
		}

		template <typename T> inline T ArcTanh(T x) {
			return Log((x + static_cast<T>(1)) / (-x + static_cast<T>(1))) / static_cast<T>(2);
		}

		template <typename T> inline T ArcCoth(T x) {
			return Log((x + static_cast<T>(1)) / (x - static_cast<T>(1))) / static_cast<T>(2);
		}

		template <typename T> inline T ArcSech(T x) {
			T t = Sqrt(-x*x + static_cast<T>(1));
			return Log((t + static_cast<T>(1)) / (-t + static_cast<T>(1))) / static_cast<T>(2);
		}

		template <typename T> inline T ArcCsch(T x) {
			T t = Sqrt(-x*x + static_cast<T>(1));
			if (x < 0)
				return Log((-t + static_cast<T>(1)) / x);
			if (x > 0)
				return Log((t + static_cast<T>(1)) / x);
		}

		//-----------------------------------------------
		//其他

		template <typename T> inline T Barycentric(T value1, T value2, T value3, T amount1, T amount2) {
			return value1 + amount1 * (value2 - value1) + amount2 * (value3 - value1);
		}

		template <typename T> inline T CatmullRom(T value1, T value2, T value3, T value4, T amount) {
			T num = amount * amount;
			T num2 = amount * num;
			return 0.5f * (2.0f * value2 + (-value1 + value3) * amount
				+ (2.0f * value1 - 5.0f * value2 + 4.0f * value3 - value4) * num
				+ (-value1 + 3.0f * value2 - 3.0f * value3 + value4) * num2);
		}

		template <typename T> inline T Hermite(T value1, T tangent1, T value2, T tangent2, T amount)
		{
			T num = amount * amount;
			T num2 = amount * num;
			T num3 = 2.0f * num2 - 3.0f * num + 1.0f;
			T num4 = -2.0f * num2 + 3.0f * num;
			T num5 = num2 - 2.0f * num + amount;
			T num6 = num2 - num;
			return value1 * num3 + value2 * num4 + tangent1 * num5 + tangent2 * num6;
		}		

		template <typename T> inline T SmoothStep(T value1, T value2, T amount) {
			T num = Math::Clamp(amount, 0.0f, 1.0f);
			return Math::Lerp(value1, value2, num * num * (3.0f - 2.0f * num));
		}
	} /* namespace Math */
} /* namespace System */

#endif /* SYSTEM_MATH_H_ */
