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

#include <vector>
#include <array>
#include <iostream>
#include "SFML/System/Time.hpp"
#include "Component.h"

using std::string;
using std::vector;
using std::array;
using std::unique_ptr;
using std::bitset;
using std::move;
using std::cerr;
using std::endl;

namespace S2D{
#define MAX_COMPONENTS 64
	
	class Component;
	class EntityManager;
	
	class Entity{
		friend class EntityManager;
		friend class CompareEntityZ;
	private:
		EntityManager* owner;

		bitset<MAX_COMPONENTS> componentBitset;
		string name;
		bool alive{true};
		int z = 0;

		vector<unique_ptr<Component>> components;
		array<Component*, MAX_COMPONENTS> componentArray;
		
		//Allows components to add other components during the update.
		//New components will be added before the next update.
		bool iterating{false};
		vector<Component*> queuedComponents;

		Entity(string name, EntityManager* owner) : name(name), owner(owner){

		}

		void addQueuedComponents();

	public:
		//The next 3 functions are from Vittorio Romeo. https://www.youtube.com/watch?v=QAmtgvwHInM
		//Some modifications were made.
		template<class T>
		bool hasComponent(){
			return componentBitset[getComponentTypeID<T>()];
		}

		template<class T, typename... args>
		T& addComponent(args&&... componentArgs){
			assert(!hasComponent<T>());

			T* component = new T(forward<args>(componentArgs)...);
			size_t componentID = getComponentTypeID<T>();
			component->id = componentID;
			component->setOwner(this);
			if(!iterating){
				unique_ptr<Component> uniqueComponentPtr{component};
				components.emplace_back(move(uniqueComponentPtr));
				componentArray[componentID] = component;
				componentBitset[componentID] = true;
				component->init();
			}else{
				this->queuedComponents.emplace_back(component);
			}
			return *component;
		}

		template<class T>
		T& getComponent(){
			assert(hasComponent<T>());
			auto componentPtr(componentArray[getComponentTypeID<T>()]);
			return *static_cast<T*>(componentPtr);
		}

		void onStart();
		bool update(float frameTime);
		void draw(sf::RenderTarget& target);
		int getZ();
		void setZ(int newZ);

		const string getName();
		const bool isAlive();
		void destroy();
	};

}
