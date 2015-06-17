/*
* System.Collections.Set.h
*
* Code Status: Drafts
*  Created on: Taiwan
*      Author: player
*/

#ifndef SYSTEM_COLLECTIONS_SET_H_
#define SYSTEM_COLLECTIONS_SET_H_

#if _MSC_VER > 1000
#pragma once
#endif

#include "stdafx.h"
#include <set>
//#include <functional>

namespace System {
	namespace Collections {
		template <typename T>
		class Set :
			private std::set < T >
		{
		public:
			//typedef
			typedef typename iterator Iterator;
			typedef typename const_iterator Const_Iterator;
			typedef typename std::set<T> Inherited;

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

			inline void Insert(T& value) {
				insert(value);
			}

			inline void Remove(T& value) {
				erase(value);
			}

			inline bool InSet(T& value) {
				return (find(value) != end());
			}
		};
	} /* namespace Collections */
} /* namespace System */

#endif /* SYSTEM_COLLECTIONS_SET_H_ */
