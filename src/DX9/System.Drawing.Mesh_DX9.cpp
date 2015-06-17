/*
 * System.Drawing.Mesh_DX9.cpp
 *
 *  Created on: Taiwan
 *      Author: player
 */

#include "../../include/stdafx.h"
#if (_DRAWING_MODE == _DRAWING_MODE_DX9)

#include "../../include/DX9/System.Drawing.Mesh.h"
#include "../../include/DX9/System.Drawing.Renderer.h"
#include "../../include/System.String.h"

namespace System {
	namespace Drawing {
		//---------------------------------------------------------------------------------------------------------
		// class Mesh
		Mesh::Mesh(Mesh_Desc& desc, Renderer* pRender)
		{
			HRESULT hr;
			V(D3DXCreateMesh(
				desc.NumFaces,				//[in]   DWORD NumFaces,
				desc.NumVertices,			//[in]   DWORD NumVertices,
				desc.Options,				//[in]   DWORD Options,
				desc.pDeclaration,			//[in]   const LPD3DVERTEXELEMENT9* pDeclaration,
				pRender->GetDevice(),		//[in]   LPDIRECT3DDEVICE9 pD3DDevice,
				&_ptr						//[out]  LPD3DXMESH *ppMesh
				));

			if FAILED(hr)
				_ptr = NULL;
		}

		Mesh::Mesh(ID3DXMesh* pMesh, DWORD NumMaterials, LPD3DXBUFFER pBuffer, Renderer* pRender)
		{
			_ptr = pMesh;
			_NumMaterials = NumMaterials;

			// We need to extract the material properties and texture names from the
			// pD3DXMtrlBuffer
			D3DXMATERIAL* pMaterials = (D3DXMATERIAL*)pBuffer->GetBufferPointer();
			_MeshMaterials.SetSize(_NumMaterials);
			_MeshTextures.SetSize(_NumMaterials);

			for (DWORD i = 0; i < _NumMaterials; i++) {
				// Copy the material
				D3DMATERIAL9* pMaterial = new D3DMATERIAL9;
				memcpy(&pMaterial, &pMaterials[i].MatD3D, sizeof(D3DMATERIAL9));

				// Set the ambient color for the material (D3DX does not do this)
				pMaterial->Ambient = pMaterial->Diffuse;

				LPSTR pFileName = pMaterials[i].pTextureFilename;
				if (pFileName != NULL && strlen(pFileName) > 0) {
#if defined(_UNICODE)
					// Create the texture
					String strFileName = String(pFileName);
					Texture2D* pTexture2D = Texture2D::FromFile(strFileName, pRender);
#else
					// Create the texture
					Texture2D* pTexture2D = Texture2D::FromFile(g, pFileName);
#endif
					_MeshTextures.SetAt(i, pTexture2D);
				}
				else {
					_MeshTextures.SetAt(i, NULL);
				}

				_MeshMaterials.SetAt(i, pMaterial);
			}

			// Done with the material buffer
			pBuffer->Release();
		}

		Mesh::~Mesh() {
			Texture2D* pTexture2D;
			for (int i = 0; i < _MeshTextures.GetSize(); i++) {
				pTexture2D = _MeshTextures.GetAt(i);
				SafeDelete(pTexture2D);
			}
			_MeshTextures.RemoveAll();

			D3DMATERIAL9* pMaterials;
			for (int i = 0; i < _MeshMaterials.GetSize(); i++) {
				pMaterials = _MeshMaterials.GetAt(i);
				SafeDelete(pMaterials);
			}
			_MeshMaterials.RemoveAll();
		}

		void Mesh::_Draw(IDirect3DDevice9* pDevice) {
			for (DWORD i = 0; i < _NumMaterials; i++) {
				pDevice->SetMaterial(_MeshMaterials.GetAt(i));
				pDevice->SetTexture(0, *_MeshTextures.GetAt(i));

				// Draw the mesh subset
				_ptr->DrawSubset(i);
			}
		}

		Mesh* Mesh::FromXFile(LPCTSTR pFile, Renderer* pRender)
		{
			HRESULT hr;
			LPD3DXBUFFER pBuffer;
			DWORD NumMaterials;
			LPD3DXMESH pMesh;

			// Load the mesh from the specified file
			V(D3DXLoadMeshFromX(
				pFile,					//[in]   LPCTSTR pFilename,
				D3DXMESH_SYSTEMMEM,		//[in]   DWORD Options,
				pRender->GetDevice(),	//[in]   LPDIRECT3DDEVICE9 pD3DDevice,
				NULL,					//[out]  LPD3DXBUFFER *ppAdjacency,
				&pBuffer,				//[out]  LPD3DXBUFFER *ppMaterials,
				NULL,					//[out]  LPD3DXBUFFER *ppEffectInstances,
				&NumMaterials,			//[out]  DWORD *pNumMaterials,
				&pMesh					//[out]  LPD3DXMESH *ppMesh
				));

			if FAILED(hr)
				return NULL;

			return new Mesh(pMesh, NumMaterials, pBuffer, pRender);
		}
	} /* namespace Drawing */
} /* namespace System */

#endif