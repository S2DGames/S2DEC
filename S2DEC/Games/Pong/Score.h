#pragma once
#include "Component.h"
#include "Game.h"
#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/Text.hpp"

using namespace S2D;
using std::to_string;

enum Player{left, right};

class Score : public Component{
private:
	sf::Font font;
	sf::Text leftText;
	sf::Text rightText;

	int leftScore{0};
	int rightScore{0};
	
public:
	Score(sf::Vector2f leftStartingPosition, sf::Vector2f rightStartingPosition){
		font.loadFromFile("resources/pongFont.ttf");
		leftText.setFont(font);
		leftText.setCharacterSize(40);
		leftText.setString("0");
		leftText.setPosition(leftStartingPosition);

		rightText.setFont(font);
		rightText.setCharacterSize(40);
		rightText.setString("0");
		rightText.setPosition(rightStartingPosition);
	}

	~Score(){

	}

	void draw(sf::RenderTarget& target) override{
		target.draw(leftText);
		target.draw(rightText);
	}

	void score(Player player){
		switch(player){
		case Player::left:
			leftScore++;
			leftText.setString(to_string(leftScore));
			break;
		case Player::right:
			rightScore++;
			rightText.setString(to_string(rightScore));
			break;
		}
	}

};