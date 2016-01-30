#include "Spell.h"
#include "WizardUtility.h"
#include "Enemy.h"

using namespace S2D;

class WaterBlast : public Spell {
private:

public:
	WaterBlast(sf::Vector2f position, sf::Vector2f endPosition) : Spell(position, endPosition, SpellType::Water) {
		Spell::image.setSize(sf::Vector2f{ image.getSize().x,image.getSize().y * 2.5f });
		Spell::image.setOrigin((image.getSize().x) / 2.0f, (image.getSize().y) / 2.0f);
	}


	void update(float frameTime) override {
		Spell::update(frameTime);

		/*if (explosion.getRadius()<1 && explosion.getRadius() > 0) {
			this->owner->destroy();
		}*/
		

	}

	void draw(sf::RenderTarget& target) override {
		Spell::draw(target);
	}

	void beginCollision(Component* collidedComponent, b2Contact* contact) override {

	}

	void endCollision(Component* collidedComponent, b2Contact* contact) override {

	}
};