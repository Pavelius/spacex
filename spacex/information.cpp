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

void shipi::getinfo(stringbuilder& sb) const {
	header(sb, "Корпус", get(Hull) - get(HullDamage), get(Hull));
	header(sb, "Скорость", get(Speed));
	//header(sb, "Крус", get(Speed));
}

void variant::getinfo(stringbuilder& sb) const {
	sb.addn("##%1", getname());
	switch(getkind()) {
	case Planet: bsdata<planeti>::elements[getvalue()].getinfo(sb); break;
	case System: bsdata<systemi>::elements[getvalue()].getinfo(sb); break;
	case Ship: bsdata<shipi>::elements[getvalue()].getinfo(sb); break;
	default: break;
	}
}