#include "bsreq.h"
#include "crt.h"
#include "io_plugin.h"

using namespace io;

bool readft(const char* url, bsreq::custom& custom) {
	struct proxy : serializer::reader {
		bsreq::custom& custom;
		const bsinf* findsource(const char* id) {
			for(auto& e : bsdata<bsinf>()) {
				if(strcmp(e.id, id) == 0)
					return &e;
			}
			return 0;
		}
		void* findobject(bsinf* metadata, const char* id, bool create) {
			if(!metadata || !metadata->type)
				return 0;
			auto ps = metadata->source;
			if(!ps)
				return 0;
			id = szdup(id);
			auto ri = ps->find(id, 0);
			if(ri == -1) {
				if(create) {
					ri = ps->indexof(metadata->source->add());
					if(ri == -1)
						return 0;
					auto p = ps->ptr(ri);
					*((const char**)p) = id;
					custom.create(metadata->type, p);
				} else
					return 0;
			}
			return ps->ptr(ri);
		}
		static const bsreq* getmeta(const serializer::node& e) {
			return (bsreq*)e.metadata;
		}
		static void* getobject(const serializer::node& e) {
			return e.object;
		}
		void open(serializer::node& e) override {
			switch(e.getlevel()) {
			case 0:
				if(e.name[0] != 0)
					e.skip = true;
				break;
			case 1:
				e.object = (void*)findsource(e.name);
				break;
			case 2:
				e.metadata = (void*)((bsinf*)e.parent->object)->type;
				e.object = findobject((bsinf*)e.parent->object, e.name, true);
				break;
			default:
				e.metadata = (void*)getmeta(*e.parent)->find(e.name);
				if(e.metadata) {
					e.object = getmeta(e)->ptr(e.parent->object);
					e.metadata = (void*)((bsreq*)e.metadata)->type;
				} else
					e.object = 0;
				break;
			}
		}
		void warning(const char* text, ...) override {
		}
		static int getnumber(const char* v) {
			int result;
			stringbuilder::read(v, result);
			return result;
		}
		void set(serializer::node& e, const char* value) override {
			auto pm = getmeta(*e.parent)->find(e.name);
			if(!pm && e.name == "element")
				pm = getmeta(*e.parent);
			else
				e.index = 0;
			if(!pm) {
				warning("Can't find requisit \"%1\"", e.name);
				return;
			}
			auto ps = pm->ptr(getobject(*e.parent), e.index);
			if(pm->type == bsmeta<int>::meta)
				pm->set(ps, getnumber(value));
			else if(pm->type == bsmeta<const char*>::meta)
				pm->set(ps, (int)szdup(value));
			else if(pm->is(KindEnum)) {
				auto i = pm->findenum(value);
				if(i==-1) {
					warning("Can't find enum value \"%1\"", value);
					return;
				}
				pm->set(ps, i);
			} else
				custom.read(this, pm, e, value);
		}
		proxy(bsreq::custom& custom) : custom(custom) {
		}
	};
	proxy reader_proxy(custom);
	return io::read(url, reader_proxy);
}