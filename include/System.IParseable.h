/*
 * System.IParseable.h
 *
 * Code Status: Drafts
 *  Created on: Taiwan
 *      Author: player
 */

#ifndef SYSTEM_IPARSEABLE_H_
#define SYSTEM_IPARSEABLE_H_

#if _MSC_VER > 1000
	#pragma once
#endif

#include "System.String.h"

namespace System {

	template <typename T>
	class IParseable {
	public:
		//IParseable() {}
		virtual ~IParseable() {}

		virtual T Parse(LPCTSTR pStr);
	};

} /* namespace System */

#endif /* SYSTEM_IPARSEABLE_H_ */
