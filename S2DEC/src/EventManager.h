// Copyright (C) 2015 Doug Madden (dmadden772@gmail.com)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.

/*USAGE

//To watch an event
Game::watchEvent(std::bind(&ClassWithEventChecker::eventChecker,		 &classWithEventChecker),
				 std::bind(&ClassWithCallbackFunction::callbackFunction, &classWithCallbackFunction));
*/
#pragma once

#include "Entity.h"
#include <functional>
#include <map>

using std::vector;
using std::map;
using std::function;
using std::forward;

namespace S2D{

	class CallbackEvent{
		friend class EventManager;
	private:
		function<bool()> eventChecker;
		vector<function<void()>> callbacks;

		CallbackEvent(function<bool()> eventChecker, function<void()> callback);
		void checkEvent();
		void extend(function<void()> callback);
	};

	class EventManager{
	private:
		bool iterating;
		map<Component*, vector<CallbackEvent>> callbackEvents;
		map<Component*, vector<CallbackEvent>> queuedEvents;

	public:
		EventManager();

		template<class TYPE1, class TYPE2>
		const void watchEvent(TYPE1&& eventChecker, TYPE2&& callback, Component* component){
			auto mapIterator = callbackEvents.find(component);
			CallbackEvent callbackEvent(forward<TYPE1>(eventChecker), forward<TYPE2>(callback));
			if(mapIterator == callbackEvents.end()){
				if(!iterating){
					callbackEvents.insert({component, {callbackEvent}});
				}else{
					auto queuedMapIterator = queuedEvents.find(component);
					if(queuedMapIterator == queuedEvents.end()){
						queuedEvents.insert({component, {callbackEvent}});
					}else{
						queuedMapIterator->second.emplace_back(callbackEvent);
					}
				}
			}else{
				mapIterator->second.emplace_back(callbackEvent);
			}
		}

		template<class TYPE1>
		const bool extendEvent(const string existingEventID, TYPE1&& callback){
			auto event = callbackEvents.find(existingEventID);
			if(event == callbackEvents.end()){
				return false;
			}
			event->second.extend(forward<TYPE1>(callback));
			return true;
		}

		void checkEvents();
	};

}