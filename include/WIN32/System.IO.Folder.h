/*
 * System.IO.Folder.h
 *
 * Code Status: Drafts
 *  Created on: Taiwan
 *      Author: player
 *  References:
 *		http://msdn.microsoft.com/en-us/library/windows/desktop/aa363950.aspx
 */

#include "../stdafx.h"
#if (_CODE_MODE == _CODE_MODE_WIN32)
#ifndef SYSTEM_IO_FOLDER_H_
#define SYSTEM_IO_FOLDER_H_

#if _MSC_VER > 1000
#pragma once
#endif

#include "../System.String.h"

#include <Shlwapi.h>
#pragma comment(lib, "Shlwapi.lib")

namespace System {
	namespace IO {
		namespace Folder {
			//Creates a new directory.
			inline BOOL CreateFolder(LPTSTR pFolder) {
				return CreateDirectory(pFolder, NULL);
			}

			//Deletes a directory.
			inline BOOL DeleteFolder(LPTSTR pFolder) {
				return RemoveDirectory(pFolder);
			}

			inline String GetCurrentFolder() {
				TCHAR szPath[MAX_PATH];
				const DWORD len = GetCurrentDirectory(MAX_PATH, szPath);

				if (len == 0)
					return String("");

				return String(szPath);
			}

			//Changes the current working directory.
			inline BOOL SetCurrentFolder(LPTSTR pFolder) {
				return SetCurrentDirectory(pFolder);
			}

			inline String GetBaseFolder() {
				String strPath;
				if (0 != GetModuleFileName(NULL, strPath.GetBuffer(MAX_PATH), MAX_PATH)) {
					strPath.ReleaseBuffer();
					int nPos = strPath.ReverseFind(_T('\\'));
					if (nPos != -1)
						return strPath.Left(nPos + 1);
				}

				GetCurrentDirectory(MAX_PATH, strPath.GetBuffer(MAX_PATH));
				strPath.ReleaseBuffer();
				return strPath;
			}

			inline BOOL IsFolder(LPTSTR pFolder) {
				return PathIsDirectory(pFolder);
			}
		} /* namespace Folder */
	} /* namespace IO */
} /* namespace System */

#endif /* SYSTEM_IO_FOLDER_H_ */
#endif