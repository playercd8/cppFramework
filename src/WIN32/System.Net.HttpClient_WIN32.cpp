/*
* System.Net.HttpClient_WIN32.cpp
*
* Code Status: Drafts
*  Created on: Taiwan
*      Author: player
*/

#include "../../include/stdafx.h"

#if defined(_WINDOWS)

#pragma warning(disable : 4996) 

#include "../../include/WIN32/System.Net.HttpClient.h"
#include "../../include/System.Collections.Queue.h"


namespace System {
namespace Net {	
	using namespace System::Collections;

	#define HttpHttpClientAgentName _T("System.Net.HttpClient 1.0")

	//case insensitive search functions...
#ifdef UNICODE
	#define _tcsustr wcsustr
#else
	#define _tcsustr strustr
#endif

	char* strustr(char *source, char *s);
	wchar_t* wcsustr(wchar_t *source, wchar_t *s);

	char* strustr(char *source, char *s)
	{
		//make an uppercase copy af source and s
		char *csource = strdup(source);
		char *cs = strdup(s);
		strupr(csource);
		strupr(cs);
		//find cs in csource...
		char *result = strstr(csource, cs);
		if (result) {
			//cs is somewhere in csource
			int pos = result - csource;
			result = source;
			result += pos;
		}
		//clean up
		free(csource);
		free(cs);
		return result;
	}

	wchar_t* wcsustr(wchar_t *source, wchar_t *s)
	{
		//make an uppercase copy af source and s
		wchar_t *csource = wcsdup(source);
		wchar_t *cs = wcsdup(s);
		wcsupr(csource);
		wcsupr(cs);
		//find cs in csource...
		wchar_t *result = wcsstr(csource, cs);
		if (result) {
			//cs is somewhere in csource
			int pos = result - csource;
			result = source;
			result += pos;
		}
		//clean up
		free(csource);
		free(cs);
		return result;
	}

