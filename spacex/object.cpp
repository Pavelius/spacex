#include "main.h"

bool object::isweapon() const {
	equipmenti* peq = *this;
	if(peq)
		return peq->damage.hits[0]!=0;
	return false;
}

damagei object::getdamage() const {
	equipmenti* p = *this;
	if(!p)
		return {1, 10};
	damagei result = p->damage;
	result.upgrade((equipment_s)getvalue(), getpower());
	return result;
}

int	object::getusemaximum() const {
	switch(origin) {
	case Rebels: return 60;
	case Confideration: return 80;
	case Corporation: return 120;
	default: return 40;
	}
}

bool object::iseffective(int range) const {
	switch(getkind()) {
	case Equipment: return bsdata<equipmenti>::elements[getvalue()].iseffective(range);
	default: return false;
	}
}

void object::create(equipment_s type, fraction_s origin, int power) {
	auto& e = bsdata<equipmenti>::elements[type];
	setvariant(Equipment, type);
	this->origin = origin;
	this->power = power;
	this->variation = rand() % 4;
	this->used = 0;
	switch(origin) {
	case Rebels:
	case Pirates:
		weight = game.random(e.weight[0], e.weight[1], 2);
	default:
		weight = game.random(e.weight[0], e.weight[1], 1);
		break;
	}
}