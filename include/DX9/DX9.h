/*
 * DX9.h
 *
 * Code Status: Drafts
 *  Created on: Taiwan
 *      Author: player
 */

#include "../stdafx.h"
#if (_DRAWING_MODE == _DRAWING_MODE_DX9)

#ifndef DX9_H_
#define DX9_H_

#if _MSC_VER > 1000
	#pragma once
#endif

#pragma warning(disable : 4005) 

//-----------------------------------------------------------
//DirectX 9相關
#include "./library/DXSDK/Include/d3dx9.h"

//fix錯誤	error LNK2001: 無法解析的外部符號 _IID_IDirect3DTexture9
#pragma comment(lib, "dxguid.lib")

#if defined(_M_IX86)
	#pragma comment(lib, "./library/DXSDK/lib/x86/d3d9.lib")
	#pragma comment(lib, "./library/DXSDK/lib/x86/d3dx9.lib")
#elif defined(_M_X64)
	#pragma comment(lib, "./library/DXSDK/lib/x64/d3d9.lib")
	#pragma comment(lib, "./library/DXSDK/lib\/64/d3dx9.lib")
#endif

//-----------------------------------------------------------
//Debug相關
#include "./library/DXSDK/Include/dxerr.h"
#if defined(_M_IX86)
#pragma comment(lib, "./library/DXSDK/lib/x86/DxErr.lib")
#elif defined(_M_X64)
#pragma comment(lib, "./library/DXSDK/lib/x64/DxErr.lib")
#endif

#if (_DRAWING_MODE > 0) && (defined(DEBUG) || defined(_DEBUG))
#define V(x)           { hr = x; if( FAILED(hr) ) { DXTrace( __FILE__, (DWORD)__LINE__, hr, L#x, _SHOW_ERR_MSGBOX ); } }
#define V_RETURN(x)    { hr = x; if( FAILED(hr) ) { return DXTrace( __FILE__, (DWORD)__LINE__, hr, L#x, _SHOW_ERR_MSGBOX ); } }
#else
#define V(x)           { hr = x; }
#define V_RETURN(x)    { hr = x; if( FAILED(hr) ) { return hr; } }
#endif

#pragma warning(default:4005)

#endif /* DX9_H_ */
#endif