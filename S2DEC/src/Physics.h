#pragma once

#include <map>
#include "Box2D/Box2D.h"
#include "Entity.h"
#include "Component.h"
#include "Position.h"

using std::map;

namespace S2D{

	class Entity;

	class Physics : public Component, public Position{

	private:
		b2World* world;
		Entity* owner;

	protected:
		b2Body* body;
		b2BodyDef bodyDef;
		map<string, b2FixtureDef> fixtureDefs;

	public:
		Physics(Entity* entity, b2BodyDef bodyDef);
		~Physics();

		void init(b2World* world);
		const bool hasPosition();
		bool addFixture(string name, b2FixtureDef fixtureDef);
		virtual void beginCollision(Physics* physicsComponent, b2Contact* contact);
		virtual void endCollision(Physics* physicsComponent, b2Contact* contact);
	};

}