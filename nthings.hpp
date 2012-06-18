#ifndef __N_THINGS__
#define __N_THINGS__

#include <nall/platform.hpp>
#include <phoenix.hpp>

#include "ncanvas.hpp"

using namespace nall;
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
		image im;//(0, 32, 0xff000000,0xff0000,0xff00,0xff);
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

/*struct ListLayout : HorizontalLayout {
	ListView tabs;
	VerticalLayout panel;
	void addTab(string n, Layout &l) {
		tabs.append(n);
		panel.append(l);
	}
};*/

/**** fieldset ****/
struct FrameBorderTop : HorizontalLayout {
	Label label;
	CheckBox cblabel;
	NCanvas _ctl, _ctr, _cbl, _cbr;
	VerticalLayout _cl, _cl2, _cr, _cr2;
	Widget pxl, pxl2, pxr, pxr2;
	bool hasBorder, isCheckbox;
	void setText(const string &l) { label.setText(l); cblabel.setText(l); }
	void create(const string &s="Label", uint32_t col=0xc0c0c0c0, const bool &b=true, const bool &cb=false) {
		setText(s);
		_ctl.setSize({3,2}); _ctl.reset(col); _ctl.line({0,1},{2,1},0xc0ffffff);// _ctl.plot({0,0}, 0x20ffffff);
		_cbl.setSize({1,3}); _cbl.reset(col);
		_ctr.setSize({1024,2}); _ctr.reset(col); _ctr.line({0,1},{1023,1},0xc0ffffff);// _ctr.plot({2047,0}, 0x20ffffff);
		_cbr.setSize({1,3}); _cbr.reset(col);
		setBorderCheckbox(b,cb);
	}
	void setBorderCheckbox(const bool &b=true, const bool &cb=true) {
		hasBorder = b;
		isCheckbox = cb;
		reflow();
	}
	void setBorder(const bool &b=true) {hasBorder = b; reflow();}
	void setCheckbox(const bool &b=true) {isCheckbox = b; reflow();}
	void reflow() {
		_cl.setAlignment(0.0); _cl2.setAlignment(0.0);
		_cr.setAlignment(1.0); _cr2.setAlignment(1.0);
		_cl.append(pxl, {1,1}); _cl.append(_cbl, {1,3});
		_cl2.append(_ctl, {3,2}); _cl2.append(pxl2, {3,3});
		_cr.append(_ctr, {~0,2}); _cr.append(pxr,{~0,3});
		_cr2.append(pxr2,{1,1}); _cr2.append(_cbr, {1,3});
		setAlignment(1.0);
		remove(_cl); remove(_cl2); remove(label); remove(cblabel); remove(_cr); remove(_cr2);
		if (hasBorder) {
			append(_cl, {1,4},0);
			append(_cl2,{3,4},2);
		}
		if (isCheckbox) append(cblabel, {0,0}, 2);
		else append(label, {0,0}, 2);
		append(_cr, {~0,4});
		append(_cr2,{1,4});
		_cr.setVisible(hasBorder); _ctr.setVisible(hasBorder); pxr.setVisible(hasBorder);
		_cr2.setVisible(hasBorder); _cbr.setVisible(hasBorder); pxr2.setVisible(hasBorder);
	}
};
struct FrameBorderBottom : HorizontalLayout {
	NCanvas _c;
	Widget pxl, pxr;
	void create(uint32_t col=0xc0c0c0c0) {
		_c.setSize({1024,1}); _c.reset(col);
		reflow();
	}
	void reflow() {
		setAlignment(0.0);
		append(pxl,{1,1});
		append(_c,{~0,1});
		append(pxr,{1,1});
	}
	void setVisible(const bool &b=true) {
		HorizontalLayout::setVisible(b);
		pxl.setVisible(b);
		_c.setVisible(b);
		pxr.setVisible(b);
	}
};
struct Fieldset : VerticalLayout {
	NCanvas _cl, _cr;//, _cz;
	FrameBorderTop _lt;
	FrameBorderBottom _lb;
	HorizontalLayout _lm;
	VerticalLayout _lv;
	Widget _pt, _pb;
	bool hasBorder, isCheckbox;
	void setText(const string &l) { _lt.setText(l); }
	void create(const string &s="Label", const bool &b=true, const bool &cb=false) {
		uint32_t col = 0xc0c0c0c0;
		_lt.create(s,col,b,cb);
		_lb.create(col);
		uint32_t *dp;
		unsigned i, j;
		_cl.setSize({1, 1024}); _cl.reset(col);
		_cr.setSize({1, 1024}); _cr.reset(col);
		//_cz.setSize({2048, 1}); _cz.reset(col);
		_lv.setAlignment(0.5);
		hasBorder = b; isCheckbox = cb; reflow();
		//setBorderCheckbox(b,cb);
	}
	void setBorderCheckbox(const bool &b=true, const bool &cb=true) {
		hasBorder = b; isCheckbox = cb;
		_lt.setBorderCheckbox(b,cb);
		reflow();
	}
	void setBorder(const bool &b=true) {
		hasBorder = b;
		_lt.setBorder(b);
		reflow();
	}
	void setCheckbox(const bool &b=true) {
		isCheckbox = b;
		_lt.setCheckbox(b);
		reflow();
	}
	void reflow() {
		remove(_lt); remove(_lm); remove(_lb);// remove(_cz);
		_lm.remove(_cl); _lm.remove(_lv); _lm.remove(_cr);
		//if (hasBorder) {
			_lm.append(_cl, {1,~0}, 3);
			_lm.append(_lv, {~0,~0}, 3);
			_lm.append(_cr, {1,~0});
		//}
		//else _lm.append(_lv,{~0,~0});
		_cl.setVisible(hasBorder); _cr.setVisible(hasBorder);
		append(_lt, {~0,0});
		append(_lm, {~0,~0});
		append(_lb, {~0,1}); _lb.setVisible(hasBorder);
		//if (hasBorder) append(_lb, {~0,1});
	}
	void appendIt(Sizable& s) { appendIt(s,{~0,~0},0); }
	void appendIt(Sizable& s, const Size& z) { appendIt(s, z, 0); }
	void appendIt(Sizable& s, const Size& z, const int& p) { _lv.append(s, z, p); _lv.append(_pb, {~0, 3}); }
};

