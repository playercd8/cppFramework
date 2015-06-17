/*
* System.Assembly.h
*
* Code Status: Drafts
*  Created on: Taiwan
*      Author: player
*
*  include:
*     C:\Program Files (x86)\Windows Kits\8.1\Include\shared\minwindef.h
*     C:\Program Files (x86)\Windows Kits\8.1\Include\um\WinBase.h
*/

#ifndef _WIN32
#error This library needs at least a WIN32 compliant compiler
#else

#ifndef SYSTEM_ASSEMBLY_H_
#define SYSTEM_ASSEMBLY_H_

#if _MSC_VER > 1000
	#pragma once
#endif

#include <stdlib.h>			//NULL
#include <minwindef.h>		//HMODULE
#include <WinBase.h>		//LoadLibrary, FreeLibrary

namespace System {
	class Assembly
	{
	private:
		HMODULE _hModule;

	public:
		Assembly(LPCTSTR pFileName) {
			_hModule = ::LoadLibrary(pFileName);
		}

		virtual ~Assembly() {
			if (_hModule != NULL) {
				::FreeLibrary(_hModule);
			}
		}

		template <typename T>
		T GetProcAddress(LPCTSTR pProcName) {
			return reinterpret_cast<T>(::GetProcAddress(_hModule, pProcName));
		}
	};
} /* namespace System */

#endif /* SYSTEM_ASSEMBLY_H_ */
#endif
