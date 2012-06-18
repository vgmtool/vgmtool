#ifndef __VGM_PANEL_DATA_H__
#define __VGM_PANEL_DATA_H__

#include "../vgm.objs.hpp"

struct VPData : VGMPanel {
	// layout
	Banner banner;
	HorizontalLayout hl0, hl1, hl2;
	VerticalLayout vl0;
	// funcs
	VerticalLayout hlProc;
	Fieldset lPrSelect;
		VerticalLayout vlSel;
		Button btnSelAll;
		Button btnSelNone;
		Button btnSelInv;
		Button btnSelGuess;
	Fieldset lPrCount;
		VerticalLayout vlCnt;
		Button btnCntCount;
		Button btnCntStrip;
	// psg
	Fieldset lSN76489;
		HorizontalLayout vlSN;
		Fieldset psgTone;
			VerticalLayout vlSNTone;
			CheckBox snTone[3];
		Fieldset psgMisc;
			VerticalLayout vlSNMisc;
			CheckBox psgNoise;
			CheckBox psgStereo;
	// ym2413
	Fieldset lYM2413;
		HorizontalLayout hlYM2413;
		Fieldset ym2413Tone;
			VerticalLayout vlYM2413Tone[3];
			HorizontalLayout hlYM2413Tone;
			CheckBox ym2413Ch[9];
			CheckBox ym2413ToneU;
			CheckBox ym2413Inv;
		Fieldset ym2413Perc;
			VerticalLayout vlYM2413Perc;
			CheckBox ym2413PercHat;
			CheckBox ym2413PercCym;
			CheckBox ym2413PercTom;
			CheckBox ym2413PercSnr;
			CheckBox ym2413PercKick;
	// ym2612
	Fieldset lYM2612;
		HorizontalLayout hlYM2612;
		Fieldset ym2612Tone;
			HorizontalLayout hlYM2612t;
			VerticalLayout vlYM2612t[2];
			CheckBox ym2612Ch[6];
		Fieldset ym2612Misc;	// dac, csm-mode ch3 0xA*
			VerticalLayout vlYM2612m;
			CheckBox ym2612DAC;
			CheckBox ym2612CSM[3];
	// ym2151
	Fieldset lYM2151;
		HorizontalLayout hlYM2151;
		VerticalLayout vlYM2151[2];
		CheckBox ym2151Ch[8];
	// proc
	VPData() {
		setName("Analyze VGM Data");
		banner.create("vgmtool-h-data.png",0xff102080);
		unsigned i;
		//// SUPER-LOOP TO ENCOMPASS GUI POPULATION
		for (i=0;i<9;++i) {
			ym2413Ch[i].setText(i+1);
			if (i<8) {
				ym2151Ch[i].setText(i+1);
				if (i<6) {
					ym2612Ch[i].setText(i+1);
					if (i<3) {
						snTone[i].setText(i+1);
						ym2612CSM[i].setText((string){"CSM ",i+1});
					}
				}
			}
		}
		lPrSelect.create("Select");
			btnSelAll.setText("All");
			btnSelNone.setText("None");;
			btnSelInv.setText("Invert");
			btnSelGuess.setText("Guess");
		lPrCount.create("Process");
			btnCntCount.setText("Count All");
			btnCntStrip.setText("Strip Selected"); btnCntStrip.setEnabled(false);
		lSN76489.create("SN76489", true, true);
			psgTone.create("Tone", false, true);
			psgMisc.create("Misc", false, true);
				psgNoise.setText("Noise");
				psgStereo.setText("Stereo");
		lYM2413.create("YM2413", true, true);
			ym2413Tone.create("Tone", false, true);
				ym2413ToneU.setText("User Instrument");
				ym2413Inv.setText("Invalid Registers");
			ym2413Perc.create("Perc", false, true);
				ym2413PercHat.setText("Hi-Hat");
				ym2413PercCym.setText("Cymbal");
				ym2413PercTom.setText("Toms");
				ym2413PercSnr.setText("Snare");
				ym2413PercKick.setText("Kick");
		lYM2612.create("YM2612", true, true);
			ym2612Tone.create("Tone", false, true);
			ym2612Misc.create("Misc", false, true);
				ym2612DAC.setText("DAC");
		lYM2151.create("YM2151", true, true);
		initProc();
		reflow();
	}
	//void checkSN76489() {}
	//void checkYM2413() {}
	//void checkYM2612() {}
	//void checkYM2151() {}
	void toggleAll(const bool &b) {
		lSN76489._lt.cblabel.setChecked(b); lSN76489._lt.cblabel.onToggle();
		lYM2413._lt.cblabel.setChecked(b); lYM2413._lt.cblabel.onToggle();
		lYM2612._lt.cblabel.setChecked(b); lYM2612._lt.cblabel.onToggle();
		lYM2151._lt.cblabel.setChecked(b); lYM2151._lt.cblabel.onToggle();
	}
	void toggleInv() {
		//// SUPER-LOOP TO ENCOMPASS GUI POPULATION
		unsigned i;
		for (i=0;i<9;++i) {
			ym2413Ch[i].setChecked(!ym2413Ch[i].checked());
			if (i<8) {
				ym2151Ch[i].setChecked(!ym2151Ch[i].checked());
				if (i<6) {
					ym2612Ch[i].setChecked(!ym2612Ch[i].checked());
					if (i<3) {
						snTone[i].setChecked(!snTone[i].checked());
						ym2612CSM[i].setChecked(!ym2612CSM[i].checked());
					}
				}
			}
		}
		psgNoise.setChecked(!psgNoise.checked());
		psgStereo.setChecked(!psgStereo.checked());
		ym2413ToneU.setChecked(!ym2413ToneU.checked());
		ym2413Inv.setChecked(!ym2413Inv.checked());
		ym2413PercHat.setChecked(!ym2413PercHat.checked());
		ym2413PercCym.setChecked(!ym2413PercCym.checked());
		ym2413PercTom.setChecked(!ym2413PercTom.checked());
		ym2413PercSnr.setChecked(!ym2413PercSnr.checked());
		ym2413PercKick.setChecked(!ym2413PercKick.checked());
		ym2612DAC.setChecked(!ym2612DAC.checked());
	}
	void initProc() {
		//// SELECT
		btnSelAll.onActivate = [&](){
			//MessageWindow::information(*window(), "TODO: toggle all true");
			toggleAll(true);
		};
		btnSelNone.onActivate = [&](){
			//MessageWindow::information(*window(), "TODO: toggle all false");
			toggleAll(false);
		};
		btnSelInv.onActivate = [&](){
			//MessageWindow::information(*window(), "TODO: toggle all invert");
			toggleInv();
		};
		btnSelGuess.onActivate = [&](){
			MessageWindow::information(*window(), "TODO: guess selection");
		};
		//// SN76489
		psgTone._lt.cblabel.onToggle = [&](){
			bool c = psgTone._lt.cblabel.checked();
			unsigned i;
			for(i=0;i<3;++i) snTone[i].setChecked(c);
		};
		psgMisc._lt.cblabel.onToggle = [&](){
			bool c = psgMisc._lt.cblabel.checked();
			psgNoise.setChecked(c);
			psgStereo.setChecked(c);
		};
		lSN76489._lt.cblabel.onToggle = [&](){
			bool c = lSN76489._lt.cblabel.checked();
			psgTone._lt.cblabel.setChecked(c); psgTone._lt.cblabel.onToggle();
			psgMisc._lt.cblabel.setChecked(c); psgMisc._lt.cblabel.onToggle();
		};
		//// YM2413
		ym2413Tone._lt.cblabel.onToggle = [&](){
			bool c = ym2413Tone._lt.cblabel.checked();
			unsigned i;
			for(i=0;i<9;++i) ym2413Ch[i].setChecked(c);
			ym2413ToneU.setChecked(c);
			ym2413Inv.setChecked(c);
		};
		ym2413Perc._lt.cblabel.onToggle = [&](){
			bool c = ym2413Perc._lt.cblabel.checked();
			ym2413PercHat.setChecked(c);
			ym2413PercCym.setChecked(c);
			ym2413PercTom.setChecked(c);
			ym2413PercSnr.setChecked(c);
			ym2413PercKick.setChecked(c);
		};
		lYM2413._lt.cblabel.onToggle = [&](){
			bool c = lYM2413._lt.cblabel.checked();
			ym2413Tone._lt.cblabel.setChecked(c); ym2413Tone._lt.cblabel.onToggle();
			ym2413Perc._lt.cblabel.setChecked(c); ym2413Perc._lt.cblabel.onToggle();
		};
		//// YM2612
		ym2612Tone._lt.cblabel.onToggle = [&](){
			bool c = ym2612Tone._lt.cblabel.checked();
			unsigned i;
			for(i=0;i<6;++i) ym2612Ch[i].setChecked(c);
		};
		ym2612Misc._lt.cblabel.onToggle = [&](){
			bool c = ym2612Misc._lt.cblabel.checked();
			ym2612DAC.setChecked(c);
			unsigned i;
			for(i=0;i<3;++i) ym2612CSM[i].setChecked(c);
		};
		lYM2612._lt.cblabel.onToggle = [&](){
			bool c = lYM2612._lt.cblabel.checked();
			ym2612Tone._lt.cblabel.setChecked(c); ym2612Tone._lt.cblabel.onToggle();
			ym2612Misc._lt.cblabel.setChecked(c); ym2612Misc._lt.cblabel.onToggle();
		};
		//// YM2151
		lYM2151._lt.cblabel.onToggle = [&](){
			bool c = lYM2151._lt.cblabel.checked();
			unsigned i;
			for(i=0;i<8;++i) ym2151Ch[i].setChecked(c);
		};
	}
	void reflow() {
		unsigned i,q;
		append(banner,{~0,0},4);
		hl0.setAlignment(0.0);
		hl1.setAlignment(0.0);
		hl2.setAlignment(0.0);
		hlProc.setAlignment(0.0);
		hlProc.append(lPrCount,{~0,0},4);
			vlCnt.append(btnCntCount,{~0,0});
			vlCnt.append(btnCntStrip,{~0,0});
			lPrCount.appendIt(vlCnt);
		hlProc.append(lPrSelect,{~0,0});
			vlSel.append(btnSelAll,{~0,0});
			vlSel.append(btnSelNone,{~0,0});
			vlSel.append(btnSelInv,{~0,0});
			vlSel.append(btnSelGuess,{~0,0});
			lPrSelect.appendIt(vlSel);
		hl0.append(hlProc,{96,0},4);
		//// SUPER-LOOP TO ENCOMPASS GUI POPULATION
		//// IF THERE'S A MORE EFFICIENT UNROLL, PLS DO!
		for (i=0;i<9;++i) {
			if (i<8) {
				vlYM2151[i&1].append(ym2151Ch[i],{~0,0},i<6?4:0);
				if (i<6) {
					vlYM2612t[i&1].append(ym2612Ch[i],{~0,0},i<4?4:0);
					if (i<3) {
						hlYM2413Tone.append(vlYM2413Tone[i],{~0,0},i<2?2:0);
						vlSNTone.append(snTone[i],{~0,0},i<2?4:0);
						vlYM2612m.append(ym2612CSM[i],{~0,0},4);
						if (i<2) {
							hlYM2612t.append(vlYM2612t[i],{~0,0},i<1?2:0);
							hlYM2151.append(vlYM2151[i],{~0,0},i<1?2:0);
						}
					}
				}
			}
			vlYM2413Tone[i%3].append(ym2413Ch[i],{~0,0},i<6?4:0);
		}
		lSN76489.appendIt(vlSN);
			vlSN.setAlignment(0.0);
			vlSN.append(psgTone,{0,0},4);
				psgTone.appendIt(vlSNTone);
			vlSN.append(psgMisc,{0,0});
				vlSNMisc.append(psgNoise,{~0,0},4);
				vlSNMisc.append(psgStereo,{~0,0});
				psgMisc.appendIt(vlSNMisc);
		lYM2413.appendIt(hlYM2413);
			hlYM2413.setAlignment(0.0);
			hlYM2413.append(ym2413Tone,{~0,0},4);
				hlYM2413Tone.setAlignment(0.0);
				ym2413Tone.appendIt(hlYM2413Tone,{~0,0},1);
				ym2413Tone.appendIt(ym2413ToneU,{~0,0},4);
				ym2413Tone.appendIt(ym2413Inv,{~0,0},3);
			hlYM2413.append(ym2413Perc,{0,0});
				vlYM2413Perc.append(ym2413PercHat,{~0,0},4);
				vlYM2413Perc.append(ym2413PercCym,{~0,0},4);
				vlYM2413Perc.append(ym2413PercTom,{~0,0},4);
				vlYM2413Perc.append(ym2413PercSnr,{~0,0},4);
				vlYM2413Perc.append(ym2413PercKick,{~0,0});
				ym2413Perc.appendIt(vlYM2413Perc);
		lYM2612.appendIt(hlYM2612);
			hlYM2612.setAlignment(0.0);
			hlYM2612.append(ym2612Tone,{~0,0},4);
				ym2612Tone.appendIt(hlYM2612t);
			hlYM2612.append(ym2612Misc,{0,0});
				vlYM2612m.append(ym2612DAC,{~0,0});
				ym2612Misc.appendIt(vlYM2612m);
		lYM2151.appendIt(hlYM2151);
			hlYM2151.setAlignment(0.0);
		hl1.append(lYM2413,{0,0},4);
		hl1.append(lSN76489,{0,0},4);
		hl2.append(lYM2612,{0,0},4);
		hl1.append(lYM2151,{~0,0});
		vl0.append(hl1,{~0,0},4);
		vl0.append(hl2,{~0,0});
		hl0.append(vl0,{~0,~0});
		append(hl0,{~0,0});
		append(sp,{~0,~0});
	}
};


#endif