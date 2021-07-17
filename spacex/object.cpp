#include "main.h"

bool object::isweapon() const {
	equipmenti* peq = *this;
	if(peq)
		return peq->slots.is(SlotGun) || peq->slots.is(SlotLaser) || peq->slots.is(SlotRocket);
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