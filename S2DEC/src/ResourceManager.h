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

#include <map>
#include <memory>
#include <assert.h>
#include <string>
#include "SFML/Graphics/Texture.hpp"
#include "Util.h"

using std::map;
using std::string;
using std::unique_ptr;
using std::move;

class ResourceManager{
private:
	map<string, unique_ptr<sf::Texture>> textures;
	map<string, sf::Texture*> _textures;

	void manage(string filename, sf::Texture* texture){
		unique_ptr<sf::Texture> uniqueTexturePtr{texture};
		_textures[filename] = texture;
		textures[filename] = move(uniqueTexturePtr);
	}

	sf::Texture* getTexture(string filename){
		auto it = _textures.find(filename);
		if(it == _textures.end()){
			return nullptr;
		}
		return it->second;
	}

public:
	const sf::Texture& loadTexture(string filename){
		//If the texture is already loaded, return it
		sf::Texture* managedTexture = getTexture(filename);
		if(managedTexture != nullptr){
			return *managedTexture;
		}
		//Otherwise, load the texture and return it
		sf::Texture* t = new sf::Texture;
		//assert that the file exists.
		assert(t->loadFromFile(filename));
		manage(filename, t);
		return *t;
	}

	sf::Texture* loadTexture(string filename, bool pointer){
		//If the texture is already loaded, return it
		sf::Texture* managedTexture = getTexture(filename);
		if(managedTexture != nullptr){
			return managedTexture;
		}
		//Otherwise, load the texture and return it
		sf::Texture* t = new sf::Texture;
		t->loadFromFile(filename);
		manage(filename, t);
		return t;
	}

	void unloadTexture(string filename){
		_textures.erase(filename);
		textures.erase(filename);
	}
};