#include "main.h"

BSDATA(protoshipi) = {
	{"Zond", "����", 0, 10, 0, {}, Confideration},
	{"Capsule", "�������", 1, 20, 40, {}, Confideration},
	{"Shuttle", "�����", 1, 60, 50, {MachineGun}, Confideration},
	{"Fighter", "�����������", 1, 100, 100, {MachineGun, MachineGun}, Confideration},
	{"Ranger", "��������", 3, 250, 60, {MachineGun, Laser}, Confideration},
	{"Interceptor", "��������", 6, 250, 120, {MachineGun, MachineGun, Laser}, Pirates},
	{"Battleship", "���������", 10, 450, 80, {MachineGun, MachineGun, Laser, Laser, Rocket}, Confideration},
	{"Transporter", "���������", 6, 450, 60, {MachineGun, Transponder}, Confideration},
	{"Cruiser", "�������", 50, 600, 80, {MachineGun, Laser, Laser, Laser, Rocket, Rocket}, Confideration},
	{"Carrier", "���������", 50, 800, 50, {MachineGun, MachineGun, MachineGun}, Confideration},
	{"Linkor", "������", 100, 900, 40, {MachineGun, MachineGun, MachineGun, Laser, Laser, Laser, Rocket, Rocket, Rocket}, Confideration},
	{"Dreadnought", "������������", 1000, 1300, 40, {MachineGun, MachineGun, MachineGun, Laser, Laser, Laser, Rocket, Rocket, Rocket}, Confideration},
	{"Station", "�������", 10000, 5000, 30, {MachineGun, MachineGun, Laser, Laser, Laser}, Confideration},
};
assert_enum(protoshipi, Station)