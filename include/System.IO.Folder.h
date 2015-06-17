/*
 * System.IO.Folder.h
 *
 * Code Status: Drafts
 *  Created on: Taiwan
 *      Author: player
 */

#include "stdafx.h"

#if (_CODE_MODE == _CODE_MODE_WIN32)
	#include "WIN32/System.IO.Folder.h"
#elif (_CODE_MODE = _CODE_MODE_POSIX)
	#include "POSIX/System.IO.Folder.h"
#endif


