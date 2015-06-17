/*
* System.Threading.Thread.cpp
*
*  Created on: Taiwan
*      Author: player
*/

#include "../../include/stdafx.h"

//#include <process.h>

#if (_CODE_MODE == _CODE_MODE_CPP11)

#include "../../include/CPP11/System.Threading.Thread.h"

namespace System {
	namespace Threading {

		// 執行緒啟動時的資料
		struct THREAD_STARTUP {
			Thread* pThread;
		};

		// 執行緒進入點
		void ThreadEntry(void* param) {
			THREAD_STARTUP *startup = (THREAD_STARTUP *)param;

			Thread* pThread = startup->pThread;
			pThread->SetEventDead(false);
			DWORD result = pThread->Run();
			pThread->SetExitCode(result);
			pThread->SetEventDead(true);
		}

		// 建構子
		Thread::Thread():
			_hThread(NULL),
			_eventKill(false),
			_eventDead(false),
			_exitCode(0) {
		}

		// 解構子
		Thread::~Thread() {
			Stop();
		}

		// 建立執行緒
		bool Thread::Start()
		{
			try {
				THREAD_STARTUP startup;
				memset(&startup, 0, sizeof(startup));
				startup.pThread = this;

				std::thread cpp_thread(ThreadEntry, this);
				_hThread = new std::thread(std::move(cpp_thread));

				return true;
			}
			catch (std::system_error & ex) {
				UNREFERENCED_PARAMETER(ex);
				return false;
			}
			catch (std::bad_alloc &) {
				return false;
			}			
		}

		// 停止執行緒
		void Thread::Stop() {
			if (_hThread) {
				_eventKill = true;
				while (_eventDead != true) {
					Sleep(1);
				}
				//if (_hThread->joinable())
				//	_hThread->detach();
				_hThread = NULL;
			}
		}

	}
}

#endif