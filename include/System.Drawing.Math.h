/*
* System.Drawing.Math.h
*
* Code Status: Drafts
*  Created on: Taiwan
*      Author: player
*
*/

#include "stdafx.h"
#if (_MATH_TYPE == _MATH_TYPE_D3DX)
	#include "Math/System.Drawing.Math_D3DX.h"
#elif (_MATH_TYPE == _MATH_TYPE_SSE)
	#include "Math/System.Drawing.Math_SSE.h"
#elif (_MATH_TYPE == _MATH_TYPE_XNA)
	#include "Math/System.Drawing.Math_XNA.h"
//#elif (_MATH_TYPE == _MATH_TYPE_AVX)
//	#include "Math/System.Drawing.Math_AVX.h"
#else
	#undef _MATH_TYPE
	#define	_MATH_TYPE _MATH_TYPE_CPP
	#include "Math/System.Drawing.Math_CPP.h"	
#endif

