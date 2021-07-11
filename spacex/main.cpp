#include "main.h"

static systemi* find_system(const char* id) {
	variant v(id);
	return (systemi*)v;
}

int main() {
	srand(clock());
	if(!game.readf("data/planets.json"))
		return -1;
	draw::initialize();
	draw::setbitmap("space2");
	auto p = find_system("Sun");
	if(!p)
		return -1;
	p->play();
	return 0;
}

int __stdcall WinMain(void* ci, void* pi, char* cmd, int sw) {
	return main();
}