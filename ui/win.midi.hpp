#ifndef __VGM_WINMIDI_H__
#define __VGM_WINMIDI_H__

#include <nall/platform.hpp>
using namespace nall;

#include <phoenix.hpp>
using namespace phoenix;

#include "../vgm.objs.hpp"
#include "../vgm.cfg.hpp"

/**** MIDI panels ****/

/**** MIDI config window ****/
struct MidiWin : public NWin {
	Config cfg;
	// WINDOW
	Banner banner;
	VerticalLayout layMain;
	// "TAB" VIEW
	HorizontalLayout hlSw;
	//VerticalLayout flSw;
	ListView lvSw;
	// PROC
	MidiWin();
	void create();
	void reflow();
};

#endif