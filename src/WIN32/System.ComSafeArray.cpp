/*
* ComSafeArray.cpp
*
* Code Status : Drafts
*  Created on : Taiwan
*      Author : player
*/
#include "../../include/WIN32/System.ComSafeArray.h"

#if defined(_WINDOWS)

namespace System {
	ComSafeArray::ComSafeArray()
		: _pSA(NULL)
	{
	}

	ComSafeArray::~ComSafeArray()
	{
		Destroy();
	}

	///////////////////////////////////////////////////////////////////////////////
	// Members

	///////////////////////////////////////////////////////////////////////////////
	// Create : Creates a SafeArray object
	bool ComSafeArray::Create(VARTYPE  vt, UINT  cDims, UINT lBound, UINT cCount)
	{
		Destroy();

		if (cDims == 1)	// this is somewhat faster...
			_pSA = SafeArrayCreateVector(vt, lBound, cCount);
		else
		{
			SAFEARRAYBOUND rgsabound[1] = { 0 };
			rgsabound[0].lLbound = lBound;
			rgsabound[0].cElements = cCount;
			_pSA = SafeArrayCreate(vt, cDims, rgsabound);
		}
		return (_pSA != NULL);
	}

	///////////////////////////////////////////////////////////////////////////////
	// Destroy : Destroy the safeArray object (can't destroy it object is locked)
	bool ComSafeArray::Destroy()
	{
		if (NULL != _pSA)
		{
			// Maybe the object is locked!
			if (SUCCEEDED(SafeArrayDestroy(_pSA)))
				_pSA = NULL;
		}
		return (_pSA == NULL);
	}

	///////////////////////////////////////////////////////////////////////////////
	// GetArray : return Safearray pointer
	LPSAFEARRAY ComSafeArray::GetArray()
	{
		return _pSA;
	}

	///////////////////////////////////////////////////////////////////////////////
	// GetDimension : Get Dimemsion of the SafeArray
	UINT ComSafeArray::GetDimension()
	{
		UINT uDim = 0;
		if (NULL != _pSA)
			uDim = SafeArrayGetDim(_pSA);
		return uDim;
	}

	///////////////////////////////////////////////////////////////////////////////
	// Attach : Attach an existing SafeArray to this object
	bool ComSafeArray::Attach(LPSAFEARRAY psa)
	{
		if (NULL != psa)	// prevent 'destroy' for null pointer
		{
			Destroy();
			_pSA = psa;
			return true;
		}
		return false;
	}

	///////////////////////////////////////////////////////////////////////////////
	// Detach: Detach this SafeArray
	LPSAFEARRAY ComSafeArray::Detach()
	{
		if (NULL == _pSA)
			return NULL;

		LPSAFEARRAY psa = _pSA;
		_pSA = NULL;
		return psa;
	}

	///////////////////////////////////////////////////////////////////////////////
	// AttachFromVariant: Attach a Variant SafeArray
	bool ComSafeArray::AttachFromVariant(VARIANT* pVariant)
	{
		if (NULL != pVariant)
		{
			if (pVariant->vt & VT_ARRAY)
			{
				LPSAFEARRAY psa = pVariant->parray;
				if (pVariant->vt & VT_BYREF)	// VB use this...
					psa = *pVariant->pparray;
				return Attach(psa);
			}
		}
		return false;
	}

	///////////////////////////////////////////////////////////////////////////////
	// GetAsVariant
	// Description: Return a variant object of this SafeArray.  This function will
	//				try to represent the data based on features or size of elements
	VARIANT ComSafeArray::GetAsVariant()
	{
		VARIANT var;
		VariantClear(&var);
		if (NULL != _pSA)
		{
			var.vt = VT_ARRAY | VT_BYREF;
			var.pparray = &_pSA;
			USHORT fFeatures = _pSA->fFeatures;
			LONG cbElements = _pSA->cbElements;
			if (fFeatures & FADF_BSTR)
				var.vt |= VT_BSTR;
			else if (fFeatures & FADF_UNKNOWN)
				var.vt |= VT_UNKNOWN;
			else if (fFeatures & FADF_DISPATCH)
				var.vt |= VT_DISPATCH;
			else if (fFeatures & FADF_VARIANT)
				var.vt |= VT_VARIANT;
			else if (fFeatures & FADF_RECORD)
				var.vt |= VT_RECORD;
			else if (fFeatures & FADF_HAVEVARTYPE)
			{
				// these are just guess based on size of element, may not be accurated...
				if (sizeof(char) == cbElements) // 1 byte
					var.vt |= VT_UI1;
				else if (sizeof(short) == cbElements) // 2 bytes
					var.vt |= VT_UI2;
				else if (sizeof(long) == cbElements) // 4 bytes -- or float (VT_R4)
					var.vt |= VT_UI4;
				else if (sizeof(double) == cbElements) // 8 bytes -- or Currency (VT_CY)
					var.vt |= VT_R8;
			}
		}
		return var;
	}

	///////////////////////////////////////////////////////////////////////////////
	// AccessData : Get Access the SafeArray data
	bool ComSafeArray::AccessData(void FAR* FAR* pvData)
	{
		if (NULL != _pSA && NULL != pvData)
			return (SafeArrayAccessData(_pSA, pvData) == S_OK);

		return false;
	}

	///////////////////////////////////////////////////////////////////////////////
	// UnaccessData : Unaccess the safeArray data pointer
	bool ComSafeArray::UnaccessData()
	{
		if (NULL != _pSA)
			return (SafeArrayUnaccessData(_pSA) == S_OK);

		return false;
	}

	///////////////////////////////////////////////////////////////////////////////
	// Lock : Lock the SafeArray
	bool ComSafeArray::Lock()
	{
		if (NULL != _pSA)
			return (SafeArrayLock(_pSA) == S_OK);

		return false;
	}

	///////////////////////////////////////////////////////////////////////////////
	// Unlock : Unlock the SafeArray
	bool ComSafeArray::Unlock()
	{
		if (NULL != _pSA)
			return (SafeArrayUnlock(_pSA) == S_OK);

		return false;
	}

	///////////////////////////////////////////////////////////////////////////////
	// PutElement : Set element data
	bool ComSafeArray::PutElement(long lIndices, void FAR* vData)
	{
		if (NULL != _pSA)
			return (SafeArrayPutElement(_pSA, &lIndices, vData) == S_OK);

		return false;
	}

	///////////////////////////////////////////////////////////////////////////////
	// GetElement : Get element data
	bool ComSafeArray::GetElement(long lIndices, void FAR* vData)
	{
		if (NULL != _pSA)
			return (SafeArrayGetElement(_pSA, &lIndices, vData) == S_OK);

		return false;
	}
} /* namespace System */

#endif