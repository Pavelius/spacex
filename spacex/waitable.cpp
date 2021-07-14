#include "main.h"

bool waitable::iswait() const {
	return stamp > game.getround();
}

void waitable::wait(unsigned hours) {
	auto r = game.getround();
	if(stamp < r)
		stamp = r;
	stamp += hours;
}