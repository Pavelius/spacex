#include "main.h"

BSDATA(actioni) = {
	{"Landing", "Совершить посадку"},
	{"Investigate", "Исследовать окресности"},
	{"Flyup", "Взлететь"},
	{"SetCourse", "Установить курс"},
	{"GoingClose", "Приблизиться ближе"},
	{"GoingAway", "Отдалиться от гущи сражения"},
};
assert_enum(actioni, GoingAway)