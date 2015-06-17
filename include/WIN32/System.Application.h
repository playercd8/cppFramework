/*
* System.Application.h
*
* Code Status: Drafts
*  Created on: Taiwan
*      Author: player
*/

#include "../stdafx.h"

#if defined(_WINDOWS) 

#include <windows.h>

#if (_APP_MODE == _APP_MODE_CLIENT)
	#include "System.ClientApp.h"
#elif (_APP_MODE == _APP_MODE_SERVER)
	#include "System.ServerApp.h"
#endif

#endif