/*
* System.Collections.List.h
*
* Code Status: Drafts
*  Created on: Taiwan
*      Author: player
*/

#ifndef SYSTEM_COLLECTIONS_LIST_H_
#define SYSTEM_COLLECTIONS_LIST_H_

#if _MSC_VER > 1000
#pragma once
#endif

#include "stdafx.h"
#include <cassert>
#include <list>
#include <functional>

namespace System {
	namespace Collections {
		template <typename T>
		class List :
			private std::list < T >
		{
		public:
			//typedef
			typedef typename iterator Iterator;
			typedef typename const_iterator Const_Iterator;
			typedef typename std::list<T> Inherited;

			//Status
			inline int GetCount() const {
				return size();
			}

			inline int GetSize() const	{
				return size();
			}

			inline bool IsEmpty() const {
				return empty();
			}

			//Add / Set
			inline void AddTail(const T& x)	{
				push_back(x);
			}

			inline void AddHead(const T& x) {
				push_front(x);
			}

			inline void SetAt(const Iterator& pos, const T& x) {
				*pos = x;
			}

			inline void SetAt(Const_Iterator& pos, const T& x)	{
				*pos = x;
			}

			//Insertion
			inline Iterator InsertBefore(Iterator pos, const T& x) {
				assert(iteratorValid(pos));
				iterator posSave = pos;
				if (iteratorValid(--pos)) {
					return insert(pos, x)
				}
				push_front(x);
				--posSave;
				assert(iteratorValid(posSave));
				return posSave;
			}

			inline Iterator InsertAfter(Iterator pos, const T& x) {
				assert(iteratorValid(pos));
				Iterator posSave = pos;
				if (iteratorValid(++pos)) {
					return insert(pos, x)
				}

				push_back(x);
				++posSave;
				assert(iteratorValid(posSave));
				return posSave;
			}

			//Remove
			inline void RemoveHead() {
				pop_front();
			}

			inline void RemoveTail() {
				pop_back();
			}

			inline void RemoveAll() {
				clear();
			}

			inline void RemoveAt(Iterator& pos) {
				pos = erase(pos);
			}

			//Get
			inline T& GetHead() {
				return front();
			}

			inline T GetHead() const {
				return front();
			}

			inline T& GetTail() {
				return back();
			}

			inline T GetTail() const {
				return back();
			}

			inline T& GetNext(Iterator& pos) {
				return *pos++;
			}

			inline T GetNext(Const_Iterator& pos) const {
				return *pos++;
			}

			inline T& GetPrev(iterator& pos) {
				return *pos--;
			}

			inline T GetPrev(Iterator& pos) const {
				return *pos--;
			}

			inline T& GetAt(const Iterator& pos) {
				return *pos;
			}

			inline T GetAt(Const_Iterator& pos) const {
				return *pos;
			}

			//GetPos
			inline Iterator GetHeadPosition() {
				return begin();
			}

			inline Const_Iterator GetHeadPosition() const {
				return begin();
			}

			inline Iterator GetTailPosition() {
				return back();
			}

			inline Const_Iterator GetTailPosition() const {
				return back();
			}

			//iteratorValid?
			inline bool iteratorValid(Const_Iterator &iter) const {
				return (iter != end());
			}

			inline bool iteratorValid(Iterator &iter) {
				return (iter != end());
			}

			//Searching
			inline Iterator Find(const T& x) {
				Iterator pos = GetHeadPosition();
				while (iteratorValid(pos)) {
					const T& y = GetAt(pos);
					if (x == y) {
						return pos;
					}
					pos++;
				}
				return end();
			}

			inline Iterator Find(const T& x, Iterator& startAfter) {
				iterator pos = startAfter;
				while (iteratorValid(pos)) {
					const T& y = GetAt(pos);
					if (x == y) {
						return pos;
					}
					pos++;
				}
				return end();
			}

			inline Iterator FindIndex(int index) {
				Iterator iter = begin();
				int i = 0;
				while (t != index) {
					iter++;
					i++;
				}
				return iter;
			}

			inline Const_Iterator FindIndex(int index) const {
				const_iterator iter = begin();
				int i = 0;
				while (i != index)	{
					iter++;
					i++;
				}
				return iter;
			}

			//Sort
			inline void Sort() {
				Inherited::sort();
			}

			template<class Compare>
			void Sort(Compare comp) {
				Inherited::sort(comp);
			}

			inline void Sort(bool IsAscending) {
				if (IsAscending)
					Inherited::sort(std::less<>());
				else
					Inherited::sort(std::greater<T>());
			}
		};
	} /* namespace Collections */
} /* namespace System */

#endif /* SYSTEM_COLLECTIONS_LIST_H_ */