	HttpClient::HttpClient() :
		_Headers(0), _ReceivedData(0) {
		_LastError = 0;
		_hInternetOpen = InternetOpen(HttpHttpClientAgentName, INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
		_hInternetConnect = NULL;
		_hHttpOpenRequest = NULL;
	}

	HttpClient::~HttpClient() {
		_ReceivedData.Clear();
		_Headers.Clear();
		if (_hHttpOpenRequest) 
			InternetCloseHandle(_hHttpOpenRequest);
		if (_hInternetConnect) 
			InternetCloseHandle(_hInternetConnect);
		if (_hInternetOpen) 
			InternetCloseHandle(_hInternetOpen);
	}

	bool HttpClient::OpenUrl(const TCHAR *url)
	{
		if (_hHttpOpenRequest) 
			InternetCloseHandle(_hHttpOpenRequest);

		_hHttpOpenRequest = InternetOpenUrl(_hInternetOpen, url, NULL, 0, HTTP_QUERY_DATE, 0);
		if (_hHttpOpenRequest) {
			return true;
		} else {
			_LastError = GetLastError();
			return false;
		}
	}

	bool HttpClient::PostUrl(const TCHAR *url, const char *PostData, int PostDataLength)
	{
		//check length of postdata
		if (PostDataLength == -1)
			PostDataLength = strlen(PostData);
		//some variable that we need...
		URL_COMPONENTS uc;
		//let's split the url...
		uc.dwStructSize = sizeof(uc);
		uc.lpszScheme = NULL;
		uc.dwSchemeLength = 0;
		uc.lpszHostName = NULL;
		uc.dwHostNameLength = 1;
		uc.nPort = 0;
		uc.lpszUserName = NULL;
		uc.dwUserNameLength = 0;
		uc.lpszPassword = NULL;
		uc.dwPasswordLength = 0;
		uc.lpszUrlPath = NULL;
		uc.dwUrlPathLength = 1;
		uc.lpszExtraInfo = NULL;
		uc.dwExtraInfoLength = 0;
		InternetCrackUrl(url, _tcslen(url), 0, &uc);

		//post the data...
		if (_hInternetConnect) InternetCloseHandle(_hInternetConnect);

		TCHAR *HostName = _tcsdup(uc.lpszHostName);
		HostName[uc.dwHostNameLength] = '\0';
		TCHAR *FileName = _tcsdup(uc.lpszUrlPath);
		FileName[uc.dwUrlPathLength] = '\0';

		if (_hHttpOpenRequest) InternetCloseHandle(_hHttpOpenRequest); //if open, close the handle to the connection
		DWORD flags;

		if (uc.nPort == 80) {
			//we are talking plain http
			flags = INTERNET_FLAG_NO_CACHE_WRITE;
		} else {
			//we are talking secure https
			flags = INTERNET_FLAG_NO_CACHE_WRITE | 
					INTERNET_FLAG_SECURE |
					INTERNET_FLAG_IGNORE_CERT_CN_INVALID | 
					INTERNET_FLAG_IGNORE_CERT_DATE_INVALID;
		}
		TCHAR headers[] = _T("Content-Type: application/x-www-form-urlencoded"); //content type for post...
		TCHAR szAccept[] = _T("*/*"); //we accept everything...
		LPTSTR AcceptTypes[2] = { 0 };
		AcceptTypes[0] = szAccept;
		_hInternetConnect = InternetConnect(_hInternetOpen, HostName, uc.nPort, _T(""), _T(""), INTERNET_SERVICE_HTTP, INTERNET_FLAG_NO_CACHE_WRITE, 0);
		_hHttpOpenRequest = HttpOpenRequest(_hInternetConnect, _T("POST"), FileName, NULL, NULL, (LPCTSTR*)AcceptTypes, flags, 0);
		if (!HttpSendRequest(_hHttpOpenRequest, headers, _tcslen(headers), (TCHAR*)PostData, PostDataLength))
		{
			_LastError = GetLastError();
			free(HostName);
			free(FileName);
			return false;
		}
		free(HostName);
		free(FileName);
		return true;
	}

	Buffer& HttpClient::GetHeaders(const TCHAR *url)
	{
		//did we get an url?
		if (url == NULL) {
			_LastError = -1;
			_Headers.Clear();
			return _Headers;
		}

		//open the url...
		OpenUrl(url);

		//delete old headers...
		_Headers.Clear();

		//get the size headers
		DWORD d = 1, d2 = 0;
		TCHAR temp[1];
		int i = HttpQueryInfo(_hHttpOpenRequest, HTTP_QUERY_RAW_HEADERS, temp, &d, &d2);

		//alloc some space for the headers
		_Headers.Resize(d * sizeof(TCHAR));

		if (!HttpQueryInfo(_hHttpOpenRequest, HTTP_QUERY_RAW_HEADERS, _Headers.GetPtr(), &d, &d2)) {
			_Headers.Clear();
		}
		return _Headers;
	}

	Buffer& HttpClient::GetPage(const TCHAR *url, bool Post, const char *PostData, int PostDataLength)
	{
		_ReceivedData.Clear();

		//did we get an url?
		if (url == NULL) {
			_LastError = -1;
			return _ReceivedData;
		}

		//get the page and store it in ReceivedData...
		if (Post) {
			//use http post...
			if (!PostUrl(url, PostData, PostDataLength)) {
				return _ReceivedData;
			}
		} else {
			//use http get
			if (!OpenUrl(url)) { 
				return _ReceivedData;
			}
		}

		Queue<LPBYTE> BuffQueue = Queue<LPBYTE>();
		const int rdsize = 16 * 1024;	
		LPBYTE pBuff = new BYTE[rdsize];
		DWORD rd;
		int curpos = 0;

		while (InternetReadFile(_hHttpOpenRequest, pBuff, rdsize, &rd)) {
			if (rd <= 0) break;
			curpos += rd;
			BuffQueue.AddToEnd(pBuff);
			pBuff = new BYTE[rdsize];
		}
		delete[] pBuff;

		_ReceivedData.Resize(curpos + 1);
		pBuff = BuffQueue.GetFromFront();
		while (pBuff) {
			if (curpos >= rdsize) {
				rd = rdsize;
				curpos -= rdsize;
			} else {
				rd = curpos;
			}
			_ReceivedData.Write(pBuff, 0, rd);
			delete[] pBuff;
		}
		_ReceivedData << '\0';

		return _ReceivedData;
	}

	TCHAR* HttpClient::GetHeaderLine(TCHAR *s)
	{
		//find a line in the headers that contains s, and return a pointer to the line...
		if (_Headers == NULL) return NULL;
		TCHAR *ts = (TCHAR*)_Headers.GetPtr();
		if (_tcsustr(ts, s) != NULL) return ts;
		while (1)
		{
			if (*ts == '\0' && ts[1] == '\0') break;
			if (*ts == '\0') {
				ts++;
				if (_tcsustr(ts, s) != NULL) return ts;
			}
			else ts++;
		}
		return NULL;
	}

	int HttpClient::GetPageStatusCode()
	{
		//get the correct header line
		TCHAR *s = GetHeaderLine(_T("http"));
		if (s == NULL) return 0; //no headers
		//find the 3 digit code...
		if (_tcslen(s) < 3) return 0; //some error,  the string is too short...
		while (!(isdigit(s[0]) && isdigit(s[1]) && isdigit(s[2]))) {
			if (s[3] == '\0') return 0; //we have reached the end of the string, without finding the number...
			s++;
		}
		//make a copy of s, and return the code
		TCHAR *code = _tcsdup(s);
		code[3] = '\0'; //remove all text after the 3 digit response code
		int result = _ttoi(code);
		free(code);
		return result;
	}
	
} /* namespace Net */	
} /* namespace System */

#pragma warning(default:4005)

#endif
