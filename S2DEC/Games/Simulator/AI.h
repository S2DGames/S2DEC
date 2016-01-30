#pragma once

#include "SFML/Graphics/RenderTarget.hpp"
#include "Box2D/Collision/Shapes/b2PolygonShape.h"
#include "Component.h"
#include "Game.h"
#include "Util.h"
#include "sf_b2.h"
#include "NPC.h"
#include <type_traits>

using namespace S2D;
using std::is_base_of;

class AITask{
	string name;

public:
	AITask(string name) : name(name){

	}

	string getName(){
		return name;
	}

	virtual bool performTask(NPC& npc) = 0;

};

class AITaskMoveToPoint : public AITask{
private:
	sf::Vector2f destination;
public:
	AITaskMoveToPoint(sf::Vector2f destination) : AITask("Move"), destination(destination){

	}

	bool performTask(NPC& npc) override{
		return npc.moveTowardsPoint(destination);
	}
};

class AITaskMoveToArea : public AITask{
private:
	sf::FloatRect destination;
public:
	AITaskMoveToArea(sf::FloatRect destination) : AITask("Move"), destination(destination){

	}

	bool performTask(NPC& npc) override{
		return npc.moveTowardsArea(destination);
	}
};

struct TaskIndexPair{
public:
	int index;
	unique_ptr<AITask> task;

	TaskIndexPair(int index, unique_ptr<AITask> task) : index(index), task(move(task)){

	}
};

class AIPlan{
private:
	NPC& npc;
	vector<unique_ptr<AITask>> tasks;
	vector<unique_ptr<AITask>> queuedTasks;
	vector<int> queuedIndecies;
	bool iterating = false;
	bool clearTasks = false;

	void addTask(unique_ptr<AITask> task, int index){
		;
	}

public:
	AIPlan(NPC& npc) : npc(npc){

	}

	template<class T, typename... Targs>
	void addTask(int index, Targs&&... args){
		bool isBase = is_base_of<AITask, T>();
		assert(isBase);
		unique_ptr<AITask> task{new T(forward<Targs>(args)...)};
		if(!iterating){
			if(index >= 0){
				tasks.insert(tasks.begin() + index, move(task));
			} else{
				tasks.emplace_back(move(task));
			}
		} else{
			queuedTasks.emplace_back(move(task));
			queuedIndecies.emplace_back(index);
		}
	}

	void removeTask(string name){

	}

	void removeAllTasks(){
		queuedTasks.clear();
		queuedIndecies.clear();
		if(iterating){
			clearTasks = true;
		} else{
			tasks.clear();
		}
	}

	void step(){
		int i = 0;
		for(auto& task : queuedTasks){
			addTask(move(task), queuedIndecies[i]);
			i++;
		}
		queuedTasks.clear();
		queuedIndecies.clear();

		if(clearTasks){
			tasks.clear();
			return;
		}

		iterating = true;
		if(tasks.size() > 0){
			if(tasks[0] != nullptr){
				if(tasks[0]->performTask(npc)){
					tasks.erase(tasks.begin());
				}
			}
		}
		iterating = false;
	}

	bool hasTasks(){
		return tasks.size() > 0 ? true : false;
	}
};

class AI : public Component, public AIPlan{
private:
	//current objective
	//current plan to acheive objective
	//current view
	//current knowledge

	
public:
	AI(NPC& npc) : AIPlan(npc){
		
	}

	/**
	* Called when this component is added to an Entity.
	*/
	void init() override{
		
	}

	/**
	* Called when the Game starts.
	*/
	void onStart() override{

	}

	/**
	* Called once every frame.
	*/
	void update(float frameTime) override{
		AIPlan::step();
	}

	/**
	* Called once every frame.
	*/
	void draw(sf::RenderTarget& target) override{

	}

	/**
	* Called if a physics body connected with this component collides with another physics body.
	* To connect a Box2d body to this component use b2Body::SetUserDate(this); inside the init or onStart function.
	* Do not delete or add physics objects in the scope of this function.
	*/
	void beginCollision(Component* collidedComponent, b2Contact* contact) override{

	}

	/**
	* Called if a physics body connected with this component collides with another physics body.
	* To connect a Box2d body to this component use b2Body::SetUserDate(this); inside the init or onStart function.
	* Do not delete or add physics objects in the scope of this function.
	*/
	void endCollision(Component* collidedComponent, b2Contact* contact) override{

	}
};