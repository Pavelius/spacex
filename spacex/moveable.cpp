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

void moveable::setmovement(point v) {
	start_position = position;
	target_position = v;
	start_date = game.getround();
}

bool moveable::moving(int velocity) {
	if(!ismoving())
		return false;
	unsigned maximum = distance(start_position, target_position);
	if(!maximum) {
		position = target_position;
		return false;
	}
	unsigned passed_time = game.getround() - start_date;
	unsigned current = velocity * passed_time / datetime::mpd;
	if(current >= maximum)
		position = target_position;
	else {
		position.x = start_position.x + (start_position.x - target_position.x) * current / maximum;
		position.y = start_position.y + (start_position.y - target_position.y) * current / maximum;
	}
	return true;
}