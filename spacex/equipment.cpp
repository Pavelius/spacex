#include "main.h"

BSDATA(equipmenti) = {
	{"MachineGun", "�������", {SlotGun}, {{16, 30}}, {30, 50}, {0, 3, 4}},
	{"Laser", "�����", {SlotLaser}, {{10, 20}}, {15, 40}, {0, 1, 2, 3, 4, 5}},
	{"Rocket", "������", {SlotRocket}, {{12, 25}, 3}, {20, 30}, {2, 4, 5}},
};
assert_enum(equipmenti, Rocket)