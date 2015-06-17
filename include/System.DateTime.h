/*
* System.DateTime.h
*
* Code Status: Drafts
*  Created on: Taiwan
*      Author: player
*/

#ifndef SYSTEM_DATETIME_H_
#define SYSTEM_DATETIME_H_

#if _MSC_VER > 1000
#pragma once
#endif

#include "stdafx.h"
#include "System.AutoPtr.h"
#include <ctime>		// time

namespace System {

#pragma region Declared class

	class DateTime {
	private:
		time_t _rawtime;
		AutoPtr<tm> _pTimeinfo;

	public:
		DateTime();
		DateTime(time_t rawtime);
		DateTime(int year, int month, int day, int hour, int minute, int second);

		~DateTime();

		DateTime& Now();

		int Year();
		DateTime& Year(int year);
		int Month();
		DateTime& Month(int month);
		int Day();
		DateTime& Day(int day);
		int Hour();
		DateTime& Hour(int hour);
		int Minute();
		DateTime& Minute(int minute);
		int Second();
		DateTime& Second(int second);
		
		int DayOfWeek();
		int DayOfYear();

		operator time_t();
		operator tm();

		double operator-(DateTime t);
	};
#pragma endregion Declared class

#pragma region Definition class
#pragma endregion Definition class

		inline DateTime::DateTime() :
			_rawtime(0) {
		}

		inline DateTime::DateTime(time_t rawtime) :
			_rawtime(rawtime) {
			_pTimeinfo = localtime(&_rawtime);
		}

		inline DateTime::DateTime(int year, int month, int day, int hour, int minute, int second) {
			_rawtime = 0;
			_pTimeinfo = localtime(&_rawtime);
			_pTimeinfo->tm_year = year;
			_pTimeinfo->tm_mon = month;
			_pTimeinfo->tm_mday = day;
			_pTimeinfo->tm_hour = hour;
			_pTimeinfo->tm_min = minute;
			_pTimeinfo->tm_sec = second;
			_rawtime = mktime(_pTimeinfo);
		}

		inline DateTime::~DateTime() {
		}

		inline DateTime& DateTime::Now() {
			time(&_rawtime);  /* get current time; same as: timer = time(NULL)  */
			_pTimeinfo = localtime(&_rawtime);
			return *this;
		}

		inline int DateTime::Year() {
			if (_pTimeinfo.IsEmpty())
				_pTimeinfo = localtime(&_rawtime);
			return _pTimeinfo->tm_year;
		}

		inline DateTime& DateTime::Year(int year) {
			if (_pTimeinfo.IsEmpty())
				_pTimeinfo = localtime(&_rawtime);
			_pTimeinfo->tm_year = year;
			_rawtime = mktime(_pTimeinfo);
			return *this;
		}

		inline int DateTime::Month() {
			if (_pTimeinfo.IsEmpty())
				_pTimeinfo = localtime(&_rawtime);
			return _pTimeinfo->tm_mon;	//0~11
		}

		inline DateTime& DateTime::Month(int month) {
			if (_pTimeinfo.IsEmpty())
				_pTimeinfo = localtime(&_rawtime);
			_pTimeinfo->tm_mon = month;
			_rawtime = mktime(_pTimeinfo);
			return *this;
		}

		inline int DateTime::Day() {
			if (_pTimeinfo.IsEmpty())
				_pTimeinfo = localtime(&_rawtime);
			return _pTimeinfo->tm_mday;	//1~31
		}

		inline DateTime& DateTime::Day(int day) {
			if (_pTimeinfo.IsEmpty())
				_pTimeinfo = localtime(&_rawtime);
			_pTimeinfo->tm_mday = day;
			_rawtime = mktime(_pTimeinfo);
			return *this;
		}

		inline int DateTime::Hour() {
			if (_pTimeinfo.IsEmpty())
				_pTimeinfo = localtime(&_rawtime);
			return _pTimeinfo->tm_hour;	//0~23
		}

		inline DateTime& DateTime::Hour(int hour) {
			if (_pTimeinfo.IsEmpty())
				_pTimeinfo = localtime(&_rawtime);
			_pTimeinfo->tm_hour = hour;
			_rawtime = mktime(_pTimeinfo);
			return *this;
		}

		inline int DateTime::Minute() {
			if (_pTimeinfo.IsEmpty())
				_pTimeinfo = localtime(&_rawtime);
			return _pTimeinfo->tm_min;	//0~59
		}

		inline DateTime& DateTime::Minute(int minute) {
			if (_pTimeinfo.IsEmpty())
				_pTimeinfo = localtime(&_rawtime);
			_pTimeinfo->tm_min = minute;
			_rawtime = mktime(_pTimeinfo);
			return *this;
		}

		inline int DateTime::Second() {
			if (_pTimeinfo.IsEmpty())
				_pTimeinfo = localtime(&_rawtime);
			return _pTimeinfo->tm_sec;	//0~59
		}

		DateTime& DateTime::Second(int second) {
			if (_pTimeinfo.IsEmpty())
				_pTimeinfo = localtime(&_rawtime);
			_pTimeinfo->tm_sec = second;
			_rawtime = mktime(_pTimeinfo);
			return *this;
		}

		inline int DateTime::DayOfWeek() {
			if (_pTimeinfo.IsEmpty())
				_pTimeinfo = localtime(&_rawtime);
			return _pTimeinfo->tm_wday;	//0~6
		}

		inline int DateTime::DayOfYear() {
			if (_pTimeinfo.IsEmpty())
				_pTimeinfo = localtime(&_rawtime);
			return _pTimeinfo->tm_yday;	//0~365
		}

		inline DateTime::operator time_t() {
			return _rawtime;
		}

		inline DateTime::operator tm() {
			return *_pTimeinfo;
		}

		inline double DateTime::operator-(DateTime t) {
			return difftime(_rawtime, (time_t)t);
		}
	};
} /* namespace System */

#endif /* SYSTEM_DATETIME_H_ */
