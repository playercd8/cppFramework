/*
* System.Buffer.h
*
* Code Status: Drafts
*  Created on: Taiwan
*      Author: player
*/

#ifndef SYSTEM_BUFFER_H_
#define SYSTEM_BUFFER_H_

#if _MSC_VER > 1000
#pragma once
#endif

#include "stdafx.h"
#include <memory.h>
#include "System.AutoPtr.h"

typedef unsigned char BYTE;
typedef unsigned char* LPBYTE;

namespace System {
#pragma region Declared class
	class Buffer {
	private:
		LPBYTE _pBuff;
		int _size;
		int _pos;

	public:
		Buffer(int size, bool initZero = false);
		~Buffer();

		bool IsEmpty() const;
		int GetSize() const;
		void Clear();
		void Resize(int size);
		int GetPos();
		void SetPos(int pos);
		void Fill(BYTE value = 0);
		operator LPBYTE ();
		void* GetPtr();

		template <typename T> Buffer& operator << (T data);
		template <typename T> Buffer& operator >> (T& data);
		int Read(LPBYTE pDest, int offset, int len);
		int Write(LPBYTE pSrc, int offset, int len);

		inline Buffer& Append(Buffer& src);
		void Copy(Buffer& src);
	};
#pragma endregion Declared class

#pragma region Definition class

	inline Buffer::Buffer(int size, bool initZero) :
		_size(size), _pos(0) {
		_pBuff = new BYTE[size];
		if (initZero)
			Fill(0);
	}

	inline Buffer::~Buffer() {
		SafeDeleteArray(_pBuff);
	}

	inline bool Buffer::IsEmpty() const {
		return (_size == 0);
	}

	inline int Buffer::GetSize() const {
		return _size;
	}

	inline void Buffer::Clear() {
		if (_pBuff) {
			delete[] _pBuff;
			_pBuff = NULL;
		}
		_size = 0;
		_pos = 0;
	}

	inline void Buffer::Resize(int size) {
		if (size <= 0) {
			Clear();
		}
		else {
			LPBYTE pBuff = new BYTE[size];
			if (_pBuff) {
				::memcpy(pBuff, _pBuff, _size);
				delete[] _pBuff;
			}
			_size = size;
			_pBuff = pBuff;
		}
	}

	inline int Buffer::GetPos() {
		if (_pos >= 0 && _pos < _size)
			return _pos;
		else
			return 0;
	}

	inline void Buffer::SetPos(int pos) {
		if (pos >= 0 && pos < _size)
			_pos = pos;
	}

	inline void Buffer::Fill(BYTE value) {
		for (int i = 0; i < _size; i++)
			_pBuff[i] = value;
	}

	inline Buffer::operator LPBYTE () {
		return _pBuff;
	}

	inline void* Buffer::GetPtr() {
		return _pBuff;
	}

	template <typename T>
	inline Buffer& Buffer::operator << (T data) {
		int s = _pos + sizeof(T);
		if ((s > _size))
			Resize(s);

		T* pBuff = (T*)&_pBuff[_pos];
		*pBuff = data;
		_pos += sizeof(T);

		return *this;
	}

	template <typename T>
	inline Buffer& Buffer::operator >> (T& data) {
		if ((_pos + sizeof(T) <= _size)) {
			T* pBuff = (T*)&_pBuff[_pos];
			data = *pBuff;
			_pos += sizeof(T);
		}
		return *this;
	}

	inline int Buffer::Read(LPBYTE pDest, int offset, int len) {
		try {
			if ((_pos + len <= _size)) {
				::memcpy(&pDest[offset], &_pBuff[_pos], len);
				_pos += len;
			}
			return len;
		}
		catch (...) {}
		return -1;
	}

	inline int Buffer::Write(LPBYTE pSrc, int offset, int len) {
		try {
			int s = _pos + len;
			if ((s > _size))
				Resize(s);

			::memcpy(&_pBuff[_pos], &pSrc[offset], len);
			_pos += len;

			return len;
		}
		catch (...) {}
		return -1;
	}

	inline Buffer& Buffer::Append(Buffer& src) {
		int size = GetSize();
		int count = src.GetSize();
		int newSize = size + count;
		Resize(newSize);
		LPBYTE pBuff = src;
		::memcpy(&_pBuff[size], pBuff, count);
		return *this;
	}

	inline void Buffer::Copy(Buffer& src) {
		int count = src.GetSize();
		Resize(count);
		LPBYTE pBuff = src;
		::memcpy(_pBuff, pBuff, count);
	}
#pragma endregion Definition class
} /* namespace System */

#endif /* SYSTEM_BUFFER_H_ */