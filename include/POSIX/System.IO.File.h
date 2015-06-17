/*
 * System.IO.File.h
 *
 *  Created on: Taiwan
 *      Author: player
 */

#include "..\stdafx.h"
#if (_CODE_MODE != _CODE_MODE_POSIX)
	#error This library needs at least a POSIX compliant compiler
#else

#ifndef SYSTEM_IO_FILE_H_
#define SYSTEM_IO_FILE_H_

#if _MSC_VER > 1000
	#pragma once
#endif

#include <cstdlib>
#include <cstdio>

namespace System {
	namespace IO {

	class File {
	public:
		File() {

		}
		virtual ~File() {}

		Buffer ReadFile(LPSTR pFileName) {
			// Open file to read binary
			FILE* fp = fopen(pFileName, "rb");
			if (!fp)
				return NULL;

			// File is open
			fseek( fp, 0, SEEK_END );
			long nFileByteLen = ftell(fp);
			fseek( fp, 0, SEEK_SET );

			// Allocate Buffer
			Buffer buf(nFileByteLen);

			// Read file
			size_t result;
			if (nFileByteLen)
				result = fread( buf.GetPtr(), nFileByteLen, 1, fp );

			fclose( fp );

			if (result != nFileByteLen)
				return NULL;

			return buf;
		}

		bool Delete(LPSTR pFileName) {
			return (remove(pFileName) == 0);
		}

		bool Rename(LPSTR pOldName, LPSTR pNewName) {
			return (rename(pOldName, pNewName) == 0);
		}

		// check a file is exist
		bool IsExist(LPSTR pFileName) {
			if (FILE* fp = fopen(pFileName, "r")) {
				fclose(fp);
				return true;
			} else {
				return false;
			}
		}
	};

	} /* namespace IO */
} /* namespace System */


#endif /* SYSTEM_IO_FILE_H_ */

#endif
