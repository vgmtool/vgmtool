#ifndef __VGM_PANEL_PROC_H__
#define __VGM_PANEL_PROC_H__

#include "../vgm.objs.hpp"

struct VPProc : VGMPanel {
	Banner banner;
	HorizontalLayout hl[5];
	// funcs
	Button toText; Label toTextLbl;
	Button decomp; Label decompLbl;
	Button comp; Label compLbl;
	Button play; Label playLbl;
	Button round; Label roundLbl;
	// proc
	VPProc() {
		setName("Process VGM");
		banner.create("vgmtool-h-proc.png",0xff102080);
		toText.setText("Write to Text");
			toTextLbl.setText("Create a text file detailing in human-readable form \nthe information contained in the VGM file.");
		decomp.setText("Decompress VGZ");
			decompLbl.setText("Decompress the VGM file");
		comp.setText("Compress to VGZ");
			compLbl.setText("Compress or re-compress the VGM file \nwith maximum compression");
		play.setText("Play File");
			playLbl.setText("Play the file");
		round.setText("Round to Frames");
			roundLbl.setText((string){"Group pauses to be frame-accurate"," (WIP, not working)"});
		reflow();
	}
	void reflow() {
		append(banner,{~0,0},4);
		unsigned i;
		hl[0].append(toText,{96,0},4); hl[0].append(toTextLbl,{~0,0});
		hl[1].append(decomp,{96,0},4); hl[1].append(decompLbl,{~0,0});
		hl[2].append(comp,{96,0},4); hl[2].append(compLbl,{~0,0});
		hl[3].append(play,{96,0},4); hl[3].append(playLbl,{~0,0});
		hl[4].append(round,{96,0},4); hl[4].append(roundLbl,{~0,0});
		round.setEnabled(false);
		for (i=0;i<5;++i) append(hl[i],{~0,0},i<4?4:0);
		append(sp,{~0,~0});
		//append(hl[5],{~0,0});
	}
};

#endif