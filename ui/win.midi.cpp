#include "win.midi.hpp"

void MidiWin::reflow() {
}
void MidiWin::create() {
	setVisible(true);
}
MidiWin::MidiWin() {
	// MAIN
	init("Convert to MIDI Options");
	// "STATUSBAR"
	setStatusText("");
	setStatusVisible();
	// MAIN PANEL
	banner.create("vgmtool-hdr.png",0xff102080);
	// "TAB" PANEL
	lvSw.append("General");
	lvSw.append("SN76489");
	lvSw.append("OPL");	// ym2413/opll, ym3812/opl2, ym3526/opl, y8950/msx, ymf262/opl3
	//lvSw.append("YM2413");
	lvSw.append("OPN");	// ym2612/opn2+ym3438/opn2c, ym2203/opn, ym2608/opna, ym2610/opnb
	//lvSw.append("YM2612");
	lvSw.append("OPM");	// ym2151/opm
	//lvSw.append("YM2151");
	//lvSw.append("YM3812");
	//lvSw.append("YM3526");
	//lvSw.append("Y8950");
	//lvSw.append("YMF262");
	//lvSw.append("YM2203");
	//lvSw.append("YM2608");
	//lvSw.append("YM2610/B");
	reflow();
	// PROC
	lvSw.onChange = [&]() { MessageWindow::information(*this, {"TODO: switch to panel ",lvSw.selection()}); };
}
