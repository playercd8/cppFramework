/*
* System.ScriptEngine_MsScript.cpp
*
*  Created on: Taiwan
*      Author: player
* References:
*		http://www.codeproject.com/Articles/2539/Adding-VBScript-and-JScript-support-in-your-C-appl
*		http://mattn.kaoriya.net/software/lang/c/20080319121041.htm
*/

#include "../../include/stdafx.h"

#if defined(_WINDOWS) && ((_SCRIPT_ENGINE_LANG == _SCRIPT_ENGINE_JSCRIPT) || (_SCRIPT_ENGINE_LANG == _SCRIPT_ENGINE_VBSCRIPT))

#include "../../include/ScriptEngine/System.ScriptEngine_MsScript.h"

namespace System {
	//---------------------------------------------------------------------------------------------------------
	// class ScriptObject
#pragma region class ScriptObject

	STDMETHODIMP ScriptObject::QueryInterface(REFIID rid, LPVOID *ppv) {
		*ppv = NULL;
		if (::IsEqualIID(rid, IID_IUnknown)) {
			*ppv = this;
			AddRef();
			return S_OK;
		}
		if (::IsEqualIID(rid, IID_IDispatch)) {
			*ppv = this;
			AddRef();
			return S_OK;
		}
		return E_NOINTERFACE;
	}

	ULONG STDMETHODCALLTYPE ScriptObject::AddRef() {
		ULONG ref = InterlockedIncrement(&_refCount);
		return ref;
	}

	ULONG STDMETHODCALLTYPE ScriptObject::Release() {
		ULONG ref = InterlockedDecrement(&_refCount);
		return ref;
	}

	STDMETHODIMP ScriptObject::GetTypeInfoCount(UINT *ptiCount) {
		if (ptiCount) *ptiCount = 0;
		return S_OK;
	}

	STDMETHODIMP ScriptObject::GetTypeInfo(UINT iTInfo, LCID lcid, ITypeInfo **pptInfo) {
		if (pptInfo) *pptInfo = NULL;
		return S_OK;
	}

	STDMETHODIMP ScriptObject::GetIDsOfNames(REFIID riid, OLECHAR **rgszNames, UINT cNames, LCID lcid, DISPID *rgDispID) {
		//USES_CONVERSION;

		for (UINT n = 0; n < cNames; n++) {
			StringW strName = rgszNames[n];
			List<SCRIPT_OBJECT_METHOD_TABLE>::Iterator iter = _methodTable.GetHeadPosition();
			while (_methodTable.iteratorValid(iter)) {
				if (strName.Compare(iter->name) == 0) {
					rgDispID[n] = iter->dispid;
					break;
				}
				iter++;
			}
			if (!_methodTable.iteratorValid(iter)) return E_UNEXPECTED;
		}
		return S_OK;
	}

	STDMETHODIMP ScriptObject::Invoke(DISPID dispID, REFIID riid, LCID lcid, WORD wFlags, DISPPARAMS *pDispParams, VARIANT *pVarResult, EXCEPINFO *pExcepInfo, UINT *puArgErr) {
		List<SCRIPT_OBJECT_METHOD_TABLE>::Iterator iter = _methodTable.GetHeadPosition();
		while (_methodTable.iteratorValid(iter)) {
			if (iter->dispid == dispID) {
				return (this->*(iter->fn))(pDispParams, pVarResult);
			}
			iter++;
		}

		return E_UNEXPECTED;
	}

#pragma endregion class ScriptObject

	//---------------------------------------------------------------------------------------------------------
	// class ScriptObject
#pragma region class ScriptEngine

	ScriptEngine::ScriptEngine()
		: _LangName(ScriptLang)
	{
		IScriptControlPtr _pScript;
		HRESULT hr = _pScript.CreateInstance(__uuidof(ScriptControl));
		_com_util::CheckError(hr);
		_ptr = _pScript.GetInterfacePtr();

		// 設定 Script Engine
		_ptr->PutLanguage(_bstr_t(static_cast<LPCWSTR>(_LangName)));
		_ptr->Timeout = -1;
		_ptr->PutAllowUI(VARIANT_FALSE);
	}

	ScriptEngine::~ScriptEngine()
	{
	}

	void ScriptEngine::Reset()
	{
		_ptr->Reset();
		_FunctionList.RemoveAll();
	}

	void ScriptEngine::AddCode(LPTSTR strCode)
	{
		HRESULT hr = _ptr->AddCode(
			_bstr_t(strCode)	//[in] BSTR Code
			);
		GetMethodsName();
	}

	bool ScriptEngine::GetMethodsName()
	{
		bool bResult = false;
		if (_ptr != NULL)
		{
			ComPtr<IScriptProcedureCollection> pProcedures(_ptr->GetProcedures());

			// empty list...
			_FunctionList.RemoveAll();

			try{
				long count = pProcedures->GetCount();
				for (long index = 1; index <= count; index++)
				{
					IScriptProcedurePtr pIProcPtr = pProcedures->GetItem(_variant_t(index));
					_bstr_t name = pIProcPtr->GetName();
					_FunctionList.AddTail((LPCTSTR)name);
					pIProcPtr = NULL;
				}

				bResult = true;
			}
			catch (...)
			{
			}

			pProcedures = NULL;
		}
		return bResult;
	}

	LPCTSTR ScriptEngine::GetScriptFunction(LPCTSTR szName)
	{
		List<String>::Iterator iter = _FunctionList.GetHeadPosition();
		while (_FunctionList.iteratorValid(iter))
		{
			if ((*iter).CompareNoCase(szName) == 0)
				return *iter;

			iter++;
		}
		return _T("");
	}

	bool ScriptEngine::SetObject(ScriptObject& obj, bool AddMembers)
	{
		HRESULT hr = _ptr->AddObject(
			_bstr_t(static_cast<LPCWSTR>(obj.GetID())),
			obj,
			(VARIANT_BOOL)AddMembers);

		if FAILED(hr)
			return false;

		return true;
	}

	bool ScriptEngine::ExecuteStatement(LPCTSTR szStatement)
	{
		try {
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
		}

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
			catch (_com_error& ex)
			{
				UNREFERENCED_PARAMETER(ex);
				//TRACE((LPSTR)ex.Description());
				//TRACE((LPSTR)"\n");
			}
		}
		return ret;
	}

#pragma endregion class ScriptEngine
} /* namespace System */

#endif