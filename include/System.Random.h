/*
 * System.Random.h
 *
 * Code Status: Drafts
 *  Created on: Taiwan
 *      Author: player
 */

#ifndef SYSTEM_RANDOM_H_
#define SYSTEM_RANDOM_H_

#if _MSC_VER > 1000
#pragma once
#endif

#include "stdafx.h"
#include <stdlib.h>     // srand, rand
#include <ctime>		// time

namespace System {
	class Random {
	public:
		Random() {
			/* initialize random seed: */
			::srand(::time(NULL));
		}

		virtual ~Random() {
		}

		//<summary>
		//取亂數
		//</summary>
		//<returns>亂數值</returns>
		//<remarks></remarks>
		inline int Next() {
			return ::rand();
		}

		//<summary>
		//取亂數
		//</summary>
		//<param name="max">最大值</param>
		//<returns>亂數值</returns>
		//<remarks></remarks>
		inline int Next(int max) {
			return (::rand() % (max + 1));
		}

		//<summary>
		//取亂數
		//</summary>
		//<param name="min">最小值</param>
		//<param name="max">最大值</param>
		//<returns>亂數值</returns>
		//<remarks></remarks>
		inline int Next(int min, int max) {
			return ((::rand() % (max + 1 - min)) + min);
		}

		//<summary>
		//骰子
		//</summary>
		//<param name="x">骰子數量</param>
		//<param name="face">骰子面數</param>
		//<returns></returns>
		//<remarks></remarks>
		inline int Dice(int x, int face) {
			int total = 0;
			if (x) {
				for (int i = 0; i < x; i++) {
					total += Next(face);
				}
			}
			return total;
		}
	};
} /* namespace System */

#endif /* SYSTEM_RANDOM_H_ */
