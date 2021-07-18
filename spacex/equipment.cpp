#include "main.h"

BSDATA(equipmenti) = {
	{"MachineGun", "Пулемет", {{16, 30}}, {30, 50}, {0, 3, 4}},
	{"Laser", "Лазер", {{10, 20}}, {15, 40}, {0, 1, 2, 3, 4, 5}},
	{"Rocket", "Ракеты", {{12, 25}, 3}, {20, 30}, {2, 4, 5}},
	{"Transponder", "Транспондер", {}, {1}, {}},
};
assert_enum(equipmenti, Transponder)