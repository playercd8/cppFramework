/*
 * System.String.h
 *
 * Code Status: Drafts
 *  Created on: Taiwan
 *      Author: player
 */

#ifndef SYSTEM_STRING_H_
#define SYSTEM_STRING_H_

#if _MSC_VER > 1000
#pragma once
#endif

#include "stdafx.h"
#include <tchar.h>
#include <xstring>
#include <algorithm>
#include "System.IComparable.h"

typedef char CHAR;
typedef wchar_t WCHAR;
typedef const char* LPCSTR;
typedef const wchar_t* LPCWSTR;
typedef char* LPSTR;
typedef wchar_t* LPWSTR;

#ifdef _UNICODE
typedef wchar_t TCHAR;
typedef wchar_t* LPTSTR;
typedef const wchar_t* LPCTSTR;
#else
typedef char TCHAR;
typedef char* LPTSTR;
typedef const char* LPCTSTR;
#endif

#if !defined(BSTR)
typedef wchar_t* BSTR;
#endif

namespace System {
	//---------------------------------------------------------------------------------------------------------
	// class  CA2W
#pragma region class CA2W
	class CA2W {
	public:
		CA2W(LPCSTR pStr);
		~CA2W();
		operator LPCWSTR();

	protected:
		LPWSTR _ptr;
	};
#pragma endregion class CA2W

	//---------------------------------------------------------------------------------------------------------
	// class  CW2A
#pragma region class CW2A
	class CW2A {
	public:
		CW2A(LPCWSTR pStr);
		~CW2A();
		operator LPCSTR();

	protected:
		LPSTR _ptr;
	};
#pragma endregion class CW2A

	//---------------------------------------------------------------------------------------------------------
	// class StringBasic
#pragma region class StringBasic
	template<typename T>
	class StringBasic :
		public std::basic_string < T >
	{
	protected:
		static int __strlen(const T* pStr) {
			return pStr ? std::char_traits<T>::length(pStr) : 0;
		}

	public:
		typedef typename StringBasic<T> StrType;
		typedef typename std::basic_string<T> Inherited;

		// Construction Methods
		StringBasic();
		StringBasic(LPCSTR pStr);
		StringBasic(LPCWSTR pStr);
		StringBasic(CHAR ch, int repeat = 1);
		StringBasic(WCHAR ch, int repeat = 1);
		StringBasic(LPCSTR pStr, int length);
		StringBasic(LPCWSTR pStr, int length);
		StringBasic(const std::string& str);
		StringBasic(const std::wstring& str);
		StringBasic(const StringBasic<CHAR>& str);
		StringBasic(const StringBasic<WCHAR>& str);

		virtual ~StringBasic() {
		}

		const static StringBasic<T> EmptyString;

		//Overloading assignments
		StrType& operator = (LPCSTR pStr);
		StrType& operator = (LPCWSTR pStr);
		StrType& operator = (const std::string& str);
		StrType& operator = (const std::wstring& str);
		StrType& operator = (const StringBasic<CHAR>& str);
		StrType& operator = (const StringBasic<WCHAR>& str);

		operator LPCSTR() const;
		operator LPCWSTR() const;

		//String as an Array Methods
		int GetLength() const {
			return size();
		}

		bool IsEmpty() const {
			return empty();
		}

		void Empty() {
			erase(begin(), end());
		}

		T GetAt(int index) const {
			return at(index);
		}

		T operator[] (int index) const {
			return at(index);
		}

		void SetAt(int index, T ch) {
			*at(index) = ch;
		}

		//Comparison Methods
		int Compare(const T* pStr) const {
			return compare(pStr);
		}

		int CompareNoCase(const T* pStr) const {
			String str1(c_str());
			String str2(pStr);
			str1.MakeLower();
			str2.MakeLower();
			return str1.Compare(str2);
		}

		bool operator != (const T* pStr) {
			return Compare(pStr) != 0;
		}

		bool operator == (const T* pStr) {
			return Compare(pStr) == 0;
		}

		//Extraction Methods
		StrType Mid(int first, int count) const {
			return substr(first, count);
		}

		StrType Mid(int first) const {
			return substr(first);
		}

		StrType Left(int count) const {
			return substr(0, count);
		}

		StrType Right(int count) const {
			nCount = (int)size() < nCount ? (int)size() : nCount;
			return substr(size() - nCount);
		}

		//Other Conversion Methods
		StrType& MakeUpper() {
			std::transform(begin(), end(), begin(), toupper);
			return *this;
		}

		StrType& MakeLower() {
			std::transform(begin(), end(), begin(), tolower);
			return *this;
		}

		StrType& MakeReverse() {
			std::reverse(begin(), end());
			return *this;
		}

		//void TrimLeft() {};
		StrType& TrimLeft(T chTarget) {
			size_type idx = find_first_not_of(chTarget);
			if (idx != npos)
				erase(0, idx);
			else
				erase();
			return *this;
		}

		StrType& TrimLeft(const T* pTargets) {
			size_type idx = find_first_not_of(pTargets);
			if (idx != npos)
				erase(0, idx);
			else
				erase();
			return *this;
		}

		//void TrimRight() {};
		StrType& TrimRight(T chTarget) {
			size_type idx = find_last_not_of(chTarget);
			if (idx != npos)
				erase(++idx);
			return *this;
		}

		StrType& TrimRight(const T* pTargets) {
			size_type idx = find_last_not_of(pTargets);
			if (idx != npos)
				erase(++idx);
			return *this;
		}

		StrType& Trim(T chTarget) {
			return TrimRight(chTarget).TrimLeft(chTarget);
		}

		StrType& Trim(const T* pTargets) {
			return TrimRight(pTargets).TrimLeft(pTargets);
		}

		//Searching Methods
		int Find(T ch) const {
			return find_first_not_of(ch);
		}

		int Find(T ch, int start) const {
			return find_first_not_of(ch, start);
		}

		int Find(const T* lpszSub) const {
			return find_first_not_of(lpszSub);
		}

		int Find(const T* pSubStr, int start) {
			return find_first_not_of(pSubStr, start);
		}

		int ReverseFind(T ch) const {
			return find_last_not_of(ch);
		}

		int FindOneOf(const T* lpszCharSet) const {
			return find_last_not_of(lpszCharSet);
		}

		//Buffer Access Methods
		T* GetBuffer(int minBufLength) {
			if ((int)size() < minBufLength)
				resize(minBufLength);
			return empty() ? const_cast<TCHAR*>(data()) : &(at(0));
		}

		T* GetBufferSetLength(int newLength){
			resize(newLength);
			return empty() ? const_cast<TCHAR*>(data()) : &(at(0));
		}

		void ReleaseBuffer(int newLength = -1) {
			resize(newLength > -1 ? newLength : __strlen(c_str()));
		}

		int CompareTo(T& other) {
			if (_val < other)
				return -1;
			if (_val > other)
				return 1;
			return 0;
		}

#if defined(_WIN32)
		BSTR AllocSysString() const;
#endif

		void Format(LPCSTR lpszFormat, ...);
		void Format(LPCWSTR lpszFormat, ...);
	};

