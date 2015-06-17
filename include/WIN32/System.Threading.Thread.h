/*
* System.Threading.Thread.h
*
* Code Status: Drafts
*  Created on: Taiwan
*      Author: player
*
* include:
*      C:\Program Files (x86)\Windows Kits\8.1\Include\um\WinBase.h
*
*/
#include "../stdafx.h"

#if (_CODE_MODE != _CODE_MODE_WIN32)
	#error This library needs at least a WIN32 compliant compiler
#else

#ifndef SYSTEM_THREADING_THREAD_H_
#define SYSTEM_THREADING_THREAD_H_

#if _MSC_VER > 1000
	#pragma once
#endif

#include <stdlib.h>
#include <WinBase.h>

namespace System {
	namespace Threading {

		enum ThreadPriority {
			AboveNormal = THREAD_PRIORITY_ABOVE_NORMAL,
			Highest = THREAD_PRIORITY_HIGHEST,
			Normal = THREAD_PRIORITY_NORMAL,
			Lowest = THREAD_PRIORITY_LOWEST,
			Unknown = -1
		};

		class Thread
		{
		private:
			HANDLE		_eventKill;
			HANDLE		_eventDead;
			HANDLE		_hThread;
			UINT		_ThreadId;
			volatile int _exitCode;

		//protected:
			
		public:
			Thread();
			virtual ~Thread();

			bool Start();
			void Stop();
			virtual int Run() = 0;

			bool isRunning() const {
				return (::WaitForSingleObject(_eventKill, 0) != WAIT_OBJECT_0);
			}
			
			//等待執行緒完成工作
			void Join() {
				if (_hThread)
					::WaitForSingleObject(_hThread, INFINITE);
			}

			//Retrieves the priority value for the specified thread. 
			//This value, together with the priority class of the thread's process, 
			//determines the thread's base-priority level.
			ThreadPriority GetThreadPriority() {
				int i = ::GetThreadPriority(_hThread);
				ThreadPriority priority = static_cast<ThreadPriority>(i);
				return priority;
			}

			//Sets the priority value for the specified thread. 
			//This value, together with the priority class of the thread's process, 
			//determines the thread's base priority level.
			BOOL SetThreadPriority(ThreadPriority priority) {
				return ::SetThreadPriority(_hThread, (int) priority);
			}

			//Suspends the execution of the current thread until the time-out interval elapses.
			void Sleep(long millis) {
				::Sleep(millis);
			}

			void SetExitCode(int x) {
				_exitCode = x;
			}

			int GetExitCode() const {
				return _exitCode;
			}
			//-----------------
			//以下為Win32模式下專有方法
			//-----------------

			//Decrements a thread's suspend count. 
			//When the suspend count is decremented to zero, the execution of the thread is resumed.
			DWORD ResumeThread() {
				return ::ResumeThread(_hThread);
			}

			//Suspends the specified thread.
			DWORD SuspendThread() {
				return ::SuspendThread(_hThread);
			}

			HANDLE GetEventDead() const {
				return _eventDead;
			}

			operator HANDLE() const {
				return _hThread;
			}
		};

	} /* namespace Threading */
} /* namespace System */

#endif /* SYSTEM_THREADING_THREAD_H_ */
#endif
