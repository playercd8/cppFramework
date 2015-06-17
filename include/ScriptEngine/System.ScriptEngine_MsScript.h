/*
* System.ScriptEngine_MsScript.h
*
*  Created on: Taiwan
*      Author: player
*/

#include "../stdafx.h"

#if defined(_WINDOWS) && ((_SCRIPT_ENGINE_LANG == _SCRIPT_ENGINE_JSCRIPT) || (_SCRIPT_ENGINE_LANG == _SCRIPT_ENGINE_VBSCRIPT))

#ifndef SYSTEM_SCRIPTENGINE_H_
#define SYSTEM_SCRIPTENGINE_H_

#if _MSC_VER > 1000
#pragma once
#endif

#if (_SCRIPT_ENGINE_LANG == _SCRIPT_ENGINE_JSCRIPT)
#define ScriptLang _T("JScript")
#elif (_SCRIPT_ENGINE_LANG == _SCRIPT_ENGINE_VBSCRIPT)
#define ScriptLang _T("VBScript")
#endif

#import "msscript.ocx"

#include "../System.Collections.List.h"
#include "../System.ComPtr.h"
#include "../System.OOP.h"
#include "../System.String.h"

#include <comutil.h>
#include <tchar.h>

using namespace MSScriptControl;
using  namespace System::Collections;

namespace System {
	//---------------------------------------------------------------------------------------------------------
	// class ScriptObject
#pragma region class ScriptObject
	class ScriptObject : public IDispatch {
	private:
		volatile unsigned long _refCount;
		String _id;

		// method type
		typedef HRESULT(ScriptObject::*Func)(DISPPARAMS*, VARIANT*);

		// method structure
		typedef struct _SCRIPT_OBJECT_METHOD_TABLE {
			_SCRIPT_OBJECT_METHOD_TABLE(DISPID dispid, LPWSTR name, Func fn) {
				this->dispid = dispid;
				this->name = name;
				this->fn = fn;
			}
			DISPID dispid;
			LPWSTR name;
			Func fn;
		} SCRIPT_OBJECT_METHOD_TABLE;

		// method table
		List<SCRIPT_OBJECT_METHOD_TABLE> _methodTable;
		//	protected:

	public:
		// constructor
		ScriptObject() : _refCount(0) {}
		virtual ~ScriptObject() {}

		void SetID(String id) {
			_id = id;
		};

		String GetID() {
			return _id;
		};

		virtual operator IDispatch* () {
			return this;
		}
		inline void SetMethod(DISPID dispid, LPWSTR name, Func fn) {
			_methodTable.AddTail(SCRIPT_OBJECT_METHOD_TABLE(dispid, name, fn));
		}

		STDMETHODIMP QueryInterface(REFIID rid, LPVOID *ppv);
		ULONG STDMETHODCALLTYPE AddRef();
		ULONG STDMETHODCALLTYPE Release();
		STDMETHODIMP GetTypeInfoCount(UINT *ptiCount);
		STDMETHODIMP GetTypeInfo(UINT iTInfo, LCID lcid, ITypeInfo **pptInfo);
		STDMETHODIMP GetIDsOfNames(REFIID riid, OLECHAR **rgszNames, UINT cNames, LCID lcid, DISPID *rgDispID);
		STDMETHODIMP Invoke(DISPID dispID, REFIID riid, LCID lcid, WORD wFlags, DISPPARAMS *pDispParams, VARIANT *pVarResult, EXCEPINFO *pExcepInfo, UINT *puArgErr);
	};
#pragma endregion class ScriptObject

	//---------------------------------------------------------------------------------------------------------
	// class ScriptObject
#pragma region class ScriptEngine
	class ScriptEngine : public ComPtr < IScriptControl >, public Singleton < ScriptEngine >
	{
	private:
		String _LangName;
		List<String> _FunctionList;
		bool GetMethodsName();
		LPCTSTR GetScriptFunction(LPCTSTR name);
		//protected:
	public:
		ScriptEngine();
		virtual ~ScriptEngine();

		inline String GetLanguage() {
			return _LangName;
		}

		void Reset();
		void AddCode(LPTSTR strCode);

		bool SetObject(ScriptObject& obj, bool AddMembers);
		bool ExecuteStatement(LPCTSTR szStatement);
		bool RunProcedure(LPCTSTR szProcName, SAFEARRAY** saParameters, VARIANT* varRet);
		String GetErrorString();
	};
#pragma endregion class ScriptEngine
} /* namespace System */

#endif /* SYSTEM_SCRIPTENGINE_H_ */

#endif
