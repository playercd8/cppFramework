/*
* System.ComSafeArray.h
*
* Code Status: Drafts
*  Created on: Taiwan
*      Author: player
*/

#include "../stdafx.h"

#if defined(_WINDOWS)

#ifndef SYSTEM_COMSAFEARRAY_H_
#define SYSTEM_COMSAFEARRAY_H_

#if _MSC_VER > 1000
#pragma once
#endif


#include <OaIdl.h>
//#include <comdef.h>
//#include <comutil.h>
//#include <wtypes.h>

namespace System {
class ComSafeArray
{
//private:
protected:
	LPSAFEARRAY	_pSA;

public:
	ComSafeArray();
	virtual ~ComSafeArray();

	bool Create(VARTYPE  vt, UINT  cDims, UINT lBound, UINT cCount);
	bool Destroy();
	UINT GetDimension();

	bool Attach(LPSAFEARRAY psa);
	bool AttachFromVariant(VARIANT* pVariant);
	LPSAFEARRAY Detach();
	LPSAFEARRAY GetArray();
	bool AccessData(void FAR* FAR* pvData);
	bool UnaccessData();
	bool Lock();
	bool Unlock();
	bool PutElement(long lIndices, void FAR* vData);
	bool GetElement(long lIndices, void FAR* vData);
	VARIANT GetAsVariant();
};

} /* namespace System */

#endif /* SYSTEM_APPLICATION_H_ */

#endif