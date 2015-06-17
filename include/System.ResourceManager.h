/*
* System.ResourceManager.h
*
* Code Status: Drafts
*  Created on: Taiwan
*      Author: player
*/

#ifndef SYSTEM_RESOURCE_MANAGER_H_
#define SYSTEM_RESOURCE_MANAGER_H_

#if _MSC_VER > 1000
#pragma once
#endif

#include "stdafx.h"
#include "System.OOP.h"

namespace System {
	class ResourceManager : public Singleton < ResourceManager >
	{
	public:
		ResourceManager();
		virtual ~ResourceManager();
	};
} /* namespace System */

#endif /* SYSTEM_RESOURCE_MANAGER_H_ */
