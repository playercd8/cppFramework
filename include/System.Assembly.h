/*
* System.Assembly.h
*
* Code Status: Drafts
*  Created on: Taiwan
*      Author: player
*/

#if _MSC_VER > 1000
	#pragma once
#endif

#include "stdafx.h"

#if defined(_WIN32)
	#include "WIN32/System.Assembly.h"
#elif defined(__posix)
	#include "POSIX/System.Assembly.h"
#endif