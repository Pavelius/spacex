#include "main.h"

gamei game;

static char d6() {
	return 1 + rand() % 6;
}

static int compare_lesser(const void* v1, const void* v2) {
	return *((char*)v1) - *((char*)v2);
}

static int compare_greater(const void* v1, const void* v2) {
	return *((char*)v2) - *((char*)v1);
}

result_s gamei::roll(int dices) {
	char result[5] = {};
	if(dices <= 0) {
		result[0] = d6();
		result[1] = d6();
		qsort(result, 2, sizeof(result[0]), compare_lesser);
	} else {
		if(dices > sizeof(result) / sizeof(result[0]))
			dices = sizeof(result) / sizeof(result[0]);
		for(auto i = 0; i < dices; i++)
			result[i] = d6();
		qsort(result, dices, sizeof(result[0]), compare_greater);
	}
	if(result[0] == 6) {
		if(dices >= 2 && result[1] == 6)
			return CriticalSuccess;
		return Success;
	} else if(result[0] >= 4)
		return PartialSuccess;
	return Fail;
}

variant gamei::choose(const char* title, variant_s filter) {
	answers an;
	for(auto v : draw::objects) {
		if(v.getkind() != filter)
			continue;
		an.add(v, v.getname());
	}
	an.sort();
	return an.choosev(title, 0, true, 0);
}