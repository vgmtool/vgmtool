#include <nall/platform.hpp>
using namespace nall;

#include <phoenix.hpp>
using namespace phoenix;

struct Config : configuration {
	string geoMain;
	string pathFile;
	//string geoInfo;
	Config() {
		attach(geoMain="+128,+128,640,480", "geoMain");
		attach(pathFile="", "pathFile");
		//attach(geoInfo="+512,+128,640,480", "geoInfo");
	}
};
