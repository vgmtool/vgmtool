#ifndef __N_MIDI_PROC_H__
#define __N_MIDI_PROC_H__

#include <nall/platform.hpp>

using namespace nall;

namespace MIDI {
	uint32_t readLength(file &f) {
		uint32_t ret = 0;
		uint8_t c;
		do {
			c = f.read();
			ret = (ret<<7)+(c&0x7f);
		} while (c & 0x80);
		return ret;
	}
	void writeLength(file &f, uint32_t len) {
		/*
		uint32_t buf = len&0x7f;
		while ((len>>=7)>0) {
			buf <<=8;
			buf |= 0x80;
			buf += len&0x7f;
		}
		while (1) {
			f.write(buf&0xff);
			if (buf&0x80) buf >>= 8;
			else break;
		}
		*/
	}
}

#endif