/*
* System.Threading.Event.h
*
* Code Status: Drafts
*  Created on: Taiwan
*      Author: player
*/


#ifndef SYSTEM_THREADING_EVENT_H_
#define SYSTEM_THREADING_EVENT_H_

#if _MSC_VER > 1000
	#pragma once
#endif

namespace System {
	namespace Threading {

		class Event
		{
		private:
			volatile bool _event; 

		public:
			Event():
				_event(false) {
			}

			virtual ~Event() {
			}

			void SetEvent() {
				_event = true;
			}
			//BOOL PulseEvent();
			void ResetEvent() {
				_event = false;
			}

			bool Wait(long millis) {
				if (millis == 0) {
					return _event;
				}

				while (_event) {

					//TimeOut
				}
				return _event;
			}
		
		};

		

	} /* namespace Threading */
} /* namespace System */

#endif /* SYSTEM_THREADING_EVENT_H_ */