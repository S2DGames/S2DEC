#pragma once

#include "Entity.h"
#include "Drawable.h"
#include "Physics.h"
#include "Controls.h"
#include "ResourceManager.h"
#include "EventManager.h"
#include "CollisionListener.h"

namespace S2D{

	class Game : public sf::RenderWindow, public b2World, public Controls, public ResourceManager, public EventManager, public CollisionListener{
	private:
		/*!
		* The amount of time between each step in the box2D world.
		*/
		float32 timeStep;

		/*!
		* The number of frames that box2D will process small diminshing changes in velocity.
		*/
		int32 velocityIterations;

		/*!
		* The number of frames that box2D will process small diminishing changes in position.
		*/
		int32 positionIterations;
		bool running;
	public:
		Game(unsigned int width, unsigned int height, string name);

		void setGravity(sf::Vector2f gravity);

		int play();

	};

}