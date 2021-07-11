#include "crt.h"
#include "stringbuilder.h"

#pragma once

class answers {
	char				buffer[2048];
	stringbuilder		sc;
	struct element {
		int				id;
		const char*		text;
	};
public:
	answers() : sc(buffer) {}
	adat<element, 32>	elements;
	void				add(int id, const char* name, ...) { addv(id, name, xva_start(name)); }
	void				addv(int id, const char* name, const char* format);
	int					choosev(const char* title, const char* cancel_text, bool interactive, const char* resid, bool portraits = false) const;
	static int			compare(const void* v1, const void* v2);
	int					random() const;
	void				sort();
};
