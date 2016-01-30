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
		if (explosion.getRadius() >= 0) {
			explosion.setRadius(explosion.getRadius() - .1f);
			explosion.setOrigin(explosion.getRadius(), explosion.getRadius());
		}
		if(explosion.getRadius()<1 && explosion.getRadius() > 0) {
			this->owner->destroy();
		}

	}

	void draw(sf::RenderTarget& target) override {
		target.draw(explosion);
		Spell::draw(target);
	}

	void createExplosion() {
		explosion.setRadius(40.0f);
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