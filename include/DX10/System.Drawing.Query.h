/*
 * System.Drawing.Query.h
 *
 * Code Status: Drafts
 *  Created on: Taiwan
 *      Author: player
 */

#include "../stdafx.h"
#if (_DRAWING_MODE == _DRAWING_MODE_DX10)

#ifndef SYSTEM_DRAWING_QUERY_H_
#define SYSTEM_DRAWING_QUERY_H_

#if _MSC_VER > 1000
#pragma once
#endif

#include "DX10.h"
#include "../System.ComPtr.h"

namespace System {
	namespace Drawing {
		class Renderer;
		Renderer* GetDefaultRendererPtr();

		typedef D3D10_QUERY_DESC Query_Desc;

		class Query : public ComPtr < ID3D10Query > {
			//private:
			//protected:

		public:
			Query::Query(Query_Desc& desc, Renderer* pRender = DefaultRendererPtr);
			Query(ID3D10Query* pFont = NULL);
		};
	} /* namespace Drawing */
} /* namespace System */

#endif /* SYSTEM_DRAWING_QUERY_H_ */
#endif
