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

#include "Box2D/Dynamics/b2World.h"
#include "Entity.h"
#include "Controls.h"
#include "EventManager.h"
#include "EntityManager.h"
#include "CollisionListener.h"
#include "ResourceManager.h"

namespace S2D{

	/*!
	 * An enumeration of the possibles states of the game engine.
	 */
	enum GameState{RUNNING = 0, CLOSING, PAUSED, LOADING, INITIALIZING, CLOSED};

	/*!
	 * The max frame rate that the game will run at. NOT IMPLEMENTED
	 */
	const unsigned int FRAMERATE = 60;

	/*!
	* The number of frames that box2D will process small diminshing changes in velocity.
	*/
	const int32 VELOCITY_ITERATIONS = 7;

	/*!
	* The number of frames that box2D will process small diminishing changes in position.
	*/
	const int32 POSITION_ITERATIONS = 5;

	class Game : public sf::RenderWindow, public b2World, public Controls, /*public EventManager,*/ public EntityManager, public CollisionListener/*, public ResourceManager*/{
	private:
		/*!
		* The amount of time between each step in the box2D world.
		*/
		float32 timeStep;

		/*!
		 * The current state of the engine,
		 */
		GameState state;

		/*!
		 * The video mode that will be used to create the window with SFML. Contains window width, height, and bit depth.
		 */
		sf::VideoMode videoMode;

		sf::ContextSettings settings;

		/*!
		 * The title of the window that will be created.
		 */
		string title;

	public:
		/*!
		 * Constructor
		 *
		 * \param width The width of the window that will be created.
		 * \param height The height of the window that will be created.
		 * \param name The title of the window that will be created.
		 */
		Game(unsigned int width, unsigned int height, const char* name);

		/*!
		 * Initializes a game. This must be called before calling Game::play().
		 * Creates SFML window with the specified width and height passed in the constructor.
		 */
		void init();

		void setSize(const sf::Vector2u size);

		/*!
		 * The main loop of the engine. This is where objects are udpated, input is captured,
		 * and everything is rendered each frame.
		 */
		int play();

		GameState getState();

		void endScene();

		void close();

		sf::FloatRect getCameraRect();

		static sf::Vector2u SCREEN_SIZE;
	};

}