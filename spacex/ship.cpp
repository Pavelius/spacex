#include "main.h"

struct shipnamei {
	const char*		name;
	fractionf		fractions;
};
BSDATA(shipnamei) = {
	{"��������", {Independed}},
	{"�������", {Independed}},
	{"��������", {Independed}},
	{"����������", {Independed}},
	{"�����", {Independed}},
	{"�������", {Independed}},
	{"��������", {Corporation, Confideration}},
	{"�����", {Pirates}},
	{"������", {Pirates}},
	{"�������", {Corporation, Confideration}},
	{"�����", {Corporation, Confideration}},
	{"��������", {Corporation, Confideration}},
	{"���", {Corporation, Confideration}},
	{"�����", {Pirates}},
	{"�����", {Corporation, Confideration}},
	{"�����", {Corporation, Confideration, Pirates}},
	{"�����", {Corporation, Confideration, Rebels}},
	{"�����", {Pirates}},
	{"������", {Corporation, Confideration}},
	{"��������", {Corporation, Confideration}},
	{"�������", {Rebels, Pirates, Confideration}},
	{"�������", {Corporation, Confideration}},
	{"��", {Pirates}},
	{"�������", {Corporation, Confideration}},
	{"������", {Corporation, Confideration}},
};

static void all_visible_ships(variants& objects, const systemi* system, const shipi* player) {
	objects.addships(system);
	objects.matchships(player->getposition(), system_visibility_radius, true, true);
}

static void paint_spaceships() {
	variants objects;
	auto player = game.getplayer();
	if(!player)
		return;
	systemi* system = player->getlocation();
	if(system) {
		objects.add(system);
		objects.addplanets(system);
		all_visible_ships(objects, system, player);
		objects.paint();
	}
}

bool shipi::isplayer() const {
	return game.getplayer() == this;
}

const char*	shipi::getkindname() const {
	return bsdata<protoshipi>::elements[type].name;
}

const char* shipi::getname() const {
	return bsdata<shipnamei>::elements[name].name;
}

int shipi::getvelocity() const {
	return get(Speed);
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

variant shipi::chooseaction(bool interactive, bool paused) {
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
		variants objects;
		all_visible_ships(objects, system, this);
		objects.remove(this);
		if(interactive) {
			if(objects)
				promt(an, SetConnection);
		}
	}
	if(!interactive && isorder()) {
		auto v = getorder();
		if(v && an.getname(getorder())) {
			removeorder();
			return v;
		}
	}
	if(paused)
		return an.choosev(0, "����������", interactive, 0);
	return an.choosev(0, 0, interactive, 0);
}

void shipi::chatting(shipi* opponent, bool interactive) {
	char temp[1024]; stringbuilder sb(temp); answers an;
	sb.adds("������� ������� [%1] �� �����.", opponent->getname());
	sb.adds("��� ���� ���� �������?", opponent->getname());
	an.add(1, "��� ���������� ������� ����.");
	an.add(2, "������ ��������� ������� ������ � �������� ���� ��� ���� ���. � ������ ������������� �� ������� �����.");
	auto v = an.choosev(temp, "������, ���. ������ �������� �����.", interactive, 0);
	if(!v)
		return;
	game.message(interactive, "� ��������� �������� �������� � ����� �������. ����� �����.", 0);
}

void shipi::setconnection(bool interactive) {
	systemi* system = parent;
	if(!system)
		return;
	variants objects;
	all_visible_ships(objects, system, this);
	objects.remove(this);
	shipi* opponent = objects.choose(0, interactive, true);
	chatting(opponent, interactive);
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
		case SetConnection: setconnection(interactive); break;
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
	apply(chooseaction(interactive, false), interactive);
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

static short unsigned random_name() {
	auto count = sizeof(bsdata<shipnamei>::elements) / sizeof(bsdata<shipnamei>::elements[0]);
	return rand() % count;
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
	name = random_name();
}

bool shipi::iseffective(int range) const {
	for(auto v : objects) {
		if(!v || !v.iseffective(range))
			continue;
		return true;
	}
	return false;
}

void shipi::getweapons(equipmentq& result, int range) {
	for(auto& e : objects) {
		if(!e)
			continue;
		if(!e.iseffective(range))
			continue;
		result.add(&e);
	}
}

bool shipi::is(equipment_s v) const {
	for(auto e : objects) {
		if(e.getkind() == Equipment && e.getvalue() == v)
			return true;
	}
	return false;
}

int shipi::get(resource_s v) const {
	switch(v) {
	case Credits: return credits;
	default: return 0;
	}
}