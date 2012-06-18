#ifndef __VGM_WINAPP_H__
#define __VGM_WINAPP_H__

#include <nall/platform.hpp>
using namespace nall;

#include <phoenix.hpp>
using namespace phoenix;

#include "../vgm.objs.hpp"
#include "../vgm.cfg.hpp"

/**** VGM panels ****/
#include "vgm.panel.header.hpp"
#include "vgm.panel.opt.hpp"
#include "vgm.panel.data.hpp"
#include "vgm.panel.tag.hpp"
#include "vgm.panel.proc.hpp"
#include "vgm.panel.misc.hpp"

/**** App window ****/
struct AppWin : public NWin {
	Config cfg;
	string basePath;
	// MENU
	Menu mFile, mTools, mHelp;
	Separator msFile;
	Item mFile_Quit, mHelp_About;
	Item mFile_Load, mTools_OptMidi;
	// WINDOW
	Banner banner;
	VerticalLayout layMain;
	// "TAB" VIEW
	HorizontalLayout hlSw;
	//VerticalLayout flSw;
	ListView lvSw;
	vector<VGMPanel*> vpList;
	VPHeader vpHdr;
	VPOpt vpOpt;
	VPData vpData;
	VPTag vpTag;
	VPProc vpProc;
	VPMisc vpMisc;
	// PROC
	AppWin(int argc, char** argv);
	void create();
	void reflow();
	void initConfig();
	void initMenu();
	void appendSw(VGMPanel &p);
	void reflowSw(unsigned n);
	void loadFile(const string& path);
	void loadFileVGM(const string& path);
	//void loadFileS3M(const string& path);
};

#endif