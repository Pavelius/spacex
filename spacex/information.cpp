#include "main.h"

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

void variant::getinfo(stringbuilder& sb) const {
	sb.addn("##%1", getname());
	switch(getkind()) {
	case Planet: bsdata<planeti>::elements[getvalue()].getinfo(sb); break;
	case System: bsdata<systemi>::elements[getvalue()].getinfo(sb); break;
	default: break;
	}
}