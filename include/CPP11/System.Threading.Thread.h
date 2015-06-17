/*
* System.Threading.Thread.h
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

#ifndef SYSTEM_THREADING_THREAD_H_
#define SYSTEM_THREADING_THREAD_H_

#if _MSC_VER > 1000
#pragma once
#endif

#include <chrono>
#include <thread>
#include <system_error>

namespace System {
	namespace Threading {
		enum ThreadPriority {
			AboveNormal,
			Highest,
			Normal,
			Lowest,
			Unknown
		};

		class Thread
		{
		private:
			std::thread* _hThread;
			volatile bool _eventKill;
			volatile bool _eventDead;
			volatile int _exitCode;

			//protected:

		public:
			Thread();
			virtual ~Thread();

			bool Start();
			void Stop();
			virtual int Run() = 0;

			bool isRunning() const {
				return (_eventKill != true);
			}

			//等待執行緒完成工作
			void Join() {
				try {
					if (_hThread) {
						if (_hThread->joinable()) {
							_hThread->join();
						}
					}
				}
				catch (std::system_error ex) {
				}
			}

			//Retrieves the priority value for the specified thread.
			//This value, together with the priority class of the thread's process,
			//determines the thread's base-priority level.
			ThreadPriority GetThreadPriority() {
				return ThreadPriority::Unknown;
			}

			//Sets the priority value for the specified thread.
			//This value, together with the priority class of the thread's process,
			//determines the thread's base priority level.
			int SetThreadPriority(ThreadPriority priority) {
				return 0;
			}

			//Suspends the execution of the current thread until the time-out interval elapses.
			void Sleep(long millis) {
				std::chrono::milliseconds wait(millis);
				std::this_thread::sleep_for(wait);
			}

			void SetExitCode(int x) {
				_exitCode = x;
			}

			int GetExitCode() const {
				return _exitCode;
			}

			//-----------------
			//以下為C++11模式下專有方法
			//-----------------

			//bool GetEventDead() const {
			//	return _eventDead;
			//}

			void SetEventDead(bool x) {
				_eventDead = x;
			}
		};
	} /* namespace Threading */
} /* namespace System */

#endif /* SYSTEM_THREADING_THREAD_H_ */
#endif
