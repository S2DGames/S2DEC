#pragma once

#include "SFML/Graphics/RenderTarget.hpp"
#include "Component.h"
#include "Game.h"
#include "Util.h"
#include "Tree.h"
#include <random>

using namespace S2D;
using std::random_device;
using std::mt19937;
using std::uniform_int_distribution;

struct TreeList{
public:
	Tree& tree;
	struct TreeList* next;

	TreeList(Tree& tree) : tree(tree){

	}
};

class Background : public Component{
private:
	random_device rd;
	mt19937 mt;
	uniform_int_distribution<int> dist;

	TreeList* first;
	TreeList* last;

	int maxTreeCount = 1;
	int currentCount = 0;

	float cycle = 3.0f;//seconds
	float totalTime = 0.0f;//seconds

	FireElemental& player;

	sf::Sprite image1;
	sf::Texture texture;
	sf::Sprite image2;

public:
	Background(FireElemental& player) : player(player), mt(rd()), dist(40, 400){
		texture.loadFromFile("resources/fire\ elemental/backdrop.png");
		image1.setTexture(texture);
		image1.setOrigin(texture.getSize().x / 2.0f, texture.getSize().y / 2.0f);
		image2.setTexture(texture);
		image2.setOrigin(texture.getSize().x / 2.0f, texture.getSize().y / 2.0f);
	}

	~Background(){
		while(first != nullptr){
			TreeList* temp = first->next;
			delete(first);
			first = temp;
		}
	}

	/**
	* Called when this component is added to an Entity.
	*/
	void init() override{
		first = new TreeList(game->createEntity("tree").addComponent<Tree>(sf::Vector2f{game->getView().getCenter().x + (game->getView().getSize().x / 2.0f), game->getSize().y / 2.0f + 144}, player));
		first->next = nullptr;
		last = first;

		owner->setZ(-2);
		image1.setPosition(image1.getPosition().x, game->getView().getCenter().y);
		image2.setPosition(image2.getPosition().x + game->getSize().x, game->getView().getCenter().y);
	}

	/**
	* Called when the Game starts.
	*/
	void onStart() override{

	}

	/**
	* Called once every frame.
	*/
	//TODO: randomize tree spawn distance
	void update(float frameTime) override{
		//if the player moves right a certain distance past the last tree, spawn another
		if(player.getXPosition() - dist(mt) > last->tree.getXPosition()){
			last->next = new TreeList(game->createEntity("tree").addComponent<Tree>(sf::Vector2f{game->getView().getCenter().x + (295 / 2) + (game->getView().getSize().x / 2.0f), (game->getSize().y / 2.0f) + 144}, player));
			last = last->next;
			last->next = nullptr;
		}

		if(player.getXPosition() + dist(mt) < first->tree.getXPosition()){
			TreeList* tree = new TreeList(game->createEntity("tree").addComponent<Tree>(sf::Vector2f{game->getView().getCenter().x - (295 / 2) - (game->getView().getSize().x / 2.0f), (game->getSize().y / 2.0f) + 144}, player));
			tree->next = first;
			first = tree;
		}

		//move background
		image1.setPosition(image1.getPosition().x - (player.getVelocity().x / 100.0f) + player.getVelocity().x / 5.0f, image1.getPosition().y);
		image2.setPosition(image2.getPosition().x - (player.getVelocity().x / 100.0f) + player.getVelocity().x / 5.0f, image2.getPosition().y);

		//scroll background
		if(image1.getPosition().x < (game->getView().getCenter().x - game->getSize().x)){
			//move it to the other side
			image1.setPosition(image2.getPosition().x + (texture.getSize().x) - 1.0f, image1.getPosition().y);
		}
		if(image2.getPosition().x < (game->getView().getCenter().x - game->getSize().x)){
			//move it to the other side
			image2.setPosition(image1.getPosition().x + (texture.getSize().x) - 1.0f, image2.getPosition().y);
		}
		if(image1.getPosition().x > (game->getView().getCenter().x + game->getSize().x)){
			image1.setPosition(image2.getPosition().x - (texture.getSize().x) + 1.0f, image1.getPosition().y);
		}
		if(image2.getPosition().x > (game->getView().getCenter().x + game->getSize().x)){
			image2.setPosition(image1.getPosition().x - (texture.getSize().x) + 1.0f, image2.getPosition().y);
		}
	}

	/**
	* Called once every frame.
	*/
	void draw(sf::RenderTarget& target) override{
		target.draw(image1);
		target.draw(image2);
	}
};