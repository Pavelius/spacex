#include "main.h"

void variants::addspaceunits() {
	for(auto& e : bsdata<spaceunit>()) {
		if(e)
			add(&e);
	}
}

void variants::matchaggressive(bool keep) {
	auto ps = data;
	for(auto v : *this) {
		spaceunit* pu = v;
		if(!pu)
			continue;
		if(pu->isaggressor() != keep)
			continue;
		*ps++ = v;
	}
	count = ps - data;
}

void variants::addships(variant vs, point fp, int r) {
	for(auto& e : bsdata<shipi>()) {
		if(e.getlocation() != vs)
			continue;
		if(r) {
			auto d = distance(fp, e.getposition());
			if(d > r)
				continue;
		}
		add(&e);
	}
}

void variants::addplanets(variant vs) {
	for(auto& e : bsdata<planeti>()) {
		if(e.parent != vs)
			continue;
		add(&e);
	}
}

variant variants::choose(const char* title, bool interactive, bool chooseone) const {
	answers an;
	for(auto v : *this)
		an.add((long)v.getpointer(), v.getname());
	if(interactive && chooseone && an.elements.getcount() == 1)
		return (void*)an.elements.data[0].id;
	an.sort();
	return (void*)an.choosev(title, 0, interactive, 0);
}

void variants::paint() const {
	for(auto v : *this)
		v.paint();
}