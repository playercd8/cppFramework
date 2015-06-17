/*
* System.Threading.Thread_WIN32.cpp
*
* Code Status: Drafts
*  Created on: Taiwan
*      Author: player
*/

#include "../../include/stdafx.h"

#if (_CODE_MODE == _CODE_MODE_WIN32)

#include "../../include/WIN32/System.Threading.Thread.h"

#include <process.h>

namespace System {
	namespace Threading {

		// 執行緒啟動時的資料
		struct THREAD_STARTUP {
			Thread* pThread;

			HANDLE hEvent;
			HANDLE hEvent2;
			bool error;
		};

		// 執行緒進入點
		UINT APIENTRY ThreadEntry(void *param) {
			THREAD_STARTUP *startup = (THREAD_STARTUP *)param;

			Thread* pThread = startup->pThread;

			HANDLE hEvent2 = startup->hEvent2;
			::SetEvent(startup->hEvent);

			::WaitForSingleObject(hEvent2, INFINITE);
			::CloseHandle(hEvent2);

			DWORD result = pThread->Run();
			pThread->SetExitCode(result);

			::SetEvent(pThread->GetEventDead());
			_endthreadex(result);

			return 0;
		}
		


		// 建構子
		Thread::Thread():
			_eventKill(NULL),
			_eventDead(NULL),
			_hThread(NULL),
			_ThreadId(0),
			_exitCode(0) {
		}

		// 解構子
		Thread::~Thread()
		{
			if (_eventKill)
				::CloseHandle(_eventKill);
			if (_eventDead)
				::CloseHandle(_eventDead);
			if (_hThread)
				::CloseHandle(_hThread);
		}

		// 建立執行緒
		bool Thread::Start()
		{
			_eventKill = ::CreateEvent(NULL, TRUE, FALSE, NULL);
			_eventDead = ::CreateEvent(NULL, TRUE, FALSE, NULL);

			DWORD flags = 0;
			UINT stack = 0;
			LPSECURITY_ATTRIBUTES sa = NULL;
			THREAD_STARTUP startup;
			memset(&startup, 0, sizeof(startup));

			startup.pThread = this;
			startup.hEvent = ::CreateEvent(NULL, TRUE, FALSE, NULL);
			startup.hEvent2 = ::CreateEvent(NULL, TRUE, FALSE, NULL);

			if (startup.hEvent == NULL || startup.hEvent2 == NULL) {
				if (startup.hEvent != NULL)
					::CloseHandle(startup.hEvent);
				if (startup.hEvent2 != NULL)
					::CloseHandle(startup.hEvent2);
				return false;
			}

			_hThread = (HANDLE)_beginthreadex(sa, stack, &ThreadEntry, &startup, flags | CREATE_SUSPENDED, &_ThreadId);
			if (_hThread == NULL)
				return false;

			::ResumeThread(_hThread);
			::WaitForSingleObject(startup.hEvent, INFINITE);
			::CloseHandle(startup.hEvent);

			if (flags & CREATE_SUSPENDED)
				::SuspendThread(_hThread);

			if (startup.error) {
				::WaitForSingleObject(_hThread, INFINITE);
				::CloseHandle(_hThread);
				_hThread = NULL;
				::CloseHandle(startup.hEvent2);
				return false;
			}

			::SetEvent(startup.hEvent2);
			return true;
		}

		// 停止執行緒
		void Thread::Stop() {
			if (_hThread) {
				::SetEvent(_eventKill);
				SetThreadPriority(ThreadPriority::AboveNormal);
				::WaitForSingleObject(_eventDead, INFINITE);
				::WaitForSingleObject(_hThread, INFINITE);
			}
		}

		
	}
}
#endif