/*
* System.String.cpp
*
* Code Status: Drafts
*  Created on: Taiwan
*      Author: player
*/

#define _CRT_SECURE_NO_WARNINGS 1

#include "../include/stdafx.h"
#include "../include/System.String.h"
#include <varargs.h>

namespace System {
	//---------------------------------------------------------------------------------------------------------
	// class  CA2W
#pragma region class CA2W
	CA2W::CA2W(LPCSTR pStr) {
		UINT nCodePage = GetACP();
		int nLengthA = strlen(pStr) + 1;
		int nLengthW = ::MultiByteToWideChar(nCodePage, 0, pStr, nLengthA, NULL, 0);
		_ptr = new WCHAR[nLengthW + 1];
		::MultiByteToWideChar(nCodePage, 0, pStr, nLengthA, _ptr, nLengthW);
	}

	CA2W::~CA2W() {
		delete _ptr;
	}

	CA2W::operator LPCWSTR() {
		return _ptr;
	}
#pragma endregion class CA2W

	//---------------------------------------------------------------------------------------------------------
	// class CW2A
#pragma region class CW2A
	CW2A::CW2A(LPCWSTR pStr) {
		UINT nCodePage = GetACP();
		int nLengthW = wcslen(pStr) + 1;
		int nLengthA = ::WideCharToMultiByte(nCodePage, 0, pStr, nLengthW, NULL, 0, NULL, NULL);
		_ptr = new CHAR[nLengthA + 1];
		WideCharToMultiByte(nCodePage, 0, pStr, nLengthW, _ptr, nLengthA, NULL, NULL);
	}

	CW2A::~CW2A() {
		delete _ptr;
	}

	CW2A::operator LPCSTR() {
		return _ptr;
	}

#pragma endregion class CW2A

	//---------------------------------------------------------------------------------------------------------
	// class StringBasic
#pragma region class StringBasic

	template<typename T>
	void StringBasic<T>::Format(LPCSTR lpszFormat, ...) {
		va_list arguments;
		va_start(arguments, lpszFormat);
		CHAR* pBuf = NULL;
		int iCounter = 1, uTotal = 0;
		do {
			int nLen = sizeof(CHAR)* iCounter * 1024;
			pBuf = (CHAR*)realloc((void*)pBuf, nLen);
			if (!pBuf)
				return;

			uTotal = ::_vsnprintf(pBuf, nLen - 1, lpszFormat, arguments);
			// for some implementations
			if (uTotal == -1 || (uTotal == nLen - 1)) {
				pBuf[nLen - 1] = '\0';
				if (iCounter == 7)
					break;
			}
			else {
				pBuf[uTotal] = '\0';
				break;
			}
		} while (true);

		va_end(arguments);

		//assign(pBuf);
		*this = pBuf;

		free(pBuf);
	}

	void StringW::Format(LPCWSTR lpszFormat, ...) {
		va_list arguments;
		va_start(arguments, lpszFormat);
		WCHAR* pBuf = NULL;
		int iCounter = 1, uTotal = 0;
		do {
			int nLen = sizeof(WCHAR)* iCounter * 1024;
			pBuf = (WCHAR*)realloc((void*)pBuf, nLen);
			if (!pBuf)
				return;

			uTotal = ::_vsnwprintf(pBuf, nLen - 1, lpszFormat, arguments);
			// for some implementations
			if (uTotal == -1 || (uTotal == nLen - 1)) {
				pBuf[nLen - 1] = L'\0';
				if (iCounter == 7)
					break;
			}
			else {
				pBuf[uTotal] = L'\0';
				break;
			}
		} while (true);

		va_end(arguments);

		//assign(pBuf);
		*this = pBuf;

		free(pBuf);
	}

#pragma endregion class StringBasic

	//---------------------------------------------------------------------------------------------------------
	// class StringA
#pragma region class StringA

	const StringA StringA::EmptyString;

	void StringA::Format(LPCWSTR lpszFormat, ...) {
	}
#if defined(_WIN32)
	BSTR StringA::AllocSysString() const {
		UINT nACP = GetACP();
		int nLen = ::MultiByteToWideChar(nACP, 0, c_str(), size(), NULL, NULL);
		BSTR bstr = ::SysAllocStringLen(NULL, nLen);
		if (bstr != NULL)
			::MultiByteToWideChar(nACP, 0, c_str(), size(), bstr, nLen);
		return bstr;
	}
#endif

#pragma region class StringA

	//---------------------------------------------------------------------------------------------------------
	// class StringW

#pragma region class StringW
	const StringW StringW::EmptyString;

#if defined(_WIN32)
	BSTR StringW::AllocSysString() const {
		BSTR bstr = ::SysAllocStringLen(NULL, size());
		if (bstr != NULL)
			wcscpy(bstr, c_str());
		return bstr;
	}
#endif

#pragma region class StringW
} /* namespace System */