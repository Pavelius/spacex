#include "main.h"

BSDATA(actioni) = {
	{"Landing", "Совершить посадку"},
	{"Flyup", "Взлететь"},
	{"SetCourse", "Установить курс"},
};
assert_enum(actioni, SetCourse)