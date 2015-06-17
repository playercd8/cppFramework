/*
* System.Threading.Mutex.h
*
* Code Status: Drafts
*  Created on: Taiwan
*      Author: player
*/

#include "../stdafx.h"

#if (_CODE_MODE != _CODE_MODE_WIN32)
	#error This library needs at least a WIN32 compliant compiler
#else

#ifndef SYSTEM_THREADING_MUTEX_H_
#define SYSTEM_THREADING_MUTEX_H_

#if _MSC_VER > 1000
	#pragma once
#endif

#include <windows.h>

namespace System {
	namespace Threading {

		class Mutex
		{
		private:
			CRITICAL_SECTION _cs;

		public:
			Mutex() {
				::InitializeCriticalSection(&_cs);
			}

			virtual ~Mutex() {
				::DeleteCriticalSection(&_cs);
			}

			void Lock() {
				::EnterCriticalSection(&_cs);
			}

			void Unlock() {
				::LeaveCriticalSection(&_cs);
			}

			//嘗試Lock, 成功時傳回 true
			bool TryLock() {
				return  (::TryEnterCriticalSection(&_cs) != 0);
			}
		};

		class Lock
		{
		private:
			Mutex&	_mutex;

		public:
			Lock(Mutex& mutex): 
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
