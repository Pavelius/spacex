#include "main.h"

BSDATA(fractioni) = {
	{"Independed", "����������� ����", {}, {Confideration}},
	{"Player", "�����"},
	{"Confideration", "������������", {Corporation}, {Rebels, Pirates, Independed}},
	{"Rebels", "���������", {Pirates}, {Confideration}},
	{"Corporation", "����������", {Confideration}, {Pirates}},
	{"Pirates", "������", {Rebels}, {Confideration, Corporation}},
};
assert_enum(fractioni, Pirates)