#pragma once

#include <vector>
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "Entity.h"
#include <exception>
#include <stdexcept>

using std::exception;

namespace S2D{

	enum LoadType{
		LOAD		/*!< Attempt to load the resource. Return the resource if it is already loaded and not modified. */,
		DUPLICATE	/*!< Load the resource into a new resource node even if the resource in the most recent node is not modified. */,
		OVERWRITE	/*!< Re-load the resource into the first resource node. Overwrites any resource that was previously there. */,
		ACCESS		/*!< Retrieve a resource even if it is modified. */
	};

	class Texture : public sf::Texture{
	public:
		const string filename;
		bool modified;
		Entity* owner;

		Texture(string filename, Entity* owner);
		Texture(Texture& texture, sf::Texture& tex);
		virtual sf::Texture& getTexture();
	};

	class BatchedTexture : public Texture{
	private:
		bool batched;
		sf::IntRect batchedRect;

	public:
		BatchedTexture(Texture& texture, sf::Texture& batch);
		sf::Texture& getTexture();
		const sf::IntRect& getBatchedCoordinates();
	};

	class ResourceManager{
	private:
		std::map<std::string, Texture*> textures;

		sf::Texture atlas;

	public:
		ResourceManager();
		~ResourceManager();

		/*!
		 * Loads a texture.
		 * \param filename The file name of the texture.
		 * \param force If the texture is already loaded, should we load it again.
		 */
		//sf::Texture* loadTexture(std::string filename, Object<>* owner, LoadType type = LOAD);

		/*!
		* Loads a texture.
		* \param filename The file name of the texture.
		* \param force If the texture is already loaded, should we load it again.
		*/
		const Texture& loadTexture(Entity* owner, LoadType type, string filename, string uniqueID, bool batch) throw(...);

		void createBatch();
	};

	//static const char* AccessUnloadedResource 

	class AccessUnloadedResource : public exception{
	public:
		virtual const char* what() const throw(){
			return "Failure: attempted to access unloaded resource.";
		}
	};

	class UnkownLoadType : public exception{
	public:
		virtual const char* what() const throw(){
			return "Failure: attempted to load resource with unkown load type";
		}
	};
}