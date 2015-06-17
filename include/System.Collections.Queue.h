/*
* System.Collections.Queue.h
*
* Code Status: Drafts
*  Created on: Taiwan
*      Author: player
*/

#ifndef SYSTEM_COLLECTIONS_QUEUE_H_
#define SYSTEM_COLLECTIONS_QUEUE_H_

#if _MSC_VER > 1000
#pragma once
#endif

#include "stdafx.h"
#include <list>

namespace System {
	namespace Collections {
		template <typename T>
		class Queue :
			private std::list < T >
		{
			//protected:
		public:
			//typedef
			typedef typename iterator Iterator;
			typedef typename const_iterator Const_Iterator;
			typedef typename std::list<T> Inherited;

		public:
			//Attributes
			inline int	GetCount() const {
				return size();
			}

			inline int	GetSize() const {
				return size();
			}

			inline bool IsEmpty() const {
				return empty();
			}

			//Operators
			inline void RemoveAll() {
				clear();
			}

			inline void AddToEnd(const T& x) {
				push_back(x);
			}

			inline T GetFromFront() {
				if (empty())
					return NULL;	//return end();

				T ret = front();
				pop_front();

				return ret;
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

#endif /* SYSTEM_COLLECTIONS_QUEUE_H_ */
