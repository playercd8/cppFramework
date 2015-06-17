/*
* System.Collections.Map.h
*
* Code Status: Drafts
*  Created on: Taiwan
*      Author: player
*/

#ifndef SYSTEM_COLLECTIONS_MAP_H_
#define SYSTEM_COLLECTIONS_MAP_H_

#if _MSC_VER > 1000
#pragma once
#endif

#include "stdafx.h"
#include <map>

namespace System {
	namespace Collections {
		template <typename KEY, typename VALUE>
		class Map :
			private std::map < KEY, VALUE >
		{
		public:
			//typedef
			typedef typename iterator Iterator;
			typedef typename const_iterator Const_Iterator;
			typedef typename std::map<KEY, VALUE> Inherited;
			typedef typename value_type v_type;

			//TODO: (STL) Status
			inline int GetCount() const {
				return size();
			}

			inline int GetSize() const {
				return size();
			}

			inline bool IsEmpty() const {
				return empty();
			}

			//Operations
			inline void SetAt(KEY key, VALUE newValue) {
				insert(v_type(key, newValue));
			}

			inline bool RemoveKey(KEY key) {
				return erase(key) != 0;
			}

			inline bool Lookup(KEY key, VALUE& refValue) const {
				const_iterator iter = find(key);
				if (iter == end()) {
					return false;
				}
				else {
					refValue = iter->second;
					return true;
				}
			}

			inline void RemoveAll() {
				clear();
			}

			inline VALUE& operator[](KEY& key) {
				return Inherited::operator[](key);
			}

			inline Inherited GetAll() {
				return Inherited(*this);
			}

			inline Iterator GetHeadPosition() {
				return begin();
			}

			inline bool iteratorValid(Const_Iterator &iter) const {
				return (iter != end());
			}

			inline bool iteratorValid(Iterator &iter) {
				return (iter != end());
			}
		};
	} /* namespace Collections */
} /* namespace System */

#endif /* SYSTEM_COLLECTIONS_MAP_H_ */
