/*
* System.Drawing.Colors.h
*
* Code Status: Drafts
*  Created on: Taiwan
*      Author: player
*
*  References:
*	1.
*/

#ifndef SYSTEM_DRAWING_COLORS_H_
#define SYSTEM_DRAWING_COLORS_H_

#if _MSC_VER > 1000
#pragma once
#endif

#ifndef SYSTEM_DRAWING_MATH_H_
#include "../stdafx.h"
#include "../System.Drawing.Math.h"
#endif

namespace System {
	namespace Drawing {
		namespace Colors {
#define _ColorRGBA(r,g,b,a) DWORD((DWORD(a) << 24) | (DWORD(r) << 16) | (DWORD(g) << 8) | DWORD(b))

			const Color Transparent(_ColorRGBA(0, 0, 0, 0));
			const Color AliceBlue(_ColorRGBA(240, 248, 255, 255));
			const Color AntiqueWhite(_ColorRGBA(250, 235, 215, 255));
			const Color Aqua(_ColorRGBA(0, 255, 255, 255));
			const Color Aquamarine(_ColorRGBA(127, 255, 212, 255));
			const Color Azure(_ColorRGBA(240, 255, 255, 255));
			const Color Beige(_ColorRGBA(245, 245, 220, 255));
			const Color Bisque(_ColorRGBA(255, 228, 196, 255));
			const Color Black(_ColorRGBA(0, 0, 0, 255));
			const Color BlanchedAlmond(_ColorRGBA(255, 235, 205, 255));
			const Color Blue(_ColorRGBA(0, 0, 255, 255));
			const Color BlueViolet(_ColorRGBA(138, 43, 226, 255));
			const Color Brown(_ColorRGBA(165, 42, 42, 255));
			const Color BurlyWood(_ColorRGBA(222, 184, 135, 255));
			const Color CadetBlue(_ColorRGBA(95, 158, 160, 255));
			const Color Chartreuse(_ColorRGBA(127, 255, 0, 255));
			const Color Chocolate(_ColorRGBA(210, 105, 30, 255));
			const Color Coral(_ColorRGBA(255, 127, 80, 255));
			const Color CornflowerBlue(_ColorRGBA(100, 149, 237, 255));
			const Color Cornsilk(_ColorRGBA(255, 248, 220, 255));
			const Color Crimson(_ColorRGBA(220, 20, 60, 255));
			const Color Cyan(_ColorRGBA(0, 255, 255, 255));
			const Color DarkBlue(_ColorRGBA(0, 0, 139, 255));
			const Color DarkCyan(_ColorRGBA(0, 139, 139, 255));
			const Color DarkGoldenrod(_ColorRGBA(184, 134, 11, 255));
			const Color DarkGray(_ColorRGBA(169, 169, 169, 255));
			const Color DarkGreen(_ColorRGBA(0, 100, 0, 255));
			const Color DarkKhaki(_ColorRGBA(189, 183, 107, 255));
			const Color DarkMagenta(_ColorRGBA(139, 0, 139, 255));
			const Color DarkOliveGreen(_ColorRGBA(85, 107, 47, 255));
			const Color DarkOrange(_ColorRGBA(255, 140, 0, 255));
			const Color DarkOrchid(_ColorRGBA(153, 50, 204, 255));
			const Color DarkRed(_ColorRGBA(139, 0, 0, 255));
			const Color DarkSalmon(_ColorRGBA(233, 150, 122, 255));
			const Color DarkSeaGreen(_ColorRGBA(143, 188, 139, 255));
			const Color DarkSlateBlue(_ColorRGBA(72, 61, 139, 255));
			const Color DarkSlateGray(_ColorRGBA(47, 79, 79, 255));
			const Color DarkTurquoise(_ColorRGBA(0, 206, 209, 255));
			const Color DarkViolet(_ColorRGBA(148, 0, 211, 255));
			const Color DeepPink(_ColorRGBA(255, 20, 147, 255));
			const Color DeepSkyBlue(_ColorRGBA(0, 191, 255, 255));
			const Color DimGray(_ColorRGBA(105, 105, 105, 255));
			const Color DodgerBlue(_ColorRGBA(30, 144, 255, 255));
			const Color Firebrick(_ColorRGBA(178, 34, 34, 255));
			const Color FloralWhite(_ColorRGBA(255, 250, 240, 255));
			const Color ForestGreen(_ColorRGBA(34, 139, 34, 255));
			const Color Fuchsia(_ColorRGBA(255, 0, 255, 255));
			const Color Gainsboro(_ColorRGBA(220, 220, 220, 255));
			const Color GhostWhite(_ColorRGBA(248, 248, 255, 255));
			const Color Gold(_ColorRGBA(255, 215, 0, 255));
			const Color Goldenrod(_ColorRGBA(218, 165, 32, 255));
			const Color Gray(_ColorRGBA(128, 128, 128, 255));
			const Color Green(_ColorRGBA(0, 128, 0, 255));
			const Color GreenYellow(_ColorRGBA(173, 255, 47, 255));
			const Color Honeydew(_ColorRGBA(240, 255, 240, 255));
			const Color HotPink(_ColorRGBA(255, 105, 180, 255));
			const Color IndianRed(_ColorRGBA(205, 92, 92, 255));
			const Color Indigo(_ColorRGBA(75, 0, 130, 255));
			const Color Ivory(_ColorRGBA(255, 255, 240, 255));
			const Color Khaki(_ColorRGBA(240, 230, 140, 255));
			const Color Lavender(_ColorRGBA(230, 230, 250, 255));
			const Color LavenderBlush(_ColorRGBA(255, 240, 245, 255));
			const Color LawnGreen(_ColorRGBA(124, 252, 0, 255));
			const Color LemonChiffon(_ColorRGBA(255, 250, 205, 255));
			const Color LightBlue(_ColorRGBA(173, 216, 230, 255));
			const Color LightCoral(_ColorRGBA(240, 128, 128, 255));
			const Color LightCyan(_ColorRGBA(224, 255, 255, 255));
			const Color LightGoldenrodYellow(_ColorRGBA(250, 250, 210, 255));
			const Color LightGreen(_ColorRGBA(144, 238, 144, 255));
			const Color LightGray(_ColorRGBA(211, 211, 211, 255));
			const Color LightPink(_ColorRGBA(255, 182, 193, 255));
			const Color LightSalmon(_ColorRGBA(255, 160, 122, 255));
			const Color LightSeaGreen(_ColorRGBA(32, 178, 170, 255));
			const Color LightSkyBlue(_ColorRGBA(135, 206, 250, 255));
			const Color LightSlateGray(_ColorRGBA(119, 136, 153, 255));
			const Color LightSteelBlue(_ColorRGBA(176, 196, 222, 255));
			const Color LightYellow(_ColorRGBA(255, 255, 224, 255));
			const Color Lime(_ColorRGBA(0, 255, 0, 255));
			const Color LimeGreen(_ColorRGBA(50, 205, 50, 255));
			const Color Linen(_ColorRGBA(250, 240, 230, 255));
			const Color Magenta(_ColorRGBA(255, 0, 255, 255));
			const Color Maroon(_ColorRGBA(128, 0, 0, 255));
			const Color MediumAquamarine(_ColorRGBA(102, 205, 170, 255));
			const Color MediumBlue(_ColorRGBA(0, 0, 205, 255));
			const Color MediumOrchid(_ColorRGBA(186, 85, 211, 255));
			const Color MediumPurple(_ColorRGBA(147, 112, 219, 255));
			const Color MediumSeaGreen(_ColorRGBA(60, 179, 113, 255));
			const Color MediumSlateBlue(_ColorRGBA(123, 104, 238, 255));
			const Color MediumSpringGreen(_ColorRGBA(0, 250, 154, 255));
			const Color MediumTurquoise(_ColorRGBA(72, 209, 204, 255));
			const Color MediumVioletRed(_ColorRGBA(199, 21, 133, 255));
			const Color MidnightBlue(_ColorRGBA(25, 25, 112, 255));
			const Color MintCream(_ColorRGBA(245, 255, 250, 255));
			const Color MistyRose(_ColorRGBA(255, 228, 225, 255));
			const Color Moccasin(_ColorRGBA(255, 228, 181, 255));
			const Color NavajoWhite(_ColorRGBA(255, 222, 173, 255));
			const Color Navy(_ColorRGBA(0, 0, 128, 255));
			const Color OldLace(_ColorRGBA(253, 245, 230, 255));
			const Color Olive(_ColorRGBA(128, 128, 0, 255));
			const Color OliveDrab(_ColorRGBA(107, 142, 35, 255));
			const Color Orange(_ColorRGBA(255, 165, 0, 255));
			const Color OrangeRed(_ColorRGBA(255, 69, 0, 255));
			const Color Orchid(_ColorRGBA(218, 112, 214, 255));
			const Color PaleGoldenrod(_ColorRGBA(238, 232, 170, 255));
			const Color PaleGreen(_ColorRGBA(152, 251, 152, 255));
			const Color PaleTurquoise(_ColorRGBA(175, 238, 238, 255));
			const Color PaleVioletRed(_ColorRGBA(219, 112, 147, 255));
			const Color PapayaWhip(_ColorRGBA(255, 239, 213, 255));
			const Color PeachPuff(_ColorRGBA(255, 218, 185, 255));
			const Color Peru(_ColorRGBA(205, 133, 63, 255));
			const Color Pink(_ColorRGBA(255, 192, 203, 255));
			const Color Plum(_ColorRGBA(221, 160, 221, 255));
			const Color PowderBlue(_ColorRGBA(176, 224, 230, 255));
			const Color Purple(_ColorRGBA(128, 0, 128, 255));
			const Color Red(_ColorRGBA(255, 0, 0, 255));
			const Color RosyBrown(_ColorRGBA(188, 143, 143, 255));
			const Color RoyalBlue(_ColorRGBA(65, 105, 225, 255));
			const Color SaddleBrown(_ColorRGBA(139, 69, 19, 255));
			const Color Salmon(_ColorRGBA(250, 128, 114, 255));
			const Color SandyBrown(_ColorRGBA(244, 164, 96, 255));
			const Color SeaGreen(_ColorRGBA(46, 139, 87, 255));
			const Color SeaShell(_ColorRGBA(255, 245, 238, 255));
			const Color Sienna(_ColorRGBA(160, 82, 45, 255));
			const Color Silver(_ColorRGBA(192, 192, 192, 255));
			const Color SkyBlue(_ColorRGBA(135, 206, 235, 255));
			const Color SlateBlue(_ColorRGBA(106, 90, 205, 255));
			const Color SlateGray(_ColorRGBA(112, 128, 144, 255));
			const Color Snow(_ColorRGBA(255, 250, 250, 255));
			const Color SpringGreen(_ColorRGBA(0, 255, 127, 255));
			const Color SteelBlue(_ColorRGBA(70, 130, 180, 255));
			const Color Tan(_ColorRGBA(210, 180, 140, 255));
			const Color Teal(_ColorRGBA(0, 128, 128, 255));
			const Color Thistle(_ColorRGBA(216, 191, 216, 255));
			const Color Tomato(_ColorRGBA(255, 99, 71, 255));
			const Color Turquoise(_ColorRGBA(64, 224, 208, 255));
			const Color Violet(_ColorRGBA(238, 130, 238, 255));
			const Color Wheat(_ColorRGBA(245, 222, 179, 255));
			const Color White(_ColorRGBA(255, 255, 255, 255));
			const Color WhiteSmoke(_ColorRGBA(245, 245, 245, 255));
			const Color Yellow(_ColorRGBA(255, 255, 0, 255));
			const Color YellowGreen(_ColorRGBA(154, 205, 50, 255));
		} /* namespace Colors */
	} /* namespace Drawing */
} /* namespace System */

#endif /*  SYSTEM_DRAWING_MATH_H_ */