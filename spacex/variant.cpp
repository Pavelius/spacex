#include "main.h"

#define NMHH(T) {FO(T,name), FO(T,text)}
#define NMHX(T) {FO(T,name)}

BSDATA(varianti) = {{""},
	{"action", bsdata<actioni>::source_ptr, NMHX(actioni)},
	{"location", bsdata<locationi>::source_ptr, NMHX(locationi)},
	{"planet", bsdata<planeti>::source_ptr, NMHX(planeti)},
	{"size", bsdata<sizei>::source_ptr, NMHX(sizei)},
	{"ship", bsdata<shipi>::source_ptr},
	{"squad", bsdata<squadi>::source_ptr},
	{"system", bsdata<systemi>::source_ptr, NMHX(systemi)},
};
assert_enum(varianti, System)

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