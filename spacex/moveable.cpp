#include "main.h"

bool moveable::ismoving() const {
	return position != target_position;
}

void moveable::stop() {
	setposition(position);
}

void moveable::setposition(point v) {
	position = v;
	start_position = v;
	target_position = v;
	start_date = 0;
}

void moveable::setposition(variant v) {
	switch(v.getkind()) {
	case Planet:
		setposition(bsdata<planeti>::elements[v.getvalue()].position);
		break;
	case System:
		setposition(point{800 / 2, 600 / 2});
		break;
	case Ship:
		setposition(bsdata<shipi>::elements[v.getvalue()].getposition());
		break;
	}
}

void moveable::setmovement(point v, unsigned stamp) {
	start_position = position;
	target_position = v;
	start_date = stamp;
}

bool moveable::moving(int velocity, unsigned stamp) {
	if(!ismoving())
		return false;
	long maximum = distance(start_position, target_position);
	if(!maximum) {
		position = target_position;
		return false;
	}
	long passed_time = stamp - start_date;
	long current = velocity * passed_time / datetime::mpd;
	if(current >= maximum)
		position = target_position;
	else {
		position.x = (short)(start_position.x + (target_position.x - start_position.x) * current / maximum);
		position.y = (short)(start_position.y + (target_position.y - start_position.y) * current / maximum);
	}
	return true;
}