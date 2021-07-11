#include "main.h"

BSDATA(populationi) = {
	{"NoPopulated", "Безжизненная"},
	{"Outposts", "Посты"},
	{"Colonies", "Колонии"},
	{"Cities", "Города"},
	{"Overpopulated", "Перенаселена"},
};
assert_enum(populationi, Overpopulated)