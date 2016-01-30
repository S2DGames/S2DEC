#include "Spell.h"
#include "WizardUtility.h"
#include "Enemy.h"

using namespace S2D;

class Fireball : public Spell {
private:
	sf::CircleShape explosion;

public:
	Fireball(sf::Vector2f position, sf::Vector2f endPosition): Spell(position, endPosition, SpellType::Fire ) {

	}


	void update(float frameTime) override {
		Spell::update(frameTime);
	}

	void draw(sf::RenderTarget& target) override {
		target.draw(explosion);
		Spell::draw(target);
	}

	void createExplosion() {
		explosion.setRadius(20.0f);
		explosion.setPosition(Spell::image.getPosition());
		explosion.setOrigin(explosion.getRadius(), explosion.getRadius());
	}

	void beginCollision(Component* collidedComponent, b2Contact* contact) override {
		if (auto enemy = dynamic_cast<Enemy*>(collidedComponent)) {
			createExplosion();
		}
	}

	void endCollision(Component* collidedComponent, b2Contact* contact) override {

	}
};