/*
 * System.IO.Folder.h
 *
 *  Created on: Taiwan
 *      Author: player
 */

#include "..\stdafx.h"
#if (_CODE_MODE != _CODE_MODE_POSIX)
#error This library needs at least a POSIX compliant compiler
#else

#ifndef SYSTEM_IO_FOLDER_H_
#define SYSTEM_IO_FOLDER_H_

#if _MSC_VER > 1000
#pragma once
#endif

#include <unistd.h>

namespace System {
	namespace IO {
		namespace Folder {
			//Creates a new directory.
			inline BOOL CreateFolder(LPTSTR pFolder) {
				return (mkdir(pFolder) == 0);
			}

			//Deletes a directory.
			inline BOOL DeleteFolder(LPTSTR pFolder) {
				return (::unlink(pFolder) == 0);
			}

			//Changes the current working directory.
			inline BOOL SetCurrentFolder(LPTSTR pFolder) {
				return (chdir(pFolder) == 0);
			}
		} /* namespace Folder */
	} /* namespace IO */
} /* namespace System */

#endif /* SYSTEM_IO_FOLDER_H_ */

#endif
