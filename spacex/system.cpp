#include "main.h"

void systemi::prepare() {
	draw::objects.clear();
	draw::objects.add(this);
	draw::objects.addplanets(this);
	draw::objects.addships(this, {}, 0);
}

void systemi::play() {
	prepare();
	auto v = game.choose("Куда проложите курс?", Planet);
}