#include "main.h"
#include "io.h"

static systemi* find_system(const char* id) {
	variant v(id);
	return (systemi*)v;
}

static void add_ship(protoship_s type, const char* planet) {
	auto p = bsdata<shipi>::add();
	p->type = type;
	p->parent = "Sun";
	p->setposition(planet);
}

static void test_ship() {
	add_ship(Ranger, "Earth");
	add_ship(Transporter, "Mars");
	add_ship(Fighter, "Saturn");
	add_ship(Interceptor, "Saturn");
	draw::setnext(game.spaceflight);
}

void printcnf(const char* text);

static void test_comsole() {
	char temp[260]; io::file::getdir(temp, sizeof(temp));
	printcnf(temp);
	printcnf("\n");
}

int main() {
	srand(clock());
	if(!game.readf("data/planets.json"))
		return -1;
	draw::initialize();
	draw::setbitmap("space2");
	test_ship();
	test_comsole();
	draw::application();
	return 0;
}

#ifdef _MSC_VER
int __stdcall WinMain(void* ci, void* pi, char* cmd, int sw) {
	return main();
}
#endif