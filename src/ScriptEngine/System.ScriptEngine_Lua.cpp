/*
* System.ScriptEngine_MsScript.cpp
*
*  Created on: Taiwan
*      Author: player
*/

#include "../../include/stdafx.h"

#if (_SCRIPT_ENGINE_LANG == _SCRIPT_ENGINE_LUA)

#include "../../include/ScriptEngine/System.ScriptEngine_Lua.h"

namespace System {

ScriptEngine::ScriptEngine()
	: _LangName(ScriptLang)
{
	_ptr = luaL_newstate();  // Open Lua
	luaL_openlibs(_ptr);
}


ScriptEngine::~ScriptEngine()
{
	lua_close(_ptr);
}

//bool ScriptEngine::GetMethodsName()
//{
//	bool bResult = false;
//	if (_ptr != NULL)
//	{
//		ComPtr<IScriptProcedureCollection> pProcedures(_ptr->GetProcedures());
//
//		// empty list...
//		_FunctionList.RemoveAll();
//
//		try{
//			long count = pProcedures->GetCount();
//			for (long index = 1; index <= count; index++)
//			{
//				IScriptProcedurePtr pIProcPtr = pProcedures->GetItem(_variant_t(index));
//				_bstr_t name = pIProcPtr->GetName();
//				_FunctionList.AddTail((LPCTSTR)name);
//				pIProcPtr = NULL;
//			}
//
//			bResult = true;
//		}
//		catch (...)
//		{
//		}
//
//		pProcedures = NULL;
//	}
//	return bResult;
//}

//LPCTSTR ScriptEngine::GetScriptFunction(LPCTSTR szName)
//{
//	List<String>::Iterator iter = _FunctionList.GetHeadPosition();
//	while (_FunctionList.iteratorValid(iter))
//	{
//		if ((*iter).CompareNoCase(szName) == 0)
//			return *iter;
//
//		iter++;
//	}
//	return _T("");
//}


bool ScriptEngine::ExecuteStatement(LPCTSTR szStatement)
{
	/*try {
		if (_ptr != NULL)
		{
			ULONG ref = _ptr->AddRef();
			_ptr->ExecuteStatement(_bstr_t(szStatement));
			ref = _ptr->Release();
			return true;
		}
	}
	catch (...)
	{
	}*/

	return false;
}

bool ScriptEngine::RunProcedure(LPCTSTR szProcName, SAFEARRAY** saParameters, VARIANT* varRet)
{
	// required argument
	//ASSERT(saParameters != NULL);
	//ASSERT(varRet != NULL);

	try {
		if (_ptr != NULL)
		{
			ULONG ref = _ptr->AddRef();
			bool  bResult = false;
			_bstr_t szFunc = GetScriptFunction(szProcName);
			if (szFunc.length() > 0)
			{
				*varRet = _ptr->Run(szFunc, saParameters);
				bResult = true;
			}
			ref = _ptr->Release();
			return bResult;
		}
	}
	catch (...)
	{
	}
	return false;
}

String ScriptEngine::GetErrorString()
{
	String ret = "";

	if (_ptr != NULL)
	{
		try{
			ComPtr<IScriptError> pError(_ptr->GetError());
			
			if (!pError.IsEmpty())
			{
				_bstr_t desc = _bstr_t("Error: ") + pError->GetDescription() + _bstr_t(", ");
				desc += pError->GetText() + _bstr_t("; in line ");
				desc += _bstr_t(pError->GetLine());
				ret = (LPCTSTR)desc;
				pError->Clear();
			}
		}
		catch (_com_error& e)
		{
			//TRACE((LPSTR)e.Description());
			//TRACE((LPSTR)"\n");
		}
	}
	return ret;
}

} /* namespace System */


#endif
