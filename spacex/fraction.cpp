#include "main.h"

BSDATA(fractioni) = {
	{"Independed", "Независимые силы", {}, {Confideration}},
	{"Player", "Игрок"},
	{"Confideration", "Конфедерация", {Corporation}, {Rebels, Pirates, Independed}},
	{"Rebels", "Повстанци", {Pirates}, {Confideration}},
	{"Corporation", "Корпорация", {Confideration}, {Pirates}},
	{"Pirates", "Пираты", {Rebels}, {Confideration, Corporation}},
};
assert_enum(fractioni, Pirates)