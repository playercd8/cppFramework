/*
* System.Threading.Mutex.h
*
*  Created on: Taiwan
*      Author: player
*/

#include "..\stdafx.h"
#if (_CODE_MODE != _CODE_MODE_POSIX)
	#error This library needs at least a POSIX compliant compiler
#else

#ifndef SYSTEM_THREADING_MUTEX_H_
#define SYSTEM_THREADING_MUTEX_H_

#include <unistd.h>  

namespace System {
	namespace Threading {

		class Mutex
		{
		private:
			pthread_mutex_t m_mutex;

		public:
			Mutex() {
				::pthread_mutexattr_t attr;
				::pthread_mutexattr_init(&attr);
				::pthread_mutex_init(&m_mutex, &attr);
			}

			virtual ~Mutex() {
				::pthread_mutex_destroy(&m_mutex);
			}

			void Lock() {
				::pthread_mutex_lock(&m_mutex);
			}

			void Unlock() {
				::pthread_mutex_unlock(&m_mutex);
			}

			//嘗試Lock, 成功時傳回 true
			bool TryLock() {
				return  (::pthread_mutex_trylock(&m_mutex) != 0);
			}
		};


		class Lock
		{
		private:
			Mutex*	m_pMutex;

		public:
			Lock(Mutex* pMutex) {
				m_pMutex = pMutex;
				m_pMutex->Lock();
			}


			virtual ~Lock()	{
				m_pMutex->Unlock();
			}
		};

	} /* namespace Threading */
} /* namespace System */

#endif /* SYSTEM_THREADING_MUTEX_H_ */
#endif
