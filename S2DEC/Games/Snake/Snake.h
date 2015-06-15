#pragma once

#include "Box2D/Collision/Shapes/b2PolygonShape.h"
#include "SFML/Graphics/RectangleShape.hpp"
#include "Game.h"
#include "Component.h"
#include "Segment.h"

using namespace S2D;
using std::vector;

class Snake : public Component{
private:
	Game* game{nullptr};
	Segment head;
	vector<Segment*> segments;
	float frameCount{0.0f};
	sf::Keyboard::Key controls[4];
	int count{0};

	bool restart{false};
	bool spawn{false};
public:
	Snake(Game* game, sf::Keyboard::Key controls[]) : game(game), head(game, controls, this){
		for(int i = 0; i < 4; i++){
			this->controls[i] = controls[i];
		}
	}

	void init() override{
		head.init();
		head.getBody()->SetUserData(this);
		owner->setZ(1);

		segments.push_back(&head);
	}

	void update(float frameTime) override{
		if(restart){
			Segment** segmentArr = new Segment*[segments.size()];
			for(int i = 0; i < segments.size(); i++){
				segmentArr[i] = segments[i];
			}
			for(int i = segments.size() - 1; i > 0; i--){
				delete segmentArr[i];
			}
			delete segmentArr;
			segments.clear();
			segments.push_back(&head);
			restart = false;
		}

		if(spawn){
			Segment* s = new Segment(game, segments[segments.size() - 1], controls, this);
			s->init();
			segments.push_back(s);
			spawn = false;
		}
		count++;
		head.captureInput();
		//update the position every 30 frames
		if(count >= 15){
			for(Segment* s : segments){
				s->update(frameTime);
			}
			count = 0;
		}
	}

	void draw(sf::RenderTarget& target) override{
		head.draw(target);
		for(Segment* s : segments){
			s->draw(target);
		}
	}

	void beginCollision(Component* collidedComponent, b2Contact* contact) override{
		if(auto snake = dynamic_cast<Snake*>(collidedComponent)){
			
			restart = true;
		}else if(auto boundary = dynamic_cast<Boundaries*>(collidedComponent)){
			restart = true;
		}else{
			spawn = true;
		}
	}
};