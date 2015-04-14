#include "CompareEntityZ.h"
#include "Entity.h"

using namespace S2D;

bool CompareEntityZ::operator()(const unique_ptr<Entity>& e1, const unique_ptr<Entity>& e2){
	return e1->z < e2->z;
}