struct LabeledFieldV : VerticalLayout {
	Label label;
	uint32_t labelHeight;
	void setLabel(const string &l) {label.setText(l);}
	void setLabelHeight(const uint32_t &w=0) {labelHeight = w; reflow();}
	virtual void reflow() = 0;
};
struct LabeledField : HorizontalLayout {
	Label label;
	uint32_t labelWidth;
	void setLabel(const string &l) {label.setText(l);}
	void setLabelWidth(const uint32_t &w=0) {labelWidth = w; reflow();}
	virtual void reflow() = 0;
};
struct ComboField : LabeledField {
	ComboBox field;
	void appendValue(const string &l) { field.append(l); }
	void create(const string &s="Label", const string &v="") {
		setLabel(s);
		setLabelWidth(0);
		//setAlignment(0.5);
		//field.setWordWrap(false);
	}
	void appendIt(const string &v) {field.append(v);}
	void reset() {field.reset();}
	unsigned selection() {return field.selection();}
	void reflow() {
		remove(label); remove(field);
		append(label, {labelWidth, 0}, 2);
		append(field, {~0, 0});
	}
};
struct TextboxField : LabeledFieldV {
	TextEdit field;
	void setText(const string &l) { setLabel(l); setValue(l); }
	void setValue(const string &l) { field.setText(l); }
	string text() { return field.text(); }
	void create(const string &s="Label", const string &v="") {
		setLabel(s);
		setValue(v);
		setLabelHeight(0);
	}
	void reflow() {
		remove(label); remove(field);
		append(label, {~0, labelHeight});
		append(field, {~0, ~0});
	}
};
struct TextField : LabeledField {
	LineEdit field;
	void setText(const string &l) { setLabel(l); setValue(l); }
	void setValue(const string &l) { field.setText(l); }
	string text() { return field.text(); }
	void create(const string &s="Label", const string &v="") {
		setLabel(s);
		setValue(v);
		setLabelWidth(0);
	}
	void reflow() {
		remove(label); remove(field);
		append(label, {labelWidth, 0}, 2);
		append(field, {~0, 0});
	}
};

struct FileEntry : HorizontalLayout {
	Label label;
	LineEdit input;
	Button bBrowse;
	Button bClear;
	string filter;
	string basePath;
	function<void (const string&)> cb;
	FileEntry() : HorizontalLayout() {
		basePath = "";
		// layout
		init("Label");
		reflow();
		// proc
		cb = dummy;
		bBrowse.onActivate = [this]() {
			//MessageWindow::information(Window::None, "TODO: browse for file");
			string _lastdir = dir(getPath())||basePath;
			string _file;
			_file = DialogWindow::fileOpen(*window(), _lastdir, filter);
			if (_file.length()) {
				setPath(_file);
				cb(getPath());
			}
			//cb(getPath());	// uncomment to run on cancelled browse
		};
		bClear.onActivate = [this]() {
			input.setText("");
			cb("");
		};
	}
	void init(const string &l, const string &b="Browse...", const string &c="Clear") {
		setLabel(l);
		bBrowse.setText(b);
		bClear.setText(c);
	}
	void reflow() {
		input.setEditable(false);
		append(label, {0, 0}, 4);
		append(input, {~0, 0}, 4);
		append(bClear, {0, 0}, 2);
		append(bBrowse, {0, 0});
	}
	void setLabel(const string &l) { label.setText(l); }
	void setPath(const string &p) { input.setText(p.length() > 0 ? p : " "); }
	string getPath() { return input.text(); }
	void setBasePath(const string &p="") { basePath = p; }
	void setFilter(const string &filt) { filter = filt; }
	void setOnLoad(const function<void (const string&)>& _cb) { cb = _cb; }
	static void dummy(const string&) {}
};

struct NWin : public Window {
	string title;
	Geometry G;
	VerticalLayout layout;
	NWin() : Window() { init("Window"); }
	NWin(const string& t) : Window() { init(t); }
	void init(const string& t="Window") {
		retitle(t);
		//layout.setMargin(4);
		append(layout);
	}
	void retitle(const string& t) { title = t; setTitle(t); }
	void setBaseGeometry(const Geometry& g, bool canResize=true) { G = g; setGeometry(g); setResizable(canResize); }
	void appendToWin(Sizable& s) { appendToWin(s, {~0, ~0}, 0); }
	void appendToWin(Sizable& s, const Size& z) { appendToWin(s, z, 0); }
	void appendToWin(Sizable& s, const Size& z, const int& p) { layout.append(s, z, p); }
};



#endif
