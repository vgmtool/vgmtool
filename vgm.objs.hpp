#ifndef __VGM_OBJ_H__
#define __VGM_OBJ_H__

#include <nall/platform.hpp>
using namespace nall;

#include <phoenix.hpp>
using namespace phoenix;

#include "nthings.hpp"

/**** tabbed panel ****/
struct VGMPanel : HorizontalLayout {
	string name;
	Widget sph, spv, sp;
	VerticalLayout lay;
	VGMPanel() {
		setMargin(4);
		HorizontalLayout::append(sph, {96,~0}, 4);
		HorizontalLayout::append(lay, {~0,~0});
		append(spv, {~0,48});
	}
	void setName(string n) {name = n;}
	void append(Sizable& w, const Size& s, unsigned spc=0) {
		lay.append(w, s, spc);
	}
};

#endif