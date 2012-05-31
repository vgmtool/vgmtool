#ifndef __VGM_PANEL_OPT_H__
#define __VGM_PANEL_OPT_H__

#include "vgm.objs.hpp"

struct VPOpt : VGMPanel {
	// layout
	Banner banner;
	HorizontalLayout hl1;
	VerticalLayout vl1, vl2;
	// trimming
	Fieldset lTrim;
		VerticalLayout vlTrim;
		TextField trStart;
		TextField trLoop;
		TextField trEnd;
		CheckBox trIncLoop;
		CheckBox trLog;
		Button trBtnRound;
		Button trBtnTrimOld;
		Button trBtnTrimNew;
	// optimize
	Fieldset lOpt;
		VerticalLayout vlOpt;
		CheckBox opRemoveOffsets;
		CheckBox opRemovePSG;
		Button opOpt;
	// debugging
	Fieldset lDebug;
		VerticalLayout vlDebug;
		Button dbTrimOnly;
		Button dbRemoveOffsets;
		Button dbOptData;
		Button dbOptPauses;
		Button dbCompress;
	VPOpt() {
		setName("Optimize VGM");
		banner.create("vgmtool-h-opt.png",0xff102080);
		lTrim.create("Trim (samples)");
			trStart.create("Start");
			trLoop.create("Loop");
			trEnd.create("End");
			trIncLoop.setText("Include looping");
			trLog.setText("Log to text");
			trBtnRound.setText("Round Times");
			trBtnTrimOld.setText("Trim (old)");
			trBtnTrimNew.setText("Trim (new)");
		lOpt.create("Optimize");
			opRemoveOffsets.setText("Remove silent offsets");
			opRemovePSG.setText("Remove silent PSG");
			opOpt.setText("Optimize");
		lDebug.create("New trim debugging");
			dbTrimOnly.setText("Trim only");
			dbRemoveOffsets.setText("Remove offsets");
			dbOptData.setText("Optimize data");
			dbOptPauses.setText("Optimize pauses");
			dbCompress.setText("Compress");
		reflow();
	}
	void reflow() {
		vl1.append(lTrim,{~0,0});
			trStart.setLabelWidth(32);
			trLoop.setLabelWidth(32);
			trEnd.setLabelWidth(32);
			vlTrim.append(trStart,{~0,0},4);
			vlTrim.append(trLoop,{~0,0},4);
			vlTrim.append(trEnd,{~0,0},4);
			vlTrim.append(trIncLoop,{~0,0},4);
			vlTrim.append(trLog,{~0,0},4);
			vlTrim.append(trBtnRound,{~0,0});
			vlTrim.append(trBtnTrimOld,{~0,0});
			vlTrim.append(trBtnTrimNew,{~0,0});
			lTrim.appendIt(vlTrim);
		vl1.append(lOpt,{~0,0});
			vlOpt.append(opRemoveOffsets,{~0,0},4);
			vlOpt.append(opRemovePSG,{~0,0},4);
			vlOpt.append(opOpt,{~0,0});
			lOpt.appendIt(vlOpt);
		vl2.append(lDebug,{~0,0});
			vlDebug.append(dbTrimOnly,{~0,0});
			vlDebug.append(dbRemoveOffsets,{~0,0});
			vlDebug.append(dbOptData,{~0,0});
			vlDebug.append(dbOptPauses,{~0,0});
			vlDebug.append(dbCompress,{~0,0});
			lDebug.appendIt(vlDebug);
		append(banner,{~0,0},4);
		append(hl1,{~0,0}); hl1.append(vl1,{~0,~0},4); hl1.append(vl2,{~0,~0});
		append(sp,{~0,~0});
	}
};

#endif