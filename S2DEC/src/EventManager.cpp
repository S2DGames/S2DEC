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
#include "EventManager.h"

using namespace S2D;


CallbackEvent::CallbackEvent(function<bool()> eventChecker, function<void()> callback) : eventChecker(eventChecker){
	callbacks.emplace_back(callback);
}

void CallbackEvent::checkEvent(){
	if(eventChecker()){
		for(auto callback : callbacks){
			callback();
		}
	}
}

void CallbackEvent::extend(function<void()> callback){
	callbacks.emplace_back(callback);
}

EventManager::EventManager(){
	iterating = false;
}

void EventManager::checkEvents(){
	if(queuedEvents.size() > 0){
		for(auto const& iter : queuedEvents){
			callbackEvents.insert({iter.first, iter.second});
		}
		queuedEvents.clear();
	}
	iterating = true;
	for(auto& iter : callbackEvents){
		for(auto& events : iter.second){
			events.checkEvent();
		}
	}
	iterating = false;
}