#include "main.h"

void systemi::prepare() {
	draw::objects.clear();
	draw::objects.add(this);
	draw::objects.addplanets(this);
	draw::objects.addships(this, {}, 0);
}