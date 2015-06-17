/*
* System.Threading.Thread.h
*
*  Created on: Taiwan
*      Author: player
*/

#include "..\stdafx.h"
#if (_CODE_MODE != _CODE_MODE_POSIX)
	#error This library needs at least a POSIX compliant compiler
#else

#ifndef SYSTEM_THREADING_THREAD_H_
#define SYSTEM_THREADING_THREAD_H_

#if _MSC_VER > 1000
	#pragma once
#endif


#include <pthread.h>

namespace System {
	namespace Threading {

		template <typename T>
		class Thread
		{
		private:
			pthread_t m_hThread = null;

		public:
			Thread() {
			}

			virtual ~Thread() {
				Stop();
			}


			void Start() {
				pthread_attr_t type;

				/* do this here before any threads exist, so there's no race condition. */
#if defined(__MACOSX__) || defined(__IPHONEOS__) || defined(__LINUX__)
				if (!checked_setname) {
					void *fn = dlsym(RTLD_DEFAULT, "pthread_setname_np");
#if defined(__MACOSX__) || defined(__IPHONEOS__)
					ppthread_setname_np = (int(*)(const char*)) fn;
#elif defined(__LINUX__)
					ppthread_setname_np = (int(*)(pthread_t, const char*)) fn;
#endif
					checked_setname = SDL_TRUE;
				}
#endif

				/* Set the thread attributes */
				if (pthread_attr_init(&type) != 0) {
					//return SDL_SetError("Couldn't initialize pthread attributes");
					return;
				}
				pthread_attr_setdetachstate(&type, PTHREAD_CREATE_JOINABLE);

				/* Create the thread and go! */
				if (pthread_create(&m_hThread, &type, runThread, (T*) this) != 0) {
					//return SDL_SetError("Not enough resources to create thread");
					return;
				}
			}

			void Stop() {
			
			}

			//等待執行緒完成工作
			void Join() {
				if (m_hThread != null) {}
					::pthread_join(m_hThread, 0);
				}
			}

			void SetPriority(int priority) {
				//::pthread_setschedparam(thread.native_handle(), policy, {priority});
			}

			static void Sleep(long millis) {
				::usleep(millis);
			}

			DWORD GetExitCode() {}
		};

	} /* namespace Threading */
} /* namespace System */

#endif /* SYSTEM_THREADING_THREAD_H_ */
#endif
