#ifndef __VGM_PANEL_MISC_H__
#define __VGM_PANEL_MISC_H__

#include "vgm.objs.hpp"

struct VPMisc : VGMPanel {
	Banner banner;
	// proc
	VPMisc() {
		setName("Miscellaneous");
		banner.create("vgmtool-h-misc.png",0xff102080);
		reflow();
	}
	void reflow() {
		append(banner,{~0,0},4);
		//append(hl1,{~0,0});
		append(sp,{~0,~0});
	}
};

#endif