/*
* System.Threading.Thread.h
*
* Code Status: Drafts
*  Created on: Taiwan
*      Author: player
*/

#include "stdafx.h"

#if (_CODE_MODE == _CODE_MODE_CPP11)
	#include "CPP11/System.Threading.Thread.h"
#elif (_CODE_MODE == _CODE_MODE_WIN32)
	#include "WIN32/System.Threading.Thread.h"
//#elif (_CODE_MODE = _CODE_MODE_POSIX)
//	#include "POSIX/System.Threading.Thread.h"
#endif