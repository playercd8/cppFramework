/*
* System.Drawing.Query.h
*
* Code Status: Drafts
*  Created on: Taiwan
*      Author: player
*/

#include "../stdafx.h"
#if (_DRAWING_MODE == _DRAWING_MODE_DX11)

#ifndef SYSTEM_DRAWING_QUERY_H_
#define SYSTEM_DRAWING_QUERY_H_

#if _MSC_VER > 1000
	#pragma once
#endif

#include "DX11.h"
#include "../System.ComPtr.h"

namespace System {
namespace Drawing {

class Renderer;
Renderer* GetDefaultRendererPtr();

typedef D3D11_QUERY_DESC Query_Desc;

class Query : public ComPtr<ID3D11Query> {
//protected:

public:
	Query::Query(Query_Desc& desc, Renderer* pRender = DefaultRendererPtr);
	Query(ID3D11Query* pFont = NULL);

};



	} /* namespace Drawing */
} /* namespace System */

#endif /* SYSTEM_DRAWING_QUERY_H_ */
#endif
