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

#include <string>
#include <bitset>
#include <memory>
#include <algorithm>
#include "SFML/System/Time.hpp"
#include "SFML/Graphics/RenderTarget.hpp"
#include "Box2D/Dynamics/Contacts/b2Contact.h"
#include "Entity.h"
#include "Util.h"

using std::string;
using std::size_t;
using std::bitset;
using std::is_base_of;

namespace S2D{

	//The next two functions are from Vittorio Romeo. https://www.youtube.com/watch?v=QAmtgvwHInM
	inline size_t getComponentID() NOEXCEPT{
		static size_t lastID{0u};
		return lastID++;
	}

	template<class T>
	inline size_t getComponentTypeID() NOEXCEPT{
		static_assert(is_base_of<Component, T>::value, "T must inheret from Component");
		static size_t typeID{getComponentID()};
		return typeID;
	}

	class Entity;

	class Component{
		friend class CollisionListener;
		friend class Entity;
	private:
		size_t id;

	protected:
		Entity* owner;

		Component(){

		}

		virtual void init(){

		}

		virtual void onStart(){

		}

		virtual void update(float frameTime){

		}

		virtual void draw(sf::RenderTarget& target){

		}

		virtual void draw(sf::RenderTarget& target, sf::RenderStates& states){

		}

		virtual void beginCollision(Component* collidedComponent, b2Contact* contact){

		}

		virtual void endCollision(Component* collidedComponent, b2Contact* contact){

		}

		void setOwner(Entity* owner){
			this->owner = owner;
		}

	public:
		virtual ~Component(){

		}

		Entity* getOwner(){
			return owner;
		}
	};

}
