/*
* System.Guid.h
*
* Code Status: Drafts
*  Created on: Taiwan
*      Author: player
*/

#ifndef SYSTEM_GUID_H_
#define SYSTEM_GUID_H_

#include "stdafx.h"
#include <stdlib.h>
#include "System.String.h"

namespace System {
	class Guid {
	private:
		String _strGuid;

	public:
		Guid(LPTSTR pStr = NULL) {
#ifdef _UNICODE
			if (pStr) {
				_strGuid = String(pStr);
			}
			else {
				_strGuid = String(L"00000000-0000-0000-0000-000000000000");
			}
#else
			if (pStr) {
				_strGuid = String((LPCTSTR)pStr);
			}
			else {
				_strGuid = String("00000000-0000-0000-0000-000000000000");
			}
#endif
		}

		~Guid() {}

		/// compare operator
		bool operator == (const Guid& rhs) {
			return _strGuid == (LPCTSTR)rhs._strGuid;
		}

		bool operator != (const Guid& rhs) {
			return _strGuid != (LPCTSTR)rhs._strGuid;
		}

		/// set guid as string
		void Set(LPTSTR pStr) {
			if (pStr)
				_strGuid = String(pStr);
		}

		/// get guid as string
		operator LPCTSTR() const {
			return _strGuid;
		}

		/// generate a new guid
		void Generate();
	};
} /* namespace System */

#endif /* SYSTEM_GUID_H_ */
