#ifndef __VGM_OBJ_H__
#define __VGM_OBJ_H__

#include <nall/platform.hpp>
using namespace nall;

#include <phoenix.hpp>
using namespace phoenix;

/**** Banner ****/
struct Banner : HorizontalLayout {
	NCanvas hdr;
	NCanvas str;
	unsigned bgc;
	string bgi;
	Banner() : bgc(0xff102080) {
		unsigned int h = 48, w = 320;
		hdr.setSize({w,h});
		hdr.reset(bgc);
		reflow(w,h);
	}
	void reflow(unsigned w, unsigned h) {
		str.setSize({1024,h});
		str.reset(bgc);
		str.update();
		hdr.update();
		remove(hdr); remove(str);
		append(hdr, {w,h});
		append(str, {~0,~0});
		//print("reflow banner ",w,"*",h,"\n");
		synchronizeLayout();
	}
	void load(const string &fn) {
		unsigned int h = 48, w = 320;
		bgi = fn;
		image im(0, 32, 0xff000000,0xff0000,0xff00,0xff);
		if (im.load((string){"res/",bgi})) {
			hdr.setImage(im);
			h = im.height; w = im.width;
			//print(w,"*",h,"\n");
			//MessageWindow::information(*window(),(string){w,"x",h});
		}
		else {
			hdr.reset(bgc);
			print("Couldn't load ",bgi,"\n");
			//MessageWindow::information(*window(),(string){"Couldn't load ",bgi});
		}
		reflow(w,h);
	}
	void create(const string &fn, const unsigned c=0xff102080) {
		bgc = c;
		load(fn);
	}
};

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