#pragma once

#include <string>
#include <vector>
#include "Box2D/Dynamics/Contacts/b2Contact.h"
#include "Physics.h"
#include "ComponentMaintainer.h"

using std::string;
using std::vector;

namespace S2D{

	class Physics;

	static int currentId;

	class Entity : protected ComponentMaintainer{
	private:
		int id;
		string name;

	public:
		Entity(string name);
		virtual ~Entity();
		const int getId();
		const string getName();
		bool addComponent(Component* component);
		virtual bool update();
		/*!
		 * This function is called by box2d when a collision occurs with a physics component in this entity.
		 */
		virtual void beginCollision(Physics* collidedComponent, b2Contact* contact);
		virtual void endCollision(Physics* collidedComponent, b2Contact* contact);
	};

}