#include "main.h"

void settlementi::play() {
	answers an;
	if(is(Hangar))
		an.add(1, "�������� �����");
	if(size>=Medium)
		an.add(2, "�������� ������� ������");
	an.add(3, "�������� ������� �����");
	an.add(4, "��������� � ������� �� �������");
	an.add(100, "��������� ����� ������� ���");
	auto r = an.choosev(0, 0, true, "EliteTroops", false);
	switch(r) {
	case 2: visit_goverment(); break;
	case 100: rest(); break;
	}
}

void settlementi::rest() {
	answers an;
}

void settlementi::visit_goverment() {
	answers an;
	auto r = an.choosev("������ ��� ������ �����������. �������� ������ �������� �����-�� ���������� �������.", "�������� ��� �������������", true, "EliteTroops", false);
}