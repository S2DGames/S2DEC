#include "Pong.h"

float topOffset = 60.0f;
float borderOffset = 12.5f;

void loadPong(Game* game){
	//Create an entity that will manage the left paddle
	Entity& leftPaddle = game->createEntity("Left Paddle");
	//Add a paddle component to this entity passing in the position and controls
	Paddle& l = leftPaddle.addComponent<Paddle>(sf::Vector2f{2.0f * borderOffset, topOffset + (game->getSize().y / 2.0f)}, sf::Vector2f{25.0f, 150.0f}, sf::Keyboard::W, sf::Keyboard::S);

	//Create an entity that will manage the right paddle
	Entity& rightPaddle = game->createEntity("Right Paddle");
	//Add a paddle component to this entity passing in the position and controls
	Paddle& r = rightPaddle.addComponent<Paddle>(sf::Vector2f{game->getSize().x - (2.0f * borderOffset), topOffset + (game->getSize().y / 2.0f)}, sf::Vector2f{25.0f, 150.0f}, sf::Keyboard::Up, sf::Keyboard::Down);

	//Create an entity that will manage the score
	Entity& score = game->createEntity("Score");
	//Add a score component to this entity passing in the positions where each score will display
	Score& scoreComponent = score.addComponent<Score>(sf::Vector2f{50.0f, 10.0f}, sf::Vector2f{game->getSize().x - 70.0f, 10.0f});

	Entity& middle = game->createEntity("Middle Line");
	middle.addComponent<Middle>(sf::Vector2f{game->getSize().x / 2.0f, 60 + (game->getSize().y / 2.0f)}, sf::Vector2f{10.0f, game->getSize().y - 120.0f});

	Entity& boundaries = game->createEntity("Bounds");
	Boundaries& bounds = boundaries.addComponent<Boundaries>();
	bounds.addVertex({12.5f, 120.0f});
	bounds.addVertex(b2Vec2{game->getSize().x - 12.5f, 120.0f});
	bounds.addVertex(b2Vec2{game->getSize().x - 12.5f, game->getSize().y - 1.0f});
	bounds.addVertex(b2Vec2{12.5f, game->getSize().y - 1.0f});
	bounds.addVertex(b2Vec2{12.5f, 120.0f});

	Entity& ball = game->createEntity("Ball 1");
	ball.addComponent<Ball>(sf::Vector2f{game->getSize().x / 2.0f, 60 + (game->getSize().y / 2.0f)}, &scoreComponent, &l, &r);

	//Entity& ball2 = game->createEntity("Ball 2");
	//ball2.addComponent<Ball>(sf::Vector2f{game->getSize().x / 2.0f, 50 + (game->getSize().y / 2.0f)}, &scoreComponent, &l, &r);

	//Entity& ball3 = game->createEntity("Ball 3");
	//ball3.addComponent<Ball>(sf::Vector2f{game->getSize().x / 2.0f, 70 + (game->getSize().y / 2.0f)}, &scoreComponent, &l, &r);


}