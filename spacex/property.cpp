#include "bsreq.h"
#include "main.h"
#include "io_plugin.h"

#define BSINF(N, T) {#N, bsdata<T>::source_ptr, bsmeta<T>::meta}
#define BSLNK(L, R) template<> struct bsmeta<L> : bsmeta<R> {}; template<> struct bsdata<L> : bsdata<R> {};

NOBSDATA(point)
BSDATAC(variant, 1024 * 8)
BSDATAC(planeti, 1024);
BSDATAC(shipi, 1024);
BSDATAC(systemi, 256);

BSLNK(size_s, sizei)

BSMETA(point) = {
	BSREQ(x), BSREQ(y),
	{}};
BSMETA(variant) = {
	{}};
BSMETA(varianta) = {
	BSREQ(start), BSREQ(count),
	{}};
BSMETA(planeti) = {
	BSREQ(id), BSREQ(name),
	BSREQ(position),
	BSREQ(parent),
	BSREQ(size),
	{}};
BSMETA(systemi) = {
	BSREQ(id), BSREQ(name),
	{}};
BSMETA(sizei) = {
	BSREQ(id), BSREQ(name),
	{}};
BSMETA(shipi) = {
	{}};
BSDATA(bsinf) = {
	BSINF(Planets, planeti),
	BSINF(Systems, systemi),
	BSINF(Ships, shipi)
};
BSDATAF(bsinf)

bool readft(const char* url, bsreq::custom& custom);

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
					reader->warning("Can't find element \"%1\"", value);
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
					reader->warning("Can't find element \"%1\"", value);
				else
					*ps = v;
			}
		}
	};
	custom context;
	return readft(url, context);
}

