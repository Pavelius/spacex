#include "main.h"

void variants::addships(variant vs, point fp, int r) {
	for(auto& e : bsdata<shipi>()) {
		if(e.parent != vs)
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