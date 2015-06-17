/*
 * System.Guid_WIN32.cpp
 *
 * Code Status: Drafts
 *  Created on: Taiwan
 *      Author: player
 */

#include "../../include/stdafx.h"

#if defined(_WINDOWS)

#include "../../include/System.Guid.h"
#include <windows.h>
#include <Rpc.h>
#include <Rpcdce.h>
#pragma comment(lib, "Rpcrt4.lib")

namespace System {

void Guid::Generate() {
    GUID guid;
    UuidCreate(&guid);
#ifdef _UNICODE
	RPC_WSTR guidStr;
    UuidToString(&guid, &guidStr);
	_strGuid = (LPWSTR)guidStr;
	RpcStringFree(&guidStr);
#else

#endif
}

} /* namespace System */

#endif
