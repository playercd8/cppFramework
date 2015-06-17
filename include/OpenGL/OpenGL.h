/*
 * OpenGL.h
 *
 *  Created on: Taiwan
 *      Author: player
 *
 *  References:
 *		1. https://www.opengl.org/documentation/specs/glut/spec3/spec3.html
 *		2. http://sourceforge.net/projects/glew/
 *		3. https://en.wikibooks.org/wiki/OpenGL_Programming
 */

#ifndef OPENGL_H_
#define OPENGL_H_

#if _MSC_VER > 1000
	#pragma once
#endif

#define GLEW_STATIC
#include "./library/OpenGL/Include/glew.h"
#include "./library/OpenGL/Include/glut.h"

#if defined(_M_IX86)
	#pragma comment(lib, "./library/OpenGL/lib/x86/glew32.lib")
	#pragma comment(lib, "./library/OpenGL/lib/x86/glut32.lib")
#elif defined(_M_X64)
	#pragma comment(lib, "./library/OpenGL/lib/x64/glew32.lib")
	#pragma comment(lib, "./library/OpenGL/lib\x64/glut32.lib")
#endif

#endif /* OPENGL_H_ */

