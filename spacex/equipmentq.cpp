#include "main.h"

void equipmentq::addweapon(shipi* p, int range, int range_enemy) {
	for(auto& e : p->objects) {
		if(!e)
			continue;
		if(!e.iseffective(range) || !e.iseffective(range_enemy))
			continue;
		add(&e);
	}
}

void equipmentq::addweapon(shipi* p, int range) {
	for(auto& e : p->objects) {
		if(!e)
			continue;
		if(!e.iseffective(range))
			continue;
		add(&e);
	}
}

void equipmentq::matchef(variants& source, bool keep) {
	auto p = data;
	for(auto pp : *this) {
		if(!pp || !*(pp))
			continue;
		bool can_shoot = false;
		for(auto v : source) {
			spaceunit* ps = v;
			if(!ps)
				continue;
			if(!pp->iseffective(3 + ps->getrange()))
				continue;
			can_shoot = true;
			break;
		}
		if(can_shoot==keep)
			*p++ = pp;
	}
	count = p - data;
}