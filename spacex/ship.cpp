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

void shipi::maketurn(bool interactive) {
	switch(parent.getkind()) {
	case System:
		if(moving(getvelocity()))
			break;
		setcourse(interactive);
		break;
	}
}