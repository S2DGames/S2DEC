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

#include <functional>

using std::bind;

#define PI 3.141592653589793
#define RADTODEG 180/PI
#define DEGTORAD PI/180
#define SCALE 100

#ifndef _MSC_VER
#define NOEXCEPT noexcept
#else
#define NOEXCEPT
#endif

#define IGNORE_DEBUG

/*!
 * Registers an event to the EventManager
 * The condition and callback must be from the same Component class
 * Example: if bool Player::has0HP() and void Player::die() are functions
 * registerLocalEvent(Player::has0HP, Player::die);
 *
 * \param condition The function to be evaluated
 * \param callback The function to be called when the condition evaluates to true
 */
#define registerLocalEvent(condition, callback) game->watchEvent(bind(&condition, this), bind(&callback, this), this)

/*!
 * Registers an event to the EventManager
 * The condition and callback can be from different Component classes
 * Example: if bool Player::isEscKeyPressed() and void Menu::openMenu() are functions
 * Call this from either class
 * registerLocalEvent(this, Player::isEscKeyPressed, this, Menu::openMenu, ptrToMenu);
 * or
 * registerLocalEvent(ptrToPlayer, Player::isEscKeyPressed, ptrToPlayer, Menu::openMenu, this);
 *
 * \param owner A Component pointer to the owner of the event
 * \param condition The function to be evaluated
 * \param component1 A Component pointer to the owner of the condition function
 * \param callback The function to be called when the condition evaluates to true
 * \param component2 A Component pointer to the owner of the callback function
 */
#define registerNonLocalEvent(owner, condition, component1, callback, component2) game->watchEvent(bind(&condition, component1), bind(&callback, component2), owner)