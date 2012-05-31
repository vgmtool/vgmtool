#ifndef __N_CANVAS__
#define __N_CANVAS__

#include <nall/platform.hpp>
#include <phoenix.hpp>

using namespace nall;
using namespace phoenix;

struct NCanvas : Canvas {
	inline void reset(uint32_t col=0x00000000) {
		Size z = size();
		uint32_t *dp = data();
		uint32_t i, j; for (i=0; i<z.height; ++i)
			for (j=0; j<z.width; ++j) *dp++ = col;
	}
	inline uint32_t at(uint32_t x, uint32_t y) {
		Size z = size();
		if (x<z.width&&y<z.height) {
			uint32_t* dp = data();
			return *(dp+y*z.width+x);
		}
		else return 0;
	}
	inline uint32_t at(const Position &p) { return at(p.x, p.y); }
	inline void plot(const uint32_t &x, const uint32_t &y, const uint32_t &col, bool precalc=false) {
		Size z = size();
		if (x<z.width&&y<z.height) {
			uint32_t* cp = data();
			uint32_t* dp = cp+y*z.width+x;
			if (col<0x01000000&&(*dp)<0x01000000) *dp = 0xff000000;	// transparent becomes black
			else {
				uint32_t c = !precalc?col:(uint32_t)((col&0xffffff)*(double(col>>24)/255)), _c = c;
				/*if (precalc) ;// print("[",x,",",y,"]=",(*dp),"+",_c,"\n");
				else {
					if ((*dp)>0) {	// TODO: alpha blend
						//_c = ((*dp)>>1)+
					}
				}*/
				*dp = _c;
			}
		}
	}
	inline void plot(const Position &p, const uint32_t &col, bool precalc=false) {plot(p.x, p.y, col, precalc);}
};

#endif
