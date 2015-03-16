#pragma once

#include <vector>
#include "Component.h"
#include "Position.h"
#include "Drawable.h"
using std::vector;

namespace S2D{
	class ComponentMaintainer{
	private:
		Position* highestPriorityPosition;
		vector<Component*> positionComponents;
		vector<Component*> updateableComponent;
		vector<Component*> visibleComponents;
		vector<Component*> controllableComponents;

		void addPositionSubComponent(Component* component){
			Position* position = dynamic_cast<Position*>(component);
			int priority = position->getPriority();
			if(highestPriorityPosition == nullptr){
				highestPriorityPosition = position;
			}else{
				if(priority > highestPriorityPosition->getPriority()){
					highestPriorityPosition = position;
				}
			}
			positionComponents.push_back(component);
		}

	public:
		ComponentMaintainer(){
			highestPriorityPosition = nullptr;
		}

		bool addComponent(Component* component){
			if(component == nullptr){
				return false;
			}
			if(component->hasPosition()){
				addPositionSubComponent(component);
			}
			if(component->hasImage()){
				visibleComponents.push_back(component);
			}
			return true;
		}
	};

}