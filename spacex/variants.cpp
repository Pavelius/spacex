#include "main.h"

void variants::addships(const systemi* fs, point fp, int r) {
	variant vs = fs;
	for(auto& e : bsdata<shipi>()) {
		if(e.parent != vs)
			continue;
		auto d = distance(fp, e.position);
		if(d > r)
			continue;
		add(&e);
	}
}

void variants::addplanets(const systemi* fs) {
	variant vs = fs;
	for(auto& e : bsdata<planeti>()) {
		if(e.parent != vs)
			continue;
		add(&e);
	}
}