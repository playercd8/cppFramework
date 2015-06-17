/*
 * System.Drawing.Mesh.h
 *
 *  Created on: Taiwan
 *      Author: player
 */

#include "../stdafx.h"
#if (_DRAWING_MODE == _DRAWING_MODE_DX10)

#ifndef SYSTEM_DRAWING_MESH_H_
#define SYSTEM_DRAWING_MESH_H_

#if _MSC_VER > 1000
#pragma once
#endif

#include "DX10.h"
#include "System.Drawing.Mesh.h"
#include "../System.ComPtr.h"

namespace System {
	namespace Drawing {
		class Renderer;
		Renderer* GetDefaultRendererPtr();

		typedef struct Mesh_Desc {
			D3D10_INPUT_ELEMENT_DESC Declaration;
			UINT DeclCount;
			LPCSTR pPositionSemantic;
			UINT VertexCount;
			UINT FaceCount;
			UINT Options;
		} Mesh_Desc;

		class Mesh : public ComPtr < ID3DX10Mesh > {
			//private:
		protected:
			void _Draw(ID3D10Device* pDevice, ID3D10EffectTechnique* pEffectTechnique, UINT Passes);
			friend class Renderer;
		public:
			Mesh(Mesh_Desc& desc, Renderer* pRender = DefaultRendererPtr);
			Mesh(ID3DX10Mesh* pMesh = NULL);

			~Mesh();

			//static Mesh* FromXFile(LPCTSTR pFile, Renderer* pRender = DefaultRendererPtr);
		};
	} /* namespace Drawing */
} /* namespace System */

#endif /* SYSTEM_DRAWING_MESH_H_ */
#endif
