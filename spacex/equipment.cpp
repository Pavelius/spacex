#include "main.h"

BSDATA(equipmenti) = {
	{"MachineGun", "�������", {SlotGun}, {{16, 30}}, {30, 50}},
	{"Laser", "�����", {SlotLaser}, {{10, 20}}, {15, 40}},
	{"Rocket", "������", {SlotRocket}, {{12, 25}, 3}, {20, 30}},
};
assert_enum(equipmenti, Rocket)