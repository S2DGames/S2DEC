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

InputEvent::InputEvent(vector<KeyEvent> keyEvents) : keyEvents(keyEvents){

}

InputEvent::InputEvent(vector<MouseEvent> mouseEvents) : mouseEvents(mouseEvents){

}

InputEvent::InputEvent(vector<KeyEvent> keyEvents, vector<MouseEvent> mouseEvents) : keyEvents(keyEvents), mouseEvents(mouseEvents){

}

const vector<KeyEvent>& InputEvent::getKeyEvents(){
	return keyEvents;
}

const std::vector<MouseEvent>& InputEvent::getMouseEvents(){
	return mouseEvents;
}

CallbackEvent::CallbackEvent(Controls* controls, InputEvent event, function<void()> fn) : functionToCall(fn), event(event){
	this->controls = controls;
}

bool CallbackEvent::checkKeyPressedEvents(){
	for(auto i : event.getKeyEvents()){
		KeyState state = controls->getKeyState(i.key);
		switch(i.keyState){
		case NOT_PRESSED:
			if(state != NOT_PRESSED){
				return false;
			}
			break;
		case KEY_RELEASED:
			if(state != KEY_RELEASED){
				return false;
			}
			break;
		case KEY_PRESSED:
			if(state != KEY_PRESSED){
				return false;
			}
			break;
		case KEY_HELD:
			if(state != KEY_HELD){
				return false;
			}
			break;
		}
	}
	return true;
}

bool CallbackEvent::checkMouseEvents(){
	return (checkMousePressedEvents() && checkMouseOverEvents());
}

bool CallbackEvent::checkMouseOverEvents(){
	for(auto i : event.getMouseEvents()){
		if(i.type == POINTER_IN_AREA || i.type == BUTTON_IN_AREA){
			if(!i.area->contains(controls->getMousePos())){
				return false;
			}
		}
	}
	return true;
}

bool CallbackEvent::checkMousePressedEvents(){
	for(auto i : event.getMouseEvents()){
		KeyState state = controls->getMouseState(i.button);
		switch(i.buttonState){
		case NOT_PRESSED:
			if(state != KEY_RELEASED && state != NOT_PRESSED){
				return false;
			}
			break;
		case KEY_RELEASED:
			if(state != KEY_RELEASED){
				return false;
			}
			break;
		case KEY_PRESSED:
			if(state != KEY_PRESSED && state != KEY_HELD){
				return false;
			}
			break;
		case KEY_HELD:
			if(state != KEY_HELD){
				return false;
			}
			break;
		}
	}
	return true;
}

void CallbackEvent::checkEvent(){
	if(checkKeyPressedEvents() && checkMouseEvents()){
		functionToCall();
	}
}

EventManager::EventManager(Controls* controls) : controls(controls){
	iterating = false;
}

void EventManager::checkEvents(){
	iterating = true;
	for(auto i : callbackEvents){
		i.checkEvent();
	}
	iterating = false;
	if(queuedEvents.size() > 0){
		callbackEvents.insert(callbackEvents.end(), queuedEvents.begin(), queuedEvents.end());
		queuedEvents.clear();
	}
}