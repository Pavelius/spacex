#include "main.h"

const int screen_width = 800;
const int screen_height = 600;
const int maximum_range = 2;

unsigned spaceunit::animation_stamp;

static void paintobjects() {
	variants objects;
	objects.addspaceunits();
	objects.paint();
}

static void mainstage() {
	draw::setbitmap("space2");
	draw::setbackground(paintobjects);
	spaceunit::waitall();
	while(true) {
		for(auto& e : bsdata<spaceunit>()) {
			auto interactive = e.isplayer();
			auto v = e.chooseaction(interactive);
			e.apply(v, interactive);
		}
	}
}

void spaceunit::cleanup() {
	bsdata<spaceunit>::source.clear();
}

void spaceunit::clear() {
	memset(this, 0, sizeof(*this));
}

void spaceunit::add(shipi* ship, bool aggressor) {
	auto p = bsdata<spaceunit>::add();
	p->clear();
	p->ship = ship;
	p->aggressor = aggressor;
	point pt = {screen_width / 2, 0};
	if(!p->isaggressor())
		pt.y = screen_height;
	p->setposition(pt);
}

void spaceunit::setrange(int v) {
	point pt;
	pt.x = screen_width / 2;
	auto dy = (screen_height / 2) / (maximum_range + 1);
	range = v;
	if(isaggressor())
		pt.y = (maximum_range - v) * dy + dy / 2;
	else
		pt.y = screen_height / 2 + v * dy + dy / 2;
	setmovement(pt, animation_stamp);
}

void spaceunit::shoot(spaceunit& enemy) {
}

void spaceunit::startbattle() {
	for(auto& e : bsdata<spaceunit>())
		e.setrange(2);
	draw::setnext(mainstage);
}

void spaceunit::waitall() {
	for(auto& e : bsdata<spaceunit>()) {
		if(e)
			e.wait();
	}
}

void spaceunit::moveall() {
	for(auto& e : bsdata<spaceunit>()) {
		if(e)
			e.maketurn();
	}
	animation_stamp++;
}

void spaceunit::maketurn() {
	if(moving(60, animation_stamp))
		return;
}

static void promt(answers& an, variant v) {
	switch(v.getkind()) {
	case Action:
		an.add(v, bsdata<actioni>::elements[v.getvalue()].name);
		break;
	}
}

variant spaceunit::chooseaction(bool interactive) const {
	answers an;
	if(getrange() > 0)
		promt(an, GoingClose);
	if(getrange() < maximum_range)
		promt(an, GoingAway);
	return an.choosev(0, 0, interactive, 0);
}

void spaceunit::apply(variant v, bool interactive) {
	switch(v.getkind()) {
	case Action:
		switch(v.getvalue()) {
		case GoingClose: setrange(getrange()-1); break;
		case GoingAway: setrange(getrange()+1); break;
		}
		break;
	}
	waitall();
}