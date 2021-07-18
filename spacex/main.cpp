#include "main.h"
#include "io.h"

static systemi* find_system(const char* id) {
	variant v(id);
	return (systemi*)v;
}

static void add_ship(protoship_s type, const char* planet) {
	auto p = bsdata<shipi>::add();
	p->create(type);
	p->parent = "Sun";
	p->setposition(planet);
}

static void test_ship() {
	add_ship(Ranger, "Earth");
	add_ship(Transporter, "Mars");
	add_ship(Fighter, "Saturn");
	add_ship(Interceptor, "Saturn");
	bsdata<shipi>::elements[0].flyup();
}

static void test_battle() {
	auto s1 = bsdata<shipi>::elements + 0;
	auto s2 = bsdata<shipi>::elements + 3;
	spaceunit::cleanup();
	spaceunit::add(s2, true);
	spaceunit::add(s1, false);
	spaceunit::startbattle();
}

int main() {
	srand(clock());
	if(!game.readf("data/planets.json"))
		return -1;
	draw::initialize();
	test_ship();
	test_battle();
	draw::application();
	return 0;
}

#ifdef _MSC_VER
int __stdcall WinMain(void* ci, void* pi, char* cmd, int sw) {
	return main();
}
#endif