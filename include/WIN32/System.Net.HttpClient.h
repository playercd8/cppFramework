/*
* System.Net.HttpClient.h
*
* Code Status: Drafts
*  Created on: Taiwan
*      Author: player
*  References:
*		http://www.codeproject.com/Articles/1345/AmHttpUtilities
*/

#include "../stdafx.h"

#if defined(_WINDOWS) && defined(_APP_MODE) && (_APP_MODE == _APP_MODE_CLIENT)

#ifndef SYSTEM_NET_HTTPCLIENT_H_
#define SYSTEM_NET_HTTPCLIENT_H_

#include <tchar.h>
#include <windows.h>
#include <Wininet.h>
#pragma comment(lib, "Wininet.lib")

#include "../System.String.h"
#include "../System.Buffer.h"

namespace System {
namespace Net {

class HttpClient {
//private:
protected:
	HINTERNET _hInternetOpen, _hInternetConnect, _hHttpOpenRequest;
	//char *_ReceivedData; //the internal databuffer
	//TCHAR *_Headers; //the internal headerbuffer
	Buffer _ReceivedData; //the internal databuffer
	Buffer _Headers;	//the internal headerbuffer
	int _LastError; //internal statuscode...

	bool PostUrl(const TCHAR *url, const char *PostData, int PostDataLength = -1); //open a page using http post
	TCHAR* GetHeaderLine(TCHAR *s); //get a specific line from the headers
	bool OpenUrl(const TCHAR *url); //open a page using http get

public:
	HttpClient();
	virtual ~HttpClient();

	int GetPageStatusCode(); //get the HTTP statuscode for the last received page
	Buffer& GetHeaders(const TCHAR *url); //return a pointer th the headers from an url
	Buffer& GetPage(const TCHAR *url, bool Post = false, const char *PostData = NULL, int PostDataLength = -1); //get a page, if post is false, HTTP GET is used othervise HTTP POST is used. if PostDataLength is -1 the data must be NULL terminated...
};
		
} /* namespace Net */
} /* namespace System */

#endif /* SYSTEM_NET_HTTPCLIENT_H_ */

#endif