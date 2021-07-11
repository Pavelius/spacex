#include "main.h"

int damagei::roll(int chance_critical) const {
	if(chance_critical > 0 && d100() < chance_critical)
		return hits[1];
	else if(chance_critical < 0)
		return hits[0];
	else if(hits[1] == hits[0])
		return hits[0];
	else
		return 1 + (rand() % (hits[1] - hits[0]));
}