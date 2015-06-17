/*
* System.ScriptEngine.h
*
* Code Status: Drafts
*  Created on: Taiwan
*      Author: player
*/

#ifndef SYSTEM_SCRIPT_ENGINE_H_
#define SYSTEM_SCRIPT_ENGINE_H_

#if _MSC_VER > 1000
	#pragma once
#endif

#include "stdafx.h"


#if (_SCRIPT_ENGINE_LANG == _SCRIPT_ENGINE_JSCRIPT)
	#include "ScriptEngine/System.ScriptEngine_MsScript.h"
#elif (_SCRIPT_ENGINE_LANG == _SCRIPT_ENGINE_VBSCRIPT)
	#include "ScriptEngine/System.ScriptEngine_MsScript.h"
#elif (_SCRIPT_ENGINE_LANG == _SCRIPT_ENGINE_LUA)
	#include "ScriptEngine/System.ScriptEngine_Lua.h"
#endif

#endif /* SYSTEM_SCRIPT_ENGINE_H_ */