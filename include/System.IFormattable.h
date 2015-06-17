/*
 * System.IFormattable.h
 *
 * Code Status: Drafts
 *  Created on: Taiwan
 *      Author: player
 */

#ifndef SYSTEM_IFORMATTABLE_H_
#define SYSTEM_IFORMATTABLE_H_

#include "System.String.h"
#include <string>	//std::to_string

namespace System {

class IFormattable {
public:
	//IFormattable() {}
	virtual ~IFormattable() {}

	//virtual String ToString(String format);
	virtual String ToString(LPCTSTR format = NULL);

protected:
	template <typename T>
	String _toString(LPCTSTR format = NULL, T& val) {
		String str = String();
#ifdef _UNICODE
		if (format == NULL) {
			std::wstring str = std::to_wstring(val);
			str.assign(str.c_str());
		}
		else {
			wchar_t buffer[64];
			swprintf(buffer, format, val);

			template<typename T>
			str.assign(buffer, std::char_traits<wchar_t>::length(buffer));
		}
#else
		if (format == NULL) {
			std::string str = std::to_string(val);
			str.assign(str.c_str());
		}
		else {
			char buffer[64];
			sprintf(buffer, format, val);
			template<typename T>
			str.assign(buffer, std::char_traits<char>::length(buffer));
		}
#endif
		return str;
	}
};

} /* namespace System */



#endif /* SYSTEM_IFORMATTABLE_H_ */
