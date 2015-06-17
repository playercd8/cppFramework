/*
 * System.Drawing.Mesh.h
 *
 * Code Status: Drafts
 *  Created on: Taiwan
 *      Author: player
 */

#include "../stdafx.h"
#if (_DRAWING_MODE == _DRAWING_MODE_DX9)

#ifndef SYSTEM_DRAWING_MESH_H_
#define SYSTEM_DRAWING_MESH_H_

#if _MSC_VER > 1000
#pragma once
#endif

#include "DX9.h"
#include "../System.Collections.Array.h"
#include "../System.ComPtr.h"
#include "System.Drawing.Texture.h"

using namespace System::Collections;

namespace System {
	namespace Drawing {
		class Renderer;
		Renderer* GetDefaultRendererPtr();

		typedef struct Mesh_Desc {
			DWORD NumFaces;
			DWORD NumVertices;
			DWORD Options;
			const LPD3DVERTEXELEMENT9 pDeclaration;
		} Mesh_Desc;

		class Mesh : public ComPtr < ID3DXMesh > {
			//private:
		protected:
			DWORD _NumMaterials;
			Array<D3DMATERIAL9*> _MeshMaterials;
			Array<Texture2D*> _MeshTextures;

			void _Draw(IDirect3DDevice9* pDevice);
			friend class Renderer;

		public:
			Mesh(Mesh_Desc& desc, Renderer* pRender = DefaultRendererPtr);
			Mesh(ID3DXMesh* pMesh, DWORD NumMaterials, LPD3DXBUFFER pBuffer, Renderer* pRender = DefaultRendererPtr);

			~Mesh();

			static Mesh* FromXFile(LPCTSTR pFile, Renderer* pRender = DefaultRendererPtr);
		};
	} /* namespace Drawing */
} /* namespace System */

#endif /* SYSTEM_DRAWING_MESH_H_ */
#endif
