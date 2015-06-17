/*
* System.Number.h
*
* Code Status: Drafts
*  Created on: Taiwan
*      Author: player
*/

#ifndef SYSTEM_NUMBER_H_
#define SYSTEM_NUMBER_H_

#if _MSC_VER > 1000
	#pragma once
#endif

#include "stdafx.h"
#include <cmath>	// atof
#include "System.String.h"
#include "System.IParseable.h"
#include "System.IFormattable.h"

namespace System {

	template <typename T>
	class Number:
		public IComparable<T>,
		public IParseable<T>,
		public IFormattable
	{
	private:
		T _val;

	//protected:

	public:
		typedef Number<T> NumberType;

		Number(T val = 0):
			_val(val) {
		}

		Number(LPCTSTR pStr):
			_val(Parse(pStr)) {
		}

		virtual ~Number() {
		}

		//Overloading assignments
		inline NumberType& operator=(T& val) {
			_val = val;
			return *this;
		}

		inline operator T() {
			return _val;
		}

		inline friend NumberType& operator += (T& num) {
			_val += num;
			return *this;
		}

		inline friend NumberType& operator -= (T& num) {
			_val -= num;
			return *this;
		}

		inline friend NumberType& operator *= (T& num) {
			_val *= num;
			return *this;
		}

		inline friend NumberType& operator /= (T& num) {
			_val /= num;
			return *this;
		}


		// binary operators
		inline NumberType operator + (T& num) const {
			NumberType ret(_val + num);
			return ret;
		}

		inline NumberType operator - (T& num) const {
			NumberType ret(_val - num);
			return ret;
		}

		inline NumberType operator * (T& num) const {
			NumberType ret(_val * num);
			return ret;
		}

		inline NumberType operator / (T& num) const {
			NumberType ret(_val / num);
			return ret;
		}

		inline bool operator == (T& num) const {
			return (_val == num);
		}

		inline bool operator != (T& num) const {
			return (_val != num);
		}

		inline bool operator > (T& num) const {
			return (_val > num);
		}

		inline bool operator < (T& num) const {
			return (_val < num);
		}

		inline bool operator >= (T& num) const {
			return (_val >= num);
		}

		inline bool operator <= (T& num) const {
			return (_val <= num);
		}


		int CompareTo(T& other) {
			if (_val < other)
				return -1;
			if (_val > other)
				return 1;
			return 0;
		}

	
		String ToString(LPCTSTR format = NULL) {
			return _toString(format, _val);
		}
	};

	class Double: public Number<double> {};
	class Float: public Number<float> {};	
	class Int8 : public Number<__int8> {};
	class Int16 : public Number<__int16> {};
	class Int32: public Number<__int32> {};
	class Int64: public Number<__int64> {};
	class Long: public Number<long> {};
	class UInt8 : public Number<unsigned __int8> {};
	class UInt16 : public Number<unsigned __int16> {};
	class UInt32 : public Number<unsigned __int32> {};
	class UInt64 : public Number<unsigned __int64> {};


	template <typename T=double>
	T Number<T>::Parse(LPCTSTR pStr) {
#ifdef _UNICODE
		return ::_wtof(pStr);
#else
		return ::atof(pStr);
#endif
	}
	
	template <typename T=float>
	T Number<T>::Parse(LPCTSTR pStr) {
#ifdef _UNICODE
		return ::_wtof(pStr);
#else
		return ::atof(pStr);
#endif
	}

	template <typename T=__int8>
	T Number<T>::Parse(LPCTSTR pStr) {
#ifdef _UNICODE
		return ::_wtoi(pStr);
#else
		return ::atoi(pStr);
#endif
	}

	template <typename T=__int16>
	T Number<T>::Parse(LPCTSTR pStr) {
#ifdef _UNICODE
		return ::_wtoi(pStr);
#else
		return ::atoi(pStr);
#endif
	}

	template <typename T=__int32>
	T Number<T>::Parse(LPCTSTR pStr) {
#ifdef _UNICODE
		return ::_wtoi(pStr);
#else
		return ::atoi(pStr);
#endif
	}

	template <typename T=__int64>
	T Number<T>::Parse(LPCTSTR pStr) {
#ifdef _UNICODE
		return ::_wtoi64(pStr);
#else
		return ::_atoi64(pStr);
#endif
	}
	
	template <typename T=long>
	T Number<T>::Parse(LPCTSTR pStr) {
#ifdef _UNICODE
		return ::_wtol(pStr);
#else
		return ::atol(pStr);
#endif
	}

	template <typename T=unsigned __int8>
	T Number<T>::Parse(LPCTSTR pStr) {
#ifdef _UNICODE
		return ::_wtoi(pStr);
#else
		return ::atoi(pStr);
#endif
	}

	template <typename T=unsigned __int16>
	T Number<T>::Parse(LPCTSTR pStr) {
#ifdef _UNICODE
		return ::_wtoi(pStr);
#else
		return ::atoi(pStr);
#endif
	}

	template <typename T=unsigned __int32>
	T Number<T>::Parse(LPCTSTR pStr) {
#ifdef _UNICODE
		return ::_wtoi(pStr);
#else
		return ::atoi(pStr);
#endif
	}

	template <typename T=unsigned __int64>
	T Number<T>::Parse(LPCTSTR pStr) {
#ifdef _UNICODE
		return ::_wtoi64(pStr);
#else
		return ::_atoi64(pStr);
#endif
	}



} /* namespace System */

#endif /* SYSTEM_DOUBLE_H_ */
