#include "main.h"

BSDATA(equipmenti) = {
	{"MachineGun", "�������", {{16, 30}}, {30, 50}, {0, 3, 4}},
	{"Laser", "�����", {{10, 20}}, {15, 40}, {0, 1, 2, 3, 4, 5}},
	{"Rocket", "������", {{12, 25}, 3}, {20, 30}, {2, 4, 5}},
	{"Transponder", "�����������", {}, {1}, {}},
};
assert_enum(equipmenti, Transponder)