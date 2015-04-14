/*USAGE

InputEvent ie;

//key events
KeyEvent ke;
ke.key = sf::Keyboard::W;
ke.keyState = KEY_HELD;
ie.keyEvents.push_back(ke);

//mouse events
MouseEvent me;
me.button = sf::Mouse::Button::Left;
me.buttonState = KEY_HELD;
me.type = BUTTON;
ie.mouseEvents.push_back(me);

//To watch the event
Game::watchEvent(ie, std::bind(&SomeClass::FunctionToCall, this));
//"this" should be an instance of SomeClass
//This will create an event that calls SomeClass::FunctionToCall when both the w key and
//the left mouse button are held
*/

#pragma once

#include "Controls.h"
#include "Entity.h"
#include <functional>

using std::vector;
using std::function;
using std::forward;

namespace S2D{

	enum MouseEventType{ BUTTON, POINTER_IN_AREA, BUTTON_IN_AREA };

	struct KeyEvent{
		sf::Keyboard::Key key;
		KeyState keyState;

		KeyEvent(sf::Keyboard::Key key, KeyState keyState){
			this->key = key;
			this->keyState = keyState;
		}
	};

	struct MouseEvent{
		sf::Mouse::Button button;
		KeyState buttonState;
		const sf::IntRect* area;
		MouseEventType type;

		MouseEvent(){
			buttonState = NO_KEY;
		}
	};

	class InputEvent{
	private:
		vector<KeyEvent> keyEvents;
		vector<MouseEvent> mouseEvents;

	public:
		InputEvent(vector<KeyEvent> keyEvents);
		InputEvent(vector<MouseEvent> mouseEvents);
		InputEvent(vector<KeyEvent> keyEvents, vector<MouseEvent> mouseEvents);

		const vector<KeyEvent>& getKeyEvents();
		const vector<MouseEvent>& getMouseEvents();
	};

	class CallbackEvent{
	private:
		Controls* controls;
		InputEvent event;
		function<void()> functionToCall;

		bool checkKeyEvents();
		bool checkMouseEvents();
		bool checkMouseOverEvents();
		bool checkMousePressedEvents();

	public:
		CallbackEvent(Controls* controls, InputEvent event, function<void()> fn);

		void checkEvent();
	};

	class EventManager{
	private:
		Controls* controls;
		bool iterating;
		vector<CallbackEvent> callbackEvents;
		vector<CallbackEvent> queuedEvents;

	public:
		EventManager(Controls* controls);

		template<class TYPE>
		void watchEvent(InputEvent event, TYPE&& fn){
			CallbackEvent callbackEvent(controls, event, forward<TYPE>(fn));
			if(!iterating){
				callbackEvents.push_back(callbackEvent);
			}else{
				queuedEvents.push_back(callbackEvent);
			}
		}

		void checkEvents();
	};

}