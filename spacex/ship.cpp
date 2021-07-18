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

static void paint_spaceships() {
	variants objects;
	auto player = game.getplayer();
	if(!player)
		return;
	systemi* system = player->parent;
	if(system) {
		objects.add(system);
		objects.addplanets(system);
		objects.addships(system, {}, 0);
		objects.paint();
	}
}

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

static void spaceflight() {
	draw::setbitmap("space2");
	draw::setbackground(paint_spaceships);
	game.play(game.passhour);
}

static void groundplay() {
	auto planet = game.getplayer()->getplanet();
	draw::setbitmap(planet->getbackground());
	game.play(game.passhour);
}

static void promt(answers& an, variant v) {
	switch(v.getkind()) {
	case Action:
		an.add(v, bsdata<actioni>::elements[v.getvalue()].name);
		break;
	}
}

variant shipi::chooseaction(bool interactive) {
	answers an;
	planeti* planet = parent;
	if(planet) {
		promt(an, Flyup);
		if(planet->population == NoPopulated
			|| planet->population == SmallColony)
			promt(an, Investigate);
	}
	systemi* system = parent;
	if(system) {
		if(getplanet())
			promt(an, Landing);
		promt(an, SetCourse);
	}
	if(!interactive && isorder()) {
		auto v = getorder();
		if(v && an.getname(getorder())) {
			removeorder();
			return v;
		}
	}
	return an.choosev(0, 0, interactive, 0);
}

void shipi::landing() {
	auto planet = getplanet();
	if(planet) {
		if(!isplayer())
			addorder(SetCourse);
		parent = planet;
		wait(1);
		if(isplayer())
			draw::setnext(groundplay);
	}
}

void shipi::flyup() {
	auto planet = getplanet();
	if(planet) {
		parent = planet->parent;
		wait(1);
		if(isplayer())
			draw::setnext(spaceflight);
	}
}

void shipi::setcourse(bool interactive) {
	systemi* system = parent;
	if(!system)
		return;
	variants objects;
	objects.addplanets(system);
	objects.remove(getplanet());
	planeti* target = objects.choose(0, interactive, false);
	if(!target)
		return;
	setmovement(target->position, game.getround());
}

void shipi::investigate() {
	wait(xrand(4, 8));
}

void shipi::apply(variant v, bool interactive) {
	switch(v.getkind()) {
	case Action:
		switch(v.getvalue()) {
		case SetCourse: setcourse(interactive); break;
		case Landing: landing(); break;
		case Flyup: flyup(); break;
		case Investigate: investigate(); break;
		}
		break;
	}
}

void shipi::maketurn(bool interactive) {
	if(iswait())
		return;
	if(moving(getvelocity(), game.getround()))
		return;
	apply(chooseaction(interactive), interactive);
}

void shipi::shoot(object& weapon, shipi& enemy) {
	auto damage = weapon.getdamage();
	enemy.hit(damage);
	weapon.use();
}

void shipi::hit(damagei& damage) {
	auto value = damage.roll() - get(Armor);
	if(value < 1)
		value = 1;
	set(HullDamage, get(HullDamage) + value);
}

void shipi::add(const object& v) {
	objects.add(v);
}

static int radnomv(int v) {
	auto d = v / 6;
	auto v1 = imax(1, v - d);
	auto v2 = v + d;
	return xrand(v1, v2);
}

void shipi::clear() {
	memset(this, 0, sizeof(*this));
}

void shipi::create(protoship_s type) {
	auto& e = bsdata<protoshipi>::elements[type];
	clear();
	this->type = type;
	set(Hull, radnomv(e.hull));
	set(Speed, radnomv(e.speed));
	set(Crew, radnomv(e.crew));
	for(auto v : e.equipments)
		add(v);
}

bool shipi::iseffective(int range) const {
	for(auto v : objects) {
		if(!v || !v.iseffective(range))
			continue;
		return true;
	}
	return false;
}

bool shipi::iseffective(int range, int enemy_range) const {
	for(auto v : objects) {
		if(!v)
			continue;
		if(!v.iseffective(range) || !v.iseffective(enemy_range + 3))
			continue;
		return true;
	}
	return false;
}