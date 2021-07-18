#include "main.h"

BSDATA(protoshipi) = {
	{"Zond", "����", 0, 10, 0, {}},
	{"Capsule", "�������", 1, 20, 20, {}},
	{"Shuttle", "�����", 1, 60, 30, {MachineGun}},
	{"Fighter", "�����������", 1, 100, 60, {MachineGun, MachineGun}},
	{"Ranger", "��������", 3, 250, 60, {MachineGun, Laser}},
	{"Interceptor", "������� �����������", 6, 250, 60, {MachineGun, MachineGun, Laser}},
	{"Battleship", "������ �������", 10, 450, 80, {MachineGun, MachineGun, Laser, Laser, Rocket}},
	{"Transporter", "���������", 6, 450, 60, {MachineGun, Transponder}},
	{"Cruiser", "�������", 50, 600, 70, {MachineGun, Laser, Laser, Laser, Rocket, Rocket}},
	{"Carrier", "���������", 50, 800, 50, {MachineGun, MachineGun, MachineGun}},
	{"Linkor", "������", 100, 900, 40, {MachineGun, MachineGun, MachineGun, Laser, Laser, Laser, Rocket, Rocket, Rocket}},
	{"Dreadnought", "�������", 1000, 1300, 30, {MachineGun, MachineGun, MachineGun, Laser, Laser, Laser, Rocket, Rocket, Rocket}},
	{"Station", "�������", 10000, 5000, 10, {MachineGun, MachineGun, Laser, Laser, Laser}},
};
assert_enum(protoshipi, Station)