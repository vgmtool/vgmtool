#include "vgmtool.hpp"
#include "ui/win.midi.cpp"
#include "ui/win.app.cpp"

int main(int argc, char** argv) {
	AppWin app(argc, argv);
	app.create();
	OS::main();
	return 0;
}