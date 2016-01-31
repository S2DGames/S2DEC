#include "UI.h"

void Spell::setDestroySpell(bool flag) {
	destroySpell = flag;
	((UI*)ui)->addPoints(5);
}