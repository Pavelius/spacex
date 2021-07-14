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

variant shipi::chooseaction(bool interactive) const {
	answers an;
	const char* resid = "jupiter";
	switch(parent.getkind()) {
	case System:
		if(getplanet())
			promt(an, Landing);
		promt(an, SetCourse);
		break;
	case Planet:
		resid = "spaceport";
		promt(an, Flyup);
		break;
	}
	return an.choosev(0, 0, interactive, resid);
}

void shipi::landing() {
	auto planet = getplanet();
	if(planet) {
		parent = planet;
		wait(xrand(3, 12));
	}
}

void shipi::flyup() {
	auto planet = getplanet();
	if(planet) {
		parent = planet->parent;
		wait(1);
	}
}

void shipi::setcourse(bool interactive) {
	systemi* system = parent;
	if(!system)
		return;
	variants objects;
	objects.addplanets(system);
	objects.remove(getplanet());
	planeti* target = objects.choose("Куда проложить курс?", interactive);
	if(!target)
		return;
	setmovement(target->position);
}

void shipi::apply(variant v, bool interactive) {
	switch(v.getkind()) {
	case Action:
		switch(v.getvalue()) {
		case SetCourse:
			setcourse(interactive);
			break;
		case Landing:
			landing();
			break;
		case Flyup:
			flyup();
			break;
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