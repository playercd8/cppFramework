/*
* System.Assembly.h
*
*  Created on: Taiwan
*      Author: player
*/

#include "..\stdafx.h"
#if (_CODE_MODE != _CODE_MODE_POSIX)
	#error This library needs at least a POSIX compliant compiler
#else

#ifndef SYSTEM_ASSEMBLY_H_
#define SYSTEM_ASSEMBLY_H_

#include <dlfcn.h>

namespace System {

	class Assembly
	{
	private:
		void*  _hModule = null;

	public:
		Assembly(LPCTSTR pFileName) {
			_hModule = ::dlopen(pFileName, RTLD_LAZY);
		}

		virtual ~Assembly() {
			if (_hModule) {
				::dlclose(m_hModule);
			}
		}
	
		template <typename T>
		T GetProcAddress(LPCTSTR pProcName) {
			return reinterpret_cast<T>(::dlsym(_hModule, pProcName));
		}	

	};

	


} /* namespace System */

#endif /* SYSTEM_ASSEMBLY_H_ */
#endif
