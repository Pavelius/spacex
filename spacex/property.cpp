#include "bsreq.h"
#include "io_plugin.h"
#include "main.h"

#define BSLNK(L, R) template<> struct bsmeta<L> : bsmeta<R> {}; template<> struct bsdata<L> : bsdata<R> {};

NOBSDATA(point)
BSDATAC(variant, 1024 * 8)
BSDATAC(planeti, 1024);
BSDATAC(shipi, 1024);
BSDATAC(systemi, 256);

BSLNK(fraction_s, fractioni)
BSLNK(landscape_s, landscapei)
BSLNK(population_s, populationi)
BSLNK(size_s, sizei)

BSMETA(fractioni) = {
	BSREQ(id), BSREQ(name),
	{}};
BSMETA(landscapei) = {
	BSREQ(id), BSREQ(name), BSREQ(text),
	{}};
BSMETA(planeti) = {
	BSREQ(id), BSREQ(name),
	BSREQ(resid),
	BSREQ(position),
	BSREQ(fraction),
	BSREQ(landscape),
	BSREQ(population),
	BSREQ(parent),
	BSREQ(size),
	{}};
BSMETA(point) = {
	BSREQ(x), BSREQ(y),
	{}};
BSMETA(populationi) = {
	BSREQ(id), BSREQ(name),
	{}};
BSMETA(systemi) = {
	BSREQ(id), BSREQ(name),
	{}};
BSMETA(sizei) = {
	BSREQ(id), BSREQ(name),
	{}};
BSMETA(shipi) = {
	{}};
BSMETA(variant) = {
	{}};
BSMETA(varianta) = {
	BSREQ(start), BSREQ(count),
	{}};

bool gamei::readf(const char* url) {
	struct custom : bsreq::custom {
		void create(const bsreq* type, void* object) override {
			if(type == bsmeta<planeti>::meta) {
				auto p = (planeti*)object;
				p->size = Medium;
				p->population = NoPopulated;
			}
		}
		void read(serializer::reader* reader, const bsreq* requisit, serializer::node& e, const char* value) override {
			if(requisit->type == bsmeta<varianta>::meta) {
				auto ps = requisit->ptr(e.parent->object);
				variant v = value;
				if(!v) {
					reader->error("Can't find element \"%1\"", value);
					return;
				}
				auto pv = (varianta*)ps;
				if(!pv->count)
					pv->start = bsdata<variant>::source.count;
				unsigned i = pv->start + pv->count;
				if(bsdata<variant>::source.count < i)
					bsdata<variant>::source.count = i;
				bsdata<variant>::elements[i] = v;
				pv->count++;
			} else if(requisit->type == bsmeta<variant>::meta) {
				auto ps = (variant*)requisit->ptr(e.parent->object, e.index);
				variant v = value;
				if(!v)
					reader->error("Can't find element \"%1\"", value);
				else
					*ps = v;
			}
		}
	};
	static bsreq sources[] = {
		BSINF(Planets, planeti),
		BSINF(Systems, systemi),
		BSINF(Ships, shipi),
		{}};
	custom context;
	context.source = sources;
	return context.readf(url);
}

