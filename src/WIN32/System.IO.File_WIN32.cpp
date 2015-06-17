/*
 * System.IO.File_CPP11.cpp
 *
 * Code Status: Drafts
 *  Created on: Taiwan
 *      Author: player
 */

#include "../../include/stdafx.h"
#if (_CODE_MODE == _CODE_MODE_WIN32)

#include "../../include/WIN32/System.IO.File.h"
#include <Shlwapi.h>
#pragma comment(lib, "Shlwapi.lib")

#pragma warning(disable : 4996) 

namespace System {
	namespace IO {
		Buffer _File::ReadFile(LPCTSTR pFileName) 
		{
			// Open file to read binary
#ifdef _UNICODE
			HANDLE hFile = CreateFileW(
				pFileName,			//[in]	LPCTSTR lpFileName,
				GENERIC_READ,		//[in]	DWORD dwDesiredAccess,
				FILE_SHARE_READ,	//[in]	DWORD dwShareMode
				NULL,				//[in]	LPSECURITY_ATTRIBUTES lpSecurityAttributes,
				OPEN_EXISTING,		//[in]	DWORD dwCreationDisposition,
				FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED,	//[in]	DWORD dwFlagsAndAttributes,
				NULL				//[in]	HANDLE hTemplateFile
				);
#else
			HANDLE hFile = CreateFileA(
				pFileName,			//[in]	LPCTSTR lpFileName,
				GENERIC_READ,		//[in]	DWORD dwDesiredAccess,
				FILE_SHARE_READ,	//[in]	DWORD dwShareMode
				NULL,				//[in]	LPSECURITY_ATTRIBUTES lpSecurityAttributes,
				OPEN_EXISTING,		//[in]	DWORD dwCreationDisposition,
				FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED,	//[in]	DWORD dwFlagsAndAttributes,
				NULL				//[in]	HANDLE hTemplateFile
				);
#endif

			if (hFile != INVALID_HANDLE_VALUE) 
				return NULL;

			// File is open
			LARGE_INTEGER FileSize = { 0 };

			GetFileSizeEx(
				hFile,		//[in]	HANDLE hFile,
				&FileSize	//[out]	PLARGE_INTEGER lpFileSize
				);

			//假如檔案大於4GB
			if (FileSize.HighPart > 0)
			{
				CloseHandle(hFile);
				return NULL;
			}
			long nFileByteLen = FileSize.LowPart;

			// Allocate Buffer
			Buffer buf(nFileByteLen);

			// Read file
			DWORD result;
			if (nFileByteLen)
				::ReadFile(
					hFile,			//[in]	HANDLE hFile,
					buf.GetPtr(),	//[out]	LPVOID lpBuffer,
					nFileByteLen,	//[in]	DWORD nNumberOfBytesToRead,
					&result,		//[out]	LPDWORD lpNumberOfBytesRead,
					NULL			//[in]	LPOVERLAPPED lpOverlapped
				);			

			CloseHandle(hFile);

			if (result != nFileByteLen)
				return NULL;

			return buf;
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

		bool _File::Delete(LPCTSTR pFileName) {
#ifdef _UNICODE
			return DeleteFileW(pFileName);
#else
			return DeleteFileA(pFileName);
#endif
		}

		bool _File::Rename(LPCTSTR pOldName, LPCTSTR pNewName) {
#ifdef _UNICODE
			return MoveFileW(pOldName, pNewName);
#else
			return MoveFileA(pOldName, pNewName);
#endif
		}

		// check a file is exist
		bool _File::IsExist(LPCTSTR pFileName) 
		{
#ifdef _UNICODE
			return  (PathFileExistsW(pFileName) == 1);
#else
			return  (PathFileExistsA(pFileName) == 1);
#endif
		}
	} /* namespace IO */
} /* namespace System */

#pragma warning(default: 4996) 
#endif