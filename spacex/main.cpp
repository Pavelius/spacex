#include "main.h"

static systemi* find_system(const char* id) {
	variant v(id);
	return (systemi*)v;
}

static void test_ship() {
	auto p = bsdata<shipi>::add();
	variant v1 = "Earth";
	p->parent = "Sun";
	p->position = ((planeti*)v1)->position;
	p->play();
}

int main() {
	srand(clock());
	if(!game.readf("data/planets.json"))
		return -1;
	draw::initialize();
	draw::setbitmap("space2");
	test_ship();
	return 0;
}

int __stdcall WinMain(void* ci, void* pi, char* cmd, int sw) {
	return main();
}