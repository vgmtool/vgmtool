#ifndef __VGM_PANEL_HDR_H__
#define __VGM_PANEL_HDR_H__

#include "vgm.objs.hpp"

struct VPHeader : VGMPanel {
	// layout
	Banner banner;
	HorizontalLayout hl1;
	VerticalLayout vl1, vl2, vl3;
	// version
	TextField vgmVer;
	// playback rate
	Fieldset lInfo;
		VerticalLayout vlInfo;
		ComboField rate;
		Button rateDetect;
	// lengths
	Fieldset lLengths;
		VerticalLayout vlLen;
		TextField lenTotal;
		TextField lenLoop;
		Button lenChk;
		Button lenCopy;
	// chip clocks
	Fieldset lClocks;
		Label clTxt;
		HorizontalLayout lhCl;
		VerticalLayout vlCl_l, vlCl_r;
		ComboField clSN76489;
		ComboField clYM2413;
		ComboField clYM2612;
		ComboField clYM2151;
		// TODO: v1.51 clocks
		// TODO: v1.60 clocks
		// TODO: v1.61 clocks
	// psg settings
	Fieldset lPSG;
		VerticalLayout vlPSG;
		ComboField psgFB;
		ComboField psgSRW;
	// PROC
	VPHeader() {
		setName("VGM Header");
		banner.create("vgmtool-h-hdr.png",0xff102080);
		lInfo.create("File Info");
			vgmVer.create("Version");
			rate.create("Hz");
				rate.appendIt("0");
				rate.appendIt("50");
				rate.appendIt("60");
			rateDetect.setText("Detect");
		lLengths.create("Lengths (m:ss)");
			lenTotal.create("Total");
			lenLoop.create("Loop");
			lenChk.setText("Check");
			lenCopy.setText("Copy");
		lClocks.create("Chip Clocks (Hz)");
			clTxt.setText("Value should be zero for unused chips.");
			clSN76489.create("SN76489");
				clSN76489.appendIt("0");
				clSN76489.appendIt("3546893");	// pal
				clSN76489.appendIt("3579545");	// ntsc
				clSN76489.appendIt("4000000");	// bbc
			clYM2413.create("YM2413");
				clYM2413.appendIt("0");
				clYM2413.appendIt("3546893");	// pal
				clYM2413.appendIt("3579545");	// ntsc
			clYM2612.create("YM2612");
				clYM2612.appendIt("0");
				clYM2612.appendIt("7600489");	// pal
				clYM2612.appendIt("7670453");	// ntsc
			clYM2151.create("YM2151");
				clYM2151.appendIt("0");
				//clYM2151.appendIt("7600489");
				clYM2151.appendIt("7670453");	// ntsc
		lPSG.create("V1.10+ PSG");
			psgFB.create("Feedback");
				psgFB.appendIt("0");	// disabled
				psgFB.appendIt("9 (Sega VDP)");	// sega vdp
				psgFB.appendIt("3 (discrete)");	// discrete
			psgSRW.create("SR Width");
				psgSRW.appendIt("0");	// disabled
				psgSRW.appendIt("16 (Sega VDP)");	// sega vdp
				psgSRW.appendIt("15 (discrete)");	// discrete
		reflow();
	}
	void reflow() {
		vl1.append(lInfo,{~0,0});
			vgmVer.setLabelWidth(36);
			rate.setLabelWidth(36);
			vlInfo.append(vgmVer,{~0,0},4);
			vlInfo.append(rate,{~0,0},4);
			vlInfo.append(rateDetect,{~0,0});
			lInfo.appendIt(vlInfo);
		vl2.append(lLengths,{~0,0});
			lenTotal.setLabelWidth(32);
			lenLoop.setLabelWidth(32);
			vlLen.append(lenTotal,{~0,0},4);
			vlLen.append(lenLoop,{~0,0},4);
			vlLen.append(lenChk,{~0,0});
			vlLen.append(lenCopy,{~0,0});
			lLengths.appendIt(vlLen);
		append(banner,{~0,0},4);
		append(hl1,{~0,0});
		hl1.append(vl1,{~0,~0},4); hl1.append(vl2,{~0,~0},4); hl1.append(vl3,{~0,~0});
		append(lClocks,{~0,0});
			clSN76489.setLabelWidth(48);
			clYM2413.setLabelWidth(48);
			clYM2612.setLabelWidth(48);
			clYM2151.setLabelWidth(48);
			lhCl.setMargin(4); lhCl.append(vlCl_l,{~0,0},4); lhCl.append(vlCl_r,{~0,0});
			vlCl_l.append(clSN76489,{~0,0}, 4); vlCl_r.append(clYM2413,{~0,0}, 4);
			vlCl_l.append(clYM2612,{~0,0}, 4); vlCl_r.append(clYM2151,{~0,0}, 4);
			lClocks.appendIt(lhCl, {~0,0}, 4);
			lClocks.appendIt(clTxt,{~0,0});
		vl3.append(lPSG,{~0,0});
			psgFB.setLabelWidth(48);
			psgSRW.setLabelWidth(48);
			vlPSG.append(psgFB,{~0,0},4);
			vlPSG.append(psgSRW,{~0,0});
			lPSG.appendIt(vlPSG,{~0,0});
		append(sp,{~0,~0});
	}
};

#endif