/*
 * System.Drawing.Query_DX9.cpp
 *
 *  Created on: Taiwan
 *      Author: player
 */

#include "../../include/stdafx.h"
#if (_DRAWING_MODE == _DRAWING_MODE_DX9)

#include "../../include/DX9/System.Drawing.Query.h"
#include "../../include/DX9/System.Drawing.Renderer.h"

namespace System {
	namespace Drawing {
		//---------------------------------------------------------------------------------------------------------
		// class Query

		Query::Query(Query_Type type, Renderer* pRender)
		{
			HRESULT hr;
			V(pRender->GetDevice()->CreateQuery(
				type,	//[in]           D3DQUERYTYPE Type,
				&_ptr	//[out, retval]  IDirect3DQuery9 **ppQuery
				));

			if FAILED(hr)
				_ptr = NULL;
		}

		Query::Query(IDirect3DQuery9* pQuery)
		{
			_ptr = pQuery;
		}
	} /* namespace Drawing */
} /* namespace System */

#endif