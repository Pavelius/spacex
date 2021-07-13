#include "main.h"

static systemi* find_system(const char* id) {
	variant v(id);
	return (systemi*)v;
}

static void test_ship() {
	auto p = bsdata<shipi>::add();
	variant v1 = "Earth";
	p->parent = "Sun";
	p->setposition(((planeti*)v1)->position);
	draw::setnext(game.adventure);
}

int main() {
	srand(clock());
	if(!game.readf("data/planets.json"))
		return -1;
	draw::initialize();
	draw::setbitmap("space2");
	test_ship();
	draw::application();
	return 0;
}

#ifdef _MSC_VER
int __stdcall WinMain(void* ci, void* pi, char* cmd, int sw) {
	return main();
}
#endif