	template<typename T> inline bool operator < (const StringBasic<T>& left, const StringBasic<T>& right) {
		return (left.Compare(right) < 0);
	}

	template<typename T> inline bool operator > (const StringBasic<T>& left, const StringBasic<T>& right) {
		return (left.Compare(right) > 0);
	}

	template<typename T> inline bool operator <= (const StringBasic<T>& left, const StringBasic<T>& right) {
		return (left.Compare(right) <= 0);
	}

	template<typename T> inline bool operator >= (const StringBasic<T>& left, const StringBasic<T>& right) {
		return (left.Compare(right) >= 0);
	}

	template<typename T> inline bool operator == (const StringBasic<T>& left, const StringBasic<T>& right) {
		return (left.Compare(right) == 0);
	}

	template<typename T> inline bool operator != (const StringBasic<T>& left, const StringBasic<T>& right) {
		return (left.Compare(right) != 0);
	}

#pragma endregion class StringBasic

	//---------------------------------------------------------------------------------------------------------
	// class  StringA
#pragma region class StringA

	typedef StringBasic <char> StringA;

	// Construction Methods
	inline StringA::StringBasic() {
		assign("");
	}

	inline StringA::StringBasic(LPCSTR pStr) {
		assign(pStr);
	}

	inline StringA::StringBasic(LPCWSTR pStr) {
		assign(CW2A(pStr));
	}

	inline StringA::StringBasic(CHAR ch, int repeat) {
		assign(ch, repeat);
	}

	inline StringA::StringBasic(WCHAR ch, int repeat) {
		const WCHAR Src[2] = { ch, 0 };
		LPCWSTR pStr = &Src[0];
		LPCSTR pDest = CW2A(pStr);
		assign(pDest[0], repeat);
	}

