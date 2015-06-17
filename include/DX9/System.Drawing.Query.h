/*
 * System.Drawing.Query.h
 *
 * Code Status: Drafts
 *  Created on: Taiwan
 *      Author: player
 */

#include "../stdafx.h"
#if (_DRAWING_MODE == _DRAWING_MODE_DX9)

#ifndef SYSTEM_DRAWING_QUERY_H_
#define SYSTEM_DRAWING_QUERY_H_

#if _MSC_VER > 1000
#pragma once
#endif

#include "DX9.h"
#include "../System.ComPtr.h"

namespace System {
	namespace Drawing {
		class Renderer;
		Renderer* GetDefaultRendererPtr();

		typedef D3DQUERYTYPE Query_Type;

		class Query : public ComPtr < IDirect3DQuery9 > {
			//private:
			//protected:
		public:
			Query::Query(Query_Type type, Renderer* pRender = DefaultRendererPtr);
			Query(IDirect3DQuery9* pFont = NULL);
		};
	} /* namespace Drawing */
} /* namespace System */

#endif /* SYSTEM_DRAWING_QUERY_H_ */
#endif
