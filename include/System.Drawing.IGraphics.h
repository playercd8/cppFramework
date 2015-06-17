/*
* System.Drawing.IGraphics.h
*
* Code Status: Drafts
*  Created on: Taiwan
*      Author: player
*/

#include "stdafx.h"

#ifndef SYSTEM_DRAWING_IGRAPHICS_H_
#define SYSTEM_DRAWING_IGRAPHICS_H_

#if _MSC_VER > 1000
	#pragma once
#endif

#include "System.Drawing.Math.h"

namespace System {
	namespace Drawing {
		class IGraphics
		{
		//private:
		//protected:
		public:
			//IGraphics() {}
			//virtual ~IGraphics() {}

			//-----------------------------------------------
			//3D計算貼圖材質是否為2的倍數
			inline bool IsPowerOf2(unsigned int n) {
				return (!(n & (n - 1)));
			}

			//取得大於或等於n的2的指數
			inline unsigned int GetLowestPowerOf2(unsigned int n) {
				unsigned int lowest = 1;
				while (lowest < n)
					lowest <<= 1;
				return lowest;
			}
		};
	} /* namespace Drawing */
} /* namespace System */

#endif /*  SYSTEM_DRAWING_IGRAPHICS_H_ */
