/*
 * System.IO.File_CPP11.cpp
 *
 * Code Status: Drafts
 *  Created on: Taiwan
 *      Author: player
 */

#include "../../include/stdafx.h"
#if (_CODE_MODE == _CODE_MODE_CPP11)

#include "../../include/CPP11/System.IO.File.h"

#pragma warning(disable : 4996) 

namespace System {
	namespace IO {
		Buffer _File::ReadFile(LPCTSTR pFileName) 
		{
			// Open file to read binary
#ifdef _UNICODE
			FILE* fp = _wfopen(pFileName, L"rb");
#else
			FILE* fp = fopen(pFileName, "rb");
#endif
			if (!fp)
				return NULL;

			// File is open
			fseek(fp, 0, SEEK_END);
			long nFileByteLen = ftell(fp);
			fseek(fp, 0, SEEK_SET);

			// Allocate Buffer
			Buffer buf(nFileByteLen);

			// Read file
			size_t result;
			if (nFileByteLen)
				result = fread(buf.GetPtr(), nFileByteLen, 1, fp);

			fclose(fp);

			if (result != nFileByteLen)
				return NULL;

			return buf;
		}

		bool _File::Delete(LPCTSTR pFileName) {
#ifdef _UNICODE
			return (_wremove(pFileName) == 0);
#else
			return (remove(pFileName) == 0);
#endif
		}

		bool _File::WriteFile(LPCTSTR pFileName, Buffer& buf) 
		{
#ifdef _UNICODE
			FILE* fp = _wfopen(pFileName, L"wb");
#else
			FILE* fp = fopen(pFileName, "wb");
#endif
			if (!fp)
				return false;

			fwrite(buf.GetPtr(), sizeof(char), buf.GetSize(), fp);

			fclose(fp);
			return true;
		}

		bool _File::Rename(LPCTSTR pOldName, LPCTSTR pNewName) 
		{
#ifdef _UNICODE
			return (_wrename(pOldName, pNewName) == 0);
#else
			return (rename(pOldName, pNewName) == 0);
#endif
		}

		// check a file is exist
		bool _File::IsExist(LPCTSTR pFileName) {
#ifdef _UNICODE
			FILE* fp = _wfopen(pFileName, L"rb");
#else
			FILE* fp = fopen(pFileName, "rb");
#endif

			if (fp) {
				fclose(fp);
				return true;
			}
			else {
				return false;
			}
		}
	} /* namespace IO */
} /* namespace System */

#pragma warning(default: 4996) 
#endif