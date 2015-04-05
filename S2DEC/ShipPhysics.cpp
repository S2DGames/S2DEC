#include "ShipPhysics.h"
#include "ShipImage.h"
#include "Util.h"

ShipPhysics::ShipPhysics(Game* game) : world(*game), window(*game){
	bodyDef.type = b2_dynamicBody;
	shape.m_radius = 1.0f;
	fixtureDef.shape = &shape;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.1f;
}

void ShipPhysics::init(){
	if(owner->hasComponent<ShipControls>()){
		shipControls = &owner->getComponent<ShipControls>();
	}else{
		cerr << owner->getName() << ": ShipControls component missing" << endl;
	}
	body = world.CreateBody(&bodyDef);
	body->SetUserData(this);
	body->SetAngularDamping(2.5f);
}

void ShipPhysics::onStart(){
	if(owner->hasComponent<ShipImage>()){
		sf::FloatRect rect = ((ShipImage&)owner->getComponent<ShipImage>()).getSprite().getGlobalBounds();
		shape.m_radius = std::max(rect.width - rect.left, rect.height - rect.top);
	} else{
		cerr << owner->getName() << ": ShipImage component missing" << endl;
	}
	body->CreateFixture(&fixtureDef);
	view = window.getView();

	view.setSize(view.getSize().x - 200.0f, view.getSize().y - 112.5f);
}

bool ShipPhysics::update(sf::Time frameTime){
	view.setCenter(body->GetPosition().x * SCALE, body->GetPosition().y * SCALE);
	view.setRotation((float)(body->GetAngle() * RADTODEG));
	window.setView(view);

	b2Vec2 velocity = body->GetLinearVelocity();
	b2Vec2 desiredVelocity(0.0f, 0.0f);
	b2Vec2 force(0.0f, 0.0f);

	if(shipControls->up()){
		desiredVelocity.x = maxSpeed;
		desiredVelocity.y = maxSpeed;
	}

	if(shipControls->down()){
		desiredVelocity.x = -maxSpeed;
		desiredVelocity.y = -maxSpeed;
	}

	b2Vec2 forceDirection = body->GetWorldVector(b2Vec2(0, 1));
	b2Vec2 velChange(desiredVelocity.x * forceDirection.x + velocity.x, desiredVelocity.y * forceDirection.y + velocity.y);
	force.x = body->GetMass() * -velChange.x;
	force.y = body->GetMass() * -velChange.y;
	body->ApplyForceToCenter(force, true);

	float angle = body->GetAngle();
	float desiredAngle = 0.0f;

	if(shipControls->left()){
		desiredAngle = (float)(angle * RADTODEG - 90);
	}

	if(shipControls->right()){
		desiredAngle = (float)(angle * RADTODEG + 90);
	}

	if(shipControls->left() || shipControls->right()){
		float nextAngle = angle + body->GetAngularVelocity() / 60;
		float totalRotation = desiredAngle * (float)DEGTORAD - nextAngle;
		while(totalRotation < -180 * (float)DEGTORAD){
			totalRotation += 360 * (float)DEGTORAD;
		}
		while(totalRotation > 180 * (float)DEGTORAD){
			totalRotation -= 360 * (float)DEGTORAD;
		}
		float desiredAngularVel = totalRotation * .25f;
		if(desiredAngularVel > 1 / 8.0){
			desiredAngularVel = 1 / 8.0;
		}
		if(desiredAngularVel < -1 / 8.0){
			desiredAngularVel = -1 / 8.0;
		}
		float inertia = body->GetInertia();
		float torque = inertia * desiredAngularVel / (1 / 30.0f);
		body->ApplyTorque(torque, true);
	}
	return false;
}

void ShipPhysics::beginCollision(Component* collidedComponent, b2Contact* contact){

}

void ShipPhysics::endCollision(Component* collidedComponent, b2Contact* contact){

}

sf::Vector2f ShipPhysics::getPosition() const{
	return{body->GetPosition().x * SCALE, body->GetPosition().y * SCALE};
}

float ShipPhysics::getAngle() const{
	return (float)(body->GetAngle() * RADTODEG);
}