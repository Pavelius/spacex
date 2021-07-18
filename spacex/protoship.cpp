#include "main.h"

BSDATA(protoshipi) = {
	{"Zond", "Зонд", 0, 10, 0, {}},
	{"Capsule", "Капсула", 1, 20, 20, {}},
	{"Shuttle", "Шаттл", 1, 60, 30, {MachineGun}},
	{"Fighter", "Истребитель", 1, 100, 60, {MachineGun, MachineGun}},
	{"Ranger", "Рейнджер", 3, 250, 60, {MachineGun, Laser}},
	{"Interceptor", "Тяжелый истребитель", 6, 250, 60, {MachineGun, MachineGun, Laser}},
	{"Battleship", "Боевой корабль", 10, 450, 80, {MachineGun, MachineGun, Laser, Laser, Rocket}},
	{"Transporter", "Транспорт", 6, 450, 60, {MachineGun, Transponder}},
	{"Cruiser", "Крейсер", 50, 600, 70, {MachineGun, Laser, Laser, Laser, Rocket, Rocket}},
	{"Carrier", "Авианосец", 50, 800, 50, {MachineGun, MachineGun, MachineGun}},
	{"Linkor", "Линкор", 100, 900, 40, {MachineGun, MachineGun, MachineGun, Laser, Laser, Laser, Rocket, Rocket, Rocket}},
	{"Dreadnought", "Флагман", 1000, 1300, 30, {MachineGun, MachineGun, MachineGun, Laser, Laser, Laser, Rocket, Rocket, Rocket}},
	{"Station", "Станция", 10000, 5000, 10, {MachineGun, MachineGun, Laser, Laser, Laser}},
};
assert_enum(protoshipi, Station)