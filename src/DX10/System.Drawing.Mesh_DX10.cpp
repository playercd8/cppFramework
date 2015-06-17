/*
 * System.Drawing.Mesh_DX10.cpp
 *
 *  Created on: Taiwan
 *      Author: player
 */

#include "../../include/stdafx.h"
#if (_DRAWING_MODE == _DRAWING_MODE_DX10)

#include "../../include/DX10/System.Drawing.Mesh.h"
#include "../../include/DX10/System.Drawing.Renderer.h"

namespace System {
	namespace Drawing {
		//---------------------------------------------------------------------------------------------------------
		// class Mesh

		Mesh::Mesh(Mesh_Desc& desc, Renderer* pRender)
		{
			HRESULT hr = D3DX10CreateMesh(
				pRender->GetDevice(),	//[in]   ID3D10Device *pDevice,
				&desc.Declaration,		//[in]   const D3D10_INPUT_ELEMENT_DESC *pDeclaration,
				desc.DeclCount,			//[in]   UINT DeclCount,
				desc.pPositionSemantic,	//[in]   LPCSTR pPositionSemantic,
				desc.VertexCount,		//[in]   UINT VertexCount,
				desc.FaceCount,			//[in]   UINT FaceCount,
				desc.Options,			//[in]   UINT Options,
				&_ptr					//[out]  ID3DX10Mesh **ppMesh
				);
		}

		Mesh::Mesh(ID3DX10Mesh* pMesh)
		{
			_ptr = pMesh;
		}

		Mesh::~Mesh()
		{
		}

		//Mesh* Mesh::FromXFile(LPCTSTR pFile, Renderer* pRender = DefaultRendererPtr)
		//{
		//}

		void Mesh::_Draw(ID3D10Device* pDevice, ID3D10EffectTechnique* pEffectTechnique, UINT Passes)
		{
			//UNREFERENCED_PARAMETER(pDevice);
			for (UINT p = 0; p < Passes; p++)
			{
				//apply technique
				pEffectTechnique->GetPassByIndex(p)->Apply(0);
				_ptr->DrawSubset(0);
			}
		}
	} /* namespace Drawing */
} /* namespace System */

#endif