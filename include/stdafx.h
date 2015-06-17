// stdafx.h : 可在此標頭檔中包含標準的系統 Include 檔，
// 或是經常使用卻很少變更的
// 專案專用 Include 檔案
//

#pragma once

#include "targetver.h"

// 屬性化定義
#define Define_Setter(METHOD, TYPE, MEMBER) inline void METHOD(TYPE& t) { this->MEMBER = t; }
#define Define_Getter(TYPE, METHOD, MEMBER) inline TYPE& METHOD() const { return this->MEMBER; }

#include <new>		// yes, this one new style header

#ifdef ANDROID_NDK
	#include <stddef.h>
#else
	#include <cstddef>
#endif

// Windows 標頭檔:
#if defined(_MSC_VER) && defined(_WIN32)
	//#define WIN32_LEAN_AND_MEAN             // 從 Windows 標頭排除不常使用的成員
	#include <windows.h>
#endif

// C RunTime 標頭檔
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

// TODO:  在此參考您的程式所需要的其他標頭
//-----------------------------------------------------------
// max, min
#ifndef max
	#define max(a,b)            (((a) > (b)) ? (a) : (b))
#endif

#ifndef min
	#define min(a,b)            (((a) < (b)) ? (a) : (b))
#endif

//-----------------------------------------------------------
// Debug
#include <cassert>
#if defined(_MSC_VER) && defined(_DEBUG)
	#include <crtdbg.h>
	#define	DEBUG_NEW	new(_NORMAL_BLOCK, __FILE__, __LINE__)
#else
	#define	DEBUG_NEW	new
#endif

#ifndef Assert
	#if defined(_MSC_VER) && (defined( DEBUG ) || defined( _DEBUG ))
		#if defined(_UNICODE)
			#define Assert(b) if (!(b)) {OutputDebugStringW(L"Assert: " #b L"\n");}
		#else
			#define Assert(b) if (!(b)) {OutputDebugStringA("Assert: " #b "\n");}
		#endif
	#else
		#define Assert(b)
	#endif //DEBUG || _DEBUG
#endif

//-----------------------------------------------------------
// _ENABLE_CPP11, _ENABLE_CPP14
#if (__cplusplus >= 201103L) || ((_MSC_VER >= 1800) && (__cplusplus == 199711L))
	#define	_ENABLE_CPP11 true
#endif
//#define	_ENABLE_CPP14 false

//-----------------------------------------------------------
// _CODE_MODE
#define	_CODE_MODE_CPP11 1
#define	_CODE_MODE_WIN32 2
#define	_CODE_MODE_WIN64 3
#define	_CODE_MODE_APPLE 4
#define	_CODE_MODE_LINUX 5
#define	_CODE_MODE_UNIX 6
#define	_CODE_MODE_POSIX 7
#define	_CODE_MODE_UNKNOWN -1

/*
#if (__cplusplus >= 201103L) || ((_MSC_VER >= 1800) && (__cplusplus == 199711L))
	#define	_CODE_MODE _CODE_MODE_CPP11
#elif defined(_WIN32)
	#define	_CODE_MODE _CODE_MODE_WIN32
#elif defined(_WIN64)
	#define	_CODE_MODE _CODE_MODE_WIN64
#elif defined(__APPLE__)
	#define	_CODE_MODE _CODE_MODE_APPLE
#elif defined(__linux)
	#define	_CODE_MODE _CODE_MODE_LINUX
#elif defined(__unix)
	#define	_CODE_MODE _CODE_MODE_UNIX
#elif defined(__posix)
	#define	_CODE_MODE _CODE_MODE_POSIX
#else
	#define	_CODE_MODE _CODE_MODE_UNKNOWN
#endif
*/

#define	_CODE_MODE _CODE_MODE_WIN32

//-----------------------------------------------------------
//_DRAWING_MODE
#define	_AUDIO_MODE_MCI 0
#define	_AUDIO_MODE_DSOUND 1
#define	_AUDIO_MODE_XAUDIO 2
#define _AUDIO_MODE _AUDIO_MODE_DSOUND

//-----------------------------------------------------------
//_DRAWING_MODE
#define	_DRAWING_MODE_DX9		9
#define	_DRAWING_MODE_DX10		10
#define	_DRAWING_MODE_DX11		11
#define	_DRAWING_MODE_OPENGL	0

#define	_DRAWING_MODE _DRAWING_MODE_DX9

//-----------------------------------------------------------
//_Math_Type
#define	_MATH_TYPE_D3DX	0
#define	_MATH_TYPE_CPP	1
#define	_MATH_TYPE_XNA	2
#define	_MATH_TYPE_SSE	3
//#define	_MATH_TYPE_AVX	4

#define	_MATH_TYPE _MATH_TYPE_CPP

#define PixelShader_FunctionName	"ps_main"
#define  PixelShader_Profile		"ps_3_0"
#define VertexShader_FunctionName	"vs_main"
#define VertexShader_Profile		"vs_3_0"

//-----------------------------------------------------------
//_SCRIPT_ENGINE_LANG
#define	_SCRIPT_ENGINE_NOUSE		0
#define	_SCRIPT_ENGINE_JSCRIPT		1
#define	_SCRIPT_ENGINE_VBSCRIPT		2
#define	_SCRIPT_ENGINE_LUA			3

#define	_SCRIPT_ENGINE_LANG _SCRIPT_ENGINE_JSCRIPT
#define	_SCRIPT_INIT_FILENAME "js\main.js"

//-----------------------------------------------------------
//Application
#define _APP_MODE_CLIENT 1
#define _APP_MODE_SERVER 2

#define _APP_MODE _APP_MODE_CLIENT

#if (_APP_MODE == _APP_MODE_CLIENT)
	#define	Application	ClientApp
	#define DefaultRendererPtr GetDefaultRendererPtr()
#elif (_APP_MODE == _APP_MODE_SERVER)
	#define	Application	ServerApp
//	#define DefaultRendererPtr
#endif

//-----------------------------------------------------------
//Debug時是否彈出視窗?
#define _SHOW_ERR_MSGBOX true

//-----------------------------------------------------------
//是否使用資源管理
#define _USE_ResourceManager false