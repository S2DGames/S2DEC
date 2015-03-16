#include "ResourceManager.h"

using namespace S2D;

Texture::Texture(string filename, Entity* owner) : filename(filename){
	this->owner = owner;
	modified = false;
}

Texture::Texture(Texture& texture, sf::Texture& tex) : filename(texture.filename), sf::Texture(tex){
	owner = texture.owner;
	modified = texture.modified;
}

sf::Texture& Texture::getTexture(){
	return *this;
}

BatchedTexture::BatchedTexture(Texture& texture, sf::Texture& batch) : Texture(texture, batch){

}

sf::Texture& BatchedTexture::getTexture(){
	return *this;
}

ResourceManager::ResourceManager(){

}

ResourceManager::~ResourceManager(){
	for(auto it : textures){
		delete(it.second);
	}
}

const Texture& ResourceManager::loadTexture(Entity* owner, LoadType type, string filename, string uniqueID, bool batch = true) throw(...){
	//check if the resource has been loaded previously
	auto it = textures.find(filename);

	if(it == textures.end()){
		//the resource has not been loaded yet
		//if we try to access unloaded resource, throw an error.
		if(type != ACCESS){
			//load it
			Texture* texture = new Texture(filename, owner);
			texture->loadFromFile(filename);
			if(batch){
				BatchedTexture* batchedTexture = new BatchedTexture(*texture, atlas);
				return *batchedTexture;
			}else{
				textures.emplace(uniqueID, texture);
				return *texture;
			}
		}else{
			throw AccessUnloadedResource();
		}
	}

	//the resource is already loaded
	switch(type){
	case LOAD:
		//check if the texture is modified. if not, return it. If it is, make a new node with the loaded texture.
		if(it->second->modified){
			
		}else{
			return *it->second;
		}
		break;
		//batchedTexture.create()
	case DUPLICATE:{
		
		
	}case OVERWRITE:
		it->second->getTexture().loadFromFile(filename);
		if(batch){

		}
		return *it->second;
	case ACCESS:
		return *it->second;
	default:
		throw UnkownLoadType();
	}
}

void ResourceManager::createBatch(){

}