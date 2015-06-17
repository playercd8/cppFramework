/*
* System.ScriptEngine_Lua.h
*
*  Created on: Taiwan
*      Author: player
*/

#include "../stdafx.h"

#if (_SCRIPT_ENGINE_LANG == _SCRIPT_ENGINE_LUA)

#ifndef SYSTEM_SCRIPTENGINE_H_
#define SYSTEM_SCRIPTENGINE_H_

#if _MSC_VER > 1000
	#pragma once
#endif


#define ScriptLang _T("Lua")


//#include "../../../library/lua-5.2.3/src/lua.hpp"
#include "../../../library/lua-5.2.3/src/lua.h"
//#include "../../../library/lua-5.2.3/src/luaconf.h"
#include "../../../library/lua-5.2.3/src/lualib.h"
#include "../../../library/lua-5.2.3/src/lauxlib.h"


#include "../System.ComPtr.h"
#include "../System.String.h"
#include "../System.Collections.List.h"

//#include <comutil.h>
#include <tchar.h>

using  namespace System::Collections;

namespace System {

class ScriptEngine //: public ComPtr<IScriptControl>
{
//private:

protected:
	String _LangName;
	lua_State* _ptr;

	//List<String> _FunctionList;
	//bool GetMethodsName();
	//LPCTSTR GetScriptFunction(LPCTSTR name);

public:
	ScriptEngine();
	virtual ~ScriptEngine();

	inline String GetLanguage() {
		return _LangName;
	}

	inline void Reset() {
		//_ptr->Reset();
		//_FunctionList.RemoveAll();
	}

	inline void AddCode(LPTSTR strCode) {
		//HRESULT hr = _ptr->AddCode(
		//	_bstr_t(strCode)	//[in] BSTR Code
		//	);
		//GetMethodsName();
	}

	bool ExecuteStatement(LPCTSTR szStatement);
	bool RunProcedure(LPCTSTR szProcName, SAFEARRAY** saParameters, VARIANT* varRet);
	String GetErrorString();


};

} /* namespace System */

#endif /* SYSTEM_SCRIPTENGINE_H_ */

#endif
