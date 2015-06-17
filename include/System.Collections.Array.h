/*
 * System.Collections.Array.h
 *
 * Code Status: Drafts
 *  Created on: Taiwan
 *      Author: player
 */

#ifndef SYSTEM_COLLECTIONS_ARRAY_H_
#define SYSTEM_COLLECTIONS_ARRAY_H_

#if _MSC_VER > 1000
#pragma once
#endif

#include "stdafx.h"
#include <vector>
#include <functional>

namespace System {
	namespace Collections {
		template <typename T>
		class Array :
			private std::vector < T >
		{
		public:
			//typedef
			typedef typename iterator Iterator;
			typedef typename const_iterator Const_Iterator;
			typedef typename std::vector<T> Inherited;

		protected:
			inline Iterator GetIterFromIndex(int index) {
				iterator iter = begin();
				iter += index;
				return iter;
			}

		public:
			//Attributes
			inline int GetCount() const {
				return size();
			}

			inline int GetSize() const {
				return size();
			}

			inline int GetUpperBound() const {
				return size() - 1;
			}

			inline bool IsEmpty() const {
				return empty();
			}

			inline void SetSize(int size)	{
				resize(size);
			}

			//Operations
			inline void RemoveAll() {
				clear();
			}

			//Element Access
			inline T& ElementAt(int index) {
				return at(index);
			}

			inline T& ElementAt(int index) const {
				return at(index);
			}

			inline T& GetAt(int index) {
				return at(index);
			}

			inline T& GetAt(int index) const {
				return at(index);
			}

			inline void SetAt(int index, const T& data) {
				T& x = at(index);
				x = data;
			}

			inline Iterator GetData() const {
				return begin();
			}

			inline Iterator GetData() {
				return begin();
			}

			//Growing the Array
			inline int Add(const T& x) {
				push_back(x);
				return GetUpperBound();
			}

			inline int Append(const Array<T>& src) {
				int size = size();
				int count = src.GetSize();
				int newSize = size + count;
				Resize(newSize);
				for (int i = size; i < newSize; i++)
					inherited::operator[](i) = src[i];
				return size;
			}

			inline void Copy(const Array<T>& src) {
				int count = src.GetSize();
				SetSize(count);
				for (int i = 0; i < count; i++)
					inherited::operator[](i) = src[i];
			}

			//Insertion/Removal
			inline void InsertAt(int index, const T& x) {
				insert(GetIterFromIndex(index), x);
			}

			inline void RemoveAt(int index) {
				erase(GetIterFromIndex(index));
			}

			//Operators []
			inline T& operator[](int index) {
				return inherited::operator[](index);
			}

			inline T operator[](int index) const {
				return inherited::operator[](index);
			}

			//Sort
			inline void Sort() {
				std::sort(begin(), end(), std::less<T>());
			}

			template<class Compare>
			void Sort(Compare comp) {
				std::sort(begin(), end(), comp);
			}

			inline void Sort(bool IsAscending)
			{
				if (IsAscending)
					std::sort(begin(), end(), std::less<T>());
				else
					std::sort(begin(), end(), std::greater<T>());
			}
		};
	} /* namespace Collections */
} /* namespace System */

#endif /* SYSTEM_COLLECTIONS_ARRAY_H_ */
