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

void damagei::upgrade(equipment_s type, int power) {
	switch(type) {
	case Laser:
		hits[0] += 2 * power;
		hits[1] += 4 * power;
		break;
	case Rocket:
		hits[0] += 1 * power;
		hits[1] += 4 * power;
		break;
	case MachineGun:
		hits[0] += 5 * power;
		hits[1] += 8 * power;
		break;
	}
}