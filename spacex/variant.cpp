#include "main.h"

#define NMHH(T) {FO(T,name), FO(T,text)}
#define NMHX(T) {FO(T,name)}

BSDATA(varianti) = {{""},
	{"action", bsdata<actioni>::source_ptr, NMHX(actioni)},
	{"equipment", bsdata<equipmenti>::source_ptr, NMHX(equipmenti)},
	{"fraction", bsdata<fractioni>::source_ptr, NMHX(fractioni)},
	{"location", bsdata<locationi>::source_ptr, NMHX(locationi)},
	{"planet", bsdata<planeti>::source_ptr, NMHX(planeti)},
	{"size", bsdata<sizei>::source_ptr, NMHX(sizei)},
	{"ship", bsdata<shipi>::source_ptr},
	{"spaceunit", bsdata<spaceunit>::source_ptr},
	{"squad", bsdata<squadi>::source_ptr},
	{"system", bsdata<systemi>::source_ptr, NMHX(systemi)},
	{"visual", bsdata<visuali>::source_ptr},
};
assert_enum(varianti, Visual)

variant::variant(const void* v) : u(0) {
	for(auto& e : bsdata<varianti>()) {
		if(!e.source)
			continue;
		auto i = e.source->indexof(v);
		if(i != -1) {
			u = i;
			c[3] = &e - bsdata<varianti>::elements;
			break;
		}
	}
}

variant::variant(const char* v) : u(0) {
	for(auto& e : bsdata<varianti>()) {
		if(!e.source || !e.names[0])
			continue;
		auto i = e.source->find(v, 0);
		if(i != -1) {
			u = i;
			c[3] = &e - bsdata<varianti>::elements;
			break;
		}
	}
}

const char* variant::getname() const {
	auto& e = bsdata<varianti>::elements[getkind()];
	if(!e.names[0])
		return "No name";
	return *(const char**)((char*)getpointer() + e.names[0]);
}

void variant::paint() const {
	switch(getkind()) {
	case Planet: bsdata<planeti>::elements[getvalue()].paint(); break;
	case Ship: bsdata<shipi>::elements[getvalue()].paint(); break;
	case Spaceunit: bsdata<spaceunit>::elements[getvalue()].paint(); break;
	case System: bsdata<systemi>::elements[getvalue()].paint(); break;
	case Visual: bsdata<visuali>::elements[getvalue()].paint(); break;
	}
}