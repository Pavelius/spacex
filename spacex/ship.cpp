#include "main.h"

struct shipnamei {
	const char*		name;
};
BSDATA(shipnamei) = {
	{"Бетси"},
	{"Клайд"},
	{"Роланд"},
	{"Росинант"},
	{"Люк"},
	{"Бенжамин"},
	{"Гротеск"},
	{"Скупуле"},
};

bool shipi::isplayer() const {
	return game.getplayer() == this;
}

const char* shipi::getname() const {
	return bsdata<protoshipi>::elements[type].name;
}

int shipi::getvelocity() const {
	return bsdata<protoshipi>::elements[type].speed;
}

planeti* shipi::getplanet() const {
	auto v = getposition();
	for(auto& e : bsdata<planeti>()) {
		if(e && e.position == v)
			return &e;
	}
	return 0;
}

static void promt(answers& an, variant v) {
	switch(v.getkind()) {
	case Action:
		an.add(v, bsdata<actioni>::elements[v.getvalue()].name);
		break;
	}
}

variant shipi::chooseaction(bool interactive) {
	answers an;
	planeti* planet = parent;
	if(planet) {
		promt(an, Flyup);
		if(planet->population == NoPopulated
			|| planet->population == SmallColony)
			promt(an, Investigate);
	}
	systemi* system = parent;
	if(system) {
		if(getplanet())
			promt(an, Landing);
		promt(an, SetCourse);
	}
	if(!interactive && isorder()) {
		auto v = getorder();
		if(v && an.getname(getorder())) {
			removeorder();
			return v;
		}
	}
	return an.choosev(0, 0, interactive, 0);
}

void shipi::landing() {
	auto planet = getplanet();
	if(planet) {
		if(!isplayer())
			addorder(SetCourse);
		parent = planet;
		wait(1);
		if(isplayer())
			draw::setnext(game.groundplay);
	}
}

void shipi::flyup() {
	auto planet = getplanet();
	if(planet) {
		parent = planet->parent;
		wait(1);
		if(isplayer())
			draw::setnext(game.spaceflight);
	}
}

void shipi::setcourse(bool interactive) {
	systemi* system = parent;
	if(!system)
		return;
	variants objects;
	objects.addplanets(system);
	objects.remove(getplanet());
	planeti* target = objects.choose(0, interactive);
	if(!target)
		return;
	setmovement(target->position);
}

void shipi::investigate() {
	wait(xrand(4, 8));
}

void shipi::apply(variant v, bool interactive) {
	switch(v.getkind()) {
	case Action:
		switch(v.getvalue()) {
		case SetCourse: setcourse(interactive); break;
		case Landing: landing(); break;
		case Flyup: flyup(); break;
		case Investigate: investigate(); break;
		}
		break;
	}
}

void shipi::maketurn(bool interactive) {
	if(iswait())
		return;
	if(moving(getvelocity()))
		return;
	apply(chooseaction(interactive), interactive);
}

void shipi::shoot(object& weapon, shipi& enemy) {
	auto damage = weapon.getdamage();
	enemy.hit(damage);
	weapon.use();
}

void shipi::hit(damagei& damage) {
}