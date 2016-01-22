#pragma once

#include "SFML/Graphics/RenderTarget.hpp"
#include "Box2D/Collision/Shapes/b2PolygonShape.h"
#include "Component.h"
#include "Game.h"
#include "Util.h"
#include "sf_b2.h"
#include "AI.h"
#include "Dstar.h"

using namespace S2D;

struct RayCollision{
	b2Fixture* fixture;
	b2Vec2 point;
	b2Vec2 normal;

	bool collision = false;

	RayCollision(){

	}

	RayCollision(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float32 fraction){
		this->fixture = fixture;
		this->point.x = point.x;
		this->point.y = point.y;
		this->normal.x = normal.x;
		this->normal.y = normal.y;
	}
};

class Sim : public Component, public NPC, public b2RayCastCallback{
private:
	sf::Sprite image;
	sf::Texture texture;

	b2Body* body{nullptr};
	b2BodyDef bodyDef;
	b2PolygonShape shape;
	b2Fixture* fixture{nullptr};

	sf::RectangleShape ray;
	sf::RectangleShape dest;

	RayCollision mostRecentRayCollision;

	Dstar* dstar;
	list<state> path;

	float viewRange = 100.0;

	bool NO_PREVIOUS_DESTINATION = true;
	bool rayCollision = false;
	b2Vec2 rayPoint;

public:
	Sim(string filename, b2Vec2 position){
		texture.loadFromFile(filename);
		image.setTexture(texture);
		image.setOrigin((texture.getSize().x) / 2.0f, (texture.getSize().y) / 2.0f);
		bodyDef.position = position;

		ray.setSize({0.5f, 1.0f});
		ray.setFillColor(sf::Color::Green);
		dest.setSize({3.0f, 3.0f});
		dest.setOrigin(dest.getSize().x / 2.0f, dest.getSize().y / 2.0f);
		dest.setFillColor(sf::Color::Blue);

		dstar = new Dstar();

	}

	/**
	* Called when this component is added to an Entity.
	*/
	void init() override{
		bodyDef.type = b2_dynamicBody;
		shape.SetAsBox(sfTob2(texture.getSize().x / 2.0f), sfTob2(texture.getSize().y / 2.0f));
		body = game->CreateBody(&bodyDef);
		body->SetUserData(this);
		body->SetFixedRotation(true);
		fixture = body->CreateFixture(&shape, 1.0f);
		fixture->SetFriction(0.0f);
		fixture->SetRestitution(1.0f);
		movesfTob2(image, body);
		movesfTob2(ray, body);
	}

	/**
	* Called when the Game starts.
	*/
	void onStart() override{
		//unique_ptr<AITask> task{new AITaskMoveToPoint(sf::Vector2f{0, 150})};
		//owner->getComponent<AI>().addTask(move(task));
		owner->getComponent<AI>().addTask<AITaskMoveToPoint>(-1, sf::Vector2f{0, 150});
		sf::Vector2f currentPos = b2Tosf(body->GetPosition());
		sf::Vector2i currentIntPos = {(currentPos.x >= 0) ? (int)(currentPos.x + 0.5) : (int)(currentPos.x - 0.5), (currentPos.y >= 0) ? (int)(currentPos.y + 0.5) : (int)(currentPos.y - 0.5)};
		dstar->init(currentIntPos.x, currentIntPos.y, currentIntPos.x, currentIntPos.y);
	}

	bool moveTowardsPoint_Direct(sf::Vector2f destination) override {
		dest.setPosition(destination);
		sf::Vector2f currentPosition = b2Tosf(body->GetPosition());
		sf::Vector2f rayBounds = {destination.x - currentPosition.x, destination.y - currentPosition.y};
		float h = sqrt((rayBounds.x * rayBounds.x) + (rayBounds.y * rayBounds.y));
		ray.setSize({h, ray.getSize().y});
		float angle = 0;
		float rayAngle = atan(rayBounds.x / rayBounds.y);
		if(rayBounds.x < 0 && rayBounds.y < 0){
			angle = 180;
			angle += (90 - abs(rayAngle) * RADTODEG);
		} else if(rayBounds.x < 0){
			angle = 90;
			angle += abs(rayAngle) * RADTODEG;
		} else if(rayBounds.y < 0){
			angle = 270;
			angle += abs(rayAngle) * RADTODEG;
		} else{
			angle = 0;
			angle = (90 - abs(rayAngle) * RADTODEG);
		}
		
		ray.setRotation(angle);

		b2Vec2 bDestination = sfTob2(destination);
		b2Vec2 velocity = bDestination - body->GetPosition();
		velocity.Normalize();
		b2AABB aabb;
		aabb.lowerBound = b2Vec2(FLT_MAX, FLT_MAX);
		aabb.upperBound = b2Vec2(-FLT_MAX, -FLT_MAX);
		b2Fixture* fixture = body->GetFixtureList();
		for(b2Fixture* fixture = body->GetFixtureList(); fixture; fixture = fixture->GetNext())
		{
			aabb.Combine(aabb, fixture->GetAABB(0));
		}
		b2Vec2 size = {aabb.upperBound.x - aabb.lowerBound.x, aabb.upperBound.y - aabb.lowerBound.y};
		if(bDestination.x >= aabb.lowerBound.x && bDestination.x <= aabb.upperBound.x){
			if(bDestination.y >= aabb.lowerBound.y && bDestination.y <= aabb.upperBound.y){
				body->SetLinearVelocity({0.0f, 0.0f});
				return true;
			}
		}

		body->SetLinearVelocity(velocity);
		return false;
	}

