/*
* System.Drawing.Query_DX11.cpp
*
*  Created on: Taiwan
*      Author: player
*/

#include "../../include/stdafx.h"
#if (_DRAWING_MODE == _DRAWING_MODE_DX11)

#include "../../include/DX11/System.Drawing.Query.h"
#include "../../include/DX11/System.Drawing.Renderer.h"


namespace System {
namespace Drawing {

//---------------------------------------------------------------------------------------------------------
// class Query

Query::Query(Query_Desc& desc, Renderer* pRender)
{
	HRESULT hr = pRender->GetDevice()->CreateQuery(
		&desc,	// [in]   const D3D11_QUERY_DESC *pQueryDesc,
		&_ptr	//[out]  ID3D11Query **ppQuery
		);


	if FAILED(hr) {
		_ptr = NULL;
	}
}

Query::Query(ID3D11Query* pQuery)
{
	_ptr = pQuery;
}

} /* namespace Drawing */
} /* namespace System */

#endif
