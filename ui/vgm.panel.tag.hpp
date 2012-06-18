#ifndef __VGM_PANEL_TAG_H__
#define __VGM_PANEL_TAG_H__

#include "../vgm.objs.hpp"

struct GD3TextField : HorizontalLayout {
	Label label;
	LineEdit en;
	LineEdit jp;
	uint32_t labelWidth;
	void create(const string &l="Label", const uint32_t &w=0) {
		setLabel(l);
		setLabelWidth(w);
	}
	void setLabel(const string &l) {label.setText(l);}
	void setLabelWidth(const uint32_t &w=0) {labelWidth=w; reflow();}
	void reflow() {
		remove(label); remove(en); remove(jp);
		append(label, {labelWidth,0},2);
		append(en, {~0,0},2);
		append(jp, {~0,0});
	}
};
struct GD3ComboField : HorizontalLayout {
	Label label;
	ComboBox en;
	LineEdit jp;
	uint32_t labelWidth;
	void create(const string &l="Label", const uint32_t &w=0) {
		setLabel(l);
		setLabelWidth(w);
	}
	void setLabel(const string &l) {label.setText(l);}
	void setLabelWidth(const uint32_t &w=0) {labelWidth=w; reflow();}
	void reflow() {
		remove(label); remove(en); remove(jp);
		append(label, {labelWidth,0},2);
		append(en, {~0,0},2);
		append(jp, {~0,0});
	}
};
struct VPTag : VGMPanel {
	// layout
	Banner banner;
	HorizontalLayout hl0, hl1;
	VerticalLayout vl1;
	Widget spl;
	Label lblEn, lblJp;
	// funcs
	Fieldset lFunc;
		VerticalLayout vlFunc;
		Button btnGD3Rem;
		Button btnGD3Upd;
		Button btnGD3Clr;
	// track
	Fieldset lTrack;
		VerticalLayout vlTrack;
		GD3TextField trTitle, trAuthor;
	// game
	Fieldset lGame;
		VerticalLayout vlGame;
		GD3TextField gameTitle;
		GD3ComboField gameSys;
		TextField gameDate;
		Widget spd;
	// vgm
	Fieldset lVGM;
		VerticalLayout vlVGM;
		TextField vgmCreator;
		TextboxField vgmNotes;
	// proc
	VPTag() {
		setName("GD3 Tagging");
		banner.create("vgmtool-h-tag.png",0xff102080);
		lblEn.setText("English"); lblJp.setText("Japanese");
		lFunc.create("Process");
			btnGD3Rem.setText("Remove GD3");
			btnGD3Upd.setText("Update GD3");
			btnGD3Clr.setText("Clear");
		lTrack.create("Track Info");
			trTitle.setLabel("Title");
			trAuthor.setLabel("Author");
			//enTrTitle.create("Title (EN)"); jpTrTitle.create("Title (JP)");
			//enTrAuthor.create("Author (EN)"); jpTrAuthor.create("Author (JP)");
		lGame.create("Game Info");
			gameTitle.setLabel("Name");
			gameSys.setLabel("System");
			gameDate.setLabel("Release Date");
			//enGameTitle.create("Name (EN)"); jpGameTitle.create("Name (JP)");
			//enGameSys.create("System (EN)"); jpGameSystem.create("System (JP)");
			//enGameDate.create("Release Date"); jpGameDate.create("Release Date (JP)");
		lVGM.create("File Info");
			vgmCreator.create("Creator");
			vgmNotes.create("Notes/Comments");
		reflow(80);
	}
	void reflow(const uint32_t &wl=80) {
		append(banner,{~0,0},4);
		hl0.setAlignment(0.0); hl1.setAlignment(1.0);
		hl1.append(spl,{wl,0},8); hl1.append(lblEn,{~0,0}); hl1.append(lblJp,{~0,0});
		lFunc.appendIt(vlFunc);
			vlFunc.append(btnGD3Rem,{~0,0});
			vlFunc.append(btnGD3Upd,{~0,0});
			vlFunc.append(btnGD3Clr,{~0,0});
		lTrack.appendIt(vlTrack);
			trTitle.setLabelWidth(wl);
			trAuthor.setLabelWidth(wl);
			vlTrack.append(trTitle, {~0,0},2);
			vlTrack.append(trAuthor, {~0,0});
		lGame.appendIt(vlGame);
			gameTitle.setLabelWidth(wl);
			gameSys.setLabelWidth(wl);
			gameDate.setLabelWidth(wl); gameDate.append(spd,{~0,0},2);
			vlGame.append(gameTitle, {~0,0},2);
			vlGame.append(gameSys, {~0,0},2);
			vlGame.append(gameDate, {~0,0});
		lVGM.appendIt(vlVGM);
			vlVGM.append(vgmCreator,{~0,0},4);
			vlVGM.append(vgmNotes,{~0,128});
		vl1.append(hl1,{~0,0});
		vl1.append(lTrack,{~0,0},4);
		vl1.append(lGame,{~0,0});
		hl0.append(lFunc,{96,0},4);
		hl0.append(vl1,{~0,~0},4);
		hl0.append(lVGM,{128,0});
		append(hl0,{~0,0});
		append(sp,{~0,~0});
	}
};

#endif