	float32 ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float32 fraction){
		RayCollision mostRecent(fixture, point, normal, fraction);
		mostRecentRayCollision = mostRecent;
		mostRecentRayCollision.collision = true;
		rayCollision = true;
		rayPoint.x = point.x;
		rayPoint.y = point.y;
		return fraction;
	}

	sf::Vector2i previousDestination;

	bool recalcPath = false;
	bool moveTowardsPoint(sf::Vector2f& destination) override{

		sf::Vector2f currentPosition = b2Tosf(body->GetPosition());
		dstar->updateStart((currentPosition.x >= 0) ? (int)(currentPosition.x + 0.5) : (int)(currentPosition.x - 0.5), (currentPosition.y >= 0) ? (int)(currentPosition.y + 0.5) : (int)(currentPosition.y - 0.5));

		if(!NO_PREVIOUS_DESTINATION){
			sf::Vector2i iDestination = {(destination.x >= 0) ? (int)(destination.x + 0.5) : (int)(destination.x - 0.5), (destination.y >= 0) ? (int)(destination.y + 0.5) : (int)(destination.y - 0.5)};
			if(previousDestination != iDestination){
				dstar->updateGoal(iDestination.x, iDestination.y);
				recalcPath = true;
			}
			previousDestination = iDestination;
		}

		b2RayCastInput rcInput;
		rcInput.p1 = body->GetPosition();
		rcInput.p2 = sfTob2(destination);
		rcInput.maxFraction = 1.0f;

		//check if there is something in this guys path
		game->RayCast(this, body->GetPosition(), sfTob2(destination));
		if(mostRecentRayCollision.collision){
			//check the distance to the point on the ray
			sf::Vector2f point = b2Tosf(rayPoint);
			float hyp = hypot(currentPosition.x - point.x, currentPosition.y - point.y);
			if(hyp < viewRange){
				//mark the point an obstacle in dstar
				dstar->updateCell((point.x >= 0) ? (int)(point.x + 0.5) : (int)(point.x - 0.5), (point.y >= 0) ? (int)(point.y + 0.5) : (int)(point.y - 0.5), -1);
				recalcPath = true;
			}
			mostRecentRayCollision.collision = false;
		}

		//recalculate path if we need to
		if(recalcPath){
			dstar->replan();
			path = dstar->getPath();
			sf::Vector2f newDestination = {(float)path.begin()++->x, (float)path.begin()++->y};
			//owner->getComponent<AI>().addTask(move(unique_ptr<AITask>(new AITaskMoveToPoint(newDestination))));
			NO_PREVIOUS_DESTINATION = false;
		}

		//update path line
		dest.setPosition(destination);
		sf::Vector2f rayBounds = {destination.x - currentPosition.x, destination.y - currentPosition.y};
		float h = sqrt((rayBounds.x * rayBounds.x) + (rayBounds.y * rayBounds.y));
		ray.setSize({h, ray.getSize().y});
		float angle = 0;
		float rayAngle = atan(rayBounds.x / rayBounds.y);
		if(rayBounds.x < 0 && rayBounds.y < 0){
			angle = 180;
			angle += (90 - abs(rayAngle) * RADTODEG);
		} else if(rayBounds.x < 0){
			angle = 90;
			angle += abs(rayAngle) * RADTODEG;
		} else if(rayBounds.y < 0){
			angle = 270;
			angle += abs(rayAngle) * RADTODEG;
		} else{
			angle = 0;
			angle = (90 - abs(rayAngle) * RADTODEG);
		}

		ray.setRotation(angle);

		b2Vec2 bDestination = sfTob2(destination);
		b2Vec2 velocity = bDestination - body->GetPosition();
		velocity.Normalize();
		b2AABB aabb;
		aabb.lowerBound = b2Vec2(FLT_MAX, FLT_MAX);
		aabb.upperBound = b2Vec2(-FLT_MAX, -FLT_MAX);
		b2Fixture* fixture = body->GetFixtureList();
		for(b2Fixture* fixture = body->GetFixtureList(); fixture; fixture = fixture->GetNext())
		{
			aabb.Combine(aabb, fixture->GetAABB(0));
		}
		b2Vec2 size = {aabb.upperBound.x - aabb.lowerBound.x, aabb.upperBound.y - aabb.lowerBound.y};
		if(bDestination.x >= aabb.lowerBound.x && bDestination.x <= aabb.upperBound.x){
			if(bDestination.y >= aabb.lowerBound.y && bDestination.y <= aabb.upperBound.y){
				body->SetLinearVelocity({0.0f, 0.0f});
				//remove the point from the path
				return true;
			}
		}
		body->SetLinearVelocity(velocity);
		return false;
	}

	bool moveTowardsArea(sf::FloatRect destination) override{
		return false;
	}

	/**
	* Called once every frame.
	*/
	void update(float frameTime) override{
		//body->SetLinearVelocity({1, 0});
		if(!owner->getComponent<AI>().hasTasks()){
			unique_ptr<AITask> task4{new AITaskMoveToPoint(game->getRandomPointInView())};
			//owner->getComponent<AI>().addTask(move(task4));
		}
		movesfTob2(image, body);
		movesfTob2(ray, body);
	}

	/**
	* Called once every frame.
	*/
	void draw(sf::RenderTarget& target) override{
		target.draw(image);
		target.draw(dest);
		target.draw(ray);
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