#include "main.h"

void settlementi::play() {
	answers an;
	if(is(Hangar))
		an.add(1, "Посетить ангар");
	if(size>=Medium)
		an.add(2, "Посетить местную власть");
	an.add(3, "Посетить местный рынок");
	an.add(4, "Двигаться в локацию на планете");
	an.add(100, "Отдохнуть здесь остаток дня");
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
	auto r = an.choosev("Сейчас нет ничего интересного. Возможно завтра появятся какие-то интересные задания.", "Покинуть зал правительства", true, "EliteTroops", false);
}