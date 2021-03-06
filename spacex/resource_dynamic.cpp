#include "crt.h"
#include "draw.h"
#include "io.h"

using namespace draw;

namespace {
struct resei {
	const char*		name;
	const char*		folder;
	sprite*			data;
	bool			notfound;
};
}

static vector<resei> source;

static resei* find(const char* name, const char* folder) {
	for(auto& e : source) {
		if(e.name == name && e.folder == folder)
			return &e;
	}
	return 0;
}

const sprite* draw::gres(const char* name, const char* folder, point maxsize) {
	auto p = find(name, folder);
	if(!p) {
		p = source.add();
		p->name = name;
		p->folder = folder;
		p->data = 0;
		p->notfound = false;
	}
	if(!p || p->notfound)
		return 0;
	if(!p->data) {
		char temp[260];
		p->data = (sprite*)loadb(szurl(temp, p->folder, p->name, "pma"));
		if(!p->data) {
			draw::surface dc;
			for(auto pg = surface::plugin::first; pg; pg = pg->next) {
				szurl(temp, p->folder, p->name, pg->name);
				if(dc.read(temp, 0, 32)) {
					unsigned size = sizeof(sprite) + dc.width * dc.height * 3;
					p->data = (sprite*)new char[size]; memset(p->data, 0, size);
					p->data->frames[0].encode = sprite::RAW;
					p->data->frames[0].sx = dc.width;
					p->data->frames[0].sy = dc.height;
					p->data->frames[0].offset = sizeof(sprite);
					p->data->count = 1;
					// ??????? ? ??????? ???????? ?????? ??? ????????????
					auto pd = (unsigned char*)p->data->ptr(p->data->frames[0].offset);
					rect rc = {0, 0, dc.width, dc.height};
					if(maxsize.x && rc.width() > maxsize.x) {
						rc.x1 = (rc.width() - maxsize.x) / 2;
						rc.x2 = rc.x1 + maxsize.x;
					}
					if(maxsize.y && rc.height() > maxsize.y) {
						rc.y1 = (rc.width() - maxsize.y) / 2;
						rc.y2 = rc.y1 + maxsize.y;
					}
					for(auto y = rc.y1; y < rc.y2; y++) {
						for(auto x = rc.x1; x < rc.x2; x++) {
							auto input = dc.ptr(x, y);
							pd[0] = input[0];
							pd[1] = input[1];
							pd[2] = input[2];
							pd += 3;
						}
					}
					break;
				}
			}
		}
	}
	if(!p->data)
		p->notfound = true;
	return p->data;
}