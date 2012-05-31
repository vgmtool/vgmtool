#include "vgmtool.hpp"

void AppWin::initConfig() {
	basePath = userpath();
	#if !defined(PHOENIX_WINDOWS)
	basePath.append(".config/");
	#endif
	basePath.append("vgmtool/");
	mkdir(basePath);
	cfg.load((string){basePath, "settings.cfg"});
	cfg.save((string){basePath, "settings.cfg"});
	//print("Loaded: ", basePath, "settings.cfg\n");
	//print("geoMap: ",cfg.geoMap,"\n");
	//print("pathMap: ",cfg.pathMap,"\n");
}
void AppWin::initMenu() {
	mFile.setText("File");
	mFile_Load.setText("Open...");
	mFile_Quit.setText("Quit");
	mHelp.setText("Help");
	mHelp_About.setText("About...");
	append(mFile);
		mFile.append(mFile_Load);
		mFile.append(msFile);
		mFile.append(mFile_Quit);
	append(mHelp);
		mHelp.append(mHelp_About);
	setMenuVisible();
}
void AppWin::loadFile(const string &path) {
	if (path.length()) {
		//MessageWindow::information(*this, {"TODO: load ",path});
		string ext = extension(path);
		if (ext=="vgm") loadFileVGM(path);
		else if (ext=="vgz") loadFileVGM(path);
		//if (ext=="it") loadFileIT(path);
		//else if (ext=="s3m") loadFileS3M(path);
		//else if (ext=="xm") loadFileXM(path);
		//else if (ext=="mod") loadFileMOD(path);
		else MessageWindow::warning(*this, {"Couldn't load as VGM ",path});
	}
}
void AppWin::loadFileVGM(const string& path) {
	MessageWindow::information(*this, {"TODO: load as vgm ",path});
	cfg.pathFile = dir(path);
	//if (wInfo.open(path)) {
	//	wInfo.setBaseGeometry(cfg.geoInfo, true);
	//	wInfo.setVisible();
	//}
	//else MessageWindow::warning(*this, {"Couldn't load as IT ",path});
}
void AppWin::reflow() {
	appendToWin(banner, {~0,0});
	//layMain.setMargin(4);
	// TABBED LAYOUT
	hlSw.setAlignment(0.0);
	//hlSw.append(flSw,{~0,~0});
	//flSw.append(vpHdr,{~0,~0});
	//flSw.append(vpOpt,{~0,~0});
	//layMain.append(hlSw,{96,~0},4);
	//appendToWin(layMain);
	hlSw.setMargin(4); appendToWin(hlSw);
	hlSw.append(lvSw,{96,~0},4);
	append(vpHdr);
	append(vpOpt);
	append(vpData);
	append(vpTag);
	append(vpProc);
	append(vpMisc);
};
void AppWin::appendSw(VGMPanel &p) {
	p.setVisible(true);
	if (p.visible()) {
		//p.synchronizeLayout();
		//hlSw.append(p,{~0,~0});
		hlSw.synchronizeLayout();
		setStatusText((string){"",p.name});
	}
	else setStatusText((string){"Unable to switch to ",p.name});
}
void AppWin::reflowSw(unsigned n) {
	vpHdr.setVisible(false);
	vpOpt.setVisible(false);
	vpData.setVisible(false);
	vpTag.setVisible(false);
	vpProc.setVisible(false);
	vpMisc.setVisible(false);
	//hlSw.remove(vpHdr);
	//hlSw.remove(vpOpt);
	if (n>=0&&n<vpList.size()) {
		//uintptr_t p = vpList[n];
		//MessageWindow::information(*this, {"TODO: switch to ",n," (",((uintptr_t)vpList[n]),")"});
		//setStatusText((string){"TODO: switch to ",n," (",(uintptr_t)(vpList[n]),")"});
		appendSw(*vpList[n]);
	}
	else {
		MessageWindow::information(*this, {"TODO: add panel ",n});
		//vpHdr.setVisible(true);
	}
}
void AppWin::create() {
	setVisible(true);
}
AppWin::AppWin(int argc, char** argv) {
	initConfig();
	// MAIN
	init("VGMTool 3a0");
	setBaseGeometry(cfg.geoMain, false);
	// MENU STUFF
	initMenu();
	// "STATUSBAR"
	setStatusText({title," by Maxim, NeoLogiX, ValleyBell"});
	setStatusVisible();
	// MAIN PANEL
	banner.create("vgmtool-hdr.png",0xff102080);
	//lvSw.setHeaderText("VGMTool"); lvSw.setHeaderVisible();
	lvSw.append("Header"); vpList.append((VGMPanel*)(&vpHdr));
	lvSw.append("Optimize"); vpList.append((VGMPanel*)(&vpOpt));
	lvSw.append("Analyze"); vpList.append((VGMPanel*)(&vpData));
	lvSw.append("GD3"); vpList.append((VGMPanel*)(&vpTag));
	lvSw.append("Process"); vpList.append((VGMPanel*)(&vpProc));
	lvSw.append("Miscellaneous"); vpList.append((VGMPanel*)(&vpMisc));
	reflow();
	// PROC
	lvSw.onChange = [&]() { reflowSw(lvSw.selection()); };
	lvSw.setSelection(0); reflowSw(lvSw.selection());
	mHelp_About.onActivate = [&]() { MessageWindow::information(*this, {title,"\n(c)2012 VGMTool Group"}); };
	onClose = mFile_Quit.onActivate = [&]() {
		cfg.geoMain = geometry().text();
		//cfg.geoInfo = wInfo.geometry().text();
		cfg.save((string){basePath, "settings.cfg"});
		OS::quit();
	};
}

int main(int argc, char** argv) {
	AppWin app(argc, argv);
	app.create();
	OS::main();
	return 0;
}