/*
* System.ComPtr.h
*
* Code Status: Drafts
*  Created on: Taiwan
*      Author: player
*/

#ifndef SYSTEM_COMPTR_H_
#define SYSTEM_COMPTR_H_

#if _MSC_VER > 1000
#pragma once
#endif

#include "stdafx.h"
#include <stdlib.h>

namespace System {
	template<typename T>
	class ComPtr
	{
	protected:
		T* _ptr;

	public:
		ComPtr(T* p = NULL) :
			_ptr(p) {
			SetComPtr(p);
		}

		ComPtr(const ComPtr& rhs) {
			_ptr = NULL;
			SetComPtr(rhs._ptr);
		}

		virtual ~ComPtr() {
			Release();
		}

		inline ComPtr& operator=(const ComPtr& rhs) const {
			SetComPtr(rhs._ptr);
			return *this;
		}

		inline T* operator=(T* p) {
			SetComPtr(p);
			return p;
		}

		inline operator T* () {
			return _ptr;
		}

		inline T* operator->() {
			return _ptr;
		}

		inline T* GetPtr() {
			return _ptr;
		}

		/*
		operator T** () {
		Release();
		return &_ptr;
		}
		*/

		inline operator void** () {
			SafeRelease(_ptr);
			return (void**)&_ptr;
		}

		inline bool IsEmpty() {
			return (_ptr == NULL);
		}

		inline void SetComPtr(T* p) {
			SafeRelease(_ptr);
			_ptr = p;
			if (_ptr) {
				_ptr->AddRef();
			}
		}

		inline void Release() {
			SafeRelease(_ptr);
		}
	};

	template<typename T>
	inline void SafeRelease(T* ptr) {
		if (ptr) {
			ptr->Release();
			ptr = NULL;
		}
	}
} /* namespace System */

#endif /*  SYSTEM_COMPTR_H_ */
