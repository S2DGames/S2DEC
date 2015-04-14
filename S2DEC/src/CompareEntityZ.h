#pragma once
#include <memory>

using std::unique_ptr;

namespace S2D{

	class Entity;

	class CompareEntityZ{
	public:
		bool operator()(const unique_ptr<Entity>& e1, const unique_ptr<Entity>& e2);
	};

	static CompareEntityZ CompareZ;

}