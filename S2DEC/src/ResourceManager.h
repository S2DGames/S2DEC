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

	sf::Texture* managed(string filename){
		auto it = _textures.find(filename);
		if(it == _textures.end()){
			return nullptr;
		}
		return it->second;
	}

public:
	const sf::Texture& loadTexture(string filename){
		sf::Texture* managedTexture = managed(filename);
		//If the texture is already loaded, return it
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
		sf::Texture* managedTexture = managed(filename);
		//If the texture is already loaded, return it
		if(managedTexture != nullptr){
			return managedTexture;
		}
		//Otherwise, load the texture and return it
		sf::Texture* t = new sf::Texture;
		//assert that the file exists.
		assert(t->loadFromFile(filename));
		manage(filename, t);
		return t;
	}

	void unloadTexture(string filename){
		_textures.erase(filename);
		textures.erase(filename);
	}

	//You probably shouldnt use this
	void unloadTexture(sf::Texture* t){
		for(auto it : _textures){
			if(it.second == t){
				unloadTexture(it.first);
				break;
			}
		}
	}
};