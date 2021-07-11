#include "main.h"

void shipi::adventure() {
	position = target_position;
}

void shipi::setcourse(bool interactive) {
	if(interactive) {
		planeti* target = game.choose("Куда проложить курс?", Planet, {});
		if(!target)
			return;
		target_position = target->position;
	} else {

	}
	start_position = position;
}

void shipi::play() {
	while(true) {
		systemi* ps = parent;
		if(!ps)
			return;
		ps->prepare();
		setcourse(true);
		adventure();
	}
}