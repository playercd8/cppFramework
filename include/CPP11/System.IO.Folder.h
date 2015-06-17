/*
 * System.IO.Folder.h
 *
 * Code Status: Drafts
 *  Created on: Taiwan
 *      Author: player
 */

#include "../stdafx.h"
#if (_CODE_MODE == _CODE_MODE_CPP11)
#ifndef SYSTEM_IO_FOLDER_H_
#define SYSTEM_IO_FOLDER_H_

#if _MSC_VER > 1000
	#pragma once
#endif

#include <direct.h>
#include "../System.String.h"

namespace System {
	namespace IO {

	class Folder {
	public:
		Folder() {

		}
		virtual ~Folder() {}

		//Creates a new directory.
		bool Create(LPTSTR pFolder) {
#ifdef _UNICODE
			return (_wmkdir(pFolder) == 0);
#else
			return (_mkdir(pFolder) == 0);
#endif
		}


		//Deletes a directory.
		bool Delete(LPTSTR pFolder) {
#ifdef _UNICODE
			return (_wrmdir(pFolder) == 0);
#else
			return (_rmdir(pFolder) == 0);
#endif
		}

		//Changes the current working directory.
		bool SetCurrentFolder(LPTSTR pFolder) {
#ifdef _UNICODE
			return (_wchdir(pFolder) == 0);
#else
			return (_chdir(pFolder) == 0);
#endif
		}

	};

	} /* namespace IO */
} /* namespace System */


#endif /* SYSTEM_IO_FOLDER_H_ */
#endif