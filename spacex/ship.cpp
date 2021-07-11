#include "main.h"

void shipi::setcourse(bool interactive) {
	if(interactive) {
		planeti* target = game.choose("Куда проложить курс?", Planet);
		if(!target)
			return;
		moveto = target->position;
	} else {

	}
	position = moveto;
}

void shipi::play() {
	while(true) {
		systemi* ps = parent;
		if(!ps)
			return;
		ps->prepare();
		setcourse(true);
	}
}