	inline StringA::StringBasic(LPCSTR pStr, int length)  {
		assign(pStr, length);
	}

	inline StringA::StringBasic(LPCWSTR pStr, int length) {
		assign(CW2A(pStr), length);
	}

	inline StringA::StringBasic(const std::string& str) {
		assign(str.c_str());
	}

	inline StringA::StringBasic(const std::wstring& str) {
		assign(CW2A(str.c_str()));
	}

	inline StringA::StringBasic(const StringBasic<CHAR>& str) {
		assign(str.c_str());
	}

	inline StringA::StringBasic(const StringBasic<WCHAR>& str) {
		assign(CW2A(str.c_str()));
	}
	//-------------
	//Overloading assignments

	inline StringA::StrType& StringA::operator = (LPCSTR pStr) {
		assign(pStr);
		return *this;
	}

	inline StringA::StrType& StringA::operator = (LPCWSTR pStr) {
		assign(CW2A(pStr));
		return *this;
	}

	inline StringA::StrType& StringA::operator = (const std::string& str) {
		assign(str.c_str());
		return *this;
	}

	inline StringA::StrType& StringA::operator = (const std::wstring& str) {
		assign(CW2A(str.c_str()));
		return *this;
	}

	inline StringA::StrType& StringA::operator = (const StringBasic<CHAR>& str) {
		assign(str.c_str());
		return *this;
	}

	inline StringA::StrType& StringA::operator = (const StringBasic<WCHAR>& str) {
		assign(CW2A(str.c_str()));
		return *this;
	}

	inline StringA::operator LPCSTR() const {
		return c_str();
	}

	inline StringA::operator LPCWSTR() const {
		return CA2W(c_str());
	}

#pragma endregion class StringA

	//---------------------------------------------------------------------------------------------------------
	// class  StringW
#pragma region class StringW
	typedef StringBasic < wchar_t > StringW;

	// Construction Methods
	inline StringW::StringBasic() {
		assign(L"");
	}

	inline StringW::StringBasic(LPCSTR pStr) {
		assign(CA2W(pStr));
	}

	inline StringW::StringBasic(LPCWSTR pStr) {
		assign(pStr);
	}

	inline StringW::StringBasic(CHAR ch, int repeat) {
		const CHAR Src[2] = { ch, 0 };
		LPCSTR pStr = &Src[0];
		LPCWSTR pDest = CA2W(pStr);
		assign(pDest[0], repeat);
	}

	inline StringW::StringBasic(WCHAR ch, int repeat) {
		assign(ch, repeat);
	}

	inline StringW::StringBasic(LPCSTR pStr, int length)  {
		assign(CA2W(pStr), length);
	}

	inline StringW::StringBasic(LPCWSTR pStr, int length) {
		assign(pStr, length);
	}

	inline StringW::StringBasic(const std::string& str) {
		assign(CA2W(str.c_str()));
	}

	inline StringW::StringBasic(const std::wstring& str) {
		assign(str.c_str());
	}

	inline StringW::StringBasic(const StringBasic<CHAR>& str) {
		assign(CA2W(str.c_str()));
	}

	inline StringW::StringBasic(const StringBasic<WCHAR>& str) {
		assign(str.c_str());
	}
	//-------------
	//Overloading assignments

	inline StringW::StrType& StringW::operator = (LPCSTR pStr) {
		assign(CA2W(pStr));
		return *this;
	}

	inline StringW::StrType& StringW::operator = (LPCWSTR pStr) {
		assign(pStr);
		return *this;
	}

	inline StringW::StrType& StringW::operator = (const std::string& str) {
		assign(CA2W(str.c_str()));
		return *this;
	}

	inline StringW::StrType& StringW::operator = (const std::wstring& str) {
		assign(str.c_str());
		return *this;
	}

	inline StringW::StrType& StringW::operator = (const StringBasic<CHAR>& str) {
		assign(CA2W(str.c_str()));
		return *this;
	}
	inline StringW::StrType& StringW::operator = (const StringBasic<WCHAR>& str) {
		assign(str.c_str());
		return *this;
	}

	inline StringW::operator LPCSTR() const {
		return CW2A(c_str());
	}

	inline StringW::operator LPCWSTR() const {
		return c_str();
	}

#pragma endregion class StringW

#ifdef _UNICODE
	typedef StringW String;
#else
	typedef StringA String;
#endif
} /* namespace System */

#endif /* SYSTEM_STRING_H_ */