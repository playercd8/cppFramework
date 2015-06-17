/*
* System.AutoPtr.h
*
* Code Status: Drafts
*  Created on: Taiwan
*      Author: player
*/

#ifndef SYSTEM_AUTOPTR_H_
#define SYSTEM_AUTOPTR_H_

#if _MSC_VER > 1000
#pragma once
#endif

#include "stdafx.h"
#include <stdlib.h>

namespace System {
	template<typename T>
	class AutoPtr
	{
	protected:
		T* _ptr;

	public:
		AutoPtr(T* p = NULL) :
			_ptr(p) {
		}

		AutoPtr(AutoPtr<T>& p) :
			_ptr(p.Release()) {
		}

		AutoPtr<T>& operator=(AutoPtr<T>& p) {
			Reset(p.Release());
			return *this;
		}

		virtual ~AutoPtr() {
			Reset();
		}

		inline void operator=(T* p) const {
			Reset(p);
		}

		inline operator T*() {
			return _ptr;
		}

		inline bool operator==(T* p) const {
			return _ptr == p;
		}

		inline bool operator!=(T* p) const {
			return _ptr != p;
		}

		inline T& operator*() const {
			return *_ptr;
		}

		inline T* operator->() const {
			return _ptr;
		}

		inline T* Release()	{
			T* pTmp = _ptr;
			_ptr = NULL;
			return pTmp;
		}

		inline void Reset(T* p = NULL)
		{
			if (_ptr) && (p != _ptr)
				delete _ptr;
			_ptr = p;
		}

		inline bool IsEmpty() {
			return (_ptr == NULL);
		}
	};

	template<typename T>
	inline void SafeDelete(T* ptr) {
		if (ptr) {
			delete ptr;
			ptr = NULL;
		}
	}

	template<typename T>
	inline void SafeDeleteArray(T* ptr) {
		if (ptr) {
			delete[] ptr;
			ptr = NULL;
		}
	}
} /* namespace System */

#endif /*  SYSTEM_AUTOPTR_H_ */
