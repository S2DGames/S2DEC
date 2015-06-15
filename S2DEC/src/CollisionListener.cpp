// Copyright (C) 2015 Doug Madden (dmadden772@gmail.com)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
#include "CollisionListener.h"

using namespace S2D;

void CollisionListener::BeginContact(b2Contact* contact){
	Component* a = (Component*)contact->GetFixtureA()->GetBody()->GetUserData();
	Component* b = (Component*)contact->GetFixtureB()->GetBody()->GetUserData();
	if(a != nullptr && a->getOwner() != nullptr){
		a->beginCollision(b, contact);
	}
	if(b != nullptr && b->getOwner() != nullptr){
		b->beginCollision(a, contact);
	}
}

void CollisionListener::EndContact(b2Contact* contact){
	Component* a = (Component*)contact->GetFixtureA()->GetBody()->GetUserData();
	Component* b = (Component*)contact->GetFixtureB()->GetBody()->GetUserData();
	if(a != nullptr && a->getOwner() != nullptr){
		a->endCollision(b, contact);
	}
	if(b != nullptr && b->getOwner() != nullptr){
		b->endCollision(a, contact);
	}
}