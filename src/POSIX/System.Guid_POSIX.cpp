/*
 * System.Guid_POSIX.cpp
 *
 *  Created on: 2014/5/21
 *      Author: Administrator
 */

#include "..\..\include\stdafx.h"

#if defined(_APP_MODE_CLIENT_POSIX)

#include "System.Guid.h"
#include <uuid/uuid.h>

namespace System {

void Guid::Generate() {
	uuid_t guid;
	uuid_generate(guid);

   char guidstr[37];
   uuid_unparse(guid, guidstr);
   this->_strGuid = guidstr;
}

} /* namespace System */

#endif
