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
#pragma once

#include "Box2D\Dynamics\b2WorldCallbacks.h"
#include "Component.h"

namespace S2D{

	/*!
	 * \class CollisionListener
	 * \brief Monitors collisions and calls the objects that collide
	 */
	class CollisionListener : public b2ContactListener{

		/*!
		 * Called when this object collides with something or something collides with it.
		 * \param contact The contact created by Box2D that stores information about the collision between two fixtures.
		 */
		void BeginContact(b2Contact* contact);

		/*!
		 * Called when this object stops colliding with something.
		 * \param contact The contact created by Box2D that stores information about the collision between two fixtures.
		 */
		void EndContact(b2Contact* contact);

	};

}