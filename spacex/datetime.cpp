#include "main.h"

static const char* month_names[] = {
	"������", "�������", "�����", "������", "���", "����",
	"����", "�������", "��������", "�������", "������", "�������"
};

const char* datetime::getname() const {
	static char temp[32]; stringbuilder sb(temp);
	sb.adds("%1i", getdayofmonth());
	sb.adds(month_names[getmonth() - 1]);
	sb.adds("%1i", getyear());
	return temp;
}