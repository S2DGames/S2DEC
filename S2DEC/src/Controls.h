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
#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>

namespace S2D{

	/*!
	* Possible return values when updating controls.
	*/
	enum ReturnVal{
		CONTINUE	/*!< Nothing important happened when checking the input. */,
		CLOSE		/*!< Some input was entered to close the game. */
	};

	/*!
	* Possible values for a key state or button state. These values make it very easy for you to
	* tell if the key is being held. You will also be able to tell exactly when a key is pressed or
	* released.
	*/
	enum KeyState{
		NOT_PRESSED  /*!< The key has not been pressed for at least 2 frames. */,
		KEY_PRESSED  /*!< The key was just pressed. */,
		KEY_HELD	 /*!< The key has been pressed for at least 2 frames. */,
		KEY_RELEASED /*!< The key was just released. */,
		NO_KEY		 /*!< Used by EventManager for mouse over events */
	};

	/*!
	* Enumeration of mouse buttons.
	*/
	enum MouseButton{
		LEFT	/*!< The left mouse button. */,
		RIGHT	/*!< The right mouse button. */
	};

	/*!
	* The maximum number of keys this class tracks.
	*/
	const int NUM_KEYS = 128;

	/*!
	* The maximum number of mouse buttons this class tracks.
	*/
	const int NUM_MOUSE_BUTTONS = 5;

	/*!
	* \class Controls
	* \brief Keeps track of the states of keyboard keys and mouse buttons.
	*
	* This class keeps track of all the states of keys and buttons. Each key or button
	* has an enum KeyState assigned to it that is the current state of that key. The KeyState
	* for each key is updated every frame by polling events from the SFML window.
	*/
	class Controls{
	private:

		/*!
		* The window that will be polled for events.
		*/
		sf::RenderWindow* window;

		/*!
		* The array of KeyStates for each key from 0 to NUM_KEYS.
		*/
		KeyState keyStates[NUM_KEYS];

		/*!
		* The array of previous KeyStates for each key.
		*/
		KeyState prevKeyStates[NUM_KEYS];

		/*!
		* The array of KeyStates for each mouse button.
		*/
		KeyState mouseStates[NUM_MOUSE_BUTTONS];

		/*!
		* The array of previous KeyStates for each mouse button.
		*/
		KeyState prevMouseStates[NUM_MOUSE_BUTTONS];

		/*!
		* The current position of the mouse.
		*/
		sf::Vector2i mousePos;

		/*!
		* The previous position of the mouse.
		*/
		sf::Vector2i prevMousePos;

		/*!
		* DOXYGEN_SHOULD_SKIP_THIS
		*/
		int keyPressed(sf::Event::KeyEvent key);

		/*!
		* DOXYGEN_SHOULD_SKIP_THIS
		*/
		int keyReleased(sf::Event::KeyEvent key);

		/*!
		* DOXYGEN_SHOULD_SKIP_THIS
		*/
		void buttonPressed(sf::Event::MouseButtonEvent mouseButton);

		/*!
		* DOXYGEN_SHOULD_SKIP_THIS
		*/
		void buttonReleased(sf::Event::MouseButtonEvent mouseButton);

		/*!
		* DOXYGEN_SHOULD_SKIP_THIS
		*/
		int eventHandler(sf::Event event);

		/*!
		* DOXYGEN_SHOULD_SKIP_THIS
		*/
		void updateMousePos(sf::Vector2i mousePos);

	public:

		/*!
		* Constructor
		* \param window The window that will be polled.
		*/
		Controls(sf::RenderWindow* window);

		void setWindow(sf::RenderWindow* window);

		/*!
		* Updates the key states of all the keys and mouse buttons and the position of the mouse.
		* This is called once every frame.
		* \return NONE If nothing important happened.
		* \return CLOSE If input was entered to close the window i.e. Clicking the x or pressing escape.
		*/
		int updateControls();

		/*!
		* Gets the current state of a specific key. You can use any key in sf::Keyboard::"key letter"
		* as long as the value is less than NUM_KEYS. Does not check if you are requesting a key beyond
		* NUM_KEYS.
		* \return KeyState The current KeyState of the requested key.
		* \param key The requested key.
		*/
		KeyState getKeyState(int key);

		/*!
		* Gets the previous state of a specific key. You can use any key in sf::Keyboard::"key letter"
		* as long as the value is less than NUM_KEYS. Does not check if you are requesting a key beyond
		* NUM_KEYS.
		* \return KeyState The previous KeyState of the requested key.
		* \param key The requested key.
		*/
		KeyState getPrevKeyState(int key);

		/*!
		* Gets the current state of a specific mouse button. Does not check if you are requesting a button beyond
		* NUM_MOUSE_BUTTONS.
		* \return KeyState The current KeyState of the requested button.
		* \param button The requested button.
		*/
		KeyState getMouseState(sf::Mouse::Button button);

		/*!
		* Gets the previous state of a specific mouse button. Does not check if you are requesting a button beyond
		* NUM_MOUSE_BUTTONS.
		* \return KeyState The previous KeyState of the requested button.
		* \param button The requested button.
		*/
		KeyState getPrevMouseState(sf::Mouse::Button button);

		/*!
		* Gets the current position of the mouse in the window.
		* \return The mouse position in the window.
		*/
		sf::Vector2i getMousePos();

		/*!
		* Gets the previous position of the mouse in the window.
		* \return The previous mouse position in the window.
		*/
		sf::Vector2i getPrevMousePos();

		void setKey(sf::Keyboard::Key, KeyState);

	};

}