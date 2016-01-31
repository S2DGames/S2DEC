#pragma once

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include <cmath>

#include <memory>
#include <array>
#include <unordered_set>

namespace ltbl {
	class QuadtreeOccupant {
	private:
		class QuadtreeNode* _pQuadtreeNode;
		class Quadtree* _pQuadtree;

		bool _isAwake;
		bool _isTurnedOn;

	public:
		QuadtreeOccupant()
			: _pQuadtreeNode(nullptr), _pQuadtree(nullptr)
		{}

		void quadtreeUpdate();
		void quadtreeRemove();

		bool isAwake();
		void setAwake(bool);
		void toggleAwake();

		void setTurnedOn(bool);
		bool isTurnedOn();
		void toggleTurnedOn();

		virtual sf::FloatRect getAABB() const = 0;

		friend class Quadtree;
		friend class QuadtreeNode;
		friend class DynamicQuadtree;
		friend class StaticQuadtree;
	};
}