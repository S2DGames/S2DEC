#include "Box2D/Collision/Shapes/b2PolygonShape.h"
#include "Box2D/Dynamics/b2Body.h"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/RenderTarget.hpp"
#include "Game.h"
#include "Util.h"

//Note that this is not a Component because a Snake has multiple Segements and this engine only
//allows one of each type of Component to be present within an Entity.
class Segment{
private:
	Game* game{nullptr};
	Segment* leadingSegment{nullptr};
	b2Body* body{nullptr};
	b2BodyDef bodyDef{};
	b2PolygonShape shape{};
	b2Fixture* fixture{nullptr};
	sf::RectangleShape image;

	sf::Keyboard::Key controls[4];
	sf::Keyboard::Key queuedDirection{sf::Keyboard::Key::S};
	sf::Keyboard::Key currentDirection{sf::Keyboard::Key::S};
	sf::Keyboard::Key previousDirection{sf::Keyboard::Key::S};
	b2Vec2 previousPosition{0.0f, 0.0f};

	float speed = 12.0f;

	void* component{nullptr};

	void move(b2Vec2 position){
		game->DestroyBody(body);
		bodyDef.position = position;
		init();
	}

public:
	//Constructor for the head of a snake
	//The head has no leading segment and the movement is in response to key presses
	Segment(Game* game, sf::Keyboard::Key controls[], void* component) : game(game), component(component){
		bodyDef.type = b2_dynamicBody;
		bodyDef.position = {120.0f / SCALE, 120.0f / SCALE};
		shape.SetAsBox(6.0f / SCALE / 2.0f, 6.0f / SCALE / 2.0f);
		image.setSize({10.0f, 10.0f});
		image.setOrigin(image.getSize().x / 2.0f, image.getSize().y / 2.0f);
		image.setPosition({120.0f, 120.0f});

		for(int i = 0; i < 4; i++){
			this->controls[i] = controls[i];
		}
	}

	//Contstructor for the body of a snake
	//The body segments move to their leading segments previous position each frame
	//They also spawn behind the leading segment with respect to its direction.
	Segment(Game* game, Segment* previousSegment, sf::Keyboard::Key controls[], void* component) : game(game), leadingSegment(previousSegment), component(component){
		bodyDef.position = leadingSegment->getPreviousb2Position();;
		shape.SetAsBox(6.0f / SCALE / 2.0f, 6.0f / SCALE / 2.0f);
		image.setSize({10.0f, 10.0f});
		image.setOrigin(image.getSize().x / 2.0f, image.getSize().y / 2.0f);
		image.setPosition(bodyDef.position.x * SCALE, bodyDef.position.y * SCALE);
		printf("New body segment spawned\n");
	}

	//intializes the physics body of this segment
	void init(){
		body = game->CreateBody(&bodyDef);
		body->SetFixedRotation(true);
		body->SetUserData(component);
		fixture = body->CreateFixture(&shape, 1.0f);
		fixture->SetFriction(0.0f);
		fixture->SetRestitution(1.0f);
		fixture->SetSensor(true);
	}

	//captures input for this segment
	//This should only be used by the head of the snake
	//This function is called every frame to keep track of the most recent key pressed
	void captureInput(){
		if(game->getKeyState(controls[0]) == KEY_PRESSED){
			queuedDirection = controls[0];
		}

		if(game->getKeyState(controls[1]) == KEY_PRESSED){
			queuedDirection = controls[1];
		}

		if(game->getKeyState(controls[2]) == KEY_PRESSED){
			queuedDirection = controls[2];
		}

		if(game->getKeyState(controls[3]) == KEY_PRESSED){
			queuedDirection = controls[3];
		}
	}

	//updates a segments position
	//this function is called every frame at most.
	//For better effect, it should be called once every 30 frames.
	void update(float frameTime){
		previousPosition = getb2Position();
		if(leadingSegment != nullptr){
			move(leadingSegment->getPreviousb2Position());
		}else{
			currentDirection = queuedDirection;
			if(controls[0] == currentDirection){
				move({getb2Position().x, getb2Position().y - (speed / SCALE)});
			}else if(controls[1] == currentDirection){
				move({getb2Position().x, getb2Position().y + (speed / SCALE)});
			}else if(controls[2] == currentDirection){
				move({getb2Position().x - (speed / SCALE), getb2Position().y});
			}else if(controls[3] == currentDirection){
				move({getb2Position().x + (speed / SCALE), getb2Position().y});
			}
		}

		//update the position of the sf::RectangleShape to macth the position of the physics body
		image.setPosition(getPosition());
	}

	sf::Vector2f getPosition(){
		return {body->GetPosition().x * SCALE, body->GetPosition().y * SCALE};
	}

	sf::Keyboard::Key getCurrentDirection(){
		return currentDirection;
	}

	b2Vec2 getb2Position(){
		return body->GetPosition();
	}

	b2Vec2 getPreviousb2Position(){
		return previousPosition;
	}

	b2Body* getBody(){
		return body;
	}

	void draw(sf::RenderTarget& target){
		target.draw(image);
#ifdef _DEBUG
#ifndef IGNORE_DEBUG
		sf::RectangleShape outline;
		outline.setFillColor(sf::Color::Transparent);
		outline.setOutlineColor(sf::Color::Red);
		outline.setOutlineThickness(1.0f);
		outline.setSize({10.0f, 10.0f});
		outline.setOrigin(outline.getSize().x / 2.0f, outline.getSize().y / 2.0f);
		outline.setPosition({body->GetPosition().x * SCALE, body->GetPosition().y * SCALE});
		target.draw(outline);
#endif
#endif
	}
};