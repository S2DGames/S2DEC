#include "Drawable.h"

using namespace S2D;

Drawable::Drawable(sf::Drawable& drawable, sf::Transformable& transformable) : Component("Drawable"), Position({0.0, 0.0}), Size({0.0, 0.0}), drawable(drawable), transformable(transformable), onScreen(false){

}

void Drawable::draw(sf::RenderTarget& target){
	if(onScreen){
		target.draw(drawable);
	}
}

void Drawable::draw(sf::RenderTarget& target, sf::RenderStates& states){
	if(onScreen){
		target.draw(drawable, states);
	}
}

void Drawable::updateOnScreen(sf::View& currentView){
	//view position
	sf::Vector2f viewSize(currentView.getSize());
	sf::Vector2f viewPosition(currentView.getCenter().x - (viewSize.x / 2.0f), currentView.getCenter().y - (viewSize.y / 2.0));
	sf::FloatRect viewRect(viewPosition, viewSize);
	sf::FloatRect drawableRect(getPosition(), getSize());
	onScreen = drawableRect.intersects(viewRect);
}

void Drawable::setPosition(sf::Vector2f position){
	Position::setPosition(position);
	transformable.setPosition(position);
}

void Drawable::setSize(sf::Vector2f size){
	sf::Vector2f currentScale = transformable.getScale();
	sf::Vector2f currentSize = getSize();
	sf::Vector2f unscaledCurrentSize{currentSize.x * (1.0f / currentScale.x), currentSize.y * (1.0f / currentScale.y)};
	transformable.setScale({size.x / unscaledCurrentSize.x, size.y / unscaledCurrentSize.y});
	Size::setSize(size);
}

void Drawable::setDrawable(sf::Drawable& drawable){
	this->drawable = drawable;
}

void Drawable::setTransformable(sf::Transformable& transformable){
	this->transformable = transformable;
	setPosition(transformable.getPosition());
}

const bool Drawable::hasPosition(){
	return true;
}

const bool Drawable::hasSize(){
	return true;
}

const bool Drawable::hasImage(){
	return true;
}