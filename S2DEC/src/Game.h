#pragma once

#include "Box2D/Dynamics/b2World.h"
#include "Entity.h"
#include "Controls.h"
#include "ResourceManager.h"
#include "EventManager.h"
#include "EntityManager.h"
#include "CollisionListener.h"

namespace S2D{

	const unsigned int FRAMERATE = 60;

	/*!
	* The number of frames that box2D will process small diminshing changes in velocity.
	*/
	const int32 VELOCITY_ITERATIONS = 9;

	/*!
	* The number of frames that box2D will process small diminishing changes in position.
	*/
	const int32 POSITION_ITERATIONS = 8;

	class Game : public sf::RenderWindow, public b2World, public Controls, public ResourceManager, public EventManager, public EntityManager, public CollisionListener{
	private:
		/*!
		* The amount of time between each step in the box2D world.
		*/
		float32 timeStep;

		/*!
		 * If the game is running, this will be true.
		 */
		bool running;

		sf::VideoMode videoMode;

		string title;

	public:
		Game(unsigned int width, unsigned int height, const string name);

		void setGravity(sf::Vector2f gravity);
		void init();
		int play();
	};

}