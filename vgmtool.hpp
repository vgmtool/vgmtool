#include <nall/platform.hpp>
using namespace nall;

#include <phoenix.hpp>
using namespace phoenix;

#include "nthings.hpp"
#include "vgm.cfg.hpp"
#include "formats/vgm.hpp"

/**** VGM panels ****/
#include "vgm.objs.hpp"
#include "vgm.panel.header.hpp"
#include "vgm.panel.opt.hpp"
#include "vgm.panel.data.hpp"
#include "vgm.panel.tag.hpp"
#include "vgm.panel.proc.hpp"
#include "vgm.panel.misc.hpp"

/**** App ****/
struct AppWin : public NWin {
	Config cfg;
	string basePath;
	// MENU
	Menu mFile, mHelp;
	Separator msFile;
	Item mFile_Load, mFile_Quit, mHelp_About;
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
