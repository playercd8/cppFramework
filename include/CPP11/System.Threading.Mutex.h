/*
* System.Threading.Mutex.h
*
* Code Status: Drafts
*  Created on: Taiwan
*      Author: player
*/

#include "../stdafx.h"
#if (_CODE_MODE == _CODE_MODE_CPP11)

#if !((__cplusplus >= 201103L) || ((_MSC_VER >= 1800) && (__cplusplus == 199711L)))
#error This library needs at least a C++11 compliant compiler
#endif

#ifndef SYSTEM_THREADING_MUTEX_H_
#define SYSTEM_THREADING_MUTEX_H_

#if _MSC_VER > 1000
#pragma once
#endif

#include <mutex>

namespace System {
	namespace Threading {
		class Mutex
		{
		private:
			std::recursive_mutex _mutex;

		public:
			Mutex() {
			}

			virtual ~Mutex() {
			}

			void Lock() {
				_mutex.lock();
			}

			void Unlock() {
				_mutex.unlock();
			}

			//嘗試Lock, 成功時傳回 true
			bool TryLock() {
				return _mutex.try_lock();
			}
		};

		class Lock
		{
		private:
			Mutex&	_mutex;

		public:
			Lock(Mutex& mutex) :
				_mutex(mutex) {
				_mutex.Lock();
			}

			~Lock()	{
				_mutex.Unlock();
			}
		};
	} /* namespace Threading */
} /* namespace System */

#endif /* SYSTEM_THREADING_MUTEX_H_ */
#endif