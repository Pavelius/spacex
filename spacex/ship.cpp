#include "main.h"

struct shipnamei {
	const char*		name;
};
BSDATA(shipnamei) = {
	{"�����"},
	{"�����"},
	{"������"},
	{"��������"},
	{"���"},
	{"��������"},
	{"�������"},
	{"�������"},
};

int shipi::getvelocity() const {
	return 100;
}

void shipi::setcourse(bool interactive) {
	systemi* system = parent;
	if(!system)
		return;
	system->prepare();
	planeti* target = game.choose("���� ��������� ����?", Planet, {});
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