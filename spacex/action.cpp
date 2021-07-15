#include "main.h"

BSDATA(actioni) = {
	{"Landing", "Совершить посадку"},
	{"Investigate", "Исследовать окресности"},
	{"Flyup", "Взлететь"},
	{"SetCourse", "Установить курс"},
};
assert_enum(actioni, SetCourse)