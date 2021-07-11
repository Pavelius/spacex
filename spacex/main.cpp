#include "main.h"

static systemi* find_system(const char* id) {
	for(auto& e : bsdata<systemi>()) {
		if(strcmp(e.id, id) == 0)
			return &e;
	}
	return 0;
}

int main() {
	srand(clock());
	draw::initialize();
	draw::setbitmap("space2");
	game.readf("data/planets.json");
	auto p = find_system("Sun");
	p->play();
	return 0;
}

int __stdcall WinMain(void* ci, void* pi, char* cmd, int sw) {
	return main();
}