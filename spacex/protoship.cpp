#include "main.h"

BSDATA(protoshipi) = {
	{"Zond", "Зонд", 0, 10, 0, {}, Confideration},
	{"Capsule", "Капсула", 1, 20, 40, {}, Confideration},
	{"Shuttle", "Шаттл", 1, 60, 50, {MachineGun}, Confideration},
	{"Fighter", "Истребитель", 1, 100, 100, {MachineGun, MachineGun}, Confideration},
	{"Ranger", "Рейнджер", 3, 250, 60, {MachineGun, Laser}, Confideration},
	{"Interceptor", "Налетчик", 6, 250, 120, {MachineGun, MachineGun, Laser}, Pirates},
	{"Battleship", "Штурмовик", 10, 450, 80, {MachineGun, MachineGun, Laser, Laser, Rocket}, Confideration},
	{"Transporter", "Транспорт", 6, 450, 60, {MachineGun, Transponder}, Confideration},
	{"Cruiser", "Крейсер", 50, 600, 80, {MachineGun, Laser, Laser, Laser, Rocket, Rocket}, Confideration},
	{"Carrier", "Авианосец", 50, 800, 50, {MachineGun, MachineGun, MachineGun}, Confideration},
	{"Linkor", "Линкор", 100, 900, 40, {MachineGun, MachineGun, MachineGun, Laser, Laser, Laser, Rocket, Rocket, Rocket}, Confideration},
	{"Dreadnought", "Уничтожитель", 1000, 1300, 40, {MachineGun, MachineGun, MachineGun, Laser, Laser, Laser, Rocket, Rocket, Rocket}, Confideration},
	{"Station", "Станция", 10000, 5000, 30, {MachineGun, MachineGun, Laser, Laser, Laser}, Confideration},
};
assert_enum(protoshipi, Station)