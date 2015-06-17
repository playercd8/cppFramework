/*
* System.Collections.Stack.h
*
* Code Status: Drafts
*  Created on: Taiwan
*      Author: player
*/

#ifndef SYSTEM_COLLECTIONS_STACK_H_
#define SYSTEM_COLLECTIONS_STACK_H_

#if _MSC_VER > 1000
#pragma once
#endif

#include "stdafx.h"
#include <cassert>
#include <list>

namespace System {
	namespace Collections {
		template <typename T>
		class Stack :
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

			inline int	GetSize() const {
				return size();
			}

			inline bool IsEmpty() const {
				return empty();
			}

			//Push / Pop
			inline void Push(const T& x) {
				push_back(x);
			}

			inline T Pop() {
				T ret = back();
				std::list<T>::pop_back();
				return ret;
			}

			//Peek
			inline Iterator Peek() {
				return IsEmpty() ? end() : back();
			}

			inline Const_Iterator Peek() const{
				return IsEmpty() ? end() : back();
			}

			//iteratorValid?
			inline bool iteratorValid(Const_Iterator &iter) const {
				return (iter != end());
			}

			inline bool iteratorValid(Iterator &iter) {
				return (iter != end());
			}
		};
	} /* namespace Collections */
} /* namespace System */

#endif /* SYSTEM_COLLECTIONS_STACK_H_ */
