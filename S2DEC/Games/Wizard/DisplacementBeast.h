#include "Enemy.h"

using namespace S2D;

class DisplacementBeast : public Enemy {
private:
	std::uniform_int_distribution<int> randomInt{ 0,2500 };
public:
	DisplacementBeast(sf::Vector2f position, sf::Vector2f endPosition, void* spawner) : Enemy(position, endPosition, spawner) {

	}


	void update(float frameTime) override {
		Enemy::update(frameTime);
		if (game->getRandomInt(randomInt) == 1) {
			teleport();
		}
	}

	void draw(sf::RenderTarget& target) override {
		Enemy::draw(target);
	}

	void teleport() {
		game->DestroyBody(body);
		image.setFillColor(sf::Color::Green);

		image.setPosition(game->getRandomInt(xDist), game->getRandomInt(yDist));
		bodyDef.position = sfTob2(image.getPosition());

		body = game->CreateBody(&bodyDef);
		body->SetUserData(this);
		body->SetFixedRotation(true);
		fixture = body->CreateFixture(&shape, 1.0f);
		fixture->SetFriction(0.0f);
		fixture->SetRestitution(1.0f);
		fixture->SetSensor(true);

		movesfTob2(image, body);

		float xDistance = sfTob2(endPosition.x - image.getPosition().x);
		float yDistance = sfTob2(endPosition.y - image.getPosition().y);
		float hDistance = sqrt(pow(xDistance, 2.0f) + pow(yDistance, 2.0f));
		float speed = 1.5f;
		float step = speed / hDistance;
		b2Vec2 velocity = { step * xDistance, step * yDistance };

		xDist = std::uniform_int_distribution<int>(0, game->getSize().x);
		yDist = std::uniform_int_distribution<int>(0, game->getSize().y);

		body->SetLinearVelocity(velocity);
	}
};