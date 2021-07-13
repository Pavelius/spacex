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

int shipi::getvelocity() const {
	return 100;
}

void shipi::setcourse(bool interactive) {
	systemi* system = parent;
	if(!system)
		return;
	system->prepare();
	planeti* target = game.choose("Куда проложить курс?", Planet, {});
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