#include "Spell.h"
#include "WizardUtility.h"
#include "Enemy.h"

using namespace S2D;

class Fireball : public Spell {
private:
	sf::CircleShape explosion;
	std::shared_ptr<ltbl::LightPointEmission> light;
	sf::Texture lightTexture;

public:
	Fireball(sf::Vector2f position, sf::Vector2f endPosition, void* ui): Spell(position, endPosition, SpellType::Fire ) {
		explosion.setFillColor(sf::Color::Red);
		this->ui = ui;

		lightTexture.loadFromFile("resources/LTBL2/pointLightTexture.png");
		lightTexture.setSmooth(true);
	}

	void init() override {
		Spell::init();
		light = std::make_shared<ltbl::LightPointEmission>();
		light->_emissionSprite.setTexture(lightTexture);
		light->_emissionSprite.setColor(sf::Color::White);
		//light->_emissionSprite.setPosition(shape1.getPosition().x - 30, shape1.getPosition().y - 30);
		light->_localCastCenter = sf::Vector2f(0.0f, 0.0f);
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
		explosion.setRadius(50.0f);
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