/*
 * System.Drawing.Query_DX10.cpp
 *
 *  Created on: Taiwan
 *      Author: player
 */

#include "../../include/stdafx.h"
#if (_DRAWING_MODE == _DRAWING_MODE_DX10)

#include "../../include/DX10/System.Drawing.Query.h"
#include "../../include/DX10/System.Drawing.Renderer.h"

namespace System {
	namespace Drawing {
		//---------------------------------------------------------------------------------------------------------
		// class Query

		Query::Query(Query_Desc& desc, Renderer* pRender)
		{
			HRESULT hr;
			V(pRender->GetDevice()->CreateQuery(
				&desc,	// [in]   const D3D10_QUERY_DESC *pQueryDesc,
				&_ptr	//[out]  ID3D10Query **ppQuery
				));

			if FAILED(hr)
				_ptr = NULL;
		}

		Query::Query(ID3D10Query* pQuery)
		{
			_ptr = pQuery;
		}
	} /* namespace Drawing */
} /* namespace System */

#endif