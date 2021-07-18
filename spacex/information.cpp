#include "main.h"

static void header(stringbuilder& sb, const char* name, int vc, int vm) {
	if(vc < vm / 3)
		sb.addn("%1: [-%2i]/%3i", name, vc, vm);
	else if(vc < vm * 2 / 3)
		sb.addn("%1: [~%2i]/%3i", name, vc, vm);
	else
		sb.addn("%1: %2i/%3i", name, vc, vm);
}

static void header(stringbuilder& sb, const char* name, int vc) {
	sb.addn("%1: %2i", name, vc);
}

static void header(stringbuilder& sb, const char* name, const char* format, ...) {
	if(!format || format[0] == 0)
		return;
	sb.addsep('\n');
	sb.add("%1: ", name);
	sb.addv(format, xva_start(format));
}

void planeti::getinfo(stringbuilder& sb) const {
	sb.addn(bsdata<landscapei>::elements[landscape].text);
	sb.adds(bsdata<populationi>::elements[population].text);
}

void systemi::getinfo(stringbuilder& sb) const {
	variants source;
	source.addplanets(this);
	for(auto v : source)
		sb.addn(v.getname());
}

static planeti* findplanet(point pt) {
	for(auto& e : bsdata<planeti>()) {
		if(e && e.position == pt)
			return &e;
	}
	return 0;
}

void shipi::getinfo(stringbuilder& sb) const {
	header(sb, "Корпус", get(Hull) - get(HullDamage), get(Hull));
	header(sb, "Скорость", get(Speed));
	if(ismoving()) {
		auto planet = findplanet(getdestination());
		if(planet)
			header(sb, "Курс", planet->name);
	}
}

void variant::getinfo(stringbuilder& sb) const {
	auto kind = getkind();
	switch(kind) {
	case Ship:
		sb.addn("##%1 %2", bsdata<shipi>::elements[getvalue()].getkindname(), getname());
		break;
	default: sb.addn("##%1", getname()); break;
	}
	switch(kind) {
	case Planet: bsdata<planeti>::elements[getvalue()].getinfo(sb); break;
	case System: bsdata<systemi>::elements[getvalue()].getinfo(sb); break;
	case Ship: bsdata<shipi>::elements[getvalue()].getinfo(sb); break;
	default: break;
	}
}