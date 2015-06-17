/*
 * System.IO.File.h
 *
 * Code Status: Drafts
 *  Created on: Taiwan
 *      Author: player
 */

#include "../stdafx.h"
#if (_CODE_MODE == _CODE_MODE_CPP11)

#ifndef SYSTEM_IO_FILE_H_
#define SYSTEM_IO_FILE_H_

#if _MSC_VER > 1000
	#pragma once
#endif

#include <cstdlib>
#include <cstdio>
#include "../System.Buffer.h"

namespace System {
	namespace IO {

	class _File {
	public:
		//File() {}
		//virtual ~File() {}

		static Buffer ReadFile(LPCTSTR pFileName);
		static bool WriteFile(LPCTSTR pFileName, Buffer& buf);

		static bool Delete(LPCTSTR pFileName);
		static bool Rename(LPCTSTR pOldName, LPCTSTR pNewName);

		// check a file is exist
		static bool IsExist(LPCTSTR pFileName);
	};


	static _File File;

	} /* namespace IO */
} /* namespace System */


#endif /* SYSTEM_IO_FILE_H_ */
#endif