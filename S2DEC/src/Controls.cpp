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
#include "Controls.h"

using namespace S2D;

Controls::Controls(sf::RenderWindow* window) : window(window){
	for(int i = 0; i < NUM_KEYS; i++){
		
		keyStates[i] = NOT_PRESSED;
		prevKeyStates[i] = NOT_PRESSED;
	}

	for(int i = 0; i < NUM_MOUSE_BUTTONS; i++){
		mouseStates[i] = NOT_PRESSED;
		prevMouseStates[i] = NOT_PRESSED;
	}

	mousePos = sf::Vector2i(0, 0);
	prevMousePos = sf::Vector2i(0, 0);
}

void Controls::setWindow(sf::RenderWindow* window){
	this->window = window;
}

int Controls::keyPressed(sf::Event::KeyEvent key){
	if(key.code >= 0){
		prevKeyStates[key.code] = keyStates[key.code];
		if(keyStates[key.code] == KEY_HELD){
			return key.code;
		} else if(keyStates[key.code] == KEY_PRESSED){
			keyStates[key.code] = KEY_HELD;
		} else{
			keyStates[key.code] = KEY_PRESSED;
		}
		return key.code;
	} else{
		//TODO: Manage key presses that are marked as UKNOWN(-1) by SFML
		//ex. Caps Lock
		return -2;
	}
}

int Controls::keyReleased(sf::Event::KeyEvent key){
	if(key.code >= 0){
		prevKeyStates[key.code] = keyStates[key.code];
		if(keyStates[key.code] == KEY_PRESSED || keyStates[key.code] == KEY_HELD){
			keyStates[key.code] = KEY_RELEASED;
		} else{
			keyStates[key.code] = NOT_PRESSED;
		}
		return key.code;
	} else{
		//TODO: Manage key presses that are marked as UKNOWN(-1) by SFML
		//ex. Caps Lock
		return -2;
	}
}

void Controls::buttonPressed(sf::Event::MouseButtonEvent mouseButton){
	if(mouseButton.button == sf::Mouse::Left){
		prevMouseStates[LEFT] = mouseStates[LEFT];
		mouseStates[LEFT] = KEY_PRESSED;
	}else if(mouseButton.button == sf::Mouse::Right){
		prevMouseStates[RIGHT] = mouseStates[RIGHT];
		mouseStates[RIGHT] = KEY_PRESSED;
	}
}

void Controls::buttonReleased(sf::Event::MouseButtonEvent mouseButton){
	if(mouseButton.button == sf::Mouse::Left){
		prevMouseStates[LEFT] = mouseStates[LEFT];
		mouseStates[LEFT] = KEY_RELEASED;
	}else if(mouseButton.button == sf::Mouse::Right){
		prevMouseStates[RIGHT] = mouseStates[RIGHT];
		mouseStates[RIGHT] = KEY_RELEASED;
	}
}

void Controls::updateMousePos(sf::Vector2i mousePos){
	prevMousePos = this->mousePos;
	this->mousePos = mousePos;
}

int Controls::eventHandler(sf::Event event){
	switch(event.type){
	case sf::Event::KeyPressed:
		if(keyPressed(event.key) == sf::Keyboard::Escape){
			return -1;
		}
		return sf::Event::KeyPressed;
	case sf::Event::KeyReleased:
		keyReleased(event.key);
		return sf::Event::KeyReleased;
	case sf::Event::MouseButtonPressed:
		this->buttonPressed(event.mouseButton);
		return sf::Event::MouseButtonPressed;
	case sf::Event::MouseButtonReleased:
		this->buttonReleased(event.mouseButton);
		return sf::Event::MouseButtonReleased;
	}
	
	if(event.type == sf::Event::Closed){
		return -1;
	}

	return event.type;
}

int Controls::updateControls(){
	sf::Event event;
	bool keyEventOccured = false;
	bool mouseButtonEventOccured = false;
	int eventCode;
	while(window->pollEvent(event)){
		eventCode = eventHandler(event);

		if(eventCode == -1){
			return CLOSE;
		}

		if(eventCode == sf::Event::KeyPressed || eventCode == sf::Event::KeyReleased){
			keyEventOccured = true;
		}

		if(eventCode == sf::Event::MouseButtonPressed || eventCode == sf::Event::MouseButtonReleased){
			mouseButtonEventOccured = true;
		}
	}

	if(!keyEventOccured){
		for(int i = 0; i < NUM_KEYS; i++){
			if(keyStates[i] == KEY_PRESSED){
				prevKeyStates[i] = keyStates[i];
				keyStates[i] = KEY_HELD;
			}else if(keyStates[i] == KEY_RELEASED){
				prevKeyStates[i] = keyStates[i];
				keyStates[i] = NOT_PRESSED;
			}
		}
	}

	if(!mouseButtonEventOccured){
		for(int i = 0; i < NUM_MOUSE_BUTTONS; i++){
			if(mouseStates[i] == KEY_PRESSED){
				prevMouseStates[i] = mouseStates[i];
				mouseStates[i] = KEY_HELD;
			}else if(mouseStates[i] == KEY_RELEASED){
				prevMouseStates[i] = mouseStates[i];
				mouseStates[i] = NOT_PRESSED;
			}
		}
	}

	updateMousePos(sf::Mouse::getPosition(*window));

	return CONTINUE;
}

KeyState Controls::getKeyState(int key){
	return keyStates[key];
}

KeyState Controls::getPrevKeyState(int key){
	return prevKeyStates[key];
}

KeyState Controls::getMouseState(sf::Mouse::Button button){
	return mouseStates[button];
}

KeyState Controls::getPrevMouseState(sf::Mouse::Button button){
	return prevMouseStates[button];
}

sf::Vector2i Controls::getMousePos(){
	return mousePos;
}

sf::Vector2i Controls::getPrevMousePos(){
	return prevMousePos;
}

void Controls::setKey(sf::Keyboard::Key key, KeyState keyState){
	prevKeyStates[key] = keyStates[key];
	keyStates[key] = keyState;
}