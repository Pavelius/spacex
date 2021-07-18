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

void variants::addships(variant vs) {
	for(auto& e : bsdata<shipi>()) {
		if(e.getlocation() != vs)
			continue;
		add(&e);
	}
}

void variants::matchships(point fp, int r, bool keep, bool apply_transponder) {
	auto ps = data;
	for(auto v : *this) {
		shipi* pu = v;
		if(pu) {
			auto d = distance(fp, pu->getposition());
			auto allow = (d <= r) || (apply_transponder && pu->is(Transponder));
			if(allow != keep)
				continue;
		}
		*ps++ = v;
	}
	count = ps - data;
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