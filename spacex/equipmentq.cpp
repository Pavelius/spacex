#include "main.h"

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