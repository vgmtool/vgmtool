#ifndef __N_MIDI_H__
#define __N_MIDI_H__

#include <nall/platform.hpp>
#include <nall/file.hpp>

using namespace nall;

/****
GM1 - channel 10 only can play drum kit
GM2 - channel 10 & 11 can play drum kit
XG - every channel can play drum kit if bank select MSB = 0x7F
****/

#include "midi.proc.hpp"
#include "midi.cc.hpp"
#include "midi.prog.hpp"

namespace MIDI {
	enum Format : uint16_t {
		SMF0 = 0,	// single-track
		SMF1,	// multi-track, single-song
		SMF2	// multi-track, multi-song
	};
	enum Event : uint8_t {
		NoteOff = 0x80,
		NoteOn = 0x90,
		Aftertouch = 0xA0,
		ControlChange = 0xB0,
		PatchChange = 0xC0,
		ChannelPressure = 0xD0,
		PitchWheel = 0xE0,
		SysEx = 0xF0,
		Meta = 0xFF
	};
	const string Message[] = {
		"Note Off",
		"Note On",
		"Key Pressure",
		"Control Change",
		"Program Change",
		"Channel Pressure",
		"Pitch Wheel",
		"System Exclusive",
		"Meta"
	};
	struct ChunkHeader {
		char id[4];
		uint32_t length;	// big-endian
	};
	struct MThd {
		ChunkHeader header;	// id=MThd, length=6
		Format format;	// big-endian
		uint16_t tracks;	// big-endian
		uint16_t ticks;	// big-endian
		MThd() {
			header.id = {'M','T','h','d'};
			header.length = 6;
			format = SMF0;
			tracks = 0;
			ticks = 0;
		}
	};
	struct MTrk {
		ChunkHeader header;	// id=MTrk, length=?
		vector<unsigned char> data;
		MTrk() {
			header.id = {'M','T','r','k'};
			header.length = 0;
		}
	};
	struct SMF {
		MThd header;
		vector<MTrk> tracks;
	};
}

#endif